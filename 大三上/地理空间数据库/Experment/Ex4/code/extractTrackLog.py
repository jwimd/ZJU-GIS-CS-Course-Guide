# -*- coding: utf-8 -*-
"""
Created on Sat Dec 20 10:21:52 2014
Modified on Mon May 4 18:23:11 2015
Modified on Mom Mar 14 21:43:52 2016

Modified on Sat Mar 14 23:55:00 2020 by dhr
@author: SongLei

"""

from bs4 import BeautifulSoup
import time
import urllib.request
from http import cookiejar
import datetime
##Global variables go here...
delimiter = u'#' # define the delimiter.

##Functions
def trySentRequest(url, iterate):
    print('cookies setting...')
    initial_url = 'https://zh.flightaware.com/account/locale_switch.rvt?locale=en_US'
    cookie = cookiejar.CookieJar()
    handler=urllib.request.HTTPCookieProcessor(cookie)
    opener = urllib.request.build_opener(handler)
    response = opener.open(initial_url)
    print('cookies setting complete...')
    
    user_agent = u'Mozilla/5.0 (Windows NT 6.3; WOW64; en-GB; Trident/7.0; rv:11.0) like Gecko'
    headers    = {'Accept-Language' : 'en-gb,en;q=0.5', 'User-Agent' : user_agent}
    data       = None
    request    = urllib.request.Request(url, data, headers)

    try:
        printcontent = '%d: sent request to ' + url
        print(printcontent %(iterate))
        contents = opener.open(request).read()
    except:
        print('requesting fail...')
        if iterate > 5:
            print("quite requseting...")
            return False
        print('sleep %d sec...'%(10))
        time.sleep(10)
        return trySentRequest(url, iterate + 1)
    else:
        if contents:
            print('requesting success...')
            return contents
        else:
            print("content is empty...")
            if iterate > 5:
                return False
                
            print('sleep %d sec...'%(10))
            time.sleep(10)
            
            return trySentRequest(url, iterate + 1)


def extractTracklog(url, outfilePath):
    outfile  = open(outfilePath, 'wb+')
    soup     = ""
    contents = trySentRequest(url, 1)
    soup     = BeautifulSoup(contents,"lxml")
    
    ##extract
    tracklogTable = soup.find('table', id = 'tracklogTable')
    thead         = tracklogTable.find('thead')
    trs_in_thead  = len(thead.find_all('tr'))
    trs           = tracklogTable.find_all('tr', class_ = lambda x : x == 'smallrow1' or x == 'smallrow2')

    temp_url    = url[url.find("flight/"):].split("/")
    temp_url[3] = temp_url[3][0:4] + '-' + temp_url[3][4:6] + '-' + temp_url[3][6:8]
    day_dict    = {"Mon" : 1, "Tue": 2, "Wed" : 3, "Thu" : 4, "Fri" : 5, "Sat" : 6, "Sun" : 7}
    day_st      = ""

    log_num = 0
    for i in range(trs_in_thead, len(trs)):
        temp = {}
        tr   = trs[i]
        
        classes = tr.get('class', [])
        if len(classes) > 1:
            continue

        tds  = tr.find_all('td')
        if len(tds) != 9:
            continue
        
        temp['Code'] = temp_url[1]

        tds[0] = tds[0].contents[0]   # date
        tds[1] = tds[1].contents[0]   # latitude
        tds[2] = tds[2].contents[0]   # longitude
        tds[3] = tds[3].contents[0]   # direction
        tds[6] = tds[6].contents[0]   # height (foot)
    
        if(tds[0] and tds[0].string):
            arr_tds = tds[0].string.split()
            if day_st == "":
                day_st = arr_tds[0]
            day_diff = day_dict[arr_tds[0]] - day_dict[day_st]
            time1 = datetime.datetime.strptime(temp_url[3] + " " + arr_tds[1], '%Y-%m-%d %H:%M:%S')
            if time1.hour != 12 and arr_tds[2] == 'PM':
                time1 = time1 + datetime.timedelta(hours = 24 * day_diff + 12)
            elif time1.hour == 12 and arr_tds[2] == 'AM':
                time1 = time1 + datetime.timedelta(hours = 24 * day_diff - 12)
            else:
                time1 = time1 + datetime.timedelta(hours = 24 * day_diff)
            temp['Date'] = datetime.datetime.strftime(time1,'%Y-%m-%d %H:%M:%S')
        else:
            temp['Date'] = u'null'
            
        if(tds[1] and tds[1].string):
            temp['Latitude'] = tds[1].string
        else:
            temp['Latitude'] = u'null'
            
        if(tds[2] and tds[2].string):
            temp['Longitude'] = float(tds[2].string)
            if temp['Longitude'] < 0:
                temp['Longitude'] += 360
            temp['Longitude'] = str(temp['Longitude'])
        else:
            temp['Longitude'] = u'null'
        
        if(tds[3] and tds[3].string):
            temp['Direction'] = tds[3].string.split()[1]
        else:
            temp['Direction'] = u'null'

        if(tds[6] and tds[6].string):
            temp['Height'] = tds[6].string.replace(',', '')
        else:
            temp['Height'] = u'null'
            
        res  = temp['Code'] + delimiter
        res += temp['Date'] + delimiter
        res += temp['Latitude'] + delimiter
        res += temp['Longitude'] + delimiter
        res += temp['Direction'] + delimiter
        res += temp['Height'] + '\n'

        log_num += 1
        #print(res)
        outfile.write(res.encode('utf-8'))
    outfile.close()
    print('successfully extracted ' + str(log_num) + ' rows in ' + outfilePath)
    


## main scripts
url = 'https://zh.flightaware.com/live/flight/CHH7178/history/20200306/1050Z/ZSHC/ZBAA/tracklog'
extractTracklog(url, "./Tracklog.txt")



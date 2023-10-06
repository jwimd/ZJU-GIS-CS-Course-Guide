#coding:utf-8
import json, re, os, codecs;
from IPython.core.display import display_html, HTML, display_javascript, Javascript


class properties:
    def __init__(self, popupContent,num):
        self.popupContent = popupContent
        self.num=num
    def to_JSON(self):
        return json.dumps(self, default=lambda o: o.__dict__)


class Feature:
    def __init__(self, geometry, popupContent,id,index,num=None):
        self.type = "Feature"
        self.geometry = geometry
        self.properties = properties(popupContent,num)
        self.id = id
        self.index=index
    def to_JSON(self):
        return json.dumps(self, default=lambda o: o.__dict__)


class FeatureCollection:
    type = "FeatureCollection"
    def __init__(self):
        self.features = [] 
        
    def addFeature(self, feature):
        self.features.append(feature)
        
    def dump(self):
        if len(self.features) > 1:
            return json.dumps(self,default=lambda o: o.__dict__,ensure_ascii=False)
         
        else:
            return json.dumps(self.features[0], default=lambda o: o.__dict__,ensure_ascii=False)


def toHTML(divId,zoom,baseMapType,showToolTipLayer,redraw=False):
    # HTML
    html = ""
    if not redraw:
        html ="<div id='" + divId 
        html += """' style="width: 1000px; height: 400px"></div>"""
    html += """
    <link rel="stylesheet" href="tools/leaflet.css">
    <link rel="stylesheet" href="tools/map.css">
        <script src="tools/leaflet.js" type="text/javascript"></script>
        <script src="jsonData/""" +divId + """.json" type="text/javascript"></script>
        <script src="tools/wkx.js" type="text/javascript"></script>
        <script src="tools/geom_display.js" type="text/javascript"></script>
        <script src="tools/d3.min.js" type="text/javascript"></script>
         <script type="text/javascript"> 
        """
    html += "(new GeoMap('" + divId  + "' ," + str(zoom) +","+str(baseMapType)+","+str(showToolTipLayer)+")).display();</script>";
    html = html.format('')
    # Display in IPython notebook
    #print html
    display_html(HTML(data=html))


    
def addFeature(featureCollection, result,type,index=0):

    try:
        if type=="choroplethMap":
            if not result[0].has_key('value'):
                raise Exception('无对应的value列，results的关系类型为(gid, name, geom, value)')
            elif not result[0].has_key('geom'):
                raise Exception('无对应的geom列，results的关系类型为(gid, name, geom, value)')
            elif not result[0].has_key('name'):
                raise Exception('无对应的name列，results的关系类型为(gid, name, geom, value)')
            elif not result[0].has_key('gid'):
                raise Exception('无对应的gid列，results的关系类型为(gid, name, geom, value)')
            else:
                for row in result:
                    featureCollection.addFeature(Feature(row['geom'], row['name'],row['gid'],index,num=row['value']))
        elif type=="":
            if not result[0].has_key('gid'):
                raise Exception('无对应的gid列，results的关系类型为(gid, name, geom, value)')
            elif not result[0].has_key('geom'):
                raise Exception('无对应的geom列，results的关系类型为(gid, name, geom, value)')
            elif not result[0].has_key('name'):
                raise Exception('无对应的name列，results的关系类型为(gid, name, geom, value)')
            else:
                for row in result:
                    featureCollection.addFeature(Feature(row['geom'], row['name'],row['gid'],index))
                    # print json.dumps(row['name'], ensure_ascii = False)
        elif type=="heatMap":
            if not result[0].has_key('gid'):
                raise Exception('无对应的gid列，results的关系类型为(gid, name, geom)或者(gid, name, geom, value)')
            elif not result[0].has_key('geom'):
                raise Exception('无对应的geom列，results的关系类型为(gid, name, geom)或者(gid, name, geom, value)')
            elif not result[0].has_key('name'):
                raise Exception('无对应的name列，results的关系类型为(gid, name, geom)或者(gid, name, geom, value)')
            else:
                if result[0].has_key('value'):
                    for row in result:
                        featureCollection.addFeature(Feature(row['geom'], row['name'],row['gid'],index,num=row['value']))
                else:
                    for row in result:
                        featureCollection.addFeature(Feature(row['geom'], row['name'],row['gid'],index))

                
    except Exception as e:
        print(e)
        return False
    return True

    


def display(results, divId, zoom, baseMapType=0, showToolTipLayer=0):
    writeDataToFile(results,divId,type="");
    toHTML(divId,zoom,baseMapType,showToolTipLayer);
	
def writeDataToFile(results,divId,type):
    featureCollection = FeatureCollection()
    if type=="heatMap" or type=="choroplethMap":
        addFeature(featureCollection, results,type)
    else:
        for index,result in enumerate(results):
            addFeature(featureCollection, result,type,index)
    if len(featureCollection.features) > 0:
        if os.path.exists('jsonData') == False:
            os.makedirs('jsonData')
        # with open("jsonData/" + divId + ".json", 'w') as fd:
        with codecs.open("jsonData/" + divId + ".json", 'w', 'utf-8') as fd:
	        words = featureCollection.dump()
	        # print words
	        p = re.compile("'\[")
	        words = p.sub("[", words)
	        p = re.compile("]'")
	        words = p.sub("]", words)

	        fd.write("geometry = " + words)

def displayAll():
    toHTML("map1", 12,'',0,True)
    toHTML("map2", 12,'',0,True)
    toHTML("map3", 12,'',0,True)
    toHTML("map4", 13,'',0,True)
    toHTML("map5", 13,'',0,True)
    toHTML("map6", 13,'',0,True)
    toHTML("map7", 13,'',0,True)
    toHTML("map8", 13,'',0,True)
    toHTML("map9", 15,'',0,True)
    toHTML("map10", 15,'',0,True)
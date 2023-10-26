#include "print.h"
#include "sbi.h"

void puts(char *s) {
    while(*s!='\0')
    {
        uint64 char_code = *s;                        //获取字符编码
        sbi_ecall(0x1, 0x0, char_code, 0, 0, 0, 0, 0);//调用打印字符ecall
        s++;
    }

    return;
}

void puti(int x) {
    char s[int_max] = {0};//分配字符串空间
    int_to_str(x, s);
    puts(s);

    return;
}

void int_to_str(int num, char *str)
{
    int i = 0;   //指示填充str
    if (num < 0) //如果num为负数，将num变正
    {
        num = -num;
        str[i++] = '-';
    }
    //从低位到高位写入字符串
    do
    {
        str[i++] = num % 10 + code_0;
        num /= 10;                
    } while (num);               

    str[i] = '\0';

    int j = 0;
    if (str[0] == '-') //如果有负号，负号不用调整
    {
        j = 1; //从第二位开始调整
        ++i;   //由于有负号，所以交换的对称轴也要后移1位
    }
    //将字符串的数字部分倒转
    for (; j < i / 2; j++)
    {
        str[j] = str[j] + str[i - 1 - j];
        str[i - 1 - j] = str[j] - str[i - 1 - j];
        str[j] = str[j] - str[i - 1 - j];
    }

    return;
}
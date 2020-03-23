import http.client
import urllib,parser
import os
import random
import codecs

#中文需要转unicode，而且自带encode("unicode_escape")还tm不行
#https://blog.csdn.net/qq_26346457/article/details/78501249

#update Mar,23 2020 这个函数在这没用的
def to_unicode(string):
 
    ret = ''
    for v in string:
        ret = ret + hex(ord(v)).upper().replace('0X', '\\u')
 
    return ret


conn = http.client.HTTPSConnection("v1.hitokoto.cn")

if(random.randint(0,3)==0):
    conn.request("GET","/?c=k")
elif (random.randint(0,3)==1):
    conn.request("GET","/?c=d")
elif (random.randint(0,3)==2):
    conn.request("GET","/?c=i")
else:
    conn.request("GET","/?c=c")


text = conn.getresponse().read().decode("utf-8")

pos = text.find("hitokoto")
hitokoto = ""
for now in text[pos+12:len(text)]:
    if(now!='\n'):
        hitokoto+=now
    else:
        break

#codecs.open 以utf-8读写.txt https://www.cnblogs.com/buptldf/p/4805879.html

#一定要注意编码格式, 必须得utf-8编码才可以传输到CoolQ上


#python相对路径文件调用 https://www.jianshu.com/p/cd421014cfbb

module_path = os.path.dirname(__file__)
filename = module_path + './hitokoto.txt'
fo = codecs.open(filename, "w", encoding = "utf-8")

#fo = codecs.open("G:\\Github Repositories\\CoolQ_C++\\bot Rat\\src\\hitokoto.txt", "w", encoding = "utf-8")

fo.write(hitokoto[0:-2])
fo.write(" --- ")

"""

conn = http.client.HTTPSConnection("v1.hitokoto.cn")
conn.request("GET","/?encode=text")
text = conn.getresponse().read().decode("utf-8")

fo = codecs.open("G:\\Github Repositories\\CoolQ_C++\\bot Rat\\src\\hitokoto.txt", "w", encoding = "utf-8")

fo.write(text)

fo.close()
"""

#print(code_gbk)
#print(to_unicode(hitokoto[0:-2]),end=" --- ")
#print(to_unicode(hitokoto[0:-2]).encode('utf-8').decode('unicode_escape') ,end=" --- ")

pos = text.find("from")
author = ""
for now in text[pos+8:len(text)]:
    if(now!=','):
        author+=now
    else:
        break

fo.write(author[0:-1])
fo.close()
#print(to_unicode(author[0:-1]))
#print(author.encode("unicode_escape"))
#print("dysudyusdyusd")


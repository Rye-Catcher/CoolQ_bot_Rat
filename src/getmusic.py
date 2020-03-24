import http.client
import urllib,parser
from urllib.parse import quote
import os
import random
import string
import codecs
 
conn = http.client.HTTPSConnection("api.imjad.cn")


#https://blog.csdn.net/cc9200/article/details/79999741
#中文网址问题

module_path = os.path.dirname(__file__)
filename = module_path + './getmusic.txt'

fo = codecs.open(filename, "r", encoding = "utf-8")
song_name = fo.read()
fo.close()

url = '/cloudmusic/?type=search&search_type=1&s={}'.format(quote(song_name))
#print(url)

#conn.request("GET", "/?type=search&search_type=1&s=%E5%B0%8F%E5%B0%8F%E7%9A%84%E6%89%8B%E5%BF%83")

flag = 1

fo = codecs.open(filename, "w", encoding = "utf-8")

while(flag):
    
    url = '/cloudmusic/?type=search&search_type=1&s={}'.format(quote(song_name))
    conn.request("GET",url)
    text = conn.getresponse().read().decode("utf-8")

    #print(text)
 

    pos = text.find("\"id\":")


    if pos == -1:
        print("wtf")
        fo.write("Sorry we cannot find that song")
        fo.close()
        exit(0)
    else:
        pos2= text.find("\"pst\"")
        id_num = text[pos+5:pos2-1]
        print(id_num)

    url = '/cloudmusic/?type=song&id={}&br=128000'.format(id_num)

    conn.request("GET",url)
    text = conn.getresponse().read().decode("utf-8")


    pos= text.find("\"url\":")
    pos2= text.find("\"br\":")

    durl = text[pos+7:pos2-2]
    
    #print(durl[11:12])

    if(durl[11:12] == "8"):
        flag=0
        print(durl)
        fo.write(durl)
        fo.close()
 
    elif(flag>=20):
        flag=0
        print("nope")
        fo.write("Sorry we can only find this: ")
        fo.write(durl)
        fo.write("\nYou may need a proxy to set your IP in China to watch it")
        fo.close()

    else:
        flag+=1

    





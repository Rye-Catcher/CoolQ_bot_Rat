#pragma once
#include <iostream>
#include <cstdio>
#include <memory>
#include <cstdlib>
#include <string>
#include <Windows.h>

using namespace std;

namespace GetMusic{
    void getmusic(string src_path, string song_name){
        
        FILE *fp=NULL;
        char buf[1005];
        memset(buf,0,sizeof(buf));
        string command;
	    string output;

        //delete existing file 
        command="del \"" + src_path + "getmusic.txt\"";
        system(command.c_str());

        //make a new file and input the name
        command=src_path + "getmusic.txt";
        fp = fopen(command.c_str(), "w");
        fprintf(fp, "%s", song_name.c_str());
        fclose(fp);
        
        
        //call http client
        command= "python \"" + src_path + "getmusic.py\"";
        fp = _popen(command.c_str(), "r");
        _pclose(fp);
        
        return ;
    }
};
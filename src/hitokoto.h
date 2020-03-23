#pragma once
#include <iostream>
#include <cstdio>
#include <memory>
#include <cstdlib>
#include <string>
#include <Windows.h>

using namespace std;

namespace GetHitokoto{
	
        void httpget(string src_path){
		
                FILE *fp=NULL;
                char buf[1005];
                memset(buf,0,sizeof(buf));
                string command;
	        string output;

                //command="python ./hitokoto.py";	
                
                command= "python \"G:\\Github Repositories\\CoolQ_C++\\bot Rat\\src\\hitokoto.py\"";
                //command= "python \"" + src_path + "hitokoto.py\"";
								
                fp = _popen(command.c_str(), "r");
                while(fgets(buf, 1000, fp)!=0){
		    	output+=buf;
		    	memset(buf,0,sizeof(buf));
                }   
                _pclose(fp);
				
		/*		
		fp = fopen("G:\\Github Repositories\\CoolQ_C++\\bot Rat\\src\\hitokoto.txt", "r");
				
		fscanf(fp, "%s", buf);
		
                string output_text(buf);
				
                return output_text;
                */
               return ;
	}
};      
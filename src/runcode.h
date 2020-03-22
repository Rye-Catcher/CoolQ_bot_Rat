#pragma once
#include <iostream>
#include <cstdio>
#include <memory>
#include <cstdlib>
#include <string>
#include <Windows.h>

using namespace std;

/*
_popen insted of popen in Microsoft Compiler
https://stackoverflow.com/questions/38876218/execute-a-command-and-get-output-popen-and-pclose-undefined/38876219
*/

int file_id=5;

/*--------------------------------------------------------------*/
/*请编辑你要保存运行代码的路径 (路径名称中请使用\\)*/
/*PLease edit the path to save the code (remember to use \\)*/
string src_address="G:\\Github Repositories\\CoolQ_C++\\src\\";


namespace DelExisting{
    void del_existing_exe(){

        string command="del \"" + src_address + to_string(file_id) + ".exe\"";
        system(command.c_str());
        return ;
    }
}

namespace UnicodeToANSI{

    string UnicodeToANSI(const std::wstring & wstr){

        std::string ret;
        std::mbstate_t state = {};
        const wchar_t *src = wstr.data();
        size_t len = std::wcsrtombs(nullptr, &src, 0, &state);
        if (static_cast<size_t>(-1) != len) {
        std::unique_ptr< char [] > buff(new char[len + 1]);
        len = std::wcsrtombs(buff.get(), &src, len, &state);
        if (static_cast<size_t>(-1) != len) {
            ret.assign(buff.get(), len);
            }
        }
        return ret;
    };
};

namespace RunCpp{
    
    

    string run_code(string text_input){
        FILE *fp=NULL;
        string file_name=to_string(file_id)+".cpp";
        char address[1005];
        memset(address,0,sizeof(address));
        strcat(address, src_address.c_str());
        strcat(address, file_name.c_str());
        
        fp=fopen(address, "w");
        fprintf(fp,text_input.c_str());
        fclose(fp);

        //删除已经存在的.exe
        DelExisting::del_existing_exe();

        char buf[1005];
        string output,command;

        command="g++ \"" + src_address + to_string(file_id)+ ".cpp\" -o \"" + src_address + to_string(file_id) +".exe\"";
        fp = _popen(command.c_str(), "r");
        
        _pclose(fp);  

        command="if exist \"" + src_address + to_string(file_id) + ".exe\" echo Yes";
        fp = _popen(command.c_str(), "r");

        while(fgets(buf, 1000, fp)!=0){
		    output+=buf;
		    memset(buf,0,sizeof(buf));
        }
		_pclose(fp);
                
        if(output=="") return "看起来代码在编译中出了点小问题...";

        output.clear();
        command="\"" + src_address +to_string(file_id) + ".exe\"";

	    fp = _popen(command.c_str(), "r");    

        while(fgets(buf, 1000, fp)!=0){
		    output+=buf;
		    memset(buf,0,sizeof(buf));
        }   
        
        _pclose(fp);

        file_id++;

        return output;
    }


    string _main(string text_input){
        
        //int file_id=save_code(text_input);
        return run_code( text_input );

    }
};


namespace RunC{
    
   

    string run_code(string text_input){
        FILE *fp=NULL;
        string file_name=to_string(file_id)+".c";
        char address[1005];
        memset(address,0,sizeof(address));
        strcat(address, src_address.c_str());
        strcat(address, file_name.c_str());
        
        fp=fopen(address, "w");
        fprintf(fp,text_input.c_str());
        fclose(fp);

        //删除已经存在的 .exe
        DelExisting::del_existing_exe();

        char buf[1005];
        string output,command;

        command="gcc \"" + src_address + to_string(file_id)+ ".c\" -o \"" + src_address + to_string(file_id) +".exe\"";
        fp = _popen(command.c_str(), "r");
        
        _pclose(fp);

        command="if exist \"" + src_address + to_string(file_id) + ".exe\" echo Yes";
        fp = _popen(command.c_str(), "r");

        while(fgets(buf, 1000, fp)!=0){
		    output+=buf;
		    memset(buf,0,sizeof(buf));
        }
		_pclose(fp);
                
        if(output=="") return "看起来代码在编译中出了点小问题...";

        
        output.clear();
        command="\"" + src_address +to_string(file_id) + ".exe\"";

	    fp = _popen(command.c_str(), "r");    

        while(fgets(buf, 1000, fp)!=0){
		    output+=buf;
		    memset(buf,0,sizeof(buf));
        }   
        
        _pclose(fp);

        file_id++;

        return output;
    }


    string _main(string text_input){
        
        //int file_id=save_code(text_input);
        return run_code( text_input );

    }
};
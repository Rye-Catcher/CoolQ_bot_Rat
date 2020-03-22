#pragma once
#include <Windows.h>
#include <wchar.h>
#include "ChineseToUTF8.h"

using namespace std;

void CN2Utf8(char *input,char *output)
{
    int len ;
    wchar_t *out = (wchar_t *) malloc(len*sizeof(wchar_t));

    len = MultiByteToWideChar(CP_ACP,0,input,-1,out,strlen(input)+1);
    WideCharToMultiByte(CP_UTF8,0,out,wcslen(out),output,len,NULL,NULL);

    return ;
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include "check_input_string.h"


int check_input_string(wchar_t *string, int size)
{
    
    wchar_t *error_result = fgetws(string,size,stdin);
    size_t len = wcslen(string);
    if(error_result !=NULL && string[len-1]=='\n')
    {
        string[len-1]='\0';
        return (0);
    }
    else
    {
        fputws(L"Input error !!\n",stdout);
        return (1);
    }
    
}
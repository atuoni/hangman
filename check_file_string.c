//****************************************************************************
// File:   check_file_string.c
// Author: Amauri Tuoni
//
// Função para ler string de um arquivo                 Version 1.0
// 
// Created on 14 de Outubro de 2020, 15:49
//****************************************************************************

#include <stdlib.h>  //header of standard library
#include <stdio.h>   //header of I/O library
#include <wchar.h>    //header of wide characters (UNICODE)
#include "check_file_string.h"  //header of this file

int check_file_string(wchar_t *string, int size, FILE *file_pointer)
{
    
    wchar_t *error_result = fgetws(string,size,file_pointer);  //get the data of the file
    size_t len = wcslen(string);     //calculate the size of the string
    if(error_result !=NULL && string[len-1]=='\n')  //find a line feed on the string
    {
        string[len-1]='\0';   //swap line feed to end string
        return (0);           //return that the read was good
    }
    else
    {
        fputws(L"File error !!\n",stdout);
        return (1);                   //return that there was an error
    }
    
}
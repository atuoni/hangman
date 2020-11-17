//****************************************************************************
// File:   check_input_string.c
// Author: Amauri Tuoni
//
// Função para ler string do teclado                Version 1.0
// 
// Created on 14 de Outubro de 2020, 15:49
//****************************************************************************
#include <stdlib.h>
#include <stdio.h>
//#include <string.h>
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
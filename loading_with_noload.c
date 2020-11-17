//****************************************************************************
// File:   loading_with_noload.c
// Author: Amauri Tuoni
//
// Função que imprime "loading" na tela                 Version 1.0
// (A função main fica "presa")
// 
// Created on 14 de Outubro de 2020, 15:49
//****************************************************************************

#include <stdio.h>   //cabeçalho para as funçoes de i/o
#include <unistd.h>  //cabeçalho para a função usleep
#include <wchar.h>    //cabeçalho para as funções com wide character  
#include "loading_with_noload.h"   //cabeçalho com o prototipo da função

void loading_with_noload(void)
{
    const int trigger = 500; //define tempo em ms 
    const int numDots = 15;    //determina o numero de '.' que serão exibidos
    const wchar_t message[] = L"Computer is loading the secret word";    //armazena mensagem que irá aparecer na tela
    int loop = 0;                            //iniciliza a qtde de loops = 0
    fputws(L"\e[?25l", stdout);  //desliga o aparecimento do cursor
    
    //fputs("\e[?25h", stdout); //liga o aparecimento do cursor
    
    while (loop<1) //Executa 1 loops e sai da função
    {
        // Return and clear with spaces, then return and print prompt.
        wprintf(L"\r%*ls\r%ls", (int)sizeof(message) - 1 + numDots, "", message);
        fflush(stdout);    //limpa buffer de video

        // Print numDots number of dots, one every trigger milliseconds.
        for (int i = 0; i < numDots; i++)   //executa loop para imprimir na tela
        {
            usleep(trigger * 1000);   //suspende a execução pelo tempo informado na função(500ms)
            fputwc(L'.', stdout);   //imprime na tela '.'
            fflush(stdout);       //limpa buffer de video
        }
        loop++; //incrementa q qtde de loops
    }
}// fim da função
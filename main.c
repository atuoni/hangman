
//****************************************************************************
// File:   main.c
// Author: Amauri Tuoni
//
//  HangMan Game (Jogo da Forca)          Version 1.2
//
// Created on 15 de Novembro de 2020, 15:49
//****************************************************************************

#include <stdio.h>   //library for I/O functions
#include <stdlib.h>  // standard library
#include <string.h>  // library for string functions
#include <locale.h>  // library to set the location
#include <wchar.h>   // library to use wide character (UNICODE)
#include "check_input_string.h" // header of the function to check a string in stdin
#include "check_file_string.h"  //header of the function to check a string in a file
#include "loading_with_noload.h"  //header of the function to print the loading message on the screen
#include <time.h>    //library to use date and time functions

#define TRUE 1
#define FALSE 0
#define QTD_GAMES 6      //define the quantity of games to play

struct user                                       //struct that define a user
    {
        wchar_t secret_word[30];                 // store the secret word
        wchar_t name[30];                        //store the players name
        wchar_t level[3];                        //store the level of difficult
        int score;                               //store the score of the player
        int attempts;                            //store the number of attempts of the player
        size_t word_length;                     //store the length of the secret word
    };
    
wchar_t copy_word[30];                   //variable to store a copy of secret_word
wchar_t player_option[2];               //variable to store the selection of numbers of players
wchar_t *p_wrong_moves;                   // a pointer to the allocated memory of wrong letters
int number_games = 1;                  //set the number games to start as 1
FILE *fp;                              // a pointer to the file with the secret words

void create_copy_word(struct user *);              //prototype of the function to create the copy word
int play_screen(struct user *,struct user *);       //prototype of the function that has the engine of the game
void print_secret_word(struct user * ,int, int);   //prototype of the function that print the secret word
int final_result(char, struct user *);            //prototype of the function that determine the final result
int count_words(struct user *);                   //prototype of the function that count the number of words in the file
int number_generator(int);                       //prototype of the function that generate the number of the secret word in the file

int main(void) 
{
    setlocale(LC_ALL,"pt_BR.utf8");  //set the location of the program to use portuguese language
    //freopen(NULL,"w",stdout);
    fputws(L"********************* Hang Man V1.2 ***************** Created by A.T. ******",stdout); // print the message on the screen
    fputws(L"\n\nType your name: ",stdout);                       //print the message to get the name of player 1
    struct user player1;  
    struct user player2;
    player1.score=0;   //set player1 score as 0
    player2.score=0;   //set player2 score as 0
   
    while(check_input_string(player1.name,sizeof(player1.name)));  //get the player1 name
   
    wprintf(L"%ls, select who you want to play with:\n",player1.name);     //print the message on the screen
    do                                           // print the menu on the screen
    {
        fputws(L"(1) - Friend\n",stdout);               // play with a friend
        fputws(L"(2) - Computer\n",stdout);             // play against the computer
        fputws(L"(3) - None (exit)\n",stdout);          // quit the program
        while(check_input_string(player_option,sizeof(player_option)));   // get the player1 option
    }while(player_option[0]<'1' || player_option[0]>'3');   //verify if the player option is right
    
    if(player_option[0]<'3')       //if player option is equal 1 or 2 get the difficult level
    {
        do   //print the menu with levels on the screen
        {
            wprintf(L"%ls, select the level of difficult: \n",player1.name);   //print the level of difficult
            fputws(L"(1) - Easy\n",stdout);                  // play on the easy level
            fputws(L"(2) - Normal\n",stdout);               //play on the normal level
            fputws(L"(3) - Hard\n",stdout);                 //play on the hard level
            while(check_input_string(player1.level,3));      // get the player1 level
        }while(player1.level[0]<'1' || player1.level[0]>'3');  //verify if the level is right
    }
    switch(player_option[0])
    {
        case '1':        // selected to play with a friend
            
            fputws(L"Type the name of your friend: ",stdout);    // print a message on the screen
            while(check_input_string(player2.name,sizeof(player2.name)));  //get the player2 name
            while(number_games<QTD_GAMES)  // loop until five games played
            {
                wprintf(L"Ask to %ls to type the secret word [%lu]: \n",player2.name,number_games);  //print the message on the screen
                while(check_input_string(player1.secret_word,sizeof(player1.secret_word)));   // get the secret of word for the player1
                system("clear");                                     //clean the screen
                create_copy_word(&player1);                          // call function to create a copy of the secret word
                int score = play_screen(&player2,&player1);          // call function to player1 play 
                if(score)                                            
                {
                    player2.score++;                                // if player1 missed the game
                }
                else
                {
                    player1.score++;                               // if player1 won the game
                }
                wprintf(L"\n\nScore:%ls %lu X %lu %ls\n\n",player1.name,player1.score,player2.score,player2.name);   //print the score on the screen
                number_games++;         //increase the number of games played
            }
            break;
        case '2':
           
            if((fp = fopen("./Secret_Words/Computer_Words","r+"))==NULL)  //open the secret words file
            {
                fputws(L"Fail to open the file",stdout);
                exit(1);
            }
            wcscpy(player2.name,L"Computer");           // define the player2 name as Computer
            int numero=count_words(&player1);            // call function to count the number of words in secret words file
            while(number_games<QTD_GAMES)                //verify the number of games played
            {
                wprintf(L"This is the game %ld of 5, %ls. Play!\n",number_games,player1.name);
                loading_with_noload();                    //call function to print the loading message
                rewind(fp);                               //rewind the secret words file
                int random_number=number_generator(numero);    //call function to generate a random number
                //wprintf(L"\nComputer is generating the secret word of game %ld...",number_games);
                for(int i=1;i<=random_number;i++)    // run from the first word until reach the word with the random number
                {
                    check_file_string(player1.secret_word,sizeof(player1.secret_word),fp);   // read each word in the secret word file
    
                }
                create_copy_word(&player1);                          // call function to create a copy of the secret word
                int score = play_screen(&player2,&player1);          // call function of the game engine 
                if(score)                                            
                {
                    player2.score++;                                // if player1 missed the game
                }
                else
                {
                    player1.score++;                               // if player1 won the game
                }
                wprintf(L"\n\nScore:%ls %lu X %lu %ls\n\n",player1.name,player1.score,player2.score,player2.name);  //print the score on the screen
                number_games++;  //increase the number of games played
            }
                fclose(fp);   //close the secret word file
                break;
            
        case '3':
            fputws(L"Leaving...\n",stdout);     //print the message on the screen
            exit(0);                          //exit to the system and close all open files
            break;
    }
    return(0);   // return to the system
} //end of main function

//***********************************************************************************************************************************************************
// random number generator using the maximum number of words in the secret word file
//************************************************************************************************************************************************************
int number_generator(int max_number)
{
    int random_number;
    srand(time(NULL));                    //generate a random seed 
    random_number=(rand()%max_number)+1;  //generate the random number (range: 1 to max_number)
    return random_number;                 // return the random number
}


//************************************************************************************************************************************************************
// function to count the number of words in the file
//************************************************************************************************************************************************************
int count_words(struct user *player)
{
    int nWords=0;
    while(fgetws(player->secret_word,sizeof(player->secret_word),fp)!=NULL)  //read each word until reach the end of the file
    {
        nWords++;            //increase the quantity of words
    }
    
    return nWords;
}


//***************************************************************************************************************************************************************************
// function to copy the secret word and determine the number of attempts
//***************************************************************************************************************************************************************************

void create_copy_word(struct user *player)
{   
 
    player->word_length = wcslen(player->secret_word);         //get length of secret word and store
    switch(player->level[0])                                   // calculate the level of difficult
    {
        case '1':  
                player->attempts=player->word_length*3;       //easy level: 3 * length of secret word = number of attempts 
                break;
        case '2': 
                player->attempts=player->word_length*2;      // normal level: 2 * length of secret word = number of attempts
                break;
        case '3':
                player->attempts=player->word_length*1;      // hard level : 1 * length of secret word = number of attempts
                break;
    }
    for(int letter=0;letter<player->word_length;letter++)  // for loop until the end of secret word
    {
        copy_word[letter]='?';  // complete copy_word with '?' character   
       
    }
    p_wrong_moves = (wchar_t *)malloc(sizeof(wchar_t)*(player->attempts)); //allocate memory with the size of the number of attempts * wchar_t size ("wrong moves")
    
    for(int index=0;index<player->attempts;index++)  //for loop until the number of attempts
    {
        *(p_wrong_moves+index)='*';    // complete all the memory allocated with the '*' character
        
    }
    //free(p_wrong_letter);
}//end of the function

//**************************************************************************************************************************************************************************
// function to print on the screen the secret word and wrong attempts
//**************************************************************************************************************************************************************************
void print_secret_word(struct user *player, int times , int hits)
{
    wprintf(L"Secret word [Game %ld]:     ",number_games);   //print the message on the screen
    for(int index=0; index<player->word_length; index++)  //loop until the end of secret word
    {
        wprintf(L"%lc   ",copy_word[index]);           //print the copy word on the screen
    } 
    wprintf(L"\n\nRemaining attempts = %lu       Hits = %lu\n\n",times,hits);      // print the attempts and hits on the screen
        
    for(int index=0; index<player->attempts; index++)    // loop until the number of attemps
    {
        wprintf(L"%li-%lc   ",index+1, p_wrong_moves[index]);   // print * character on the screen
    }
} //end of the function

//***************************************************************************************************************************************************************************
// function to print on the screen if the player1 won or missed each game
//***************************************************************************************************************************************************************************
int final_result(char result, struct user *player)
{
    
    if(!result)   //verify the final result of each game
    {
        wprintf(L"\nYou won the game %lu, %ls!!",number_games, player->name);  //print the message that the player1 won the game
        return 0;                                                              
    }
    else
    {
        wprintf(L"You lost the game %lu, %ls!!",number_games, player->name);  //print the message that the player1 lost the game
        return 1;                                                              
    }
} //end of the function

//***************************************************************************************************************************************************************************
// function that implement the game engine to discover the secret word
//***************************************************************************************************************************************************************************
int play_screen(struct user *player2, struct user *player1)
{
    wint_t enter_key;                   // save the key pressed by the player
    char right_moves = 0;               // save the number of right letters 
    wchar_t letter_attempt[3];          // array to store the letter that the player try
    wchar_t word_attempt[50];          // array to store the word that the player try
    char end_flag = FALSE;             // flag to show when arrived the last letter    
    char letter_flag= FALSE;     // flag to show when the player get a right letter
    int nAttempts = player1->attempts;   // save the number of attempts to loop variable
    
    while(right_moves < player1->word_length && !end_flag && nAttempts>0)
    {
        system("clear");     // clean the screen on each loop 
        print_secret_word(player1,nAttempts, right_moves);   //call function to print the secret word
        letter_flag = FALSE;   
        
        fputws(L"\n\n\nType a letter or type '@' to try a word (Type '!' to game exit)",stdout); //print on the screen
        int flag_input = check_input_string(letter_attempt,sizeof(letter_attempt));  // get the letter try of the player
        
        if(letter_attempt[0]=='@')   // verify if the player want to try a word
        {
            fputws(L"Type the word: ",stdout);    // print on the screen the message
            flag_input = check_input_string(word_attempt,sizeof(word_attempt));       //get the word try of the player
            char flag_result = wcscmp(word_attempt,player1->secret_word);  // compare the word try with the secret word
            if (!flag_result)  // if they are equal
            {
                letter_flag= TRUE;      // set that the word is right
                end_flag= TRUE;              // set flag and go out of the while loop 
                wcscpy(copy_word,player1->secret_word);  //copy the secret word for copy word
            }
            
        }
        if(letter_attempt[0]=='!')    // verify if the player wants to exit
        {
            fputws(L"Leaving...",stdout);    // print the message
            exit(0);   // go to the system and close all files
        }
        else                 
        {
            for(int index=0;index<player1->word_length;index++)  //loop to run until end of secret word
            {
                if( *(player1->secret_word+index) == letter_attempt[0])  // verifying if there is some letter equal the letter typed
                {
                    if(*(player1->secret_word+index)!=copy_word[index]) // and verify if the letter have already found (looking the copy word)
                    {
                        letter_flag=TRUE;  //set that the player move was right
                        right_moves++;      // increase the number of hits
                        copy_word[index]=*(player1->secret_word+index);  // put the letter that is right on the copy word array
                    }
               
                }
            }
        }
        if(!letter_flag)   //if the letter played wasn't right
        {
            
            p_wrong_moves[nAttempts-1]=letter_attempt[0];   // put the letter played on the memory allocated (array of mistakes)
            wprintf(L"\nBad! Wrong move, %ls!!\n",player1->name); // print the message on the screen
            nAttempts--;    // decrease the number letters verified
        }
        else          // if the letter played was right
        {
            p_wrong_moves[nAttempts-1]='$';     // put the character '$' on the memory allocated (array of mistakes)
            wprintf(L"\nGood! Right move, %ls!!\n",player1->name);       // print the message on the screen
        }
        enter_key = 0x00;        // clean key pressed                     
    
        while(enter_key!= 0x0A)    // wait until the player press the enter key
        {
            enter_key = getwchar(); //get the key pressed
        }
        //loop--;   //option of attempts counted  (right moves + wrong moves)
        
    }
    char flag_result = wcscmp(copy_word,player1->secret_word);   // compare copy word with the secret word
    
    return(final_result(flag_result,player1));      //return and print the comparasion result
    
} //end of the function

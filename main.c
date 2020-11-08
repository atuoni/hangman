
//****************************************************************************
// File:   main.c
// Author: Amauri Tuoni
//
//  HangMan Game (Jogo da Forca)          Version 1.1
//
// Created on 25 de Outubro de 2020, 15:49
//****************************************************************************

#include <stdio.h>   //library for I/O functions
#include <stdlib.h>  // standard library
#include <string.h>  // library for string functions
#include <locale.h>  // library to set the location
#include <wchar.h>   // library to use wide character (UNICODE)
#include "check_input_string.h" // library to get a wchar string in stdin

#define TRUE 1
#define FALSE 0

struct user                                       //struct that define a user
    {
        wchar_t secret_word[30];                 // store the secret word
        wchar_t name[30];                        //store the players name
        wchar_t level[3];                        //store the level of difficult
        int score;                               //store the score of the player
        int attempts;                            //store the number of attempts of the player
        size_t word_length;                     //store the length of the secret word
    };
    
wchar_t copy_word[30];  //variable to store a copy of secret_word
wchar_t player_option[2]; //variable to store the selection of numbers of players
char *p_wrong_moves;   // a pointer to the allocated memory of wrong letters
int number_games = 1;  //set the number games to start as 1

void create_copy_word(struct user *);  //prototype of the function to create the copy word
int play_screen(struct user *,struct user *);   //prototype of the function that the user play
void print_secret_word(struct user * ,int, int); //prototype of the function that print the secret word
int final_result(char, struct user *);    //prototype of the function that determine the final result

int main(void) 
{
    setlocale(LC_ALL,"pt_BR.utf8");  //set the location of the program to use portuguese language
    //freopen(NULL,"w",stdout);
    fputws(L"********************* Hang Man V1.1 ***************** Made by A.T. ******",stdout); // print the message on the screen
    fputws(L"\n\nType your name: ",stdout);                       //print the message to get the name of player 1
    struct user player1;
    struct user player2;
    player1.score=0;
    player2.score=0;
   
   
    while(check_input_string(player1.name,sizeof(player1.name)));  //call function to get the player1 name
   
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
        //struct user player2;
        do   //print the messages of level on the screen
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
            while(number_games<6)  // loop until five games played
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
                number_games++;         //increase the of games played
            }
            break;
        case '2':
            fputws(L"it will be implemented soon",stdout);   //not implemented yet
            break;
        case '3':
            fputws(L"Leaving...",stdout);     //print the message on the screen
            exit(0);  //exit to the system
            break;
    }
    return(0);// return to the system
} //end of main function

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
        copy_word[letter]='?';  // complete copy_word with ? character   
       
    }
    p_wrong_moves = (char *)malloc(sizeof(char)*(player->attempts)); //allocate memory with the size of the number of attempts * char size ("wrong moves")
    
    for(int index=0;index<player->attempts;index++)  //for loop until the number of attempts
    {
        *(p_wrong_moves+index)='*';    // complete all the memory allocated with the '*' character
        
    }
    //free(p_wrong_letter);
    
}
//**************************************************************************************************************************************************************************
// function to print on the screen the secret word and wrong attempts
//**************************************************************************************************************************************************************************
void print_secret_word(struct user *player, int times , int hits)
{
    fputws(L"Secret word:     ",stdout);   //print the message on the screen
    for(int index=0; index<player->word_length; index++)  //loop until the end of secret word
    {
        wprintf(L"%lc   ",copy_word[index]);           //print the copy word on the screen
    } 
    wprintf(L"\n\nRemaining attempts = %lu       Hits = %lu\n\n",times,hits);      // print the attempts and hits on the screen
        
    for(int index=0; index<player->attempts; index++)    // loop until the number of attemps
    {
        wprintf(L"%li-%lc   ",index+1, p_wrong_moves[index]);   // print * character on the screen
    }
}

//***************************************************************************************************************************************************************************
// function to print on the screen if the player won or missed the game
//***************************************************************************************************************************************************************************
int final_result(char result, struct user *player)
{
    
    if(!result)   // if result of the compare is zero
    {
        wprintf(L"\nYou won the game %lu, %ls!!",number_games, player->name);  //print the message that the player won the game
        return 0;                                                              //return zero when leave
    }
    else
    {
        wprintf(L"You lost this game %lu, %ls!!",number_games, player->name);  //print the message that the player lost the game
        return 1;                                                              //return 1 when leave
    }
}

//***************************************************************************************************************************************************************************
// function that implement the engine to discover the secret word
//***************************************************************************************************************************************************************************
int play_screen(struct user *player2, struct user *player1)
{
    wint_t enter_key;                   // save the key pressed by the player
    char right_moves = 0;               // save the number of right letters 
    wchar_t letter_attempt[3];          // array to store the letter that the player try
    wchar_t word_attempt[50];          // array to store the word that the player try
    char end_flag = FALSE;             // flag to show when arrived the last letter    
    char letter_flag= FALSE;     // flag to show when the player get a right letter
    int loop = player1->attempts;   // save the number of attempts to loop variable
    
    while(right_moves < player1->word_length && !end_flag && loop>0)
    {
        system("clear");     // clean the screen on each loop 
        print_secret_word(player1,loop, right_moves);   //call function to print the secret word
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
            exit(0);   // go to the system
        }
        else                 
        {
            for(int index=0;index<player1->word_length;index++)  //loop to run until end of secret word
            {
                if( *(player1->secret_word+index) == letter_attempt[0])  // verifying if there is some letter equal
                {
                    if(*(player1->secret_word+index)!=copy_word[index]) // and verify if the letter have already found (looking the copy word)
                    {
                        letter_flag=TRUE;  //set that the play was right
                        right_moves++;      // increase the number of hits
                        copy_word[index]=*(player1->secret_word+index);  // put the letter that is right on the copy word array
                    }
               
                }
            }
        }
        if(!letter_flag)   //if the letter played wasn't right
        {
            
            p_wrong_moves[loop-1]=letter_attempt[0];   // put the letter played on the memory allocated (array of mistakes)
            wprintf(L"\nBad! Wrong letter, %ls!!\n",player1->name); // print the message on the screen
            loop--;    // decrease the number letters verified
        }
        else          // if the letter played was right
        {
            p_wrong_moves[loop-1]='$';     // put the character '$' on the memory allocated (array of mistakes)
            wprintf(L"\nGood! Right letter, %ls!!\n",player1->name);       // print the message on the screen
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

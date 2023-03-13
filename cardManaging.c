#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "cardManaging.h"
#include "safeinput.h"


int cardsInSystem(CardsList *cardList){
    int ch; 
    int counter = 0;
    FILE* file; 
    file = fopen("listOfRegisterdCards.dat", "rb"); 
    if (file == NULL) {
            printf("Something went wrong when opening the file");
            fclose(file);
            return 0;
    }

    if ((ch = fgetc(file)) == EOF){
        printf("\nThere are no registerd cards in the system.");
        fclose(file); 
        return 0; 
    }

    fseek(file, sizeof(Card[0]), SEEK_SET);
    printf("\nCards registerd in system:");
    while (!feof(file)){
        if(counter == 0)
            cardList -> cards = (Card *)malloc(1 * sizeof(Card)); 
        else 
            cardList -> cards = (Card *)realloc(cardList -> cards, (counter + 1)  * sizeof(Card)); 
        fread(&cardList->cards[counter], sizeof(cardList->cards[0]), 1, file);
        counter++;
    }   

    for(int i = 0; i < counter - 1; i++){
        if (cardList->cards[i].access)
            printf("\nCardnumber: %d, \nRegistered on: %s\nAccess\n", cardList->cards[i].cardNumber, cardList->cards[i].dateOfRegistration);
        else 
            printf("\nCardnumber: %d, \nRegistered on: %s\nNo access\n", cardList->cards[i].cardNumber, cardList->cards[i].dateOfRegistration);

    }

   fclose(file); 
return 0;
}


/*
manageAccess

open file with cards
go through it one by one

promt user to input cardnumber

if card exists
    print if card has access or not.
else 
    ask if want to add card. 
    close file
    go to add card


User can change access
    press 1 to give access
    press 2 to remove acess

print updated carddetails
close file
*/


void addCardToFile(CardsList *cardList, int tempCardNum, bool tempAccess){
    char currentDate[26];
    time_t timer;
    struct tm* date_info;  
    timer = time(NULL);
    date_info = localtime(&timer);  
    strftime(currentDate,26, "%Y-%m-%d", date_info);

    FILE* file; 
    file = fopen("listOfRegisterdCards.dat", "ab"); 
    if (file == NULL) {
            printf("Something went wrong when opening the file");
            fclose(file);
            return;
    }
    cardList->numOfCards++;
  
    if(cardList -> numOfCards == 1)
        cardList -> cards = (Card *)malloc(1 * sizeof(Card)); 
    else 
        cardList -> cards = (Card *)realloc(cardList -> cards, cardList ->numOfCards * sizeof(Card)); 

    cardList->cards[cardList -> numOfCards -1].cardNumber = tempCardNum; 
    cardList ->cards[cardList->numOfCards -1].access = tempAccess; 
    strcpy(cardList ->cards[cardList->numOfCards -1].dateOfRegistration, currentDate); 

    fwrite(&cardList->cards[cardList->numOfCards -1], sizeof(Card), 1, file); 
    fclose(file);
return;
}

int inputCardDetails(CardsList *cardList){
    int tempCardNum;
    int userChoice; 
    bool tempAccess = true;  
    
    while(true){
        GetInputInt("Input card details:\nCard number: ", &tempCardNum); 
        //Need to make a function here to check if the card is already registerd. 
        GetInputInt("\nWill the card have access?\n1.Yes\n2.No\n",&userChoice);
        if(userChoice == 2)
            tempAccess = false; 

        printf("\nThe information you have entered:\n");
        if(tempAccess)
            printf("Cardnumber: %d, has access.\n", tempCardNum);
        else
            printf("Cardnumber: %d, does not have access.\n", tempCardNum); 

        GetInputInt("\nIs the information entered correct?\n1.Yes\n2.No\n", &userChoice);
        if (userChoice == 1){
            addCardToFile(cardList,tempCardNum,tempAccess);
            printf("Card succesfully saved.\n");
            break; 
        }
    }
return 0; 
}




/*

testAccess

open file with cards
go through it one by one

print lamp status
Promt user to input cardnumber

check if card is in system
    if not tell user to enter valid card number. 

if the card has access
    lamp turns green
else 
    lamp turns red

close cardfile


*/
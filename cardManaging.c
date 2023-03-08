#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "cardManaging.h"
#include "safeinput.h"


int cardsInSystem(const CardsList *cardList){
    int ch; 
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
    } else {
        printf("All cards in system:\n"); 
        for(int i = 0; i < cardList ->numOfCards; i++){
            if(cardList->cards[i].access)
                printf("Cardnumber: %d, Registerd on: %s\n Access", cardList -> cards[i].cardNumber, cardList -> cards[i].dateOfRegistration);
            printf("Cardnumber: %d, Registerd on: %s\nNo access", cardList -> cards[i].cardNumber, cardList -> cards[i].dateOfRegistration);
        }
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


/*
addCard

open file with cards in apprehend mode

promt user to input carddetails
    card number
    acces status
    (date will be added automaticly)

print the enterd details and ask if they are correct
    if yes
        print list to file
        sort by cardnumber order
        close file
    else 
        ask user to input details again. 

    close file
*/
int addCardToFile(CardsList *cardList, int tempCardNum, bool tempAccess){
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
            return 1;
    }
    cardList->numOfCards++;
  
    if(cardList -> numOfCards == 1)
        cardList -> cards = (Card *)malloc(1 * sizeof(Card)); 
    else 
        cardList -> cards = (Card *)realloc(cardList -> cards, cardList ->numOfCards * sizeof(Card)); 

    cardList->cards->cardNumber = tempCardNum; 
    cardList ->cards->access = tempAccess; 
    strcpy(cardList ->cards ->dateOfRegistration, currentDate); 

    fwrite(&cardList->cards, sizeof(Card), 1, file); 
    free(cardList->cards);
    fclose(file);

return 0; 
}

int inputCardDetails(CardsList *cardList){
    int tempCardNum;
    int userChoice; 
    bool tempAccess = true;  
    
    while(true){
        GetInputInt("Input card details:\nCard number: ", &tempCardNum); 
        GetInputInt("\nWill the card have access?\n1.Yes\n2.No",&userChoice);
        if(userChoice == 2)
            tempAccess = false; 

        if(tempAccess)
            printf("Cardnumber: %d, has access\n", tempCardNum);
        else
            printf("Cardnumber: %d, does not have access\n", tempCardNum); 

        GetInputInt("Is the information entered correct?\n1.Yes\n2.No", &userChoice);
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
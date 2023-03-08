#include <stdio.h>
#include <stdbool.h>
#include "cardManaging.h"



int cardsInSystem(const CardsList *cardList){
    int ch; 
    FILE* file; 
    file = fopen("listOfRegisterdCards.dat", "r"); 
    if (file == NULL) {
            printf("Something went wrong array with when opening the file");
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
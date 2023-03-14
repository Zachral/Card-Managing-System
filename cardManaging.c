#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h> // Makes sleep() avalible in linux
/*#include <Windows.h> Needs to be uncommented to use sleep() on a Windows device*/
#include "cardManaging.h"
#include "safeinput.h"
#include "menu.h"
#include "empty_stdin.h"


int readCardList(CardsList *cardList){
    int ch; 
    int counter = 0;
    file = fopen("listOfRegisterdCards.dat", "rb+"); 
    if (file == NULL) {
            printf("Something went wrong when opening the file");
            return 0;
    }

    if ((ch = fgetc(file)) == EOF){
        printf("\nThere are no registerd cards in the system.");
        return 0; 
    }

    fseek(file, sizeof(Card[0]), SEEK_SET);
    while (!feof(file)){
        if(counter == 0)
            cardList -> cards = (Card *)malloc(1 * sizeof(Card)); 
        else 
            cardList -> cards = (Card *)realloc(cardList -> cards, (counter + 1)  * sizeof(Card)); 
        fread(&cardList->cards[counter], sizeof(cardList->cards[0]), 1, file);
        counter++;
    }   
return counter;
}

void printCardDetails(CardsList * cardList, int i){
    if (cardList->cards[i].access)
        printf("\nCardnumber: %d, \nRegistered on: %s\nAccess\n", cardList->cards[i].cardNumber, cardList->cards[i].dateOfRegistration);
    else 
        printf("\nCardnumber: %d, \nRegistered on: %s\nNo access\n", cardList->cards[i].cardNumber, cardList->cards[i].dateOfRegistration); 
}

int cardsInSystem(CardsList *cardList){ 
    printf("\nCards registerd in system:");
    for(int i = 0; i < readCardList(cardList) - 1; i++){
        printCardDetails(cardList, i); 
    }
    fclose(file); 
return 0;
}

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

    fwrite(&cardList->cards[cardList ->numOfCards -1], sizeof(Card), 1, file); 
    fclose(file);
return;
}

int inputCardDetails(CardsList *cardList){
    int tempCardNum;
    int accessChoice;
    int confirmInformation; 
    bool tempAccess = true;  
    
    while(true){
        printf("\nInput card details:\nCard number: ");
        if(scanf(" %d", &tempCardNum)){
            while(true){
                for(int i = 0;i < readCardList(cardList) - 1; i++){
                    if(tempCardNum == cardList->cards[i].cardNumber){
                        printf("A card with card number %d is already registerd in the system.\nEnter a different number.\n", tempCardNum);
                        i = 0; 
                        empty_stdin(); 
                        while(true){
                            printf("\nCard number: ");
                            if(scanf(" %d", &tempCardNum)){
                                break;
                            } else {
                                printf("\nInput must be a number.");
                                empty_stdin(); 
                            }
                        }
                    }
                }
                fclose(file); 
                break; 
            }
            while(true){
                printf("\nWill the card have access?\n1.Yes\n2.No\n");
                scanf(" %d",&accessChoice);
                if(accessChoice != 1 && accessChoice != 2){
                    printf("\nInvalid input.");
                    empty_stdin(); 
                }else{
                    empty_stdin();
                    break; 
                }
            }
            if(accessChoice == 2)
                tempAccess = false; 

            printf("\nThe information you have entered:\n");
            if(tempAccess)
                printf("Cardnumber: %d, has access.\n", tempCardNum);
            else
                printf("Cardnumber: %d, does not have access.\n", tempCardNum); 
                
            while(true){
                confirmInformation = 0; 
                printf("\nIs the information entered correct?\n1.Yes\n2.No\n");
                scanf(" %d",&confirmInformation);
                if(confirmInformation != 1 && confirmInformation != 2){
                    printf("\nInvalid input.");
                    empty_stdin(); 
                }else{
                    empty_stdin();
                    break; 
                }
            }
            if(confirmInformation == 1){
                addCardToFile(cardList,tempCardNum,tempAccess);
                printf("Card succesfully saved.\n");
                return 0; 
            }
        }else{
            printf("\nInput must be a number.");
            empty_stdin();  
        }
    }
return 0; 
}

int manageAccess(CardsList *cardList){
    int cardNum, changeAcess, userChoice; 
    while(true){
        printf("Input cardnumber: ");
        if(scanf(" %d", &cardNum)){
            for(int i = 0;i < readCardList(cardList) - 1; i++){
                if(cardNum == cardList->cards[i].cardNumber){
                    printCardDetails(cardList, i); 
                    while(true){
                        printf("\nDo you want to change the access status?\n1.Yes\n2.No\n"); 
                        scanf(" %d", &changeAcess); 
                        if(changeAcess != 1 && changeAcess != 2){
                            printf("Invalid input. Must be 1 or 2.");
                            empty_stdin(); 
                        }else 
                            break; 
                    }
                    if (changeAcess == 1){
                        cardList->cards[i].access = !cardList->cards[i].access; 
                        printf("\nUpdated details:");
                        printCardDetails(cardList, i); 
                        fwrite(&cardList->cards[i], sizeof(Card), 1, file); // Fix writing to file
                        fclose(file);
                        empty_stdin(); 
                        return 0;
                    }else{
                        fclose(file); 
                        return 0;  
                    }
                }
            }
            empty_stdin(); 
            printf("\nThere is no card registerd in the system with cardnumber: %d\n", cardNum);
            while (true){
                userChoice = 0;
                printf("\nDo you want to:\n1.Add a new card.\n2.Input a differnt cardnumber\n3.Exit to menu\n");
                scanf(" %d", &userChoice);
                if(userChoice != 1 && userChoice != 2 && userChoice != 3){
                    printf("Invalid input.\n");
                    empty_stdin();  
                }else{ 
                    if(userChoice == 1){
                        empty_stdin();
                        inputCardDetails(cardList);
                        return 0; 
                    }else if (userChoice == 2)
                        break; 
                    else{
                        empty_stdin();
                        return 0; 
                    }
                }
            }
        }else{
            printf("Input must be a number.\n");
            empty_stdin(); 
        }
    }
return 0;
}

void testAccess(CardsList *cardList){
    int cardNumTest; 
    int userChoice;
    puts("CURRENTLY LAMP IS: Off");
    sleep(1); 
    while (true){
        printf("Input cardnumber to test access: ");
        if(scanf(" %d", &cardNumTest)){
            empty_stdin();
            for(int i = 0; i < readCardList(cardList) - 1; i++){
                if(cardList->cards[i].cardNumber == cardNumTest){
                    if(cardList->cards[i].access){
                        puts("CURRENTLY LAMP IS: Green"); 
                        sleep(3);
                        puts("CURRENTLY LAMP IS: Off");
                        fclose(file);
                        return;
                    } else {
                        puts("CURRENTLY LAMP IS: Red"); 
                        sleep(3);
                        puts("CURRENTLY LAMP IS: Off");
                        fclose(file);
                        return;
                    }
                }   
            }
            printf("\nCard number %d is not registerd in the system.\n", cardNumTest); 
            while(true){
            printf("Do you want to:\n1. Enter a new number\n2. Exit to menu\n");
            scanf(" %d",&userChoice);     
                if(userChoice != 1 && userChoice != 2){
                    printf("\nInvalid input\n");
                    empty_stdin();
                }else{ 
                    empty_stdin();
                    if(userChoice == 1)
                        break;
                    else if(userChoice == 2){
                        fclose(file);   
                        return; 
                    }
                }
            }
        }else{
            printf("Input must be a number.\n");
            empty_stdin(); 
        }
    }
}

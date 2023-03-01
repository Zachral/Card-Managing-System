/*

Print menu

user chooses 1, go to REMOTE OPEN DOOR
user chooses 2, go to LIST ALL CARDS IN SYSTEM
user chooses 3, go to  ADD/REMOVE ACCESS
user chooses 4, EXIT program
user chooses 9. FAKE TEST CARDS

if any other input:
    tell user to add a valid input
    reprint menu. 


*/

#include <stdio.h>
#include <stdbool.h>
#include "safeinput.h"

int showMenu(){
    while(true){
        int userSelection; 
        puts("Admin menu\n"
            "1. Remote open door\n"
            "2. List all cards in system\n"
            "3. Add/remove access\n"
            "4. Exit\n"
            "9. FAKE TEST SCAN CARD\n");

        GetInputInt("", &userSelection);

        if(userSelection != 1 && userSelection != 2 && userSelection != 3 && userSelection != 4 && userSelection != 9)
            puts("Invalid choice. Try again ");
        else 
            return userSelection;  
        }
}
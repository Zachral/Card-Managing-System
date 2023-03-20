#include <stdio.h>
#include <stdbool.h>
#include "safeinput.h"
#include "empty_stdin.h"

int showMenu(){
    while(true){
        int userSelection; 
        puts("\nAdmin menu\n"
            "1. Remote open door\n"
            "2. List all cards in system\n"
            "3. Add/remove access\n"
            "4. Exit\n"
            "9. FAKE TEST SCAN CARD");

        GetInputInt("", &userSelection);

        if(userSelection != 1 && userSelection != 2 && userSelection != 3 && userSelection != 4 && userSelection != 5 && userSelection != 9){
            puts("Invalid choice. Try again\n");
        }else 
            return userSelection;  
        }
}
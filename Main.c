/*


Menu goes here


*/
#include <stdio.h>
#include <stdbool.h>
#include "menu.h"
#include "doorControl.h"
#include "cardManaging.h"

int main(){
    CardsList cardList = {NULL, 0}; 
    while(true){
        int menuSelection = showMenu(); 

        switch(menuSelection){
        case 1: 
            remoteOpenDoor();
            break; 
        case 2:
            cardsInSystem(&cardList);
            break; 
        case 3: 
            manageAccess(&cardList); 
            break;
        case 4: 
            return false; 
            break; 
        case 5: 
            inputCardDetails(&cardList); 
            break; 
        case 9:
            testAccess(&cardList);
            break; 
        default: 
            puts("Invalid input, try again"); 
            break; 
        }
    }

return 0; 
}
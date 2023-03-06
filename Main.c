/*


Menu goes here


*/
#include <stdio.h>
#include <stdbool.h>
#include "menu.h"
#include "doorControl.h"
#include "cardManaging.h"

int main(){
    while(true){
        int menuSelection = showMenu(); 

        switch(menuSelection){
        case 1: 
            remoteOpenDoor();
            break; 
        case 2:
            cardsInSystem();
            break; 
        case 3: 
            //manageAccess(); 
            break;
        case 4: 
            return false; 
            break; 
        case 9:
            //testAccess();
            break; 
        default: 
            puts("Invalid input, try again"); 
            break; 
        }
    }

return 0; 
}
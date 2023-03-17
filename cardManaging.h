#ifndef _CARDMANAGING_
#define _CARDMANAGING_
#include <stdbool.h>

int cardsInSystem(); 
int manageAccess(); 
int inputCardDetails(); 
int readCardList(); 
void testAccess(); 

typedef struct{
    int cardNumber; 
    char dateOfRegistration[26]; 
    bool access; 
}Card;

typedef struct{
    Card *cards; 
    int numOfCards; 
} CardsList; 

FILE* file; 

#endif
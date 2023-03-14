#ifndef _CARDMANAGING_
#define _CARDMANAGING_

int cardsInSystem(); 
int manageAccess(); 
int inputCardDetails(); 
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
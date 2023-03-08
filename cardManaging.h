#ifndef _CARDMANAGING_
#define _CARDMANAGING_

int cardsInSystem(); 
void manageAcess(); 
void addCard(); 
void testAcess(); 

typedef struct{
    int cardNumber; 
    char dateOfRegistration[26]; 
    bool access; 
}Card ; 

typedef struct{
    Card *cards; 
    int numOfCards; 
} CardsList; 

#endif
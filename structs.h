#ifndef __CARD_STRUCT_
#define __CARD_STRUCT_
#include <stdbool.h>

FILE *file; 

typedef struct{
    int cardNumber; 
    char dateOfRegistration[26]; 
    bool access; 
}Card;

typedef struct{
    Card *cards; 
    int numOfCards; 
} CardsList;

#endif
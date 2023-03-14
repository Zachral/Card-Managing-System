#include <stdio.h> 

// helper-function to empty stdin 
    void empty_stdin (void) {
    int c = getchar();

    while (c != '\n' && c != EOF)
        c = getchar();
}
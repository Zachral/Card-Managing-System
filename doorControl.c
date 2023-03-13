#include <stdio.h>
#include <time.h>
#include <unistd.h> // Makes sleep() avalible in linux
/*#include <Windows.h> Needs to be uncommented to use sleep() on a Windows device*/

void remoteOpenDoor(){
    puts("CURRENTLY LAMP IS: Green"); 
    sleep(3);
    puts("CURRENTLY LAMP IS: Off");
    sleep(1);
    
}



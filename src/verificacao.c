#include <stdio.h>
#include <ctype.h>

int VerificarSeSoTemLetras(const char *nome){
    while (*nome)
    {
        if(!isalpha(*nome)){
            return 0;
        }
        nome++;
    }
    return 1;
}
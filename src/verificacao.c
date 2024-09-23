#include <stdio.h>
#include <ctype.h>
#include <string.h>

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

int VerificarSeSoTemNumero(char entrada[]){
    for(int cont = 0; cont < strlen(entrada);cont++){
        if(!isdigit(entrada[cont])){
            return 0;
        }
    }
    return 1;
}
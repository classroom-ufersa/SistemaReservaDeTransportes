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

int VerificarData(const char* data) {
    //verifica o tamanho da string (no maximo 10 caracteres)
    if (strlen(data) != 10) {
        return 0;
    }

    //verifica se as barras estao nas posiçoes certas
    if (data[2] != '/' || data[5] != '/') {
        return 0;
    }

    //verifica se os caracteres sao numeros e se estao nas posiçoes certas
    for (int i = 0; i < 10; i++) {
        if (i != 2 && i != 5) { // as posições 2 e 5 sao barras, entao vai ignorar essas posições
            if (!isdigit(data[i])) {
                return 0;
            }
        }
    }

    return 1;
}

int VerificarHora(const char* hora) {
    //verifica se a string tem 5 caracteres (hh:mm)
    if (strlen(hora) != 5) {
        return 0;
    }

    //verifica se os ":" estao na posição 2
    if (hora[2] != ':') {
        return 0;
    }

    //verifica se os outros caracteres sao apenas numeros
    if (!isdigit(hora[0]) || !isdigit(hora[1]) || !isdigit(hora[3]) || !isdigit(hora[4])) {
        return 0;
    }

    return 1;
}


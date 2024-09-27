#ifndef VERIFICACAO_H
#define VERIFICACAO_H

//função que vai verificar se só existe lestras no nome
int VerificarSeSoTemLetras(const char *nome);

//função que vai verificar se só existe numeros 
int VerificarSeSoTemNumero(char entrada[]);

//função para verificar se a data esta sendo escrita corretamente
int VerificarData(const char* data);
#endif
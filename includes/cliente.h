#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estrututa para fazer a reserva do cliente
typedef struct reserva Reserva;

//Estrutura para fazar lista
typedef struct no No;

//Função para criar o primeiro Nó
No * CriarNo(char * NomeSolitante, int Data, int HoraInicio , int HoraTermino , char * Destino);

//Função para ligar um Nó no outro
No * AdicionarCliente(No * lista,char * NomeSolitante, int Data, int HoraInicio , int HoraTermino , char * Destino);
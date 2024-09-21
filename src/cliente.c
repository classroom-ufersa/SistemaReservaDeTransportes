#include "cliente.h"

struct reserva{
    char nome_do_solitante[50];
    int data_de_reserva;
    int horario_de_inicio;
    int horario_de_termino;
    char destino[50];
};

struct no{
    Reserva * reserva;
    struct no * ant;
    struct no  * prox;
};

No * CriarNo(char * NomeSolitante, int Data, int HoraInicio , int HoraTermino , char * Destino){
    No * nova_reserva = (No*) malloc(sizeof(No));
    nova_reserva->reserva = (Reserva*) malloc(sizeof(Reserva));
    if(nova_reserva == NULL){
        printf("Nao existe memoria suficiente!\n");
        exit(1);
    }
    else{
        strcpy(nova_reserva->reserva->nome_do_solitante,NomeSolitante);
        nova_reserva->reserva->data_de_reserva = Data;
        nova_reserva->reserva->horario_de_inicio = HoraInicio;
        nova_reserva->reserva->horario_de_termino = HoraTermino;
        strcpy(nova_reserva->reserva->destino, Destino);
        nova_reserva->prox = NULL;
        nova_reserva->ant = NULL;
    }
    return nova_reserva;
}

No * AdicionarCliente(No * lista,char * NomeSolitante, int Data, int HoraInicio , int HoraTermino , char * Destino){
    No * nova_reserva =  CriarNo(NomeSolitante,Data,HoraInicio,HoraTermino,Destino);
    if(lista == NULL){
        lista = nova_reserva;
    }
    else{
        nova_reserva->prox = lista;
        lista->ant = nova_reserva;
    }
    return nova_reserva;
}


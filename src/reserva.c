#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/reserva.h"
#include "../includes/verificacao.h"

void inicializaListaReserva(ListaReserva* lista) {
    lista->inicio = NULL;
}

Veiculo* criaVeiculo(int codigo, TipoVeiculo tipo, int capacidade, const char* motorista) {
    Veiculo* novoVeiculo = (Veiculo*) malloc(sizeof(Veiculo));
        novoVeiculo->codigo = codigo;
        novoVeiculo->tipo = tipo;
        novoVeiculo->capacidade = capacidade;
        strcpy(novoVeiculo->motorista, motorista);
        novoVeiculo->disponibilidade = 1; // veiculo ja vai vir disponivel por padrão
        novoVeiculo->prox = NULL;
        return novoVeiculo;
}

void adicionarReserva(ListaReserva* lista, Veiculo* listaVeiculos) {
    char nomeSolicitante[50], data[20], horarioInicio[10], horarioTermino[10], destino[100];
        int codigoVeiculo;

            printf("Nome do Cliente: ");
             scanf(" %[^\n]", nomeSolicitante);
             if(!VerificarSeSoTemLetras(nomeSolicitante)){
                printf("Nome invalido.Digite novamente!");
             }
            printf("Data (dd/mm/aaaa): ");
            scanf(" %[^\n]", data);
    
            printf("Horario de inicio (hh:mm): ");
            scanf(" %[^\n]", horarioInicio);
    
            printf("Horario de termino (hh:mm): ");
            scanf(" %[^\n]", horarioTermino);
    
            printf("Destino: ");
            scanf(" %[^\n]", destino);
    
            printf("Codigo do veiculo para reservar: ");
            scanf("%d", &codigoVeiculo);

    // verifica se o veiculos está disponivel para a reserva
    Veiculo* veiculoEscolhido = NULL;
    Veiculo* atual = listaVeiculos;
        while (atual != NULL) {
             if (atual->codigo == codigoVeiculo && atual->disponibilidade == 1) {
            veiculoEscolhido = atual;
            break;
        }
        atual = atual->prox;
    }

    if (veiculoEscolhido == NULL) {
        printf("O Veiculo solicitado nao esta disponivel ou nao foi encontrado!\n");
        return;
    }

    Reserva* novaReserva = (Reserva*) malloc(sizeof(Reserva));
    strcpy(novaReserva->nomeSolicitante, nomeSolicitante);
    strcpy(novaReserva->data, data);
    strcpy(novaReserva->horarioInicio, horarioInicio);
    strcpy(novaReserva->horarioTermino, horarioTermino);
    strcpy(novaReserva->destino, destino);
    novaReserva->veiculoAssociado = veiculoEscolhido;
    novaReserva->prox = lista->inicio; // Inserir no início da lista
    lista->inicio = novaReserva;

    // quando escolher o veiculo vai marcar como indisponivel
    veiculoEscolhido->disponibilidade = 0;

    printf("Reserva adicionada com sucesso!\n");
}

void excluirReserva(ListaReserva* lista, const char* nomeSolicitante) {
    Reserva *atual = lista->inicio;
    Reserva *anterior = NULL;

    // laço para percorrer a lista para encontrar a reserva desejada
    while (atual != NULL) {
        if (strcmp(atual->nomeSolicitante, nomeSolicitante) == 0) {
            // verifica se a reserva foi encontrada

            // verifica se foi o primeiro nó (cabeça da lista)
            if (anterior == NULL) {
                lista->inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }

            // atualizar o veiculo associdado como disponivel agora
            if (atual->veiculoAssociado != NULL) {
                atual->veiculoAssociado->disponibilidade = 1;
            }

            // liberar a memória que foi alocada para a reserva
            free(atual);

            printf("a Reserva excluida com sucesso!\n");
            return;
        }

        // avança para o próximo nó
        anterior = atual;
        atual = atual->prox;
    }

    printf("a Reserva nao encontrada!\n");
}
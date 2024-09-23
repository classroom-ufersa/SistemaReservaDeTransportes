#include <stdio.h>
#include <stdlib.h>
#include "../includes/verificacao.h"

int main(void)
{
    char opcao[10];

    int opcaoint;
    do
    {
        printf("\n|Bem Vindo ao Nosso Sistema de Reserva de Transportes!|\n");
        printf("1.Adicionar Reserva\n");
        printf("2.Excluir Reserva\n");
        printf("3.Listar Reserva\n");
        printf("4.Buscar Reserva Por Solicitante\n");
        printf("5.Editar Dados Da Reserva\n");
        printf("6.Consultar Veículos Disponíveis\n");
        printf("7.Consultar Quantitativo De Reserva\n");
        printf("8.Sair\n");
        scanf("%s", opcao);
        if (!VerificarSeSoTemNumero(opcao))
        {
            printf("apenas numeros!");
            opcaoint = 10;
        }
        else
        {
            opcaoint = atoi(opcao);
        }
        switch (opcaoint)
        {
        case 8:
            printf("Saindo...\n");
            break;
        default:
            printf("Valor Invalido\n");
            break;
        }
    } while (opcaoint != 8);
}
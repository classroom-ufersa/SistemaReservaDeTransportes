#include <stdio.h>
#include <stdlib.h>
#include "../includes/reserva.h"
#include "../includes/verificacao.h"

int main(void){
    ListaReserva *reserva = (ListaReserva*) malloc(sizeof(ListaReserva*));
    Veiculo * veiculo =  NULL;
    inicializaListaReserva(reserva); 
    
    char opcao[10];

    int opcaoint;
    do
    {
        printf("\n|Bem Vindo ao Nosso Sistema de Reserva de Transportes!|\n");
        printf("1.Adicionar Reserva\n");
        printf("2.Excluir Reserva\n");
        printf("3.Listar Reserva\n");
        printf("4.Buscar Reserva Por Cliente\n");
        printf("5.Editar Dados Da Reserva\n");
        printf("6.Consultar Veiculos Disponiveis\n");
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
        case 1:
            adicionarReserva(reserva, &veiculo);
            break;

        case 2:
        {
            char nomeCliente[50];
            printf("Digite o nome do solicitante da reserva que deseja excluir: ");
            scanf(" %[^\n]", nomeCliente);
            excluirReserva(reserva, nomeCliente);
            break;
        }

        case 3:
            listarReservas(reserva);
            break;

        case 4:
        {
            char nomeCliente[50];
            printf("Digite o nome do cliente para buscar a reserva: ");
            scanf(" %[^\n]", nomeCliente);
            buscarReservaPorCliente(reserva, nomeCliente);
            break;
        }

        case 5:
        {
            char nomeCliente[50];
            printf("Digite o nome do cliente da reserva que deseja editar: ");
            scanf(" %[^\n]", nomeCliente);
            editarReserva(reserva, veiculo, nomeCliente);
            break;
        }

        case 6:
            consultarVeiculosDisponiveis(veiculo);
            break;

        case 7:
            consultarQuantitativoReservas(reserva);
            break;

        case 8:
            sair(reserva, veiculo);
            break;

        default:
            printf("Valor Invalido\n");
            break;
        }

    } while (opcaoint != 8);

    return 0;
 
}
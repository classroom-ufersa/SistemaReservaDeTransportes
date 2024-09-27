#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/reserva.h"
#include "../includes/verificacao.h"

struct Veiculo {
    int codigo;
    TipoVeiculo tipo;
    int disponibilidade; // se = 1 veiculo disponível ,se = 0 veiculos indisponível
    int capacidade;
    char motorista[50];
    struct Veiculo* prox;
};

struct Reserva {
    char nomeCliente[50];
    char data[20];
    char horarioInicio[10];
    char horarioTermino[10];
    char destino[100];
    Veiculo* veiculoAssociado;
    struct Reserva* prox;
};

struct ListaReserva{
    Reserva* inicio;
};

void inicializaListaReserva(ListaReserva* lista) {
    lista->inicio = NULL;
}

void inicializaVeiculos(Veiculo** listaVeiculos) {
    Veiculo* veiculo1 = criaVeiculo(1, ONIBUS, 50, "Motorista 1");
    adicionarVeiculo(listaVeiculos, veiculo1);

    Veiculo* veiculo2 = criaVeiculo(2, VAN, 15, "Motorista 2");
    adicionarVeiculo(listaVeiculos, veiculo2);

    Veiculo* veiculo3 = criaVeiculo(3, PICKUP, 10, "Motorista 3");
    adicionarVeiculo(listaVeiculos, veiculo3);

    Veiculo* veiculo4 = criaVeiculo(4, CARRO_CONVENCIONAL, 5, "Motorista 4");
    adicionarVeiculo(listaVeiculos, veiculo4);

    printf("Todos os Veiculos estao disponiveis!\n");
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

void adicionarVeiculo(Veiculo** listaVeiculos, Veiculo* novoVeiculo) {
    novoVeiculo->prox = *listaVeiculos;  
    *listaVeiculos = novoVeiculo;        
}

void adicionarReserva(ListaReserva* lista, Veiculo** listaVeiculos) {

    char nomeCliente[50], data[20], horarioInicio[10], horarioTermino[10], destino[100];
        int codigoVeiculo;
        TipoVeiculo tipoVeiculo;
            do{ 
            printf("Nome do Cliente: ");
             scanf(" %[^\n]", nomeCliente);
             if(!VerificarSeSoTemLetras(nomeCliente)){
                printf("\nERROR! O nome so deve conter letras. Digite novamente!\n");
             }
            }while(!VerificarSeSoTemLetras(nomeCliente));
            do{
            printf("Data (dd/mm/aaaa): ");
            scanf(" %[^\n]", data);
            if (!VerificarData(data)) {
            printf("Data invalida! Deve estar no formato dd/mm/aaaa. Digite novamente.\n");
            }
            } while (!VerificarData(data));
               do {
            printf("Horario de inicio (hh:mm): ");
            scanf(" %[^\n]", horarioInicio);
            if (!VerificarHora(horarioInicio)) {
            printf("Horario invalido! Deve estar no formato hh:mm. Digite novamente.\n");
             }
             } while (!VerificarHora(horarioInicio));
            do {
            printf("Horario de termino (hh:mm): ");
             scanf(" %[^\n]", horarioTermino);
            if (!VerificarHora(horarioTermino)) {
            printf("Horario invalido! Deve estar no formato hh:mm. Digite novamente.\n");
             }
             } while (!VerificarHora(horarioTermino));
            do{ 
            printf("Destino: ");
            scanf(" %[^\n]", destino);
            if(!VerificarSeSoTemLetras(destino)){
                printf("O destino so deve conter letras!\n");
            }
            }while(!VerificarSeSoTemLetras(destino));
            do{ 
            printf("Qual veiculo deseja reservar?:\n");
            printf("1.Onibus\n");
            printf("2.Van\n");
            printf("3.Pickup\n");
            printf("4.Carro Convencional\n");
            printf("Escolha: ");
            scanf("%d", &codigoVeiculo);
            switch (codigoVeiculo) {
            case 1:
            tipoVeiculo = ONIBUS;  // Define o tipo de veículo selecionado
                        break;
            case 2:
            tipoVeiculo = VAN;
                        break;
            case 3:
            tipoVeiculo = PICKUP;
                        break;
            case 4:
            tipoVeiculo = CARRO_CONVENCIONAL;
                        break;
            default:
            printf("Codigo invalido!\n");
            continue;
}
            }while(codigoVeiculo < 1 || codigoVeiculo > 4);

    // verifica se o veiculos está disponivel para a reserva
    Veiculo * veiculoEscolhido = NULL;
    Veiculo * veiculoAtual = *listaVeiculos;
    printf("Lista de veiculos:\n");
    while (veiculoAtual != NULL) {
        printf("Codigo: %d, Disponibilidade: %d\n", veiculoAtual->codigo, veiculoAtual->disponibilidade);
        veiculoAtual = veiculoAtual->prox;
    }

    // Verifica se o veículo está disponível para a reserva
    veiculoAtual = *listaVeiculos;

    while (veiculoAtual != NULL) {
    if (veiculoAtual->tipo == tipoVeiculo && veiculoAtual->disponibilidade == 1) {
        veiculoEscolhido = veiculoAtual; 
        break;
    }
    veiculoAtual = veiculoAtual->prox;
}

    if (veiculoEscolhido == NULL) {
        printf("\no Veiculo solicitado nao foi encontrado ou nao esta disponivel!\n");
        return;
    }
    Reserva* novaReserva = (Reserva*) malloc(sizeof(Reserva));
    if (novaReserva == NULL){
        printf("a Memoria nao foi alocada!\n");
    }
    
    strcpy(novaReserva->nomeCliente, nomeCliente);
    strcpy(novaReserva->data, data);
    strcpy(novaReserva->horarioInicio, horarioInicio);
    strcpy(novaReserva->horarioTermino, horarioTermino);
    strcpy(novaReserva->destino, destino);
    novaReserva->veiculoAssociado = veiculoEscolhido;
    novaReserva->prox = lista->inicio; // Inserir no início da lista
    lista->inicio = novaReserva;

    // quando escolher o veiculo vai marcar como indisponivel
    veiculoEscolhido->disponibilidade = 0;

    printf("\nReserva adicionada com sucesso!\n");
}

void excluirReserva(ListaReserva* lista, const char* nomeCliente) {
    Reserva *atual = lista->inicio;
    Reserva *anterior = NULL;

    // laço para percorrer a lista para encontrar a reserva desejada
    while (atual != NULL) {
        if (strcmp(atual->nomeCliente, nomeCliente) == 0) {
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

// converter o tipo de veículo escolhido para string
const char* tipoVeiculoParaString(TipoVeiculo tipo) {
    switch (tipo) {
        case ONIBUS: return "Onibus";
        case VAN: return "Van";
        case PICKUP: return "Pickup";
        case CARRO_CONVENCIONAL: return "Carro Convencional";
        default: return "Desconhecido";
    }
}

void listarReservas(ListaReserva* lista) {
    Reserva* atual = lista->inicio;

    if (atual == NULL) {
        printf("Nao ha reservas cadastradas.\n");
        return;
    }

    printf("~~~~~ Lista de Reservas ~~~~~~\n");
    while (atual != NULL) {
        printf("Nome do Cliente: %s\n", atual->nomeCliente);
        printf("Data da reserva: %s\n", atual->data);
        printf("Horario de inicio: %s\n", atual->horarioInicio);
        printf("Horario de termino: %s\n", atual->horarioTermino);
        printf("Destino: %s\n", atual->destino);
        
        if (atual->veiculoAssociado != NULL) {
            printf("Veiculo associado: %s (Codigo: %d)\n", 
                tipoVeiculoParaString(atual->veiculoAssociado->tipo), 
                atual->veiculoAssociado->codigo);
        } else {
            printf("Nenhum veiculo associado.\n");
        }

        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        atual = atual->prox;
    }
}

void buscarReservaPorCliente(ListaReserva* lista, const char* nomeCliente) {
    Reserva* atual = lista->inicio;

    while (atual != NULL) {
        if (strcmp(atual->nomeCliente, nomeCliente) == 0) {
            printf("Reserva encontrada:\n");
            printf("Nome do Cliente: %s\n", atual->nomeCliente);
            printf("Data da reserva: %s\n", atual->data);
            printf("Horario de inicio: %s\n", atual->horarioInicio);
            printf("Horario de termino: %s\n", atual->horarioTermino);
            printf("Destino: %s\n", atual->destino);
            
            if (atual->veiculoAssociado != NULL) {
                printf("Veiculo associado: %s (Codigo: %d)\n", 
                    tipoVeiculoParaString(atual->veiculoAssociado->tipo), 
                    atual->veiculoAssociado->codigo);
            } else {
                printf("\nNenhum veiculo associado.\n");
            }

            return;
        }
        atual = atual->prox;
    }

    printf("\na Reserva nao foi encontrada para o solicitante: %s\n", nomeCliente);
}

void editarReserva(ListaReserva* lista, Veiculo* listaVeiculos, const char* nomeCliente) {
    Reserva* atual = lista->inicio;

    while (atual != NULL) {
        if (strcmp(atual->nomeCliente, nomeCliente) == 0) {
            int opcao;
            printf("a Reserva foi encontrada, o que deseja editar?\n");
            printf("1. Nome do Cliente\n");
            printf("2. Data\n");
            printf("3. Horario de inicio\n");
            printf("4. Horario de termino\n");
            printf("5. Destino\n");
            printf("6. Veiculo associado\n");
            printf("Digite sua opcao: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    do{ 
                    printf("Novo nome do Cliente: ");
                    scanf(" %[^\n]", atual->nomeCliente);
                    if(!VerificarSeSoTemLetras(atual->nomeCliente)){
                        printf("Nome invalido. Digite novamente!\n");
                    }
                    }while(!VerificarSeSoTemLetras(atual->nomeCliente));
                    break;
                case 2:
                    printf("Nova data (dd/mm/aaaa): ");
                    scanf(" %[^\n]", atual->data);
                    break;
                case 3:
                    printf("Novo horario de inicio (hh:mm): ");
                    scanf(" %[^\n]", atual->horarioInicio);
                    break;
                case 4:
                    printf("Novo horario de termino (hh:mm): ");
                    scanf(" %[^\n]", atual->horarioTermino);
                    break;
                case 5:
                    do{ 
                    printf("Novo destino: ");
                    scanf(" %[^\n]", atual->destino);
                    if (!VerificarSeSoTemLetras(atual->destino)){
                        printf("Apenas letras!\n");
                    }
                    
                    }while(!VerificarSeSoTemLetras(atual->destino));
                    break;
                case 6: {
                    int codigoVeiculo;
                    printf("Codigo do novo veiculo: ");
                    scanf("%d", &codigoVeiculo);
                    Veiculo* novoVeiculo = NULL;
                    Veiculo* veiculoAtual = listaVeiculos;
                    while (veiculoAtual != NULL) {
                        if (veiculoAtual->codigo == codigoVeiculo && veiculoAtual->disponibilidade == 1) {
                            novoVeiculo = veiculoAtual;
                            break;
                        }
                        veiculoAtual = veiculoAtual->prox;
                    }

                    if (novoVeiculo != NULL) {
                        if (atual->veiculoAssociado != NULL) {
                            atual->veiculoAssociado->disponibilidade = 1;
                        }
                        atual->veiculoAssociado = novoVeiculo;
                        novoVeiculo->disponibilidade = 0;
                        printf("Veiculo atualizado com sucesso.\n");
                    } else {
                        printf("o Veiculo nao esta disponivel.\n");
                    }
                    break;
                }
                default:
                    printf("Opcao invalida!\n");
            }

            printf("os Dados da reserva foram atualizados!\n");
            return;
        }

        atual = atual->prox;
    }

    printf("a Reserva nao foi encontrada para o cliente: %s\n", nomeCliente);
}

void consultarVeiculosDisponiveis(Veiculo* listaVeiculos) {
    Veiculo* atual = listaVeiculos;

    printf("---- Veiculos Disponíveis ----\n");
    while (atual != NULL) {
        if (atual->disponibilidade == 1) {
            printf("Codigo do Veiculo: %d\n", atual->codigo);
            printf("Tipo: %s\n", tipoVeiculoParaString(atual->tipo));
            printf("Capacidade: %d\n", atual->capacidade);
            printf("Motorista: %s\n", atual->motorista);
            printf("-----------------------------\n");
        }
        atual = atual->prox;
    }

    printf("Nao ha mais veiculos disponiveis.\n");
}

void consultarQuantitativoReservas(ListaReserva* lista) {
    int totalReservas = 0;
    int onibus = 0, van = 0, pickup = 0, carroConvencional = 0;
    Reserva* atual = lista->inicio;

    while (atual != NULL) {
        totalReservas++;

        if (atual->veiculoAssociado != NULL) {
            switch (atual->veiculoAssociado->tipo) {
                case ONIBUS: onibus++; 
                break;

                case VAN: van++; 
                break;

                case PICKUP: pickup++; 
                break;

                case CARRO_CONVENCIONAL: carroConvencional++; 
                break;
            }
        }

        atual = atual->prox;
    }
    printf("~~~~ Quantitativo de Reservas ~~~~\n");
    printf("Total de reservas: %d\n", totalReservas);
    printf("Onibus: %d\n", onibus);
    printf("Van: %d\n", van);
    printf("Pickup: %d\n", pickup);
    printf("Carro Convencional: %d\n", carroConvencional);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void liberarListaReservas(ListaReserva* lista) {
    Reserva* atual = lista->inicio;
    Reserva* proximo;
    
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}

void liberarListaVeiculos(Veiculo* listaVeiculos) {
    Veiculo* atual = listaVeiculos;
    Veiculo* proximo;
    
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}

void sair(ListaReserva* lista, Veiculo* listaVeiculos) {
    liberarListaReservas(lista);
    liberarListaVeiculos(listaVeiculos);
    printf("Memoria liberada!.\n");
    exit(0); 
}
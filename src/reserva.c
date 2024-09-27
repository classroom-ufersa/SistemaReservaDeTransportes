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

void adicionarReserva(ListaReserva* lista, Veiculo** listaVeiculos) {

    char nomeCliente[50], data[20], horarioInicio[10], horarioTermino[10], destino[100];
        int codigoVeiculo;
        TipoVeiculo tipoVeiculo;
            do{ 
            printf("Nome do Cliente: ");
             scanf(" %[^\n]", nomeCliente);
             if(!VerificarSeSoTemLetras(nomeCliente)){
                printf("Nome invalido.Digite novamente!\n");
             }
            }while(!VerificarSeSoTemLetras(nomeCliente));
            printf("Data (dd/mm/aaaa): ");
            scanf(" %[^\n]", data);
    
            printf("Horario de inicio (hh:mm): ");
            scanf(" %[^\n]", horarioInicio);
    
            printf("Horario de termino (hh:mm): ");
            scanf(" %[^\n]", horarioTermino);
            do{ 
            printf("Destino: ");
            scanf(" %[^\n]", destino);
            if(!VerificarSeSoTemLetras(destino)){
                printf("So deve ter letras!\n");
            }
            }while(!VerificarSeSoTemLetras(destino));
            do{ 
            printf("Codigo do veiculo para reservar:\n");
            printf("1.Onibus\n");
            printf("2.Van\n");
            printf("3.Pickup\n");
            printf("4.Carro Convencional\n");
            printf("Escolha: ");
            scanf("%d", &codigoVeiculo);
            switch (codigoVeiculo){
            case 1:
                tipoVeiculo = ONIBUS;
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
    printf("Lista de veículos:\n");
    while (veiculoAtual != NULL) {
        printf("Código: %d, Disponibilidade: %d\n", veiculoAtual->codigo, veiculoAtual->disponibilidade);
        veiculoAtual = veiculoAtual->prox;
    }

    // Verifica se o veículo está disponível para a reserva
    veiculoAtual = *listaVeiculos;

    while (veiculoAtual != NULL) {
        if (veiculoAtual->codigo == codigoVeiculo && veiculoAtual->disponibilidade == 1) {
            veiculoEscolhido = veiculoAtual;
            break;
        }
        veiculoAtual = veiculoAtual->prox;
    }

    if (veiculoEscolhido == NULL) {
        printf("Veículo solicitado não foi encontrado ou não está disponível!\n");
        return;
    }
    Reserva* novaReserva = (Reserva*) malloc(sizeof(Reserva));
    if (novaReserva == NULL){
        printf("menmoria nao alocada!\n");
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

    printf("Reserva adicionada com sucesso!\n");
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
        case ONIBUS: return "Ônibus";
        case VAN: return "Van";
        case PICKUP: return "Pickup";
        case CARRO_CONVENCIONAL: return "Carro Convencional";
        default: return "Desconhecido";
    }
}

void listarReservas(ListaReserva* lista) {
    Reserva* atual = lista->inicio;

    if (atual == NULL) {
        printf("Não há reservas cadastradas.\n");
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
            printf("Veículo associado: %s (Código: %d)\n", 
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
                printf("Veículo associado: %s (Código: %d)\n", 
                    tipoVeiculoParaString(atual->veiculoAssociado->tipo), 
                    atual->veiculoAssociado->codigo);
            } else {
                printf("Nenhum veiculo associado.\n");
            }

            return;
        }
        atual = atual->prox;
    }

    printf("a Reserva nao foi encontrada para o solicitante: %s\n", nomeCliente);
}

void editarReserva(ListaReserva* lista, Veiculo* listaVeiculos, const char* nomeCliente) {
    Reserva* atual = lista->inicio;

    while (atual != NULL) {
        if (strcmp(atual->nomeCliente, nomeCliente) == 0) {
            int opcao;
            printf("a Reserva foi encontrada, o que vai editar?\n");
            printf("1. Nome do Cliente\n");
            printf("2. Data\n");
            printf("3. Horário de inicio\n");
            printf("4. Horário de termino\n");
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
                        printf("Nome invalido.Digite novamente!\n");
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

    printf("---- Veículos Disponíveis ----\n");
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
    printf("Ônibus: %d\n", onibus);
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
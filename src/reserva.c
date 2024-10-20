#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

    FILE *arquivo = fopen("../data/veiculos.txt", "rt");
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
    }

    int codigo; TipoVeiculo tipo; int capacidade; char motorista[50];

    while (fscanf(arquivo,"%d\t%u\t%d\t%[^\n]",&codigo,&tipo,&capacidade,motorista) != EOF){
        Veiculo *aux = criaVeiculo(codigo,tipo,capacidade,motorista);
        adicionarVeiculo(listaVeiculos, aux);
    }

    fclose(arquivo);
}

Veiculo* criaVeiculo(int codigo, TipoVeiculo tipo, int capacidade, char* motorista) {
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
            printf("Nome do Cliente: \n");
             scanf(" %[^\n]", nomeCliente);
             if(!VerificarSeSoTemLetras(nomeCliente)){
                printf("\nERROR! O nome so deve conter letras. Digite novamente!\n");
             }
            }while(!VerificarSeSoTemLetras(nomeCliente));

            converterParaMaiuscula(nomeCliente);

            do{
            printf("Data (dd/mm/aaaa): \n");
            scanf(" %[^\n]", data);
            if (!VerificarData(data)) {
            printf("\nData invalida! Deve estar no formato dd/mm/aaaa. Digite novamente.\n");
            }
            } while (!VerificarData(data));
            do {
                printf("Horario de inicio (hh:mm): ");
                scanf(" %[^\n]", horarioInicio);
                if (!VerificarHora(horarioInicio)) {
                printf("\nHorario invalido! Deve estar no formato hh:mm. Digite novamente.\n");
                }
                } while (!VerificarHora(horarioInicio));

                int minutosInicio, minutosTermino;

            do {
                printf("Horario de termino (hh:mm): ");
                scanf(" %[^\n]", horarioTermino);
                if (!VerificarHora(horarioTermino)) {
                printf("\nHorario invalido! Deve estar no formato hh:mm. Digite novamente.\n");
                } else {
                minutosInicio = converteHoraParaMinutos(horarioInicio);
                minutosTermino = converteHoraParaMinutos(horarioTermino);
                if (minutosTermino <= minutosInicio) {
                printf("\nErro! O horario de termino deve ser maior que o horario de inicio. Tente novamente.\n");
                }
            }
            } while (!VerificarHora(horarioTermino) || minutosTermino <= minutosInicio);

            do{ 
            printf("Destino: \n");
            scanf(" %[^\n]", destino);
            if(!VerificarSeSoTemLetras(destino)){
                printf("\nO destino so deve conter letras!\n");
            }
            }while(!VerificarSeSoTemLetras(destino));
 
    // verifica se o veiculos está disponivel para a reserva
 Veiculo* veiculoEscolhido = NULL;
    do {
        printf("Qual veiculo deseja reservar?:\n");
        printf("1.Onibus\n");
        printf("2.Van\n");
        printf("3.Pickup\n");
        printf("4.Carro Convencional\n");
        printf("Escolha: ");
        scanf("%d", &codigoVeiculo);

        switch (codigoVeiculo) {
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
                continue; //fica em loop se a escolha for invalida
        }

        Veiculo* veiculoAtual = *listaVeiculos;
        //percorre para ver se ha veiculo do tipo escolhido disponivel
        while (veiculoAtual != NULL) {
            if (veiculoAtual->tipo == tipoVeiculo && veiculoAtual->disponibilidade == 1) {
                veiculoEscolhido = veiculoAtual; 
                break;
            }
            veiculoAtual = veiculoAtual->prox;
        }

        if (veiculoEscolhido == NULL) {
            printf("\nO Veiculo solicitado nao foi encontrado ou nao esta disponivel!\n");
        }

    } while (veiculoEscolhido == NULL); 

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

    FILE * arquivo = fopen("../data/reservas.txt","a");
    if(arquivo == NULL){
        printf("Erro ao abrir arquivo!\n");
    }
    fprintf(arquivo, "~~~~~~~~~~~~~~Cliente~~~~~~~~~~~~~~\n");
    fprintf(arquivo, "Nome do cliente: %s\n",nomeCliente);
    fprintf(arquivo, "Data: %s\n",data);
    fprintf(arquivo, "Hora de inicio: %s\n",horarioInicio);
    fprintf(arquivo, "Hora de termino: %s\n",horarioTermino);
    fprintf(arquivo, "Destino: %s\n",destino);
    fprintf(arquivo, "Veiculo reservado: %d\n",codigoVeiculo);
    fprintf(arquivo, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    fclose(arquivo);

    limpaTela();

    printf("\nReserva adicionada com sucesso!\n");
}

void excluirReserva(ListaReserva* lista, char* nomeCliente) {
    Reserva *atual = lista->inicio;
    Reserva *anterior = NULL;
    int reservaEncontrada = 0;

    char nomeClienteMaiusculo[50];
    strcpy(nomeClienteMaiusculo, nomeCliente);
    converterParaMaiuscula(nomeClienteMaiusculo);

    // laço que vai percorrer a lista para encontrar a reserva desejada
    while (atual != NULL) {

        char nomeAtualMaiusculo[50];
        strcpy(nomeAtualMaiusculo, atual->nomeCliente);
        converterParaMaiuscula(nomeAtualMaiusculo);

        if (strcmp(nomeAtualMaiusculo, nomeClienteMaiusculo) == 0) {
            // verifica se a reserva foi encontrada
            if (anterior == NULL) {
                lista->inicio = atual->prox; // se for o primeiro nó
            } else {
                anterior->prox = atual->prox; // remove o nó atual
            }


            // atualiza o veiculo associado como disponível
            if (atual->veiculoAssociado != NULL) {
                atual->veiculoAssociado->disponibilidade = 1;
            }

            // libera a memoria alocada para a reserva
            free(atual);
            reservaEncontrada = 1;
            break; 
        }

        // avança para o próximo nó
        anterior = atual;
        atual = atual->prox;
    }

    if (!reservaEncontrada) {
        printf("A reserva nao foi encontrada!\n");
        return;
    }

    // abre o arquivo de reservas para leitura e cria um arquivo temporário para escrita
    FILE *arquivoOriginal = fopen("../data/reservas.txt", "r");
    FILE *arquivotemp = fopen("../data/reservas_temp.txt", "w"); 

    if (arquivoOriginal == NULL || arquivotemp == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    char linha[256];
    int ignorar_reserva = 0;

    while (fgets(linha, sizeof(linha), arquivoOriginal)) {
       // vai verificar se a linha é o início de uma nova reserva
    if (strncmp(linha, "~~~~~~~~~~~~~~Cliente~~~~~~~~~~~~~~", 35) == 0) {
        char nomeLinha[256];
        
        fgets(nomeLinha, sizeof(nomeLinha), arquivoOriginal);
        
        // Verifica se o nome do cliente da é o nome da reserva a ser excluída
        if (strstr(nomeLinha, nomeCliente) != NULL) {
            ignorar_reserva = 1; 
        } else {
            
            fputs(linha, arquivotemp);
            fputs(nomeLinha, arquivotemp);
        }
    } else if (ignorar_reserva) {
        
        //Verifica se a linha marca o final da reserva
        if (strncmp(linha, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", 37) == 0) {
            ignorar_reserva = 0; 
        }
        
    } else {
        
        fputs(linha, arquivotemp);
    }
}


    fclose(arquivoOriginal);
    fclose(arquivotemp);

    // Remover o arquivo original e renomear o temporário
    remove("../data/reservas.txt");
    rename("../data/reservas_temp.txt", "../data/reservas.txt"); // Corrigido para ".txt"

    printf("\nA reserva foi removida!\n");
}

// converter o tipo de veículo escolhido para string
char* tipoVeiculoParaString(TipoVeiculo tipo) {
    switch (tipo) {
        case ONIBUS: return "Onibus";
        case VAN: return "Van";
        case PICKUP: return "Pickup";
        case CARRO_CONVENCIONAL: return "Carro Convencional";
        default: return "Desconhecido";
    }
}

void listarReservas(ListaReserva* lista) {
    FILE *arquivo = fopen("../data/reservas.txt","r");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    char linha[256];
    int linhasLidas = 0;
    //le o arquivo linha por linha até chegar ao fim
    while(fgets(linha, sizeof(linha), arquivo)){
        printf("%s", linha);
        linhasLidas++;
    }

    if(linhasLidas == 0){
        printf("Lista esta vazia!\n");
    }
    fclose(arquivo);
}

void buscarReservaPorCliente(ListaReserva* lista, char* nomeCliente) {
    // abrir arquivo, modo leitura 
    FILE *arquivo = fopen("../data/reservas.txt", "r");
    //verificar se o arquivo foi aberto com sucesso 
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }
    //para um novo nó da lista
    Reserva * novaReserva;
    int encontrado = 0; 

    //loop até chegar ao final do arquivo
    while (!feof(arquivo)) {
        //alocar espaço a cada linha 
        novaReserva = (Reserva*) malloc(sizeof(Reserva));
        //fazendo a leitura do arquivo 
        fscanf(arquivo, "%s %s %s %s %s", 
            novaReserva->nomeCliente, 
            novaReserva->data, 
            novaReserva->horarioInicio, 
            novaReserva->horarioTermino, 
            novaReserva->destino);
        //inciado com null pois ainda não tem informação de veiculos 
        novaReserva->veiculoAssociado = NULL; 
        //inseri a nova reserva no inicio da lista 
        novaReserva->prox = lista->inicio;
        lista->inicio = novaReserva;
    }
    fclose(arquivo);

    //converter a primeira letra para maiusculo
     char nomeClienteMaiusculo[50];
    strcpy(nomeClienteMaiusculo, nomeCliente);
    converterParaMaiuscula(nomeClienteMaiusculo);

    Reserva* atual = lista->inicio;
    //pecorre a lista de reserva do inicio
    while (atual != NULL) {
        //converte o nome atual para maiuscula
        char nomeSalvoMaisuculo[50];
        strcpy(nomeSalvoMaisuculo, atual->nomeCliente);
        converterParaMaiuscula(nomeSalvoMaisuculo);

        
        //comparar o nome do cliente 
        if (strcmp(nomeSalvoMaisuculo, nomeClienteMaiusculo) == 0) {
            printf("Reserva encontrada:\n");
            printf("Nome do Cliente: %s\n", atual->nomeCliente);
            printf("Data da reserva: %s\n", atual->data);
            printf("Horario de inicio: %s\n", atual->horarioInicio);
            printf("Horario de termino: %s\n", atual->horarioTermino);
            printf("Destino: %s\n", atual->destino);
            //informção do veiculos associados
            if (atual->veiculoAssociado != NULL) {
                printf("Veiculo associado: %s (Codigo: %d)\n", 
                    tipoVeiculoParaString(atual->veiculoAssociado->tipo), 
                    atual->veiculoAssociado->codigo);
            } else {
                printf("Nenhum veiculo associado.\n");
            }

            encontrado = 1;
            break; 
        }
        //movendo para o proximo reserva da lista 
        atual = atual->prox;
    }

    if (!encontrado) {
        printf("\nA reserva nao foi encontrada para o solicitante: %s\n", nomeCliente);
    }
}
void salvarDepoisDeEditado(ListaReserva * lista){
    //modo escrita
    FILE *arquivo = fopen("../data/reservas.txt", "w");
    if(arquivo == NULL){
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }
    //percorre cada elemento da lista
    Reserva * atual = lista->inicio;
    
    while (atual != NULL) {
        //gravando os dados no arquivo 
        fprintf(arquivo, "~~~~~~~~~~~~~~Cliente~~~~~~~~~~~~~~\nNome do Cliente: %s\nData: %s\nHorario de inicio: %s\nHorario de termino: %s\nDestino: %s\n", 
                atual->nomeCliente, 
                atual->data, 
                atual->horarioInicio, 
                atual->horarioTermino, 
                atual->destino);

        if (atual->veiculoAssociado != NULL) {
            fprintf(arquivo, "Veiculo: %u (Codigo: %d)\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", 
                    atual->veiculoAssociado->tipo, 
                    atual->veiculoAssociado->codigo);
        } else {
            fprintf(arquivo, "Veiculo: Nenhum associado\n");
        }
        //mover ponterio para proximo nó da lista
        atual = atual->prox;
    }

    fclose(arquivo); 
}
void editarReserva(ListaReserva* lista, Veiculo* listaVeiculos, char* nomeCliente) {
    Reserva* atual = lista->inicio;
    
    // Converte o nome do cliente para maiúsculas
    char nomeClienteMaiusculo[50];
    strcpy(nomeClienteMaiusculo, nomeCliente);
    converterParaMaiuscula(nomeClienteMaiusculo);

    while (atual != NULL) {
        char nomeAtualMaiusculo[50];
        strcpy(nomeAtualMaiusculo, atual->nomeCliente);
        converterParaMaiuscula(nomeAtualMaiusculo);

        if (strcmp(nomeAtualMaiusculo, nomeClienteMaiusculo) == 0) {
            int opcao;
            printf("A reserva foi encontrada. O que deseja editar?\n");
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
                    do { 
                        printf("Novo nome do Cliente: ");
                        scanf(" %[^\n]", atual->nomeCliente);
                        if (!VerificarSeSoTemLetras(atual->nomeCliente)) {
                            printf("Nome invalido. Digite novamente!\n");
                        }
                    } while (!VerificarSeSoTemLetras(atual->nomeCliente));
                    // Converte o novo nome do cliente para maiúsculas
                    converterParaMaiuscula(atual->nomeCliente);
                    break;

                case 2:
                    do {
                        printf("Nova data (dd/mm/aaaa): ");
                        scanf(" %[^\n]", atual->data);
                        if (!VerificarData(atual->data)) {
                            printf("Data invalida! Deve estar no formato dd/mm/aaaa. Digite novamente.\n");
                        }
                    } while (!VerificarData(atual->data));
                    break;

                case 3:
                    do {
                        printf("Novo horario de inicio (hh:mm): ");
                        scanf(" %[^\n]", atual->horarioInicio);
                        if (!VerificarHora(atual->horarioInicio)) {
                            printf("Horario invalido! Deve estar no formato hh:mm. Digite novamente.\n");
                        }
                    } while (!VerificarHora(atual->horarioInicio));
                    break;

                case 4:
                    do {
                        printf("Horario de termino (hh:mm): ");
                        scanf(" %[^\n]", atual->horarioTermino);
                        if (!VerificarHora(atual->horarioTermino)) {
                            printf("Horario invalido! Deve estar no formato hh:mm. Digite novamente.\n");
                        }
                    } while (!VerificarHora(atual->horarioTermino));
                    break;

                case 5:
                    do { 
                        printf("Novo destino: ");
                        scanf(" %[^\n]", atual->destino);
                        if (!VerificarSeSoTemLetras(atual->destino)) {
                            printf("Apenas letras!\n");
                        }
                    } while (!VerificarSeSoTemLetras(atual->destino));
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
                        printf("O veiculo nao esta disponivel.\n");
                    }
                    break;
                }

                default:
                    printf("Opcao invalida!\n");
            }

            salvarDepoisDeEditado(lista);
            printf("Os dados da reserva foram atualizados!\n");
            return;
        }
        // Move para o próximo nó da lista
        atual = atual->prox;
    }

    printf("A reserva nao foi encontrada para o cliente: %s\n", nomeCliente);
}


void consultarVeiculosDisponiveis(Veiculo* listaVeiculos) {
    //aux para perorrer a lista 
    Veiculo* atual = listaVeiculos;

    printf("~~~~ Veiculos Disponiveis ~~~~\n");
    while (atual != NULL) {
        if (atual->disponibilidade == 1) {
            printf("Codigo do Veiculo: %d\n", atual->codigo);
            printf("Tipo: %s\n", tipoVeiculoParaString(atual->tipo));
            printf("Capacidade: %d\n", atual->capacidade);
            printf("Motorista: %s\n", atual->motorista);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        }
        //proximo nó da lista
        atual = atual->prox;
    }

    printf("Nao ha mais veiculos disponiveis.\n");
}

void consultarQuantitativoReservas(ListaReserva* lista) {
    int totalReservas = 0;
    int onibus = 0, van = 0, pickup = 0, carroConvencional = 0;
    //aux para percorre a lista do incio
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
        //prox nó da lista
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
    //ponteiro aux para armazenar as referencias ao proximo nó da lista, enquanto o altual está sendo liberado
    Reserva* proximo;
    
    while (atual != NULL) {
        //armazena o ponteiro para o prox nó da lista
        proximo = atual->prox;
        free(atual);
        //proximo nó
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
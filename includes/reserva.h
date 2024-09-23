#ifndef RESERVA_H
#define RESERVA_H

// enum utilizada para os tipos de veiculos
typedef enum {
    ONIBUS,
    VAN,
    PICKUP,
    CARRO_CONVENCIONAL
} TipoVeiculo;

// struct para os tipos de veiculos
typedef struct Veiculo {
    int codigo;
    TipoVeiculo tipo;
    int disponibilidade; // se = 1 veiculo disponível ,se = 0 veiculos indisponível
    int capacidade;
    char motorista[50];
    struct Veiculo* prox;
} Veiculo;

// stuct para a reserva do veiculo
typedef struct Reserva {
    char nomeSolicitante[50];
    char data[20];
    char horarioInicio[10];
    char horarioTermino[10];
    char destino[100];
    Veiculo* veiculoAssociado;
    struct Reserva* prox;
} Reserva;

// lista ecadeada para as reservas
typedef struct {
    Reserva* inicio;
} ListaReserva;

// função para inicializar a lista de reservas
void inicializaListaReserva(ListaReserva* lista);

// função para criar um novo veículo
Veiculo* criaVeiculo(int codigo, TipoVeiculo tipo, int capacidade, const char* motorista);

// função para adicionar uma nova reserva
void adicionarReserva(ListaReserva* lista, Veiculo* listaVeiculos);

//função para remover uma reserva existente
void excluirReserva(ListaReserva* lista, const char* nomeSolicitante);

// função para listar todas as reservas
void listarReservas(ListaReserva* lista);

#endif

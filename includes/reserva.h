#ifndef RESERVA_H
#define RESERVA_H

// enum utilizada para os tipos de veiculos
typedef enum {
    ONIBUS,
    VAN,
    PICKUP,
    CARRO_CONVENCIONAL
}TipoVeiculo;

// struct para os tipos de veiculos
typedef struct Veiculo Veiculo;

// stuct para a reserva do veiculo
typedef struct Reserva Reserva;

// lista ecadeada para as reservas
typedef struct ListaReserva ListaReserva;
 
// função para inicializar a lista de reservas
void inicializaListaReserva(ListaReserva* lista);

//função para inicialicar a lista de veiculos
void inicializaVeiculos(Veiculo** listaVeiculos);

// função para criar um novo veículo
Veiculo* criaVeiculo(int codigo, TipoVeiculo tipo, int capacidade, const char* motorista);

//função para adicionar um veiculo
void adicionarVeiculo(Veiculo** listaVeiculos, Veiculo* novoVeiculo);

// função para adicionar uma nova reserva
void adicionarReserva(ListaReserva* lista, Veiculo** listaVeiculos);

//função para remover uma reserva existente
void excluirReserva(ListaReserva* lista, const char* nomeCliente);

// função para listar todas as reservas
void listarReservas(ListaReserva* lista);

// função para buscar uma reserva por nome do cliente
void buscarReservaPorCliente(ListaReserva* lista, const char* nomeCliente);

// função para salvar as informações no arquivo depois de editar 
void salvarDepoisDeEditado(ListaReserva * lista);

// função para editar os dados da reserva escolhida
void editarReserva(ListaReserva* lista, Veiculo* listaVeiculos, const char* nomeCliente);

// função para consultar os veículos que estão disponíveis
void consultarVeiculosDisponiveis(Veiculo* listaVeiculos);

// função para consultar o quantitativo de reservas
void consultarQuantitativoReservas(ListaReserva* lista);

// função para liberar a lista de reservas 
void liberarListaReservas(ListaReserva* lista);

// Função para liberar a lista de veículos 
void liberarListaVeiculos(Veiculo* listaVeiculos);

// função para sair do programa e ao mesmo tempo liberar a memória alocada
void sair(ListaReserva* lista, Veiculo* listaVeiculos);

#endif

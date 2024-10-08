<div>
  <div id="nav-bar">
    <img align="right" width="110" height="170" src="https://assecom.ufersa.edu.br/wp-content/uploads/sites/24/2014/09/PNG-bras%C3%A3o-Ufersa.png">
    <br>
    <h1 align="center" style="font-weight: bold;">Sistema de Reserva de Transportes🚗</h1>
    <p align="center">
        <a href="#requirements">Requisitos do Projeto</a> •
        <a href="#tech">Tecnologia</a> •
        <a href="#about">Sobre o Projeto</a> •
        <a href="#colab">Colaboradores</a> 
    </p>
  </div>

  <h2 id="requirements" style="font-weight: bold; font-size: 2rem">Requisitos do Projeto</h2>
  <div>
    ✅A opção Sair é a única que permite sair do programa.</br>
    ✅A cada execução do seu programa, os dados devem ser armazenados em um arquivo txt e deve carregar os mesmos para o programa</br>
    ✅Cada nova reserva cadastrada deve ser inserida em uma ordem cronológica.</br>
    ✅O arquivo deve refletir o estado atual dos dados em virtude da adição ou remoção.</br>
  </div>

  <div>
    <h2 id="tech" style="font-weight: bold; font-size: 2rem">Tecnologia Utilizada</h2>
    <img width="50" height="26" alt="C" src="https://img.shields.io/badge/C-4169E1?style=for-the-badge&logo=c&logoColor=white"/>
  </div>

  <h2 id="about" style="font-weight: bold; font-size: 2rem">Sobre o Projeto</h2>

  Este projeto tem como objetivo o desenvolvimento de um sistema de gerenciamento de reservas de transportes, feito para um trabalho para a disciplina de Algoritmos e Estruturas de Dados I. O foco do nosso projeto é proporcionar uma solução eficiente para a gestão de veículos, permitindo o controle adequado das reservas de diferentes tipos de veículos.



  #### Como Funciona nosso projeto?

 Cada veículo será registrado no sistema com suas respectivas informações, incluindo o número/código do veículo, tipo, disponibilidade, capacidade de passageiros e motorista responsável. O sistema de reservas permitirá o gerenciamento dessas informações de forma prática e organizada.

 O sistema será baseado em listas encadeadas, que serão usadas para armazenar e gerenciar os dados tanto dos veículos quanto das reservas. Essa escolha se dá pela flexibilidade e eficiência das listas encadeadas para operações dinâmicas, como inserção e remoção de dados, características essenciais para a gestão de reservas.

 As reservas contem detalhes como o nome do solicitante, a data e os horários de início e término da reserva, o destino, e o veículo associado. Um menu de opções permitirá a interação do usuário com o sistema, oferecendo funcionalidades como adicionar, excluir, listar e buscar reservas, além de consultar a disponibilidade de veículos e o quantitativo de reservas.

 A implementação do sistema se dará utilizando a linguagem C, com suporte a arquivos para garantir a persistência dos dados. Cada operação no sistema atualizará os arquivos de dados, refletindo o estado atual das reservas e dos veículos.
 
  ## Como rodar na minha maquina?

  Clone o repositorio na sua maquina:

  ```bash
  git clone https://github.com/classroom-ufersa/SistemaDeReservaDeTransportes.git
  ```

  Para executar, certifique-se de que você possui um compilador C instalado na sua máquina, então navegue até onde o projeto está localizado. Você pode fazer isso usando o comando cd.

  No terminal use este comando:

  ```c
  gcc main.c -o main && ./main
```

  <h2 id="colab" align="center" style="font-weight: bold; font-size: 2rem">Colaboradores</h2>
  <div align="center">
    <table>
      <tr>
        <td align="center">
          <a href="#">
            <img src="https://avatars.githubusercontent.com/u/150745935?v=4" width="100px;" alt="chico moedas"/><br>
            <sub>
              <a href="https://github.com/andevvs"><b>Andrei Vieira</b></a>
            </sub>
          </a>
        </td>
        <td align="center">
          <a href="#">
            <img src="https://avatars.githubusercontent.com/u/144806270?v=4" width="100px;" alt="fotin"/><br>
            <sub>
              <a href="https://github.com/alissonricarte"><b>Alisson Ricarte</b></a>
            </sub>
          </a>
        </td>
    </table>
   <span style="font-weight: bold;">Um agradecimento especial a todas as pessoas que ajudaram neste projeto.</span>
  </div>
</div>

<img width=100% src="https://capsule-render.vercel.app/api?type=waving&height=110&color=F9F9F4&section=footer&reversal=false"/>

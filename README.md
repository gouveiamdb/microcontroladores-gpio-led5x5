# Projeto: pio_matrix

## 📝 Sobre o Projeto

Este projeto implementa um sistema de controle de um teclado matricial 4x4, utilizando a Raspberry Pi Pico e a linguagem C. O sistema permite detectar as teclas pressionadas e acionar uma matriz de LEDs para exibir padrões predefinidos. Além disso, diferentes comandos podem ser executados com base nas teclas pressionadas.

## 🎯 Funcionalidades

- Detecção de teclas pressionadas no teclado matricial.
- Controle da matriz de LEDs com padrões pré-definidos.
- Configuração de GPIOs para interação com os periféricos.
- Implementação de comunicação via PIO (Programmable Input/Output) para controle eficiente dos LEDs.
- Execução de comandos específicos para diferentes teclas.

## 📂 Estrutura do Projeto

O projeto é composto pelos seguintes arquivos principais:

- `pio_matrix.c`: Contém a lógica principal do sistema, incluindo a detecção de teclas e o controle dos LEDs.
- `CMakeLists.txt`: Arquivo de configuração do CMake para compilação do projeto.
- `pio_matrix.pio.h`: Arquivo gerado a partir do código PIO utilizado para o controle dos LEDs.

## 🛠️ Requisitos

- Raspberry Pi Pico
- SDK do Pico instalado
- CMake
- Compilador compatível com C e C++

## ⚙️ Compilação e Execução

1. Clone o repositório do projeto:
   ```sh
   git clone <URL_DO_REPOSITORIO>
   cd pio_matrix
   ```
2. Crie um diretório de build e entre nele:
   ```sh
   mkdir build
   cd build
   ```
3. Execute o comando CMake para configurar a compilação:
   ```sh
   cmake ..
   ```
4. Compile o projeto:
   ```sh
   make
   ```
5. Faça o upload do binário gerado para a Raspberry Pi Pico.

## 👥 Colaboradores

A equipe do projeto é composta pelos seguintes integrantes e suas respectivas contribuições:

1. **Matheus Gouveia de Deus Bastos** - Tecla 9 e Liderança do projeto - [GitHub](https://github.com/gouveiamdb)
2. **Alécio Vinicius Oliveira Silva** - Teclas 1 e A - [GitHub](https://github.com/Al3ci0)
3. **Joel Junior Nunes Araújo** - Teclas 2 e B - [GitHub](https://github.com/eijoeljunior289)
4. **Laiza Gordiano** - Teclas 3 e C - [GitHub](https://github.com/laizagordiano)
5. **Levi Silva Freitas** - Teclas 4 e vídeo - [GitHub](https://github.com/Lvi01)
6. **Marcelo Barbosa de Almeida** - Teclas 5 e * - [GitHub](https://github.com/marcelofainor)
7. **Naylane do Nascimento Ribeiro** - Teclas 6 e # - [GitHub](https://github.com/naylane)
8. **Pedro Henrique Ferreira Amorim da Silva** - Tecla 7 e Testes - [GitHub](https://github.com/PedroHenriqueFAS)
9. **Thiago de Andrade Barros Machado** - Tecla 8 e D - [GitHub](https://github.com/ThiagoMachado2)

## 🎥 Vídeo Demonstrativo

[Insira o link do vídeo aqui]

## 📜 Licença

Este projeto está licenciado sob a Licença MIT. Para mais detalhes, consulte o arquivo LICENSE.


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

//arquivo .pio
#include "pio_matrix.pio.h"

// Definição dos pinos do Keypad
#define ROW1 28
#define ROW2 27
#define ROW3 26
#define ROW4 22
#define COL1 21
#define COL2 20
#define COL3 19
#define COL4 18

//Pino de saída
#define OUT_PIN 7

//número de LEDs
#define NUM_PIXELS 25

/**
 * @brief Mapeamento das teclas do Keypad
 * 
 * A matriz de teclas representa a organização do teclado matricial 4x4.
 */
const char keys[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

//vetor para criar imagem na matriz de led - 2
double desenho2[25] =   {1.0, 0.0, 0.0, 0.0, 1.0,
                        0.0, 1.0, 0.0, 1.0, 0.0, 
                        0.0, 0.0, 1.0, 0.0, 0.0,
                        0.0, 1.0, 0.0, 1.0, 0.0,
                        1.0, 0.0, 0.0, 0.0, 1.0};


/**
 * @brief Configura os GPIOs para o teclado matricial, LEDs e buzzer.
 * 
 * Configura as linhas (ROW) como saídas e as colunas (COL) como entradas com pull-up.
 * Além de configurar os pinos dos LEDs e do buzzer como saídas.
 */
void setup_gpio();


/**
 * @brief Verifica qual tecla foi pressionada no teclado matricial.
 * 
 * Itera pelas linhas e verifica se alguma coluna foi pressionada.
 * 
 * @return O caractere da tecla pressionada ou '\0' se nenhuma tecla for pressionada.
 */
char scan_keypad();


/**
 * @brief Executa comandos baseados na tecla pressionada.
 * 
 * Executa comandos para acender os LEDs e emitir som no buzzer.
 * Além de imprimir mensagens no console para informar o comando executado.
 *
 * @param key A tecla pressionada.
 */
void execute_comando(char key, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b);


void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b);

void imprimir_binario(int num);

uint32_t matrix_rgb(double b, double r, double g);

void apagar_leds(uint32_t valor_led, PIO pio, uint sm);

/**
 * @brief Função principal do programa.
 * 
 * Inicializa os GPIOs, exibe instruções e monitora as teclas pressionadas para executar comandos.
 * Fazendo uso das funções de controle dos LEDs e do buzzer.
 * 
 * @return Retorna 0 em caso de execução bem-sucedida.
 */
int main() {
    PIO pio = pio0; 
    bool ok;
    uint16_t i;
    uint32_t valor_led;
    double r = 0.0, b = 0.0 , g = 0.0;

    //coloca a frequência de clock para 128 MHz, facilitando a divisão pelo clock
    ok = set_sys_clock_khz(128000, false);

    // Inicializar o sistema padrão e configurar GPIOs
    stdio_init_all();

    printf("iniciando a transmissão PIO");
    if (ok) printf("clock set to %ld\n", clock_get_hz(clk_sys));
    else printf("clock set failed\n");

    //configurações da PIO
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

    setup_gpio();

    while (1) {
        char key = scan_keypad();
        if (key != '\0') {  // Se uma tecla foi pressionada
            printf("Tecla pressionada: %c\n", key);
            execute_comando(key, valor_led, pio, sm, r, g, b);
            sleep_ms(300);         // Debounce
        }

        sleep_ms(50); // Pequeno atraso para evitar leituras incorretas
    }
}

// Implementações das funções
void setup_gpio() {
    // Configurando as linhas (ROW) como saídas
    gpio_init(ROW1);
    gpio_init(ROW2);
    gpio_init(ROW3);
    gpio_init(ROW4);
    gpio_set_dir(ROW1, GPIO_OUT);
    gpio_set_dir(ROW2, GPIO_OUT);
    gpio_set_dir(ROW3, GPIO_OUT);
    gpio_set_dir(ROW4, GPIO_OUT);

    // Configurando as colunas (COL) como entradas com pull-up
    gpio_init(COL1);
    gpio_init(COL2);
    gpio_init(COL3);
    gpio_init(COL4);
    gpio_set_dir(COL1, GPIO_IN);
    gpio_set_dir(COL2, GPIO_IN);
    gpio_set_dir(COL3, GPIO_IN);
    gpio_set_dir(COL4, GPIO_IN);
    gpio_pull_up(COL1);
    gpio_pull_up(COL2);
    gpio_pull_up(COL3);
    gpio_pull_up(COL4);
}

char scan_keypad() {
    // Iterando pelas linhas
    for (int row = 0; row < 4; row++) {
        // Definir a linha atual como LOW e as outras como HIGH
        gpio_put(ROW1, row == 0 ? 0 : 1);
        gpio_put(ROW2, row == 1 ? 0 : 1);
        gpio_put(ROW3, row == 2 ? 0 : 1);
        gpio_put(ROW4, row == 3 ? 0 : 1);

        // Verificar cada coluna
        if (!gpio_get(COL1)) return keys[row][0];
        if (!gpio_get(COL2)) return keys[row][1];
        if (!gpio_get(COL3)) return keys[row][2];
        if (!gpio_get(COL4)) return keys[row][3];
    }
    // Retornar '\0' se nenhuma tecla for pressionada
    return '\0';
}

void execute_comando(char key,uint32_t valor_led, PIO pio, uint sm, double r, double g, double b) {

    switch (key) {
       case 'A':
            desenho_pio(desenho2, valor_led, pio, sm, r, g, b);
            break;

        case 'B':

            break;

        case 'C':

            break;

        case 'D':
  
            break;
            
        case '0':
            //Apaga todos os LEDs
            apagar_leds(valor_led, pio, sm);
            break;
        
        case '9':
            executar_tecla9(valor_led, pio, sm);
            break;


        default:
            printf("Comando: Sem comando registrado.\n");
            printf("\n");
            break;
    }
}

void apagar_leds(uint32_t valor_led, PIO pio, uint sm) {
    for (int i = 0; i < NUM_PIXELS; i++) {
                valor_led = matrix_rgb(0.0, 0.0, 0.0);  // Todos os LEDs desligados
                pio_sm_put_blocking(pio, sm, valor_led);
            }
            printf("Todos os LEDs foram apagados.\n");  
}

void imprimir_binario(int num) {
 int i;
 for (i = 31; i >= 0; i--) {
  (num & (1 << i)) ? printf("1") : printf("0");
 }
}

uint32_t matrix_rgb(double b, double r, double g)
{
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b){

    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        if (i%2==0)
        {
            valor_led = matrix_rgb(desenho[24-i], r=0.0, g=0.0);
            pio_sm_put_blocking(pio, sm, valor_led);

        }else{
            valor_led = matrix_rgb(b=0.0, desenho[24-i], g=0.0);
            pio_sm_put_blocking(pio, sm, valor_led);
        }
    }
    imprimir_binario(valor_led);
}

void executar_tecla9(uint32_t valor_led, PIO pio, uint sm) {
    // Frame 1: LEDs formam um quadrado ao redor.
    double quadrado[25] = {
        1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 0.0, 0.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 0.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0
    };
    desenho_pio(quadrado, valor_led, pio, sm, 1.0, 1.0, 1.0); // Branco
    sleep_ms(500);

    // Frame 2: LEDs piscam em cores RGB (vermelho, verde e azul).
    for (int i = 0; i < 3; i++) {
        double r = (i == 0) ? 1.0 : 0.0;
        double g = (i == 1) ? 1.0 : 0.0;
        double b = (i == 2) ? 1.0 : 0.0;
        for (int j = 0; j < NUM_PIXELS; j++) {
            valor_led = matrix_rgb(b, r, g);
            pio_sm_put_blocking(pio, sm, valor_led);
        }
        sleep_ms(3000);
    }
    apagar_leds(valor_led, pio, sm);

    // Frame 3: LEDs mostram a palavra "END".
    double endFrame[25] = {
        // E
        1.0, 1.0, 1.0, 1.0, 0.0,
        1.0, 0.0, 0.0, 0.0, 0.0,
        1.0, 1.0, 1.0, 1.0, 0.0,
        1.0, 0.0, 0.0, 0.0, 0.0,
        1.0, 1.0, 1.0, 1.0, 0.0
    };
    desenho_pio(endFrame, valor_led, pio, sm, 1.0, 0.0, 0.0); // Vermelho
    sleep_ms(5000);

    // Frame 4: LEDs piscam rapidamente.
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < NUM_PIXELS; j++) {
            valor_led = matrix_rgb(1.0, 1.0, 1.0); // Branco
            pio_sm_put_blocking(pio, sm, valor_led);
        }
        sleep_ms(1000);
        apagar_leds(valor_led, pio, sm);
        sleep_ms(1000);
    }

    // Frame 5: Todos os LEDs se apagam.
    apagar_leds(valor_led, pio, sm);
}

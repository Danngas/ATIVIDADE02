#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/watchdog.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"

// Definir os pinos GPIO para LEDs e Buzzer
#define LED_RED_PIN 13
#define LED_GREEN_PIN 11
#define LED_BLUE_PIN 12
#define BUZZER_PIN 21
#define BUZZER_FREQUENCY 100
// Função para inicializar os pinos GPIO
void initialize_gpio()
{
    // Inicializar os pinos dos LEDs como saída
    gpio_init(LED_RED_PIN);
    gpio_init(LED_GREEN_PIN);
    gpio_init(LED_BLUE_PIN);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);

    // Inicializar o pino do Buzzer como saída
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
}

// Definição de uma função para inicializar o PWM no pino do buzzer
void pwm_init_buzzer(uint pin)
{
    // Configurar o pino como saída de PWM
    gpio_set_function(pin, GPIO_FUNC_PWM);

    // Obter o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configurar o PWM com frequência desejada
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (BUZZER_FREQUENCY * 4096)); // Divisor de clock
    pwm_init(slice_num, &config, true);

    // Iniciar o PWM no nível baixo
    pwm_set_gpio_level(pin, 0);
}

void beep(uint pin, uint duration_ms)
{
    // Obter o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configurar o duty cycle para 50% (ativo)
    pwm_set_gpio_level(pin, 2048);

    // Temporização
    sleep_ms(duration_ms);

    // Desativar o sinal PWM (duty cycle 0)
    pwm_set_gpio_level(pin, 0);

    // Pausa entre os beeps
    sleep_ms(100); // Pausa de 100ms
}

void handle_key_5() {
    // Desliga todos os LEDs
    gpio_put(LED_RED_PIN, 0);   
    gpio_put(LED_GREEN_PIN, 0); 
    gpio_put(LED_BLUE_PIN, 0);  
}

// Função para controlar o LED RGB com base no comando
void control_rgb_led(const char *comando)
{

    if (strcmp(comando, "BUZZER") == 0)
    {
        for (int j = 0; j <= 10; j++)
        {
            beep(BUZZER_PIN, 500); // Bipe de 500ms
        }
    }

    if (strcmp(comando, "RED") == 0)
    {
        gpio_put(LED_BLUE_PIN, 0);
        gpio_put(LED_RED_PIN, 1);
        gpio_put(LED_GREEN_PIN, 0);
    }
    if (strcmp(comando, "BLUE") == 0)
    {
        gpio_put(LED_BLUE_PIN, 1);
        gpio_put(LED_RED_PIN, 0);
        gpio_put(LED_GREEN_PIN, 0);
    }
    if (strcmp(comando, "GREEN") == 0)
    {
        gpio_put(LED_BLUE_PIN, 0);  // Liga o LED Azul
        gpio_put(LED_RED_PIN, 0);   // Desliga o LED Vermelho
        gpio_put(LED_GREEN_PIN, 1); // Desliga o LED Verde
    }

    if (strcmp(comando, "WHITE") == 0)
    {
        gpio_put(LED_RED_PIN, 1);
        gpio_put(LED_GREEN_PIN, 1);
        gpio_put(LED_BLUE_PIN, 1);
    }

    if (strcmp(comando, "KEY5") == 0)
{
    handle_key_5();  // Chama a função que desliga todos os LEDs
}

    if (strncmp(comando, "RGB", 3) == 0)
    {
        // Extrair valores RGB do comando, no formato "RGB_RRR_GGG_BBB"
        int r, g, b;
        if (sscanf(comando, "RGB_%d_%d_%d", &r, &g, &b) == 3)
        {
            gpio_put(LED_RED_PIN, r > 0 ? 1 : 0);
            gpio_put(LED_GREEN_PIN, g > 0 ? 1 : 0);
            gpio_put(LED_BLUE_PIN, b > 0 ? 1 : 0);
        }
        else
        {
            printf("Comando RGB invalido\n");
        }
    }

    if (strcmp(comando, "OFF") == 0)
    {
        // Desligar todos os LEDs inicialmente
        gpio_put(LED_RED_PIN, 0);
        gpio_put(LED_GREEN_PIN, 0);
        gpio_put(LED_BLUE_PIN, 0);
        gpio_put(BUZZER_PIN, 0); // Garantir que o Buzzer esteja desligado inicialmente
    }

    if (strcmp(comando, "REBOOT") == 0)
    {
        // Atividade 7: Sair do modo de execução e reiniciar o dispositivo
        printf("Reiniciando...\n");
        watchdog_enable(1000, true); // Habilita o watchdog para reiniciar o sistema após 1 segundo
        while (1)
        {
        } // Aguarda reinício
    }
}

// Loop principal do programa
int main()
{
    stdio_init_all();
    initialize_gpio();
    pwm_init_buzzer(BUZZER_PIN);

    char comando[50];
    while (1)
    {
        printf("Digite um comando: ");
        scanf("%s", comando);

        // Controlar os LEDs com base no comando
        control_rgb_led(comando);

        sleep_ms(50); // Atraso para evitar polling excessivo
    }

    return 0;
}

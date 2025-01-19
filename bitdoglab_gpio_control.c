#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/watchdog.h"

// Definir os pinos GPIO para LEDs e Buzzer
#define LED_RED_PIN 13
#define LED_GREEN_PIN 11
#define LED_BLUE_PIN 12
#define BUZZER_PIN 14

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

// Função para controlar o LED RGB com base no comando
void control_rgb_led(const char *comando)
{
    // Desligar todos os LEDs inicialmente
    gpio_put(LED_RED_PIN, 0);
    gpio_put(LED_GREEN_PIN, 0);
    gpio_put(LED_BLUE_PIN, 0);
    gpio_put(BUZZER_PIN, 0); // Garantir que o Buzzer esteja desligado inicialmente

    if (strcmp(comando, "RED") == 0)
    {
        gpio_put(LED_RED_PIN, 1);
        gpio_put(LED_GREEN_PIN, 0);
        gpio_put(LED_BLUE_PIN, 0);
    }
    else if (strcmp(comando, "BLUE") == 0)
    {
        gpio_put(LED_BLUE_PIN, 1);
        gpio_put(LED_RED_PIN, 1);
        gpio_put(LED_GREEN_PIN, 0);
    }
    else if (strcmp(comando, "BLUE") == 0)
    {
        gpio_put(LED_BLUE_PIN, 1);  // Liga o LED Azul
        gpio_put(LED_RED_PIN, 0);   // Desliga o LED Vermelho
        gpio_put(LED_GREEN_PIN, 0); // Desliga o LED Verde
    }
    else if (strcmp(comando, "WHITE") == 0)
    {
        gpio_put(LED_RED_PIN, 1);
        gpio_put(LED_GREEN_PIN, 1);
        gpio_put(LED_BLUE_PIN, 1);
    }
    else if (strncmp(comando, "RGB", 3) == 0)
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
    else if (strcmp(comando, "BUZZER") == 0)
    {
        gpio_put(BUZZER_PIN, 1); // Acionar o Buzzer
    }
    else if (strcmp(comando, "OFF") == 0)
    {
        // Já estão desligados no início da função
    }
    else if (strcmp(comando, "REBOOT") == 0)
    {
        // Atividade 7: Sair do modo de execução e reiniciar o dispositivo
        printf("Reiniciando...\n");
        watchdog_enable(1000, true); // Habilita o watchdog para reiniciar o sistema após 1 segundo
        while (1)
        {
        } // Aguarda reinício
    }
    else
    {
        printf("Comando desconhecido: %s\n", comando);
    }
}

// Loop principal do programa
int main()
{
    stdio_init_all();
    initialize_gpio();

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

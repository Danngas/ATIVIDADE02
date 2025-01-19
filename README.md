# ATIVIDADE02
## Repositório da Atividade 2 (Participativa): Controle de pinos GPIO da ferramenta educacional BitDogLab
## Links Importantes


- **Simulação**: [Simulação do Projeto no Wokwi](https://wokwi.com/projects/420513306795728897)
- **Vídeo Demonstrativo**: [Vídeo Demonstrativo do Projeto](https://youtu.be/eqFk_JDuntc)
  
### GRUPO 5 SUBGRUPO 2

---

### COMPONENTES

- **Daniel Silva de Souza**
- **[Adicionar nomes dos outros membros aqui]**

---

### Descrição do Projeto

O objetivo desta atividade é o controle de pinos GPIO do microcontrolador RP2040 utilizando a ferramenta educacional **BitDogLab**. O projeto foi desenvolvido para controlar os seguintes periféricos:

1. **LED RGB**: Conectado aos pinos GPIO 11, 12 e 13.
2. **Buzzer**: Conectado ao pino GPIO 21.

A comunicação com o sistema embarcado é feita via **porta serial UART** e os comandos de controle são enviados através do terminal emulador PuTTY. Com esses comandos, é possível controlar os LEDs RGB e acionar o buzzer, conforme descrito nos requisitos.

---

### Requisitos do Projeto

1. **Ligar LED verde (GPIO 11)** – desligar as demais GPIOs.
2. **Ligar LED azul (GPIO 12)** – desligar as demais GPIOs.
3. **Ligar LED vermelho (GPIO 13)** – desligar as demais GPIOs.
4. **Ligar os três LEDs (luz branca)**.
5. **Desligar todos os LEDs**.
6. **Acionar o buzzer por 2 segundos** – emissão de sinal sonoro.
7. **Sair do modo de execução e habilitar o modo de gravação via software (reboot)** – rotina opcional.

---

### Ambiente de Desenvolvimento

- **VS Code**: Ambiente de desenvolvimento utilizado para programar o microcontrolador RP2040.
- **Pico SDK**: Kit de Desenvolvimento de Software utilizado no projeto.
- **Wokwi**: Simulador integrado ao VS Code para testar o código.
- **PuTTY**: Software de emulação de terminal utilizado para comunicação serial entre o computador e o microcontrolador.

---

### Estrutura do Repositório

O repositório contém os seguintes arquivos:

- **bitdoglab_gpio_control.c**: Código em C que implementa o controle dos periféricos (LED RGB e Buzzer).
- **README.md**: Este arquivo, contendo a descrição do projeto e instruções.
- **Makefile**: Arquivo de configuração para compilar o código usando o Pico SDK.

---

### Como Usar

1. Clone o repositório para sua máquina local:

   ```bash
   git clone https://github.com/SEU_USUARIO/ATIVIDADE02.git


### Comandos Aceitos pelo Programa

- **RED**: Acende a luz vermelha.
- **BLUE**: Acende a luz azul.
- **WHITE**: Acende a luz branca (todas as cores dos LEDs acesas).
- **BUZZER**: Aciona o buzzer (não é uma cor, mas pode ser associado a um som ou alerta).
- **OFF**: Desliga todos os LEDs.
- **REBOOT**: Reinicia o dispositivo após 1 segundo. (Utiliza o watchdog para reiniciar o sistema).

### Exemplos Cores em formato RGB (Aceitas pelo programa)

- **RGB_255_0_0**: Vermelho
- **RGB_0_255_0**: Verde
- **RGB_0_0_255**: Azul
- **RGB_255_255_0**: Amarelo
- **RGB_0_255_255**: Ciano
- **RGB_255_0_255**: Magenta
- **RGB_128_128_128**: Cinza
- **RGB_255_105_180**: Rosa
- **RGB_255_165_0**: Laranja

### Erros

- **RGB_100_100**: Resultado em mensagem de erro (entrada inválida).

---

### Observação

O programa aceita qualquer cor no formato **RGB** conforme o padrão **RGB_<R>_<G>_<B>**, onde **R**, **G** e **B** são valores numéricos entre 0 e 255 representando as intensidades de vermelho, verde e azul, respectivamente.

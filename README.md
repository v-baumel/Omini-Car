
# Omini-Car
Omini-Car é um carrinho Bluetooth omnidirecional capaz de se mover em qualquer direção (frente, trás, deslizar para esquerda/direita e rotação) sem alterar sua orientação. Essa capacidade é alcançada utilizando rodas Mecanum e 4 motores independentes, controlados por um controle de videogame via Bluetooth.

O firmware do Arduino é construído usando PlatformIO (C++), e é usado um código em Python usando a biblioteca pygame para fazer a conexão: controle -> PC - > Arduino.

# Materiais usados
- 1x Arduino Nano
- 1x Protoboard
- 4x Rodas mecanum de 60mm
- 4x Motores DC 3-6V
- 8x Fios para os motores
- 2x Pontes H 298N
- 1x Módulo Bluetooth HC-05
- 2x [Chassis de acrílico](https://www.printables.com/model/186945-4wd-buggy-chassis-arduino)
- 16x Espaçadores de 3cm (feitos em impressora 3D)
- 32x Parafusos de 3mm
- 22x Jumpers
- 3x Resistores de 1K
- 1x Bateria 11.3V (recomendável uma de maior voltagem)
- 1x Controle de video game (com pelo menos 2 joysticks)
- 1x Computador com Bluetooth

# Setup no computador

## Pré-requisitos

Antes de instalar e executar, você precisa ter:
- Git
- Visual Studio Code 
- PlatformIO IDE (extensão do VS Code)
- Python
- pygame (biblioteca do python)

**Obervação:** Esse projeto foi testado apenas em Linux. (Mint)
## Instalação

Clone o repositório:

```bash
git clone https://github.com/v-baumel/Omini-Car.git
cd Omini-Car
```

Abra a pasta no Visual Studio Code.

Instale a extensão PlatformIO IDE (se ainda não tiver).

**Compilar o projeto:**

Clique no botão de Build na interface do PlatformIO ou execute:
```bash
pio run
```

**Enviar para o microcontrolador:**
Conecte sua placa via USB e clique no botão de Upload na interface do PlatformIO ou execute:
```bash
pio run --target upload
```

**Monitor serial (opcional):**
Para abrir o monitor serial e ver saídas do microcontrolador (via USB), clique no botão de Serial Monitor na interface do PlatformIO ou execute:
```bash
pio device monitor
```

Instale o Python (se ainda não tiver)

Instale o pygame executando:
```bash
python -m pip install pygame-ce
```

## Conectando o Bluetooth
Certifique-se de que o modulo bluetooth está piscando rapidamente, isso significa que ele está esperando para parear. Então conecte-se a ele procurando por algo com nome HC-05, o pin é 1234. 

Feito isso, descubra a qual port o módulo está conectado (no linux geralmente é  /dev/rfcomm0 ou /dev/rfcomm1), vá em ./src/Computador/controller_bluetooth.py e na linha 11 bote a variável port para o nome do seu port e salve. (Não foi implementado um método automático de procurar o port)

Agora, conecte o seu controle ao computador(pode ser por bluetooth ou não), e rode esse mesmo código. Você vai ver no terminal os inputs enviados pelo controle, e no serial monitor, você poderá ver a força que o Arduíno bota em cada motor.

# Conexões dos fios 
**observação:**  não será explicado as conexões com a bateria. 


**Ponte H frontal:**

Para o motor frontal esquerdo:  ENA=D3, IN1=D2, IN2=D4

Para o motor frontal direito: ENB=D5, IN3=D6, IN4=D7


**Ponte H traseira:**

Para o motor traseiro esquerdo:  ENA=D9, IN1=D8, IN2=D12

Para o motor traseiro direito: ENB=D10, IN3=D11, IN4=D13

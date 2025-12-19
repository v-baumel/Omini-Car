# Omini-Car
Omini-Car é um carrinho bluetooth omnidirecional capaz de se mover em qualquer direção (frente, trás, deslizar para esquerda/direita e rotação) sem alterar sua orientação. Essa capacidade é alcançada utilizando rodas Mecanum e 4 motores independentes, controlados por um controle de videogame via bluetooth.
O firmware do arduino é construído usando PlatformIO (C++), e é usado um código em Python usando a biblioteca pygame para fazer a conexão: controle -> PC - > arduino.

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
- 1x Bateria 11.3V
- 1x Controle de video game (com pelo menos 2 joysticks)

# Setup no computador

## Pré-requisitos

Antes de instalar e executar, você precisa ter:

- Git
- Visual Studio Code 
- PlatformIO IDE (extensão do VS Code)
- Python
- pygame (biblioteca do python)

## Instalação

Clone o repositório:

git clone https://github.com/v-baumel/Omini-Car.git
cd Omini-Car

Abra a pasta no Visual Studio Code.

Instale a extensão PlatformIO IDE (se ainda não tiver).

Instale o Python (se ainda não tiver)

Instale o pygame executando:
```bash
python -m pip install pygame-ce
```

*Para compilar o projeto:*

Clique no botão de Build na interface do PlatformIO ou execute:
```bash
pio run
```

*Para enviar para o microcontrolador:*

Conecte sua placa via USB e clique no botão de Upload na interface do PlatformIO ou execute:
```bash
pio run --target upload
```

Monitor serial (opcional):

Para abrir o monitor serial e ver saídas do microcontrolador (via USB), clique no botão de Serial Monitor na interface do PlatformIO ou execute:
```bash
pio device monitor
```


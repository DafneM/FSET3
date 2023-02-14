# Trabalho Final - Fundamentos de Sistemas Embarcados

| Nome | Matrícula |
| ------------- | ------------- |
| Dafne Moretti Moreira  | 190026243  |
| João Pedro Alves da Silva Chaves  | 180123203 |

Neste repositório consta o código do [trabalho final](https://gitlab.com/fse_fga/trabalhos-2022_2/trabalho-final-2022-2) que consiste em um sistema para de controle de ambiente e batimentos em hospital utilizando 3 ESP32, WIFI e protocolo MQTT.

# Hardware

O hardware para esse repositório possui 3 ESPS32, com diferentes entradas e saídas expostas abaixo:

### ESP1 

- DHT11 (GPIO 19)
- Buzzer (GPIO 2)
- Sensor magnético (GPIO 22)

### ESP 2

- Sensor de batimentos
- Sensor de luminosidade

### ESP 3

- Sensor de chama
- Led

# Dependências

[Visual Studio Code](https://code.visualstudio.com/)
[Espressif](https://www.espressif.com/)

# Como rodar

Para rodar, primeiro é necessário definir as variáveis de ambiente no menuconfig, utilizando o terminal da ESP-IDF e utilizando o comando:

```bash
idf.py menuconfig                                                                                                                               
```

Após isso, pode-se fazer o build do projeto clicando em: 

**ESP-IDF: Build project**

E compilar o código clicando em

**ESP-IDF: Flash device**

# Dashboard

A dashboard foi criada com [ThingsBoard](https://thingsboard.io/) e pode ser acessada em Dashboards com nome DafneJoaoRenan

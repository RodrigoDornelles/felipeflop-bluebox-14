// Autor: FilipeFlop
// BlueBox 14 - Placa de avisos IoT

#include <FC16.h> // Biblioteca para controle da matriz de LED
#include "CTBot.h" // Biblioteca para comunicação com o Telegram

#define pino_CS D3 // Pino de conexão entre o display de LED e o Wemos
#define qte_displays 4 // Define o número de displays da matriz
#define scroll_delay 100 // Tempo (em milissegundos) para atualização dos LEDs 

String ssid  = "insira-aqui-o-nome-da-rede-wifi"; // Nome da sua rede WiFi
String pass  = "insira-aqui-a-senha-da-rede-wifi"; // Senha da sua rede WiFi
String token = "insira-aqui-o-token-Bot-Telegram"; // Token bot Telegram

const int tamanhoArray = 30;
char mensagem[tamanhoArray]; // Variável que armazena os caracteres da mensagem recebida
unsigned long previousMillis = 0; // Variavel para armazenar o valor (tempo) da ultima atualização da mensagem
const long intervalo = 30000; //Intervalo de tempo entre checagem de mensagens (em milisegundos)

FC16 meuDisplay = FC16(pino_CS, qte_displays); // Criação e configuração do objeto display
CTBot meuBot; // Criação do objeto Bot Telegram

void setup()
{
  Serial.begin(115200); // Inicia a comunicação serial
  Serial.println("Inicializando bot Telegram...");
  
  meuBot.wifiConnect(ssid, pass); // Inicia a conexão com a rede WiFi
  
  meuBot.setTelegramToken(token); // Inicia a conexão com o Bot Telegram
  
  // Verifica se a comunicação com o Telegram foi bem sucedida
  if (meuBot.testConnection())
    Serial.println("nConexao Ok!");
  else
    Serial.println("nFalha na conexao!");

  meuDisplay.begin(); // Inicia o display
  meuDisplay.setIntensity(2); // Define o brilho do display
  meuDisplay.clearDisplay(); // Apaga qualquer informação que esteja no display
  meuDisplay.setText("BlueBox 14"); // Texto inicial exibido no display
}
void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= intervalo)
  {
    previousMillis = currentMillis;; //Armazena o valor da ultima vez que foi feita a atualização da mensagem
    TBMessage msg; //Variavel que armazena a mensagem recebida
    if (meuBot.getNewMessage(msg)) //Verifica se chegou alguma mensagem
    {
      msg.text.toCharArray(mensagem, tamanhoArray); // Copia os caracteres da string msg para a variável mensagem
      Serial.print("Mensagem recebida: "); 
      Serial.println(msg.text);// Mostra no Serial Monitor a mensagem recebida
      meuDisplay.setText(mensagem); // Atualiza o display com a nova mensagem
    }
  }
  meuDisplay.update(); // Chama a rotina de scroll
  delay(scroll_delay); // Aguarda o tempo definido
}

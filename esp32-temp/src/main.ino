
#include <WiFi.h>         //Padrão ESP32
#include <PubSubClient.h> //Necessário para fazer comunicação broker
#include <DHT.h>          // Lida com Sensor Temperatura
#include <ArduinoJson.h>  // Monta JSON para enviar as infos

// Configurar a conexão WiFi
const char *SSID = "POCOX7";
const char *PASSWORD = "12345678";

// Configuraçãoes do Broker MQTT
const char *MQTT_HOST = "broker.hivemq.com";
const int MQTT_PORT = 1883;

// Configuração do sensor DHT11
const int DHTPIN = 21;
const int DHTTYPE = DHT11;
const int PINO_WIFI = 23;


// Criando as instâncias (objetos)
WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

// Tópicos que serão recebidos
const char *MQTT_TOPICO_TEMPERATURA = "senai124/teste_conexao"; // Topico - importante

// Função para conectar no WiFi
void conectarWiFi()
{
  WiFi.begin(SSID, PASSWORD);
  Serial.println("Conectando no WiFi...");

  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(PINO_WIFI, LOW);
    delay(1000);
  }

  String ip = "" + WiFi.localIP().toString();
  Serial.println("Conectado ao WiFi");
  Serial.println(ip.c_str());
  digitalWrite(PINO_WIFI, HIGH);

}

// Função para conectar ao servidor MQTT
void conectarMQTT()
{
  // Define o servidor do MQTT que vai receber as mensagens
  client.setServer(MQTT_HOST, MQTT_PORT);

  // Define a função que será chamada quando receber uma mensagem do Broker
  // client.setCallback(mensagemRecebida);

  while (!client.connected())
  {
    // Cria um identificador único para a conexão
    String clientId = "ESP32";
    // Gera um número aleátório para simular um cliente único
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str()))
    {
      Serial.println("Conectado ao Broker :)");
      Serial.println(clientId);
    }
    else
    {
      Serial.println("Erro ao conectar no Broker :(");
      String mqttError = "Código do erro: " + String(client.state());
      Serial.println(mqttError.c_str());
    }
  }
  // Se inscreve no(s) tópico(s)
  // client.subscribe(MQTT_TOPICO_TESTE);
}

/* void mensagemRecebida (char *topico, byte *payload, unsigned int tamanho){
  Serial.println ("Chegou a mensagem ");
  Serial.println(topico);
} */

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  conectarWiFi();
  conectarMQTT();
  dht.begin();
  pinMode(PINO_WIFI, OUTPUT);
}

void loop()
{
  if (!client.connected())
  {
    Serial.println("MQTT desconectado");
    conectarMQTT();
  }
  client.loop();
  enviarTemperatura();
  delay(1);
}

void enviarTemperatura()
{
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

  if (isnan(temperatura) || isnan(umidade))
  {
    Serial.println("Erro ao ler dados");
  }
  else
  {
    Serial.println("Temperatura: ");
    Serial.println(temperatura);
    Serial.println("Umidade: ");
    Serial.println(umidade);

    //Montar o JSON com os dados
    StaticJsonDocument<200> doc;
    doc [ "temperatura"] = temperatura;
    doc ["umidade"] = umidade;

    //Serializa o JSON para envio
    char buffer[200];
    size_t tamanho = serializeJson(doc, buffer);

    //Publica no tópico
    client.publish(MQTT_TOPICO_TEMPERATURA, buffer, tamanho);
  }
}

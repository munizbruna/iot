let clienteWeb = null;
const temp = document.getElementById("temp")
const umid = document.getElementById("umid")

const clientId = 'Esp32' + Math.floor(Math.random() * 900) + 100;
clienteWeb = new Paho.MQTT.Client('broker.hivemq.com', 8884, clientId);

clienteWeb.connect({
  useSSL: true,
  onSuccess: function () {
    alert('A conexão com Broker foi bem sucedida')
    clienteWeb.subscribe('senai124/teste_conexao');
  },
  onFailure: function () {
    alert('A conexão com Broker falhou')
  }
});

clienteWeb.onMessageArrived = function (message) {
  const payload = message.payloadString;
  const dados = JSON.parse(payload);

  temp.textContent = String(dados.temperatura) + " ºC"
  umid.textContent = String(dados.umidade) + " %"

}
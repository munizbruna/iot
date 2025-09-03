let clienteWeb = null;
const temp = document.getElementById("temp")
const umid = document.getElementById("umid")
const atualizado = document.getElementById("atualizado")

const clientId = 'Esp32' + Math.floor(Math.random() * 900) + 100;
clienteWeb = new Paho.MQTT.Client('broker.emqx.io', 8084, clientId);

clienteWeb.connect({
  useSSL: true,
  onSuccess: function () {
    mostrarNotificacao('✅ Conexão com o Broker foi bem sucedida');
    clienteWeb.subscribe('senai124/teste_conexao');
  },
  onFailure: function () {
    mostrarNotificacao('❌ Falha na conexão com o Broker', '#e74c3c');
  }
});

clienteWeb.onMessageArrived = function (message) {
  const payload = message.payloadString;
  const dados = JSON.parse(payload);

  temp.textContent = String(dados.temperatura) + " ºC"
  umid.textContent = String(dados.umidade) + " %"

  const agora = new Date();
  const dataHoraPtBr = agora.toLocaleString('pt-BR'); // inclui data e hora
  atualizado.textContent = "Atualizado em: " + dataHoraPtBr;
}
function mostrarNotificacao(mensagem, cor = "#2ecc71") {
  const notif = document.getElementById("notificacao");
  notif.textContent = mensagem;
  notif.style.backgroundColor = cor;
  notif.style.display = "block";

  setTimeout(() => {
    notif.style.display = "none";
  }, 30000); // 30 segundos
}

console.log(String(dados.statusBroken))

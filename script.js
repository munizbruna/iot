const temperaturas = [
  {id: 1, temperatura: 23.4},
  {id: 2, temperatura: 25.8},
  {id: 3, temperatura: 21.7},
  {id: 4, temperatura: 28.9},
  {id: 5, temperatura: 30.2},
  {id: 6, temperatura: 26.5},
  {id: 7, temperatura: 24.1},
  {id: 8, temperatura: 32.0},
  {id: 9, temperatura: 27.3},
  {id:10, temperatura: 29.6}
]


function simularLeitura(){
    const sort = Math.floor(Math.random()* temperaturas.length)

    const tempSort = temperaturas[sort].temperatura


    const tempPage = document.getElementById("temp");
    tempPage.textContent = `${tempSort} ºC`

}
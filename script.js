const temperaturas = [
    {id: 1, temperatura:23.9},
    {id: 2, temperatura:25.9},
    {id: 3, temperatura:27.9},
    {id: 4, temperatura:29.9}
]

function simularLeitura(){
    const sort = Math.floor(Math.random()* temperaturas.length)

    const tempSort = temperaturas[sort].temperatura


    const tempPage = document.getElementById("temp");
    tempPage.textContent = `${tempSort} ºC`

}
(function mainFunction() {
    var titles= document.getElementsByTagName("h1");
    titles[0].innerHTML = "Script header";

    var paragraph = document.getElementById("paragraph");

    var buttonConnect = document.getElementById("button_connect");
    buttonConnect.addEventListener("click", connectWebSocket);

    var webSocketId;
    
    function connectWebSocket(){
      var srvConnectionString = "ws://" + window.location.hostname + ':' + `${parseInt(window.location.port)}`;
      console.log(srvConnectionString);
      var webSocket = new WebSocket("ws://localhost:3000");
      webSocketId = webSocket;
      webSocket.onmessage = function(event) {
        paragraph.innerHTML() = event.data
      }
    }

    var buttonClose = document.getElementById("button_close");
    buttonClose.onclick = function() {

      if(webSocketId != undefined)
      {
        webSocketId.close();
      }
    }

  })();
(function mainFunction() {
    var titles= document.getElementsByTagName("h1");
    titles[0].innerHTML = "Script header";

    var paragraph = document.getElementById("paragraph");

    var buttonConnect = document.getElementById("button_connect");
    buttonConnect.addEventListener("click", connectWebSocket);

    var webSocket;

    function connectWebSocket(){
      var srvConnectionString = "ws://" + window.location.hostname + ':' + `${parseInt(window.location.port)}`;
      webSocket = new WebSocket("ws://localhost:3000");
      webSocket.onmessage = function(event) {
        paragraph.innerHTML = event.data
      }
    }

    var buttonClose = document.getElementById("button_close");
    buttonClose.onclick = function() {

      if(webSocket != undefined)
      {
        webSocket.close();
      }
    }

    var buttonSend = document.getElementById("button_send");
    buttonSend.onclick = function() {
      var textFieldContent = document.getElementById("text_field");
      webSocket.send(textFieldContent.value);
    }

  })();
(function() {

    var startSocketCounter = 0;
    var closeSocketCounter = 0;
    var socketButton = document.getElementById("socketButton");
    var socketId;

    socketButton.onclick = function () {
        var element = document.getElementById("status");
        element.innerHTML = "Start clicked";

        var srvConnectionString = "ws://" + window.location.hostname + ':' + `${parseInt(window.location.port)}`;
        var webSocket = new WebSocket(srvConnectionString);
        var testElement = document.getElementById("test");
        testElement.innerHTML = srvConnectionString;

        startSocketCounter = startSocketCounter + 1;
        console.log('socketButton.onclick: # '.concat(startSocketCounter));

        webSocket.onmessage = function(event) {
            //var msg = JSON.parse(event.data);
            var msgElement = document.getElementById("message");
            msgElement.innerHTML = event.data;
        };

        socketId = webSocket;
    }

    var socketCloseButton = document.getElementById("socketCloseButton");
    socketCloseButton.onclick = function() {
        var element = document.getElementById("text_1");
        element.innerText = "Close Button clicked\n";
        closeSocketCounter = closeSocketCounter + 1;
        var text = element.innerText;
        text = text.concat(' socketCloseButton.onclick: # ').concat(closeSocketCounter.toString());
        element.innerText = text;
        if(socketId != undefined)
        {
            socketId.close();
        }
    }

    function display(msg) {
        var p = document.createElement('p');
        p.innerHTML = msg;
        document.body.appendChild(p);
    }

    display("The new text from the src client.js");

    var div_1 = document.getElementById("div_1");

    div_1.style.borderStyle = "solid";
    div_1.style.borderColor = "#000000";
    div_1.style.borderWidth = "1px";
    
    div_1.style.width = (Math.random() * 10 % 50) + 50 + 'px';
    div_1.style.height = (Math.random() * 10 % 50) + 50 + 'px';

    var changeRandHeightWidthOfDiv = function(){
        div_1.style.width = (Math.random() * 100 % 50) + 50 + 'px';
        div_1.style.height = (Math.random() * 100 % 50) + 50 + 'px';
    }
    window.setInterval(changeRandHeightWidthOfDiv, 1000);

})();

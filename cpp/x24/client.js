(function() {

    var startSocketCounter = 0;
    var closeSocketCounter = 0;
    var socketButton = document.getElementById("socketButton");

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
    }

    var socketCloseButton = document.getElementById("socketCloseButton");
    socketCloseButton.onclick = function() {
        var element = document.getElementById("text_1");
        element.innerText = "Close Button clicked\n";
        closeSocketCounter = closeSocketCounter + 1;
        var text = element.innerText;
        text = text.concat(' socketCloseButton.onclick: # ').concat(closeSocketCounter.toString());
        element.innerText = text;
    }

    function display(msg) {
        var p = document.createElement('p');
        p.innerHTML = msg;
        document.body.appendChild(p);
    }

    display("The new text from the src client.js");

})();

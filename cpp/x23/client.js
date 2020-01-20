(function() {

    var socketButton = document.getElementById("socketButton");

    socketButton.onclick = function () {
        var element = document.getElementById("status");
        element.innerHTML = "Start clicked";

        var srvConnectionString = "ws://" + window.location.hostname + ':' + `${parseInt(window.location.port)}`;
        var webSocket = new WebSocket(srvConnectionString);
        var testElement = document.getElementById("test");
        testElement.innerHTML = srvConnectionString;

        webSocket.onmessage = function(event) {
            //var msg = JSON.parse(event.data);
            var msgElement = document.getElementById("message");
            msgElement.innerHTML = event.data;
        };
    }

})();

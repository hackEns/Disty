// EDIT: Edit this according to your needs
var config = {
    "server": "localhost",
    "port": 80
};


// Websocket handler
var ws = new WebSocket("ws://"+config["server"]+":"+config["port"], ['binary', 'base64']);
ws.onopen = function(evt) {
    document.getElementById("move").innerHTML = "Waiting for commands…";
};

ws.onmessage = function(evt) {
    // Not implemented as we should not receive messages
};

ws.onclose = function(evt) {
    // Alert the user that connection has been lost
    alert("Connection closed.");
};

ws.onerror = function(evt) {
    // Alert the user of encountered errors
    alert("WebSocket error: " + evt.data)
};


// Move handler
_prevKeyDown = {}  // Store keys currently pressed


function handleMove(e) {
    var ev = e || window.event;

    if (_prevKeyDown[ev.key] == true) {  // Avoid multiple presses
        return;
    }

    switch (ev.key) {
        case "z":
            ws.send("FORWARD");
            break;
        case "s":
            ws.send("BACKWARD");
            break;
        case "q":
            ws.send("TURN LEFT");
            break;
        case "d":
            ws.send("TURN RIGHT");
            break;
        case "ArrowUp":
            ws.send("LOOK UP");
            break;
        case "ArrowDown":
            ws.send("LOOK DOWN");
            break;
        default:
            return;
    }

    // Following code is only executed if a valid key was pressed
    ev.preventDefault();

    // Prevent next fired events until released
    _prevKeyDown[ev.key] = true;
}


function handleStop(e) {
    var ev = e || window.event;

    ws.send("STOP");

    _prevKeyDown[ev.key] = false;
}


// Bind event listeners
window.addEventListener("keydown", handleMove, false);
window.addEventListener("keyup", handleStop, false);

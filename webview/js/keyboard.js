// This server and port is used to initiate the websocket to control Disty (and only for this purpose). "disty" should resolve to your Disty robot.
var config = {
    "server": "disty",
    "port": 80
};


// Whether everything is ready or not
var ready = false;


// Websocket handler
var keyboard_ws = new WebSocket("ws://"+config["server"]+":"+config["port"], ['binary', 'base64']);
keyboard_ws.onopen = function(evt) {
    document.getElementById("move").innerHTML = "Waiting for commands…";
    ready = true;
};

keyboard_ws.onmessage = function(evt) {
    // Not implemented as we should not receive messages
};

keyboard_ws.onclose = function(evt) {
    // Alert the user that connection has been lost
    alert("Connection closed: " + evt.code + " - " + evt.reason);
};

keyboard_ws.onerror = function(evt) {
    // Alert the user of encountered errors
    alert("WebSocket error.");
};


// Move handler
_prevKeyDown = {}  // Store keys currently pressed


function handleMove(e) {
    var ev = e || window.event;

    if (!ready) {
        // If not ready, forget about handling keypresses
        return;
    }

    if (_prevKeyDown[ev.key] == true) {  // Avoid multiple presses
        return;
    }

    switch (ev.keyCode) {
        case 73:  // "i"
            keyboard_ws.send("FORWARD");
            document.getElementById("move").innerHTML = "Moving forward";
            break;
        case 75:  // "k"
            keyboard_ws.send("BACKWARD");
            document.getElementById("move").innerHTML = "Moving backward";
            break;
        case 74:  // "j"
            keyboard_ws.send("TURN LEFT");
            document.getElementById("move").innerHTML = "Turning left";
            break;
        case 76:  // "l"
            keyboard_ws.send("TURN RIGHT");
            document.getElementById("move").innerHTML = "Turning right";
            break;
        case 38:  // "Up"
            keyboard_ws.send("LOOK UP");
            document.getElementById("move").innerHTML = "Look up";
            break;
        case 40:  // "Down"
            keyboard_ws.send("LOOK DOWN");
            document.getElementById("move").innerHTML = "Look down";
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

    if (ready) {
        // If ready, STOP Disty and show a "waiting for commands" text
        keyboard_ws.send("STOP");
        document.getElementById("move").innerHTML = "Waiting for commands…";
    }

    _prevKeyDown[ev.key] = false;
}


// Bind event listeners
window.addEventListener("keydown", handleMove, false);
window.addEventListener("keyup", handleStop, false);

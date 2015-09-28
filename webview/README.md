Disty webview
=============


This is the webview for Disty, to view the camera and control the robot from a web interface.

Note: You can access disty:8080 for a more complete interface provided by uv4l (but not handling moving).

To use this webview, you will need to enable the Raspberry camera module and
install `uv4l` (and its webrtc associated package).


# Starting it

Just run the Python script `run.py` (as root, because it binds port 80) to
serve the web interface on `disty` (if `disty` resolves to your Disty robot)
port 80.


# Tweaking it

To change the keyboard keys, just edit the `js/keyboard.js` file.


# A few notes

This webinterface uses WebRTC (and Google public STUN server for NAT traversal)
to handle video stream. Audio is not yet supported.

It uses a websocket to communicate with the backend code.

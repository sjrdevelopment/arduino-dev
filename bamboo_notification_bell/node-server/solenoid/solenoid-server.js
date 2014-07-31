var io = require('socket.io').listen(8080);
console.log("init socket");

var sp = require("serialport");
var serialPort = new sp.SerialPort("/dev/tty.usbmodemfd131", {
  baudrate: 9600,
  parser: sp.parsers.readline("\n")
});


io.sockets.on('connection', function (socket) {
    console.log("socket open");

    socket.on('hitBell', function (status) {
        console.log('sending ' + status + 'to Arduino..');
        serialPort.write(status+"\r", function(err, results) {

        });
    });
});


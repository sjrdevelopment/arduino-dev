var http = require('http');
var parseString = require('xml2js').parseString;
var util = require('util');
var sp = require("serialport");
var serialPort = new sp.SerialPort("/dev/tty.usbmodemfd131", {
   baudrate: 9600,
  parser: sp.parsers.readline("\n")
});

serialPort.on("open", function () {    
  console.log('Serial port opened');  
});

var lastBuildNumber = 0;

function parseXML(data) {
  parseString(data, function (err, result) {
    if(err) {
      
    } else {

      
      var currentBuildNumber = result.results.results[0].result[0]['$'].number;
      if(currentBuildNumber !== lastBuildNumber) {
        // new build, get status
        var pass = result.results.results[0].result[0]['$'].state === 'Successful' ? 1 : 0;
        console.log(pass);

        // write pass string to serial port
        serialPort.write(pass + "\r");

        lastBuildNumber = currentBuildNumber;
      } else {
        console.log('Exisiting build: ' + currentBuildNumber);
      }
      
    }
  });
}


var options = {
  host: 'bamboo.lbi.co.uk',
  path: 'http://bamboo.lbi.co.uk/rest/api/latest/result/CX-DEV?os_authType=basic&expand=results[0].result',
  method: 'GET',
  auth: 'robinsos:Kawasaki2'
};


function makeRequest() {
  var bufferLog = '';

  http.request(options, function(res) {
  /*  console.log('STATUS: ' + res.statusCode);
    console.log('HEADERS: ' + JSON.stringify(res.headers));*/
    res.setEncoding('utf8');
    res.on('data', function (chunk) {
      bufferLog += chunk;
      parseXML(bufferLog);
    });

    
  }).end();
}

// Make request every 15 seconds
setInterval(makeRequest, 15000);

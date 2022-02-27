var SerialPort = require("serialport");

const parsers = SerialPort.parsers;
const parser = new parsers.Readline({
    delimeter: '\r\n'
});

var port = new SerialPort('/dev/cu.Bluetooth-Incoming-Port', { 
    baudRate: 9600,
    dataBits: 8,
    parity: 'none',
    stopBits: 1,
    flowControl: false
});

port.pipe(parser);
parser.on('data', function(data) {
    console.log("Recieved data")
    
    // console.log('Received data from port: ' + data);
    
    // io.emit('data', data);
    
});
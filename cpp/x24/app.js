#!/usr/bin/env node
const handler = require('./handler');
const http = require('http');
const https = require('https');
const fs = require('fs');

const WebSocket = require('./ws/');
const process = require('process');

const server = http.createServer();
// const ss = https.createServer({
//   cert: fs.readFileSync('./ws/test/fixtures/certificate2.pem'),
//   key: fs.readFileSync('./ws/test/fixtures/key.pem')
// });
const wss = new WebSocket.Server({ server: server });

const getRandomUtf8Char = function(desiredLength) {
  // 0x1F600
  // 0b00011111011000000000
  // 128512
  // last emojii char 0x1f1fc  (+1806)
  var ret = '';
  let charCode;
  const offsetEmojiStarts = 128512;
  const highBound = 1806;
  for(let i=0; i<desiredLength; ++i)
  {
    charCode = Math.floor(Math.random() * 100000);
    charCode = charCode % highBound; 
    charCode = charCode + offsetEmojiStarts;
    console.log("str: ", ret, " code_added: ", charCode, " String.fromCh...= ", String.fromCharCode(charCode));
    ret = ret.concat(String.fromCharCode(charCode));
  }
  return ret;
};

const onConnection = function(ws) {
    const id = setInterval(function() {
      let dynLenth = 3 + Math.floor(Math.random() * 7);
      ws.send(getRandomUtf8Char(dynLenth), function() {
        //
        // Ignore errors.
        //
      });
    }, 10000);
    console.log('started client interval');

    ws.on('close', function() {
      console.log('stopping client interval');
      clearInterval(id);
    });
};

wss.on('connection', onConnection);

server.on('request', handler.run);

// ss.listen(8081);
server.listen(8080);
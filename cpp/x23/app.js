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

wss.on('connection', function(ws) {
    const id = setInterval(function() {
      ws.send(JSON.stringify(process.memoryUsage()), function() {
        //
        // Ignore errors.
        //
      });
    }, 1000);
    console.log('started client interval');
  
    ws.on('close', function() {
      console.log('stopping client interval');
      clearInterval(id);
    });
  });

server.on('request', handler.run);

// ss.listen(8081);
server.listen(8080);
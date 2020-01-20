#!/usr/bin/env node
const handler = require('./handler');
const http = require('http');
const server = http.createServer();
const WebSocket = require('./ws/');
const process = require('process');


const wss = new WebSocket.Server({ server });

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
server.listen(8080);
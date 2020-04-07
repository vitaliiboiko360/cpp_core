#!/usr/bin/env node
const handler = require('./handler');
const http = require('http');
const https = require('https');
const fs = require('fs');

const WebSocket = require('./ws/');
const process = require('process');
const onConnection = require('./ws-client.js').onConnection;

const server = http.createServer();
// const ss = https.createServer({
//   cert: fs.readFileSync('./ws/test/fixtures/certificate2.pem'),
//   key: fs.readFileSync('./ws/test/fixtures/key.pem')
// });
const wss = new WebSocket.Server({ server: server });

wss.on('connection', onConnection);

server.on('request', handler.run);

// ss.listen(8081);
server.listen(8080);
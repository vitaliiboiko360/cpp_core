#!/usr/bin/env node
const handler = require('./handler');
const http = require('http');
const server = http.createServer();

// server.on('request', handler.echo);
server.on('request', handler.echo);
server.listen(8080);
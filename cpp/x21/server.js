

const http = require('http');

const server = http.createServer((req, res) => {
  res.writeHead(200, {'Content-Type': 'text/plain'});
  res.end('print message\n');
});

server.listen({ host: '0.0.0.0',  port: 8080 });

console.log('Server running at http://127.0.0.1:8080/');
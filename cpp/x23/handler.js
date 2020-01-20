'use strict';

var request = require('http').request;
var response = require('http').response;
var fs = require('fs');

function run(request, response) 
{
    request.on('error', (err) => {
        console.error(err);
    });
    
    router(request, response);
}

function router(request, response) {
    if (request.url === '/client.js')
    {
        return handleClientJs(response);
    }
    if (request.url === '/')
    {
        return handleIndexJs(response);
    }
}

function handleIndexJs(response) {
    fs.readFile('./index.js', function(err, data){
            
        if (err) {
            response.writeHead(404);
            response.end(JSON.stringify(err));
            return;
        }
        response.writeHead(200, {'Content-Type': 'text/html'});
        response.write(data);
        response.end();
    });
}

function handleClientJs(response) {
    fs.readFile('./client.js', function(err, data){
        
        if (err) {
            response.writeHead(404);
            response.end(JSON.stringify(err));
            return;
        }
        response.writeHead(200, {'Content-Type': 'text/javascript'});
        response.write(data);
        response.end();
        return;
    });
}

exports.run = run;
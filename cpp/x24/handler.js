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
    if (request.url === '/')
    {
        return readFileAndWriteContent(response, './index.js', 'text/html')
    }
    if (request.url === '/client.js')
    {
        return readFileAndWriteContent(response, './client.js', 'text/javascript');
    }
}

function readFileAndWriteContent(response, fileName, contentType) {
    fs.readFile(fileName, function(err, data){
        if(err) {
            response.writeHead(404);
            response.end(JSON.stringify(err));
            return;
        }
        response.writeHead(200, {'Content-Type': contentType});
        response.write(data);
        response.end();
    });
}

exports.run = run;
'use strict';

var request = require('http').request;
var response = require('http').response;

function echo(request, response) 
{
    let body = [];
    const { headers, method, url } = request;
    request.on('error', (err)=>{
        console.error(err);
    });
    request.on('data', (chunk)=>{
        body.push(chunk);
    });
    request.on('end', ()=>{
        body = Buffer.concat(body).toString();

        response.on('error', (err) => {
            console.error(err);
          });

        response.statusCode = 200;
        response.setHeader('Content-Type', 'application/json');

        const responseBody = { headers, method, url, body };

        response.write(JSON.stringify(responseBody));
        response.end();
    });

}

exports.echo = echo;
'use strict';
const fs = require('fs');
fs.watch('target.txt', () => console.log('target.txt file changed'));
console.log('watcher.js started ...');
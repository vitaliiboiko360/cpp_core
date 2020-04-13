'use-strict';

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
      //console.log("str: ", ret, " code_added: ", charCode, " String.fromCh...= ", String.fromCharCode(charCode));
      ret = ret.concat(String.fromCharCode(charCode));
    }
    return ret;
  };

  class Actor
  {
    run(ws)
    {
        const id = setInterval(function() {
            let dynLenth = 3 + Math.floor(Math.random() * 7);
            ws.send(getRandomUtf8Char(dynLenth), function() {
                // data send 
            });
          }, 5000);

        console.log('started client interval');

        ws.on('close', function() {
            console.log('stopping client interval');
            clearInterval(id);
          });
    }
  }
  
  const onConnection = function(ws) {
      let actor = new Actor();
      return actor.run(ws);
  };

exports.onConnection = onConnection;
var express = require('express');
var app = express();
var server = require('http').createServer(app);
var io = require('socket.io')(server);

app.use(express.static(__dirname + '/node_modules'));
app.get('/', function (req, res, next) {
  res.sendFile(__dirname + '/index.html');
});

io.on('connection', function (client) {
  console.log('Client connected...');

  client.on('join', function (data) {
    console.log(data);
  });

  client.on('messages', function (data) {
    io.emit('broad', data);
    console.log(data);
  });

  client.on('disconnect', function () {
    console.log('Client disconnected!');
  });
});

server.listen(4200, () => {
  console.log('Server is up and running on port 4200')
});
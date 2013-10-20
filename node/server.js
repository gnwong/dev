/*
 *  server.js
 *    Skeleton for standalone nodejs
 *    webserver with the makings for
 *    websocket functions.
 *
 *  dependencies:
 *    node
 *    express
 *    socket.io
 *  npm install **
 *    -- OR --
 *  make dep
 *
 *  AUTHOR:     George Wong
 *  CREATED:    20 OCT 2013
 *  MODIFIED:   20 OCT 2013
 */

// Useful function definitions go here
function formatDT() {
  var formatted = "";
  var date = new Date();

  formatted += date.getDate()  + "-";
  formatted += date.getMonth() + "-";
  formatted += date.getFullYear() + " | ";
  if (date.getHours()>9) formatted += date.getHours();
  else formatted += "0" + date.getHours();
  formatted += ":";
  if (date.getMinutes()>9) formatted += date.getMinutes();
  else formatted += "0" + date.getMinutes();
  formatted += ":";
  if (date.getSeconds()>9) formatted += date.getSeconds();
  else formatted += "0" + date.getSeconds();

  return formatted; // Returns date-time in format: DD-MM-YYYY | HH:MM:SS
}


/* Main program */
console.log("\n\033[00;31mServer starting...\033[00m \n");

// Load dependencies
var http = require('http');
var express = require('express');

// Create the server
var app = express();
var http = require('http');
var server = http.createServer(app);
var io = require('socket.io').listen(server);

// Configure the server
app.configure(function() {
  app.use(express.static(__dirname + '/public'));
});
io.set('log level', 1);

// Start up the server listening
server.listen(7211);
console.log("\n\033[00;31m... online! \033[00m ")
console.log("\n\033[00;31mStart time was: " + formatDT() + "\033[00m \n"); 

// What to do when a client connects
io.sockets.on('connection', function(socket) {

  // What to do when a client sends a message
  socket.on('message', function(message) {
    // -- EDIT STUFF HERE
  });

  // What to do when a client disconnects
  socket.on('disconnect', function() {
    // -- EDIT STUFF HERE
  });

});

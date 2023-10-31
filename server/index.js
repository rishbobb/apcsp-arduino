import express from "express";
import { execSync } from "child_process";
import { SerialPort } from "serialport";
import { createInterface } from "readline";
import { WebSocketServer } from "ws";

// expressjs rest api
const app = express();
const port = 3000;
// ws server
const wss = new WebSocketServer({ port: 6969 });
// holds lines received from arduino serial
let lines = [];

// initialize serial connection with arduino
const arduino = new SerialPort({
  path: "/dev/ttyACM0",
  baudRate: 2000000,
});

// read lines as they come in and push to console and lines array
var lineReader = createInterface({
  input: arduino,
});

lineReader.on("line", function (line) {
  lines.push(line);
  console.log(line);
});

// send data from ws to arduino
wss.on("connection", (ws) => {
  ws.on("message", (data) => {
    console.log(`Got direction ${data} from ws`);
    // send data to arduino
    arduino.write(data);
  });
});

// allow cors
app.use(function (req, res, next) {
  res.setHeader("Access-Control-Allow-Origin", "*");
  res.setHeader("Access-Control-Allow-Methods", "GET, PUT, POST");
  res.setHeader(
    "Access-Control-Allow-Headers",
    "Origin, X-Requested-With, Content-Type, Accept"
  );
  next();
});

// static html for frontend
app.use(express.static("static"));

// endpoint for updating the server
app.get("/update", (req, res) => {
  // run update script
  execSync("../scripts/update.sh");
  res.setHeader("Content-Type", "application/json");
  res.end(JSON.stringify({ success: true }));
});

// endpoint for compiling and flashing arduino
app.get("/flash", (req, res) => {
  // run flash script
  execSync("../scripts/flash.sh");
  res.setHeader("Content-Type", "application/json");
  res.end(JSON.stringify({ success: true }));
});

// endpoint for getting sensor data from arduino
app.get("/data", (req, res) => {
  // clear lines array
  lines = [];
  // execute command for arduino to get data and send it
  arduino.write("4");
  // wait for serial to recieve 3 lines
  let timeoutfunc = () => {
    if (lines.length >= 3) {
      // once 3 lines receieved, send it in json data to client
      res.setHeader("Content-Type", "application/json");
      res.end(
        JSON.stringify({
          success: true,
          front: lines[0],
          back: lines[1],
          sound: lines[2],
        })
      );
    } else {
      setTimeout(timeoutfunc, 500);
    }
  };
  setTimeout(timeoutfunc, 500);
});

// endpoint for sending commands to arduino (same as ws)
app.get("/direction", (req, res) => {
  console.log(`Got direction ${req.query.direction}`);
  // send data to arduino
  arduino.write(req.query.direction);
  res.setHeader("Content-Type", "application/json");
  res.end(JSON.stringify({ success: true, direction: req.query.direction }));
});

// just to check if webserver is alive
app.get("/alive", (req, res) => {
  res.setHeader("Content-Type", "application/json");
  res.end(JSON.stringify({ alive: true }));
});

// Start server
app.listen(port, async () => {
  console.log(`listening on port ${port}`);
});

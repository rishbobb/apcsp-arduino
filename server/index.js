import express from "express";
import { execSync } from "child_process";
import { SerialPort } from "serialport";
import * as pcm from "pcm";
import * as dotenv from "dotenv";
import { createInterface } from "readline";
dotenv.config();

const app = express();
const port = 3000;

const arduino = new SerialPort({
  path: "/dev/ttyUSB0",
  baudRate: 1000000,
});

var lineReader = createInterface({
  input: arduino
});

lineReader.on('line', function (line) {
  console.log(line);
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

// static html
app.use(express.static("static"));

app.get("/update", (req, res) => {
  execSync("../scripts/update.sh");
  res.setHeader("Content-Type", "application/json");
  res.end(JSON.stringify({ success: true }));
});

app.get("/flash", (req, res) => {
  execSync("../scripts/flash.sh");
  res.setHeader("Content-Type", "application/json");
  res.end(JSON.stringify({ success: true }));
});

app.get("/direction", (req, res) => {
  arduino.write(`${req.query.direction}\n`);
  res.setHeader("Content-Type", "application/json");
  res.end(JSON.stringify({ success: true, direction: req.query.direction }));
});

function sleep(ms) {
  return new Promise((resolve) => {
    setTimeout(resolve, ms);
  });
}

app.get("/alive", (req, res) => {
  res.setHeader("Content-Type", "application/json");
  res.end(JSON.stringify({ alive: true }));
});

app.listen(port, async () => {
  console.log(`listening on port ${port}`);
});

import express from "express";
import { execSync } from "child_process";
import { SerialPort } from "serialport";
import * as pcm from "pcm";
import * as dotenv from "dotenv";
dotenv.config();

const app = express();
const port = 3000;

const arduino = new SerialPort({
  path: "/dev/ttyUSB0",
  baudRate: 9600,
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

app.get("/text", (req, res) => {
  arduino.write(`${JSON.stringify({ type: "w", line: req.query.text })}\n`);
  res.setHeader("Content-Type", "application/json");
  res.end(JSON.stringify({ success: true }));
});

app.get("/freq", (req, res) => {
  arduino.write(
    `${JSON.stringify({ type: "s", hz: parseInt(req.query.hz) })}\n`
  );
  res.setHeader("Content-Type", "application/json");
  res.end(JSON.stringify({ success: true }));
});

function sleep(ms) {
  return new Promise((resolve) => {
    setTimeout(resolve, ms);
  });
}

app.get("/music", (req, res) => {
  let samples = [];
  pcm.getPcmData(
    "temp/audio.mp3",
    { stereo: true, sampleRate: 20 },
    function (sample, channel) {
      samples.push(sample * 1000000);
    },
    async function (err, output) {
      // if (err) throw new Error(err);
      for (let i = 0; i < samples.length; i++) {
        arduino.write(
          `${JSON.stringify({ type: "s", hz: samples[i].toFixed(0) })}\n`
        );
        await sleep(1000 / 20);
      }
      res.setHeader("Content-Type", "application/json");
      res.end(JSON.stringify({ success: true }));
    }
  );
});

app.get("/alive", (req, res) => {
  res.setHeader("Content-Type", "application/json");
  res.end(JSON.stringify({ alive: true }));
});

app.listen(port, async () => {
  console.log(`listening on port ${port}`);
});

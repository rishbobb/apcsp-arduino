import express from "express";
import { execSync } from "child_process";
import * as dotenv from "dotenv";
dotenv.config();

const app = express();
const port = 3000;

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

app.get("/update", (req, res) => {
  execSync("sudo ../scripts/update.sh");
});

app.get("/flash", (req, res) => {
  execSync("../scripts/flash.sh");
});

app.listen(port, async () => {
  console.log(`listening on port ${port}`);
});

# apcsp-arduino
- This is the repository for my final arduino project for AP Computer Science Principles.
- The project consists of an arduino mega connected to multiple devices like LEDs, Ultrasonic sensors, DC Motors, and a sound detector. The arduino mega is then connected to a Raspberry Pi 3 through USB serial, and communicates with the Pi. The Pi is connected to the internet and communicates with clients through a web server and an HTML frontend.

- Directory Structure:
  - arduino: c++ code run on the arduino
  - server: nodejs REST API server code that runs on the RPI
    - index.js: the code that runs the expressjs REST API server
    - static/index.html: the HTML frontend code
  - systemd: systemd service files so that the server runs on startup on the pi
  - scripts: scripts to do various things like update the repo or flash the arduino

 - All important code files like c++ files, index.js and index.hml are commented

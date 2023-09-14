git -C /home/pi/apcsp-arduino reset --hard
git -C /home/pi/apcsp-arduino pull
# cd /home/pi/apcsp-arduino/server && /home/pi/.nvm/versions/node/v19.3.0/bin/npm i
sudo systemctl restart arduinoserver.service
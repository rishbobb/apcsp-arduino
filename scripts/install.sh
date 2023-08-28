sudo mv ./systemd/arduinoserver.service /etc/systemd/system
sudo systemctl daemon-reload
sudo systemctl enable arduinoserver.service
sudo systemctl start arduinoserver.service
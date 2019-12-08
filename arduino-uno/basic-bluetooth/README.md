# Arduino
Set up Arduino project on Linux Fedora

### Install Arduino
1. Go to https://www.arduino.cc/en/Main/Software
2. Download Arduino IDE for `Linux 64 bits`
3. Uncompress the file.  After this, you should have a folder `arduino-1.8.5-linux64` in ~/Downloads.
4. Bring up a terminal and run
```
cp ~/Downloads/arduino-1.8.5-linux64/arduino-1.8.5 ~/
cd ~/arduino-1.8.5
./install.sh
```
5. Launch Arduino IDE

### Get the project files
```
cd git
git clone git@github.com:hungple/arduino.git
```

### Add Makeblock files into Arduino libary
Run the following command:
```
cd
cp ~/git/arduino/Makeblock-Library-master/makeblock ~/Arduino/libraries/
```

### Connect your Arduino to your laptop
1. Connect USB cable
2. Launch Arduino IDE
3. Select Tools > Board > Arduino Uno
4. Select Tools > Port > /dev/ttyUSB0
5. Run
```
sudo chown <username> /dev/ttyUSB0
```
6. Select Tools > Serial Monitor
7. Power on your Arduino board
8. Connect your phone's bluetooth to your bluetooth device.
9. Test and ensure that you see data is sending in the Serial Monitor

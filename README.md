# Arduino
Set up Arduino project on Linux Fedora

### Install Arduino IDEt
1. Go to https://www.arduino.cc/en/Main/Software
2. Download Arduino IDE for `Linux 64 bits` image.
3. Open File Manager and goto ~/Downloads folder. Double click to uncompress the newly downloaded file.  After this, you should have a folder `arduino-1.8.5-linux64` in ~/Downloads.
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
3. Launch a terminal and run
```
ls /dev/tty*
```
You may have to wait a few minutes for the device to show up. The new device name may be `ttyUSB0` or `ttyACM0`
4. Change device's owner
```
sudo chown <username> /dev/<Arduino device name> 
```
Example:
```
sudo chown simon /dev/ttyACM0
```
5. Select Tools > Board > Arduino Uno
6. Select Tools > Port > /dev/<Arduino device name> (/dev/ttyUSB0 or /dev/ttyACM0)
7. Select Tools > Serial Monitor
8. Power on your Arduino board
9. Test and ensure that you see data is sending in the Serial Monitor

# arduino
Set up Arduino project on Linux Fedora

### Install Arduino
1. Go to https://www.arduino.cc/en/Main/Software
2. Download Arduino IDE for `Linux 64 bits`
3. Run
```
cd ~/Download
tar xzvf arduino-1.8.5-linux64.tar.xz
mv arduino-1.8.5-linux64/arduino-1.8.5 ~/
cd ~/arduino-1.8.5
./install.sh
```

### Get the files
```
cd git
git clone git@github.com:hungple/arduino.git
```

### Add Makeblock files into Arduino libary
```
cd
cp ~/git/Makeblock-Library-master/makeblock ~/Arduino/libraries/
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
7. Connect your phone bluetooth to your your car.
8. Test and ensure that you see data is shown in the Serial Monitor

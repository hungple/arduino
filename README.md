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

### Set up workspace
```
cd <your working directory>
git clone git@github.com:hungple/arduino.git
```

### Add Makeblock file into Arduino libary

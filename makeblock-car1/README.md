# Arduino Car
Set up your car project


### Connect your Arduino to your laptop
1. Connect USB cable
2. Launch Arduino IDE
3. Select Tools > Board > Arduino Uno
4. Select Tools > Port > /dev/ttyUSB0
5. Bring up a terminal and run
```
sudo chown <username> /dev/ttyUSB0
```
6. Select Tools > Serial Monitor
7. From your phone, launch your Bluetooth RC Controller app and connect to bluetooth device on your car.
8. Test and ensure that you see data is sending in the Serial Monitor


### Upload your code into Arduino
1. From Arduino IDE, click Verify/Compile button to ensure your code is free of bug.
2. Click Upload button to upload your code to your Arduino board
3. Power on your Arduino board
4. Test your car

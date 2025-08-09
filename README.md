# ESP8266 Bluetooth Robot Car

A wireless robot car controlled via Bluetooth using ESP8266 microcontroller and HC-05 Bluetooth module. Control your robot car remotely from your smartphone or any Bluetooth-enabled device!

##  Features

- **Wireless Control**: Control via Bluetooth using HC-05 module
- **Multiple Movement Modes**: Forward, backward, left, right, curved turns
- **Variable Speed Control**: 10 speed levels (0-9)
- **LED Control**: Turn built-in LED on/off remotely
- **Connection Status**: LED blinks when disconnected, solid when connected
- **Real-time Feedback**: Receive status messages via Bluetooth

##  Hardware Requirements

- **ESP8266 Development Board** (NodeMCU, Wemos D1 Mini, etc.)
- **HC-05 Bluetooth Module**
- **L298N Motor Driver**
- **2x DC Motors** (for differential drive)
- **Robot Car Chassis**
- **Jumper Wires**
- **Power Supply**:
  - ESP8266: 3.3V (via USB or external)
  - ** HC-05: 3.6V - 6V separate power source required**
  - Motors: 6V - 12V (depending on motor specifications)

## ⚠️ Important Power Warning

**The HC-05 module requires a separate power source between 3.6V - 6V!**

- **DO NOT** power HC-05 directly from ESP8266's 3.3V pin - it may cause unstable operation
- **DO NOT** use 5V if your HC-05 is a 3.3V logic level module
- Use a proper voltage regulator or dedicated power supply for reliable operation
- Check your HC-05 module specifications before connecting

##  Wiring Diagram

### ESP8266 to L298N Motor Driver
```
ESP8266    →    L298N
D1         →    IN1 (Left Motor)
D2         →    IN2 (Left Motor) 
D3         →    ENA (Left Motor PWM)
D4         →    IN3 (Right Motor)
D5         →    IN4 (Right Motor)
D6         →    ENB (Right Motor PWM)
GND        →    GND
```

### ESP8266 to HC-05 Bluetooth Module
```
ESP8266    →    HC-05
TX (GPIO1) →    RX
RX (GPIO3) →    TX
GND        →    GND
```

### HC-05 Power Connection
```
Power Source (3.6V-6V)    →    HC-05 VCC
GND                       →    HC-05 GND
```

### Motors to L298N
```
Left Motor   →   OUT1, OUT2
Right Motor  →   OUT3, OUT4
```

##  Control Commands

| Command | Action |
|---------|--------|
| `F` | Move Forward |
| `B` | Move Backward |
| `L` | Turn Left |
| `R` | Turn Right |
| `G` | Curve Forward Left |
| `H` | Curve Forward Right |
| `S` | Stop All Motors |
| `0-9` | Set Speed (0=Stop, 9=Maximum) |
| `O` | LED On |
| `X` | LED Off |

##  Getting Started

### 1. Hardware Setup
1. Assemble your robot car chassis with motors
2. Connect components according to wiring diagram
3. **Ensure HC-05 has proper power supply (3.6V-6V)**
4. Double-check all connections

### 2. Software Setup
1. Install Arduino IDE
2. Install ESP8266 board package
3. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/esp8266-bluetooth-robot-car.git
   ```
4. Open `esp8266_robot_car.ino` in Arduino IDE

### 3. Upload Code
1. **Disconnect HC-05 temporarily** (shares UART with programming)
2. Select your ESP8266 board and COM port
3. Upload the code
4. Reconnect HC-05 after upload completes

### 4. Bluetooth Pairing
1. Power on your robot car
2. Search for Bluetooth devices on your phone
3. Look for "HC-05" device (default PIN: `1234` or `0000`)
4. Install a Bluetooth terminal app (like "Serial Bluetooth Terminal")
5. Connect to HC-05 and start sending commands!

##  Recommended Apps

**Android:**
- Serial Bluetooth Terminal
- Bluetooth Electronics
- Arduino Bluetooth Control

**iOS:**
- LightBlue Explorer
- Bluetooth Terminal

##  Customization

### Adjusting Speed Values
Modify speed ranges in the code (ESP8266 uses 0-1023 for PWM):
```cpp
case '1': valSpeed = 100; break;  // Adjust these values
case '2': valSpeed = 200; break;
// ... etc
```

### Adding New Commands
Add new cases in the `processCommand()` function:
```cpp
case 'N': {  // New command
    // Your custom action here
    Serial.println("New Action!");
    break;
}
```

## Troubleshooting

### Common Issues:

**Robot doesn't respond to Bluetooth:**
- Check HC-05 power supply (must be 3.6V-6V)
- Verify RX/TX connections aren't swapped
- Ensure HC-05 is paired and connected

**Motors don't move:**
- Check L298N power connections
- Verify motor driver connections
- Test with higher speed values (try '5' or above)

**Can't upload code:**
- Disconnect HC-05 during upload (shares UART)
- Check ESP8266 board selection and COM port


### Debug Mode:
Disconnect HC-05 and use Serial Monitor (9600 baud) to test commands via USB.

##  License

This project is open source and available under the [MIT License](LICENSE).

##  Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

##  Support

If you encounter any issues or have questions:
- Open an issue on GitHub
- Check the troubleshooting section above
- Verify your wiring matches the diagram exactly

##  Show Your Support

If this project helped you, please give it a ⭐ on GitHub!

---

**Happy Building! 🤖**

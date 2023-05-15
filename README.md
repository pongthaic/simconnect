# FS Panel Project
This is for ESP8266

## Hardware Requirements
- 1 x LCD 16x02 I2C address = 0x27
- 2 x Rotary Encoders
- 1 x OLED 0.91" display SSD1306 128 x 64 pixel, address = 0x3C
- 1 x PCF8574 I2C pin extensions, address = 0x20
- 1 x ESP8266 v2
- 1 x On-off switch
- 2 x LED (Green >> power indicator, Red >> multipurpose)
- 1 x push button

## Wiring
- D0
- D1 - I2C SCL, connects to SCL of LCD1602, PCF8574, OLED SSD1306
- D2 - I2C SDA, connects to SDA of LCD1602, PCF8574, OLED SSD1306
- D3
- D4
- 3V3
- G
- D5
- D6 
- D7 - Rotary Encoder 1 DT
- D8 - Rotary Encoder 1 CLK
- RX
- TX
- GND - Supplies to PCF8574
- 3V3 - Supplies to PCF8574

- ADC0
- G   - Ground for 5V components
- VV  - 5V Power Source
- SD3
- SD2
- SD1
- SDC
- SD0
- SDCLK
- G
- 3V3
- EN
- RST
- G
- Vin


The PCF Pins
0 - Output LED
1 - Display Mode Switcher
2 - Input Mode Switcher
3 - Rotary 1 SW
4 - SW4
5 - SW3
6 - SW2
7 - SW1

## Functions

### Initial Stage
- Connects to Wifi network
- Start the web server to receive pushes from FS host
- When connected, LCD display IP address so that host can find the client.

### Operating Stage
- OLED displays mode of operations on top, and the value on the bottom. Available Modes are: VOR1 -> VOR2 -> COM1 -> COM2 -> DME -> ALT -> HDG -> CRS
- 
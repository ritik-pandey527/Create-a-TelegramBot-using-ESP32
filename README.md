# Telegram Bot with ESP32

This project enables you to create a Telegram bot using an ESP32 to perform tasks like controlling relays, retrieving sensor data, setting thresholds, and executing commands based on received inputs.

---

## Features
- Control relays or devices remotely.
- Retrieve sensor data in real-time.
- Add and remove authorized users.
- Execute custom tasks based on Telegram bot commands.

---

## Hardware Requirements
- ESP32 Development Board
- Wi-Fi network
- Additional peripherals (e.g., relays, sensors) as needed for your project logic

---

## Software Requirements
- Arduino IDE
- Telegram App

---

## Setup Steps

### Step 1: Create a Telegram Bot
1. Download and login to the Telegram app.
2. Search for `@BotFather` in Telegram and click **Start**.
3. Use the `/newbot` command to create a bot.
4. Assign a name and username to your bot. Once created, you will receive a bot link and HTTP API Token. Note both.

### Step 2: Get Your Chat ID
1. Search for `@myidbot` in Telegram and click **Start**.
2. Use the `/getid` command to retrieve your Chat ID. Note it down.

### Step 3: Setup Arduino IDE
1. Install Arduino IDE from [Arduino Downloads](https://www.arduino.cc/en/software).
2. Add the ESP32 board by navigating to **File > Preferences > Additional Boards Manager URLs**, and paste this URL:
   ```
   https://dl.espressif.com/dl/package_esp32_index.json
   ```
3. Go to **Tools > Board > Boards Manager**, search for "ESP32," and install it.
4. Install the required libraries:
   - WiFi
   - WiFiClientSecure
   - UniversalTelegramBot
   - ArduinoJson
   - SPI

### Step 4: Configure the Code
1. Open `Create_Telegram_Bot.ino` in Arduino IDE.
2. Replace the placeholders with your specific details:
   ```cpp
   const char* ssid = "your_ssid";
   const char* password = "your_password";
   #define BOTtoken "your_HTTP_Api"
   String CHAT_ID = "your_chat_id";
   ```
3. Upload the code to the ESP32 using a USB cable.

### Step 5: Add Your Project Logic
Modify the `handleNewMessages()` function to include custom commands and actions.

---

## Commands Supported
- `/start` - Displays the welcome message and available commands.
- `/A` - Executes Task A.
- `/Users` - Lists authorized user Chat IDs.
- `/User_add` - Allows the bot owner to add new authorized users.
- `/User_remove` - Allows the bot owner to remove authorized users.

---

## Example Workflow
1. Start the bot using the `/start` command.
2. Check the authorized users with `/Users`.
3. Add a new user with `/User_add` (owner only).
4. Remove a user with `/User_remove` (owner only).
5. Execute Task A using `/A`.

---

## Notes
- Ensure the ESP32 is connected to a stable Wi-Fi network.
- Use the UniversalTelegramBot library for handling Telegram bot communication.
- Keep your HTTP API Token and Chat ID secure.

---

## Troubleshooting
- **Wi-Fi not connecting**: Verify SSID and password in the code.
- **Bot not responding**: Check the Telegram HTTP API Token and Chat ID.
- **Adding/removing users not working**: Ensure you are the owner (bot creator).
- **No response for commands**: Verify the ESP32 serial monitor for errors.

---

## References
- [Universal Telegram Bot Library](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot)
- [ESP32 Arduino Core Documentation](https://docs.espressif.com/projects/arduino-esp32/en/latest/index.html)

---

Enjoy building your Telegram bot with ESP32!


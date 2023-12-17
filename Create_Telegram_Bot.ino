#include <WiFi.h>

#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <SPI.h>

const char* ssid = "your_ssid";
const char* password = "your_password";

#define BOTtoken "your_HTTP_Api"
String CHAT_ID = "your_chat_id";
String ALLOWED_CHAT_IDS = "your_chat_id";


WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int botRequestDelay = 500;
unsigned long lastTimeBotRan;

String userChatID = "";
bool ledState = LOW;
bool isAddingChatID = false;
bool isRemovingChatID = false;

void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    if (ALLOWED_CHAT_IDS.indexOf(chat_id) == -1) {
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }

    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      bot.sendMessage(chat_id, "Wait...", "");
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Use the following commands to control the system:\n\n";
      welcome += "/A - Command A\n";
      welcome += "/B - Command B\n";
      welcome += "/Users - Check Allowed Chat IDs\n";
      welcome += "/User_add - Add Chat ID\n";
      welcome += "/User_remove - Remove Chat ID\n";
      bot.sendMessage(chat_id, welcome, "");
    } else if (text == "/A") {
      bot.sendMessage(chat_id, "Wait...", "");
      bot.sendMessage(chat_id, "Preforming Task Task A...", "");
      String a = "Task A Done";
      bot.sendMessage(chat_id, a, "");
    } else if (text == "/Users") {
      bot.sendMessage(chat_id, "Wait...", "");
      String message = "Allowed Chat IDs:\n";
      for (size_t i = 0; i < ALLOWED_CHAT_IDS.length(); i++) {
        if (ALLOWED_CHAT_IDS[i] == ',') {
          message += '\n';
        } else {
          message += ALLOWED_CHAT_IDS[i];
        }
      }
      bot.sendMessage(chat_id, message, "");
    } else if (text == "/User_add") {
      bot.sendMessage(chat_id, "Wait...", "");
      if (chat_id == CHAT_ID) {
        bot.sendMessage(chat_id, "Please provide the chat ID you want to add to the allowed list:", "");
        isAddingChatID = true;
      } else {
        bot.sendMessage(chat_id, "Unauthorized access. Only the bot owner can grant user control.", "");
      }
    } else if (isAddingChatID && chat_id == CHAT_ID) {
      if (userChatID == "") {
        userChatID = text;
        bot.sendMessage(chat_id, "Please enter the chat ID again to confirm:", "");
      } else if (userChatID == text) {
        ALLOWED_CHAT_IDS += "," + text;
        bot.sendMessage(chat_id, "User chat ID added to allowed list.", "");
        userChatID = "";
        isAddingChatID = false;
      }
    } else if (text == "/User_remove") {
      bot.sendMessage(chat_id, "Wait...", "");
      if (chat_id == CHAT_ID) {
        bot.sendMessage(chat_id, "Please provide the chat ID you want to remove from the allowed list:", "");
        isRemovingChatID = true;
      } else {
        bot.sendMessage(chat_id, "Unauthorized access. Only the bot owner can remove users.", "");
      }
    } else if (isRemovingChatID && chat_id == CHAT_ID) {
      int userIndex = ALLOWED_CHAT_IDS.indexOf(text);
      if (userIndex != -1) {
        ALLOWED_CHAT_IDS.remove(userIndex, text.length() + 1);  // +1 to remove comma as well
        bot.sendMessage(chat_id, "User chat ID removed from allowed list.", "");
      } else {
        bot.sendMessage(chat_id, "The provided chat ID was not found in the allowed list.", "");
      }
      isRemovingChatID = false;
    } else {
      bot.sendMessage(chat_id, "Wait...", "");
      bot.sendMessage(chat_id, "Invalid Input", "");
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Use the following commands to control the system:\n\n";
      welcome += "/A - Command A\n";
      welcome += "/B - Command B\n";
      welcome += "/Users - Check Allowed Chat IDs\n";
      welcome += "/User_add - Add Chat ID\n";
      welcome += "/User_remove - Remove Chat ID\n";
      bot.sendMessage(chat_id, welcome, "");
    }
  }
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println(WiFi.localIP());
}

void loop() {

  if (millis() > lastTimeBotRan + botRequestDelay) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    if (numNewMessages > 0) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
    }
    lastTimeBotRan = millis();
  } 
}
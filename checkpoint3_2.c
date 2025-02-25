#include <WiFi.h>
#include <time.h>

// ใส่ข้อมูล WiFi ของคุณ
const char* ssid     = "i don't give you";
const char* password = "09 12 48";

// ตั้งค่า Timezone (ตัวอย่าง: เวลาไทย = GMT+7)
const long gmtOffset_sec = 3 * 3600;     
const int  daylightOffset_sec = 0;       // ถ้าไม่มี Daylight saving ก็ใส่ 0
const char* ntpServer = "pool.ntp.org";  // หรือใช้ ntp.ubuntu.com ก็ได้

void setup() {
  Serial.begin(19200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");

  // ตั้งค่าเวลาให้ ESP32 โดยดึงจาก NTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop() {
  // สร้าง struct tm เพื่อรับค่าจาก time.h
  struct tm timeinfo;
  
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    delay(1000);
    return;
  }

  // สร้าง buffer เพื่อเก็บข้อความวันที่เวลา
  char timeString[50];
  // รูปแบบการพิมพ์ตัวอย่าง: "Wednesday, January 05 2022 02:34:01"
  strftime(timeString, 
           sizeof(timeString), 
           "%A, %B %d %Y %H:%M:%S", 
           &timeinfo);

  Serial.println(timeString);
  delay(1000); // หน่วง 1 วินาที
}
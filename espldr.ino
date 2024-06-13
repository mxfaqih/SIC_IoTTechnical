#include <WiFi.h>
#include <HTTPClient.h>

// Mengganti dengan kredensial WiFi Anda
const char* ssid = "Wifi Choi";
const char* password = "tanpapassword";

// Alamat server lokal
const char* serverName = "http://192.168.1.89:8000/api/ldr";

// Pin sensor LDR
const int ldrPin = 34;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Terhubung ke WiFi dengan IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Membaca nilai sensor LDR
  int ldrValue = analogRead(ldrPin);

  // Membuat HTTP POST request
  HTTPClient http;
  http.begin(serverName);
  http.addHeader("Content-Type", "application/json");
  String requestBody = "{\"ldr_value\":" + String(ldrValue) + "}";
  int httpResponseCode = http.POST(requestBody);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("Respons dari server: " + response);
  } else {
    Serial.println("Gagal mengirim data. Kode respons: " + String(httpResponseCode));
  }

  http.end();
  delay(5000); // Menunggu 5 detik sebelum mengambil data berikutnya
}
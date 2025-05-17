/*
  WiFiAccessPoint.ino membuat access point WiFi dan menyediakan server web di dalamnya.

  Langkah:
  1. Hubungkan ke access point bernama "UHUY"
  2. Buka browser dan akses http://192.168.4.1/H untuk menyalakan LED atau http://192.168.4.1/L untuk mematikannya
     ATAU
     Gunakan perintah TCP mentah seperti "GET /H" dan "GET /L" di terminal PuTTY dengan IP 192.168.4.1 dan port 80

  Dibuat untuk arduino-esp32 pada 04 Juli 2018 oleh Elochukwu Ifediora (fedy0)
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#define LED_BUILTIN 2   // Tetapkan pin GPIO tempat LED uji terhubung. Gunakan pin 2 jika tidak ada LED bawaan

// Nama dan password access point yang ingin dibuat
const char *ssid = "UHUY";
const char *password = "123456789";

// Inisialisasi server web pada port 80
WiFiServer server(80);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Set pin LED sebagai output

  Serial.begin(115200); // Memulai komunikasi serial
  Serial.println();
  Serial.println("Mengkonfigurasi access point...");

  // Membuat access point dengan nama dan password
  if (!WiFi.softAP(ssid, password)) {
    Serial.println("Gagal membuat access point.");
    while(1); // Berhenti di sini jika gagal
  }

  // Menampilkan alamat IP dari access point yang dibuat
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Alamat IP AP: ");
  Serial.println(myIP);
  server.begin(); // Memulai server

  Serial.println("Server dimulai");
}

void loop() {
  // Menunggu koneksi dari klien
  WiFiClient client = server.available();   

  if (client) {                             
    Serial.println("Klien baru terhubung."); 
    String currentLine = "";                // Menyimpan data dari permintaan HTTP klien

    while (client.connected()) {            // Selama klien masih terhubung
      if (client.available()) {             // Jika ada data dari klien
        char c = client.read();             // Baca 1 karakter
        Serial.write(c);                    // Tampilkan karakter ke Serial Monitor

        if (c == '\n') {                    // Jika karakter adalah newline (akhir baris)
          if (currentLine.length() == 0) {  // Jika 2 baris kosong berturut-turut, permintaan selesai
            // Kirim header HTTP
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // Isi dari halaman web yang dikirim ke klien
            client.print("Klik <a href=\"/H\">di sini</a> untuk MENYALAKAN LED.<br>");
            client.print("Klik <a href=\"/L\">di sini</a> untuk MEMATIKAN LED.<br>");

            // Akhiri respon HTTP
            client.println();
            break; // Keluar dari loop karena permintaan selesai
          } else {
            currentLine = ""; // Kosongkan currentLine untuk baris baru
          }
        } else if (c != '\r') {  // Abaikan karakter carriage return
          currentLine += c;     // Tambahkan karakter ke currentLine
        }

        // Periksa apakah permintaan adalah "GET /H" atau "GET /L"
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(LED_BUILTIN, HIGH); // Nyalakan LED
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LED_BUILTIN, LOW);  // Matikan LED
        }
      }
    }
    // Tutup koneksi dengan klien setelah permintaan selesai
    client.stop();
    Serial.println("Klien terputus.");
  }
}

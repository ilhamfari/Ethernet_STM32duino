#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>  // Menambahkan pustaka PubSubClient untuk MQTT

// Alamat MAC untuk Ethernet Shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Alamat IP statis jika DHCP gagal
#define MYIPADDR 172,20,0,67
#define MYIPMASK 255,255,255,0
#define MYDNS 172,20,0,254
#define MYGW 203,6,148,2

// Variabel untuk angka
int angka = 0;

// Membuat objek EthernetClient dan objek PubSubClient untuk komunikasi MQTT
EthernetClient ethClient;
PubSubClient client(ethClient);

// Konfigurasi MQTT
const char* mqtt_server = "broker.emqx.io"; // Mengganti dengan broker MQTT lain
const int mqtt_port = 1883; // Port default untuk MQTT

const char* topic_publish = "iot/test/angka"; // Topik untuk mengirimkan data angka

void setup() {
  Serial.begin(115200); // Memulai komunikasi serial
  delay(1000);
  Serial.println("Begin Ethernet");

  // Inisialisasi Ethernet dan DHCP
  Ethernet.init(PA4);
  if (Ethernet.begin(mac)) { // Dynamic IP setup
    Serial.println("DHCP OK!");
  } else {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Jika DHCP gagal, atur IP statis
    IPAddress ip(MYIPADDR);
    IPAddress dns(MYDNS);
    IPAddress gw(MYGW);
    IPAddress sn(MYIPMASK);
    Ethernet.begin(mac, ip, dns, gw, sn);
    Serial.println("STATIC OK!");
  }

  // delay(1000);

  // Menampilkan informasi IP lokal
  Serial.print("Local IP : ");
  Serial.println(Ethernet.localIP());
  Serial.print("Subnet Mask : ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("Gateway IP : ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("DNS Server : ");
  Serial.println(Ethernet.dnsServerIP());

  Serial.println("Ethernet Successfully Initialized");

  // Setup MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  // Koneksi ke broker MQTT
  reconnect();
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Tidak digunakan dalam kasus ini, bisa disesuaikan jika ada pesan yang masuk
}

void reconnect() {
  // Mencoba untuk terhubung ke broker MQTT jika koneksi terputus
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("EthernetClient")) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed to connect. State: ");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

void loop() {
  // Cek koneksi MQTT
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Kirimkan angka ke broker MQTT setiap detik
  PublishData();

  delay(1000); // Delay 1 detik sebelum mengirimkan data lagi
}

void PublishData() {
  // Format payload untuk mengirimkan nilai angka
  String payload = String(angka);

  // Publish data ke broker MQTT
  if (client.publish(topic_publish, payload.c_str())) {
    Serial.println("Data angka sent to MQTT: " + payload);

    // Menyalakan LED setelah berhasil mengirim data
    digitalWrite(PC13, HIGH);  // LED menyala
  } else {
    Serial.println("Failed to send data angka");
    
    // Mematikan LED jika pengiriman gagal
    digitalWrite(PC13, LOW);   // LED mati
  }

  angka++; // Increment angka
}
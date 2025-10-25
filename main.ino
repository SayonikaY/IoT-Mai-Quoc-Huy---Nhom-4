// Code cho Wokwi - Sử dụng Serial Monitor thay vì Bluetooth
// Trên phần cứng thực, uncomment phần Bluetooth và comment phần Serial

// ========== PHẦN CHO WOKWI (Serial Monitor) ==========
// Comment phần này khi dùng với phần cứng thực

// Định nghĩa chân GPIO cho các relay
#define RELAY1_PIN 13  // Đèn 1
#define RELAY2_PIN 12  // Đèn 2  
#define RELAY3_PIN 14  // Quạt

// Biến lưu trạng thái các thiết bị
bool den1_state = false;
bool den2_state = false;
bool quat_state = false;

void setup() {
  Serial.begin(115200);
  delay(1000); // Đợi Serial khởi động
  
  Serial.println("\n\n=================================");
  Serial.println("HỆ THỐNG ĐIỀU KHIỂN NHÀ THÔNG MINH");
  Serial.println("=================================");
  Serial.println("Thiết bị đã sẵn sàng!");
  
  // Cấu hình các chân relay là OUTPUT
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(RELAY3_PIN, OUTPUT);
  
  // Tắt tất cả relay lúc khởi động (relay active LOW)
  digitalWrite(RELAY1_PIN, LOW);
  digitalWrite(RELAY2_PIN, LOW);
  digitalWrite(RELAY3_PIN, LOW);
  
  Serial.println("Đã tắt tất cả thiết bị.");
  
  // In hướng dẫn
  printHelp();
  Serial.println("\nNhập lệnh và nhấn Enter:");
}

void loop() {
  // Kiểm tra có dữ liệu từ Serial Monitor không
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim(); // Xóa khoảng trắng
    command.toLowerCase(); // Chuyển về chữ thường
    
    if (command.length() > 0) {
      processCommand(command);
      Serial.println("\nNhập lệnh tiếp theo:");
    }
  }
}

void processCommand(String command) {
  Serial.println(">>> Lệnh nhận được: " + command);
  
  // Điều khiển Đèn 1
  if (command == "den1 on" || command == "1 on" || command == "d1 on") {
    den1_state = true;
    digitalWrite(RELAY1_PIN, HIGH); // Relay active LOW
    Serial.println("  Đèn 1: BẬT");
  }
  else if (command == "den1 off" || command == "1 off" || command == "d1 off") {
    den1_state = false;
    digitalWrite(RELAY1_PIN, LOW);
    Serial.println("  Đèn 1: TẮT");
  }
  
  // Điều khiển Đèn 2
  else if (command == "den2 on" || command == "2 on" || command == "d2 on") {
    den2_state = true;
    digitalWrite(RELAY2_PIN, HIGH);
    Serial.println("  Đèn 2: BẬT");
  }
  else if (command == "den2 off" || command == "2 off" || command == "d2 off") {
    den2_state = false;
    digitalWrite(RELAY2_PIN, LOW);
    Serial.println("  Đèn 2: TẮT");
  }
  
  // Điều khiển Quạt
  else if (command == "quat on" || command == "3 on" || command == "q on" || command == "fan on") {
    quat_state = true;
    digitalWrite(RELAY3_PIN, HIGH);
    Serial.println("  Quạt: BẬT");
  }
  else if (command == "quat off" || command == "3 off" || command == "q off" || command == "fan off") {
    quat_state = false;
    digitalWrite(RELAY3_PIN, LOW);
    Serial.println("  Quạt: TẮT");
  }
  
  // Bật tất cả
  else if (command == "all on" || command == "tat ca on") {
    allOn();
  }
  
  // Tắt tất cả
  else if (command == "all off" || command == "tat ca off") {
    allOff();
  }
  
  // Hiển thị trạng thái
  else if (command == "status" || command == "trangthai" || command == "s") {
    showStatus();
  }
  
  // Hiển thị trợ giúp
  else if (command == "help" || command == "trogiup" || command == "?" || command == "h") {
    printHelp();
  }
  
  // Lệnh không hợp lệ
  else {
    Serial.println("✗ Lệnh không hợp lệ! Gõ 'help' để xem hướng dẫn.");
  }
}

void allOn() {
  den1_state = true;
  den2_state = true;
  quat_state = true;
  
  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);
  digitalWrite(RELAY3_PIN, HIGH);
  
  Serial.println("  Đã BẬT tất cả thiết bị!");
  showStatus();
}

void allOff() {
  den1_state = false;
  den2_state = false;
  quat_state = false;
  
  digitalWrite(RELAY1_PIN, LOW);
  digitalWrite(RELAY2_PIN, LOW);
  digitalWrite(RELAY3_PIN, LOW);
  
  Serial.println("  Đã TẮT tất cả thiết bị!");
  showStatus();
}

void showStatus() {
  Serial.println("\nTRẠNG THÁI THIẾT BỊ");
  Serial.print("  Đèn 1: ");
  if (den1_state) {
    Serial.println("BẬT");
  } else {
    Serial.println("TẮT");
  }
  
  Serial.print("  Đèn 2: ");
  if (den2_state) {
    Serial.println("BẬT");
  } else {
    Serial.println("TẮT");
  }
  
  Serial.print("  Quạt:  ");
  if (quat_state) {
    Serial.println("BẬT");
  } else {
    Serial.println("TẮT");
  }

}

void printHelp() {
  Serial.println("\n╔════════════════════════════════════╗");
  Serial.println("║        HƯỚNG DẪN SỬ DỤNG           ║");
  Serial.println("╠════════════════════════════════════╣");
  Serial.println("║ ĐIỀU KHIỂN ĐÈN 1:                  ║");
  Serial.println("║  • den1 on  / 1 on  / d1 on        ║");
  Serial.println("║  • den1 off / 1 off / d1 off       ║");
  Serial.println("║                                    ║");
  Serial.println("║ ĐIỀU KHIỂN ĐÈN 2:                  ║");
  Serial.println("║  • den2 on  / 2 on  / d2 on        ║");
  Serial.println("║  • den2 off / 2 off / d2 off       ║");
  Serial.println("║                                    ║");
  Serial.println("║ ĐIỀU KHIỂN QUẠT:                   ║");
  Serial.println("║  • quat on  / fan on / q on        ║");
  Serial.println("║  • quat off / fan off / q off      ║");
  Serial.println("║                                    ║");
  Serial.println("║ ĐIỀU KHIỂN NHÓM:                   ║");
  Serial.println("║  • all on   - Bật tất cả           ║");
  Serial.println("║  • all off  - Tắt tất cả           ║");
  Serial.println("║                                    ║");
  Serial.println("║ LỆNH KHÁC:                         ║");
  Serial.println("║  • status / s - Xem trạng thái     ║");
  Serial.println("║  • help / h   - Xem hướng dẫn      ║");
  Serial.println("╚════════════════════════════════════╝");
}


/* ========== PHẦN CHO PHẦN CỨNG THỰC (Bluetooth) ==========
// Uncomment phần này khi dùng với phần cứng thực

#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif

BluetoothSerial SerialBT;

// Trong setup(), thêm:
// SerialBT.begin("ESP32_HomeControl");
// Serial.println("Bluetooth đã sẵn sàng! Tên: ESP32_HomeControl");

// Trong loop(), thêm:
// if (SerialBT.available()) {
//   String command = SerialBT.readStringUntil('\n');
//   command.trim();
//   command.toLowerCase();
//   processCommand(command);
// }

// Trong các hàm Serial.println(), thêm SerialBT.println() tương ứng
*/
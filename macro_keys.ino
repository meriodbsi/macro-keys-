#include <HID-Project.h>

const int buttonPin = 7; // Butonun bağlı olduğu pin
int lastButtonState = LOW; // Butonun son durumu
int currentButtonState; // Butonun güncel durumu

#define SCL_PIN 13
#define SDO_PIN 12
byte Key;

int lastVolumeLevel = -1; // Son ses seviyesi

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(SCL_PIN, OUTPUT);  
  pinMode(SDO_PIN, INPUT); 
  Consumer.begin(); // HID Consumer başlatma
}

void loop() {
  currentButtonState = digitalRead(buttonPin);

  // Buton basıldığında ve önceki durum basılı değilse işlem yap
  if (currentButtonState == HIGH && lastButtonState == LOW) {
    Keyboard.press(KEY_LEFT_GUI); // Windows tuşunu basılı tut
    delay(100); // Kısa bir gecikme
    Keyboard.releaseAll(); // Tüm tuşları bırak
  }

  lastButtonState = currentButtonState; // Buton durumunu güncelle

  // Potansiyometreden analog okuma
  int sensorValue = analogRead(A0);
  
  // Analog değeri 0-1023 aralığından 0-100 aralığına çevirme
  int volumeLevel = map(sensorValue, 0, 1023, 0, 100);
  
  // Değer önceki değerle farklıysa güncelleme
  if (volumeLevel != lastVolumeLevel) {
    if (volumeLevel > lastVolumeLevel) {
      for (int i = lastVolumeLevel; i < volumeLevel; i++) {
        Consumer.write(MEDIA_VOLUME_UP);
        delay(5); // Biraz bekleyin
      }
    } else {
      for (int i = lastVolumeLevel; i > volumeLevel; i--) {
        Consumer.write(MEDIA_VOLUME_DOWN);
        delay(5); // Biraz bekleyin
      }
    }
    lastVolumeLevel = volumeLevel; // Son değeri güncelle
  }

  delay(100); // Biraz bekleyin

  /* Read the current state of the keypad */
  Key = Read_Keypad();
  
  /* If a key has been pressed output it to the serial port */
  if (Key) {
    if (Key == 1)       
      Keyboard.print("Ahmet");          // 1 tuşuna bas
    delay(100);                   // Kısa bir süre bekle
    if (Key == 2) {
      Keyboard.print("MacroKey");          // 1 tuşuna bas
      delay(100);                   // Kısa bir süre bekle
    }
    if (Key == 3) {
      Keyboard.print("Kayseri Melikgazi Yıldırım Beyazıt xxxxx");          // 1 tuşuna bas
      delay(100);                   // Kısa bir süre bekle
    }
    if (Key == 4) {
      Keyboard.print("555xxxxx38");          // 1 tuşuna bas
      delay(100);                   // Kısa bir süre bekle
    }
    if (Key == 5) {
      Keyboard.print("Ahmet Macrokey");          // 1 tuşuna bas
      delay(100);                   // Kısa bir süre bekle
    }
    if (Key == 6) {
      Keyboard.print("3838 xxxx xxxx 3838");          // 1 tuşuna bas
      delay(100);                   // Kısa bir süre bekle
    }
    if (Key == 7) {
      Keyboard.print("07/25");          // 1 tuşuna bas
      delay(100);                   // Kısa bir süre bekle
    }
    if (Key == 8) {
      Keyboard.print("388");          // 1 tuşuna bas
      delay(100);                   // Kısa bir süre bekle
    }
    if (Key == 9) {
      Keyboard.print("Ahmet MacroKey");          // 1 tuşuna bas
      delay(100);                   // Kısa bir süre bekle
    }
    if (Key == 10) {
      Keyboard.print("TR55XXXXXXXXXXXXXXX55");          // 1 tuşuna bas
      delay(100);                   // Kısa bir süre bekle
    }
    if (Key == 11) {
      Keyboard.print("Mimarsinan Vergi Dairesi");          // 1 tuşuna bas
      delay(100);                   // Kısa bir süre bekle
    }
    if (Key == 12) {
      Keyboard.print("7351 xxx xxx");          // 1 tuşuna bas
      delay(100);                   // Kısa bir süre bekle
    }
    if (Key == 13) {
      Keyboard.print("Tus 13 basildi");          // 1 tuşuna bas
      delay(100);                   // Kısa bir süre bekle
    }
    if (Key == 14) {
      Keyboard.print("Tus 14 basildi");          // 1 tuşuna bas
      delay(100);                   // Kısa bir süre bekle
    }
    if (Key == 15) {
      Keyboard.print("Tus 15 basildi");          // 1 tuşuna bas
      delay(100);                   // Kısa bir süre bekle
    }
    if (Key == 16) {
      Keyboard.print("Tus 16 basildi");          // 1 tuşuna bas
      delay(100);                   // Kısa bir süre bekle
    }
  }
}

/* Read the state of the keypad */
byte Read_Keypad(void)
{
  byte Count;
  byte Key_State = 0;
  /* Pulse the clock pin 16 times (one for each key of the keypad) 
     and read the state of the data pin on each pulse */
  for(Count = 1; Count <= 16; Count++)
  {
    digitalWrite(SCL_PIN, LOW); 
    
    /* If the data pin is low (active low mode) then store the 
       current key number */
    if (!digitalRead(SDO_PIN))
      Key_State = Count; 
    
    digitalWrite(SCL_PIN, HIGH);
  }  
  
  return Key_State; 
}
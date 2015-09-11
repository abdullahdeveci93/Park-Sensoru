#include <LiquidCrystal.h>
#include <NewPing.h> 
LiquidCrystal lcd(12,11,5,4,3,2);
int speakerPin = 13;
const int mavi = 10; 
const int yesil = 9;
const int kirmizi = 8;

const int trig =7;
const int echo= 6;
int sure=0;
int mesafe=0;
int length = 15; // the number of notes
char notes[] = "ccggaagffeeddc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;

#define buzzerPin 13

void setup() {
pinMode(mavi, OUTPUT);
pinMode(yesil, OUTPUT);
pinMode(kirmizi, OUTPUT);
pinMode(trig, OUTPUT);
pinMode(echo, INPUT);
pinMode(speakerPin, OUTPUT);
analogWrite(buzzerPin, 255); // Buzzer'ı susturuyoruz
Serial.begin(9600);

lcd.begin(16,2);
lcd.clear();
lcd.print("hi");
}

void loop() {  
digitalWrite(trig, HIGH);
delayMicroseconds(1000);
digitalWrite(trig, LOW);
sure = pulseIn(echo, HIGH);
mesafe = (sure/2) / 29.1;

if(mesafe<11)
{
analogWrite(mavi,0);
analogWrite(yesil,0);
analogWrite(kirmizi,255);
analogWrite(buzzerPin, 150); // Buzzer'ı 425 milisaniye
delay(425);      
  }
else if(mesafe>10 && mesafe <51)
{
analogWrite(mavi,255);
analogWrite(yesil,0);
analogWrite(kirmizi,0);
analogWrite(buzzerPin, 150); // Buzzer'ı 150 milisaniye
delay(150);                  // boyunca öttür
analogWrite(buzzerPin, 255); // Buzzer'ı 200 milisaniye
delay(200);  
  }
else if(mesafe >50 && mesafe <91)
{
analogWrite(mavi,0);
analogWrite(yesil,255);
analogWrite(kirmizi,0);
analogWrite(buzzerPin, 150); // Buzzer'ı 70 milisaniye
delay(70);                   // boyunca öttür :D
analogWrite(buzzerPin, 255); // Buzzer'ı 430 milisaniye
delay(430); 
  }
else if(mesafe >90 && mesafe <151)
{
analogWrite(mavi,255);
analogWrite(yesil,255);
analogWrite(kirmizi,255);
    analogWrite(buzzerPin, 255); // Buzzer'ı sustur
    delay(425); // 425 milisaniye bekle
  }
else if(mesafe>150)
{
  analogWrite(mavi,0);
analogWrite(yesil,0);
analogWrite(kirmizi,0);
for (int i = 0; i < length; i++) {
    if(i%3==0)
    {
      analogWrite(mavi,0);
analogWrite(yesil,255);
analogWrite(kirmizi,0);
      }
    if(i%3==1)
    {
      
analogWrite(mavi,255);
analogWrite(yesil,0);
analogWrite(kirmizi,0);
      }
      if(i%3==2)
    {
      
analogWrite(mavi,0);
analogWrite(yesil,0);
analogWrite(kirmizi,255);
      }    
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }

    // pause between notes
    delay(tempo / 2); 
  }
  }
 

lcd.clear();
lcd.print(" Mesafe: ");
lcd.print(mesafe);
lcd.println(" cm   ");

delay(100);

}

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

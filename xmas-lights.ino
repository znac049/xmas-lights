/*
 *
 */
#include "WiFi.h"

#define CLOCK_FREQUENCY 80000000
#define CYCLES_PER_SECOND 200
#define PRESCALER CLOCK_FREQUENCY / (CYCLES_PER_SECOND * 512)

#define POSITIVE_PHASE_PIN 26
#define NEGATIVE_PHASE_PIN 27

#define POSITIVE_POT_PIN 34
#define NEGATIVE_POT_PIN 35

#define POSITIVE_PHASE 0
#define NEGATIVE_PHASE 1

volatile int ticks = 0;
hw_timer_t *timer = NULL;

volatile static int positive_level = 64;
volatile static int negative_level = 64;
volatile static int counter;

static int state = POSITIVE_PHASE;
static int cycles = 0;

void IRAM_ATTR onTimer() {
  ticks++;

  if (ticks == 256) {
    ticks = 0;
    cycles++;

    if (state == POSITIVE_PHASE) {
      state = NEGATIVE_PHASE;
      digitalWrite(POSITIVE_PHASE_PIN, 0);
      if (negative_level == 0) {
        digitalWrite(NEGATIVE_PHASE_PIN, 0);
      }
      else {
        digitalWrite(NEGATIVE_PHASE_PIN, 1);
        counter = negative_level;
      }
    }
    else {
      state = POSITIVE_PHASE;
      digitalWrite(NEGATIVE_PHASE_PIN, 0);
      if (positive_level == 0) {
        digitalWrite(POSITIVE_PHASE_PIN, 0);
      }
      else {
        digitalWrite(POSITIVE_PHASE_PIN, 1);
        counter = positive_level;
      }
    }
  }

  counter--;
  if (counter <= 0) {
    digitalWrite(POSITIVE_PHASE_PIN, 0);
    digitalWrite(NEGATIVE_PHASE_PIN, 0);    
  }
}

void setup()
{
  Serial.begin(115200);

  Serial.print("Prescaler: ");
  Serial.println(PRESCALER);
  timer = timerBegin(0, 160, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 10, true);
  timerAlarmEnable(timer);

  pinMode(POSITIVE_PHASE_PIN, OUTPUT);
  pinMode(NEGATIVE_PHASE_PIN, OUTPUT);
  pinMode(POSITIVE_POT_PIN, INPUT);
  pinMode(NEGATIVE_POT_PIN, INPUT);
  
  digitalWrite(POSITIVE_PHASE_PIN, 0);
  digitalWrite(NEGATIVE_PHASE_PIN, 0);

  Serial.println("Setup done");

  Serial.print("H-Brige control A: Pin ");
  Serial.println(POSITIVE_PHASE_PIN);
  
  Serial.print("H-Brige control B: Pin ");
  Serial.println(NEGATIVE_PHASE_PIN);
  
  Serial.print("Positive channel pot: Pin ");
  Serial.println(POSITIVE_POT_PIN);
  
  Serial.print("Negative channel pot: Pin ");
  Serial.println(NEGATIVE_POT_PIN);
}

void loop()
{
  int next_count = 1000;
  
  positive_level = analogRead(POSITIVE_POT_PIN);
  negative_level = analogRead(NEGATIVE_POT_PIN);
      
  Serial.print("Pot A: ");
  Serial.print(analogRead(POSITIVE_POT_PIN));

  Serial.print("  Pot B: ");
  Serial.print(analogRead(NEGATIVE_POT_PIN));

  Serial.print("  Cycles: ");
  Serial.print(cycles);

  Serial.print('\r');
}

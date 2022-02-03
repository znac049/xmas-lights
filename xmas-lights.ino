/*
 *  This sketch demonstrates how to scan WiFi networks.
 *  The API is almost the same as with the WiFi Shield library,
 *  the most obvious difference being the different file you need to include:
 */
#include "WiFi.h"

#define CLOCK_FREQUENCY 80000000
#define CYCLES_PER_SECOND 200
#define PRESCALER CLOCK_FREQUENCY / (CYCLES_PER_SECOND * 512)

#define POSITIVE_PHASE_PIN 26
#define NEGATIVE_PHASE_PIN 27

#define POSITIVE_PHASE 0
#define NEGATIVE_PHASE 1

volatile int ticks = 0;
hw_timer_t *timer = NULL;

static int state = POSITIVE_PHASE;
static int cycles = 0;

void IRAM_ATTR onTimer() {
  ticks++;

  if (ticks == 512) {
    ticks = 0;
    cycles++;

    if (state == POSITIVE_PHASE) {
      digitalWrite(POSITIVE_PHASE_PIN, 0);
      digitalWrite(NEGATIVE_PHASE_PIN, 1);
      state = NEGATIVE_PHASE;
    }
    else {
      digitalWrite(NEGATIVE_PHASE_PIN, 0);
      digitalWrite(POSITIVE_PHASE_PIN, 1);
      state = POSITIVE_PHASE;
    }
  }
}

void setup()
{
  Serial.begin(115200);

  Serial.print("Prescaler: ");
  Serial.println(PRESCALER);
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 10, true);
  timerAlarmEnable(timer);

  pinMode(POSITIVE_PHASE_PIN, OUTPUT);
  pinMode(NEGATIVE_PHASE_PIN, OUTPUT);
  digitalWrite(POSITIVE_PHASE_PIN, 0);
  digitalWrite(NEGATIVE_PHASE_PIN, 0);

  Serial.println("Setup done");
}

void loop()
{
  register int copyOfTicks;
  
  Serial.print("Cycles: ");
  Serial.println(cycles);

  // Wait a bit...
  delay(2000);
}

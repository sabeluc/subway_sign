#include <Arduino.h>

constexpr uint8_t CL1_MASK = _BV(PB0);  // D8
constexpr uint8_t CL2_MASK = _BV(PB1);  // D9
constexpr uint8_t M_MASK = _BV(PB2);    // D10
constexpr uint8_t DATA_MASK = _BV(PB3); // D11

constexpr uint32_t CLOCK_PERIOD_US = 8333;
constexpr uint32_t PATTERN_PERIOD_US = 250000;
constexpr uint32_t SHIFT_EDGE_PERIOD_US = 16;
constexpr uint8_t DRIVER_COUNT = 16;
constexpr uint8_t BITS_PER_DRIVER = 40;
constexpr uint8_t PIXELS_PER_COLUMN = 7;
constexpr uint8_t COLUMN_STRIDE_BITS = 8;
constexpr uint8_t COLUMNS_PER_DRIVER = 5;
constexpr uint8_t PIXELS_PER_DRIVER = PIXELS_PER_COLUMN * COLUMNS_PER_DRIVER;
constexpr uint16_t TOTAL_TEST_BITS = DRIVER_COUNT * PIXELS_PER_DRIVER;

bool every(uint32_t period, uint32_t now, uint32_t& previous) {
  if (static_cast<uint32_t>(now - previous) < period) return false;
  previous += period;
  return true;
}

uint32_t lastClockUs = 0;
uint32_t lastPatternUs = 0;
uint32_t lastShiftUs = 0;
uint8_t clockPhase = 0;
uint16_t patternStep = 0;
uint8_t shiftDriver = 0;
uint8_t shiftBitInDriver = 0;
bool shiftClockHigh = false;
bool shifting = false;

void setClockPhase(uint8_t phase) {
  // M is twice CL1.  At phase 3, M and CL1 fall on the same update.
  switch (phase) {
    case 0: PORTB = (PORTB & ~CL1_MASK) | M_MASK; break;
    case 1: PORTB = (PORTB & ~M_MASK) | CL1_MASK; break;
    case 2: PORTB |= M_MASK | CL1_MASK; break;
    default: PORTB &= ~(M_MASK | CL1_MASK); break;
  }
}

bool outputIsOn() {
  const uint8_t bitInColumn = shiftBitInDriver & 0x07;
  if (bitInColumn == 0) return false; // Held-low position at each column start.

  const uint8_t column = shiftBitInDriver >> 3;
  const uint16_t pixel = static_cast<uint16_t>(shiftDriver) * PIXELS_PER_DRIVER
                       + column * PIXELS_PER_COLUMN + (bitInColumn - 1);
  return pixel <= patternStep;
}

void writeDataForCurrentBit() {
  if (outputIsOn()) PORTB |= DATA_MASK;
  else PORTB &= ~DATA_MASK;
}

void beginShift(uint32_t nowUs) {
  shiftDriver = 0;
  shiftBitInDriver = 0;
  shiftClockHigh = false;
  shifting = true;
  PORTB &= ~CL2_MASK;
  writeDataForCurrentBit();
  lastShiftUs = nowUs;
}

void serviceShift(uint32_t nowUs) {
  if (!shifting || !every(SHIFT_EDGE_PERIOD_US, nowUs, lastShiftUs)) return;

  if (!shiftClockHigh) {
    PORTB |= CL2_MASK;
    shiftClockHigh = true;
    return;
  }

  PORTB &= ~CL2_MASK; // HD44100 shifts on this falling edge.
  shiftClockHigh = false;
  ++shiftBitInDriver;
  if (shiftBitInDriver == BITS_PER_DRIVER) {
    shiftBitInDriver = 0;
    ++shiftDriver;
  }
  if (shiftDriver == DRIVER_COUNT) {
    shifting = false;
    return;
  }
  writeDataForCurrentBit();
}

void advancePattern(uint32_t nowUs) {
  if (!every(PATTERN_PERIOD_US, nowUs, lastPatternUs)) return;

  ++patternStep;
  if (patternStep == TOTAL_TEST_BITS) patternStep = 0;
}

void setup() {
  DDRB |= CL1_MASK | CL2_MASK | M_MASK | DATA_MASK;
  PORTB &= ~(CL1_MASK | CL2_MASK | M_MASK | DATA_MASK);
  setClockPhase(0);
}

void loop() {
  const uint32_t nowUs = micros();
  if (every(CLOCK_PERIOD_US, nowUs, lastClockUs)) {
    clockPhase = (clockPhase + 1) & 0x03;
    setClockPhase(clockPhase);

    // A CL1 falling edge latches the previous frame.  Start shifting the
    // next frame immediately so it is complete before the next latch.
    if (clockPhase == 3) {
      advancePattern(nowUs);
      beginShift(nowUs);
    }
  }

  serviceShift(nowUs);
}

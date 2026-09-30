#include <Arduino.h>

#include <string.h>

#include "ascii_font.h"
#include "glyphs.h"

constexpr uint8_t CL1_MASK = _BV(PB0);  // D8
constexpr uint8_t CL2_MASK = _BV(PB1);  // D9
constexpr uint8_t M_MASK = _BV(PB2);    // D10
constexpr uint8_t DATA_MASK = _BV(PB3); // D11

constexpr uint32_t CLOCK_PERIOD_US = 8333;
constexpr uint32_t SHIFT_EDGE_PERIOD_US = 16;
constexpr uint8_t DRIVER_COUNT = 16;
constexpr uint8_t BITS_PER_DRIVER = 40;
constexpr uint8_t PIXELS_PER_COLUMN = 7;
constexpr uint8_t COLUMNS_PER_DRIVER = 5;
constexpr uint8_t GLYPHS_PER_MESSAGE = 16;
constexpr uint32_t MESSAGE_PERIOD_US = 3000000;

constexpr uint8_t MAX_MESSAGES = 16;
constexpr uint8_t COMMAND_BUFFER_SIZE = 96;

enum class MessageEncoding : uint8_t {
  GlyphID,
  Ascii,
};

struct Message {
  MessageEncoding encoding;
  uint8_t characters[GLYPHS_PER_MESSAGE];
};

Message activeMessages[MAX_MESSAGES];
uint8_t activeMessageCount = 0;
Message stagedMessages[MAX_MESSAGES];
uint8_t stagedMessageCount = 0;

uint32_t lastClockUs = 0;
uint32_t lastMessageUs = 0;
uint32_t lastShiftUs = 0;
uint8_t clockPhase = 0;
uint8_t currentMessage = 0;
uint8_t shiftDriver = 0;
uint8_t shiftBitInDriver = 0;
bool shiftClockHigh = false;
bool shifting = false;
bool serialEcho = false;
uint32_t randomState = 0x6D2B79F5;

char commandBuffer[COMMAND_BUFFER_SIZE];
uint8_t commandLength = 0;
bool commandOverflow = false;

bool every(uint32_t period, uint32_t now, uint32_t& previous) {
  if (static_cast<uint32_t>(now - previous) < period) return false;
  previous += period;
  return true;
}

void makeAsciiMessage(Message& message, const char* text) {
  message.encoding = MessageEncoding::Ascii;
  memset(message.characters, ' ', sizeof(message.characters));
  for (uint8_t index = 0; index < GLYPHS_PER_MESSAGE && text[index] != '\0';
       ++index) {
    const uint8_t character = static_cast<uint8_t>(text[index]);
    message.characters[index] =
        character >= ASCII_FIRST && character <= ASCII_LAST ? character : ' ';
  }
}

void loadDefaultMessages() {
  makeAsciiMessage(activeMessages[0], "ABCDEFGHIJKLMNOP");
  activeMessageCount = 1;
  currentMessage = 0;
}

bool appendAsciiMessage(const char* text) {
  if (stagedMessageCount == MAX_MESSAGES) return false;
  makeAsciiMessage(stagedMessages[stagedMessageCount++], text);
  return true;
}

bool parseGlyphMessage(const char* text, Message& message) {
  message.encoding = MessageEncoding::GlyphID;
  memset(message.characters, 0, sizeof(message.characters));
  const char* cursor = text;
  uint8_t glyphCount = 0;

  while (true) {
    while (*cursor == ' ') ++cursor;
    if (*cursor < '0' || *cursor > '9') return false;
    if (glyphCount == GLYPHS_PER_MESSAGE) return false;

    uint16_t glyphId = 0;
    while (*cursor >= '0' && *cursor <= '9') {
      glyphId = glyphId * 10 + static_cast<uint8_t>(*cursor - '0');
      if (glyphId >= GLYPH_COUNT) return false;
      ++cursor;
    }
    message.characters[glyphCount++] = static_cast<uint8_t>(glyphId);

    while (*cursor == ' ') ++cursor;
    if (*cursor == '\0') return true;
    if (*cursor != ',') return false;
    ++cursor;
  }
}

bool appendGlyphMessage(const char* text) {
  if (stagedMessageCount == MAX_MESSAGES) return false;

  Message message;
  if (!parseGlyphMessage(text, message)) return false;
  stagedMessages[stagedMessageCount++] = message;
  return true;
}

uint32_t nextRandom() {
  randomState = randomState * 1664525UL + 1013904223UL;
  return randomState;
}

bool parseMessageCount(const char* text, uint8_t& messageCount) {
  if (*text < '1' || *text > '9') return false;

  uint16_t value = 0;
  while (*text >= '0' && *text <= '9') {
    value = value * 10 + static_cast<uint8_t>(*text - '0');
    if (value > MAX_MESSAGES) return false;
    ++text;
  }
  while (*text == ' ') ++text;
  if (*text != '\0' || value == 0) return false;

  messageCount = static_cast<uint8_t>(value);
  return true;
}

void makeRandomMessages(uint8_t messageCount) {
  stagedMessageCount = 0;
  for (uint8_t messageIndex = 0; messageIndex < messageCount;
       ++messageIndex) {
    Message& message = stagedMessages[stagedMessageCount++];
    message.encoding = MessageEncoding::GlyphID;
    for (uint8_t position = 0; position < GLYPHS_PER_MESSAGE; ++position) {
      message.characters[position] =
          1 + nextRandom() % (GLYPH_COUNT - 1); // Never use blank glyph 0.
    }
  }
}

void commitStagedMessages() {
  if (stagedMessageCount == 0) {
    Serial.println(F("error: no staged messages"));
    return;
  }

  memcpy(activeMessages, stagedMessages,
         static_cast<size_t>(stagedMessageCount) * sizeof(Message));
  activeMessageCount = stagedMessageCount;
  currentMessage = 0;
  lastMessageUs = micros();
  Serial.print(F("ok: active="));
  Serial.println(activeMessageCount);
}

void handleCommand(char* command) {
  if (strcmp(command, "clear") == 0) {
    stagedMessageCount = 0;
    Serial.println(F("ok: cleared"));
    return;
  }

  if (strcmp(command, "commit") == 0) {
    commitStagedMessages();
    return;
  }

  if (strcmp(command, "status") == 0) {
    Serial.print(F("status: active="));
    Serial.print(activeMessageCount);
    Serial.print(F(" staged="));
    Serial.println(stagedMessageCount);
    return;
  }

  if (strncmp(command, "random ", 7) == 0) {
    uint8_t messageCount = 0;
    if (!parseMessageCount(command + 7, messageCount)) {
      Serial.println(F("error: expected message count 1-16"));
      return;
    }
    makeRandomMessages(messageCount);
    commitStagedMessages();
    return;
  }

  if (strcmp(command, "echo on") == 0) {
    serialEcho = true;
    Serial.println(F("ok: echo on"));
    return;
  }

  if (strcmp(command, "echo off") == 0) {
    serialEcho = false;
    Serial.println(F("ok: echo off"));
    return;
  }

  if (strncmp(command, "ascii", 5) == 0 &&
      (command[5] == '\0' || command[5] == ' ')) {
    const char* text = command + 5;
    if (*text == ' ') ++text;
    if (appendAsciiMessage(text)) Serial.println(F("ok: staged ascii"));
    else Serial.println(F("error: message limit"));
    return;
  }

  if (strncmp(command, "glyph ", 6) == 0) {
    if (appendGlyphMessage(command + 6)) Serial.println(F("ok: staged glyph"));
    else Serial.println(F("error: expected 1-16 IDs 0-145, or message limit"));
    return;
  }

  Serial.println(F("commands: clear, ascii, glyph, random, commit, status, echo [on off]"));
}

void serviceSerial() {
  // A frame shift has a 16 us edge cadence. Receive and parse commands only
  // in the idle time between shifts; the 256-byte UART buffer holds input
  // arriving at 115,200 baud while a frame is being shifted.
  if (shifting) return;

  while (Serial.available() > 0) {
    const char input = static_cast<char>(Serial.read());
    if (input == '\r') continue;

    if (input == '\b' || static_cast<uint8_t>(input) == 0x7F) {
      if (commandLength > 0) {
        --commandLength;
        if (serialEcho) Serial.print(F("\b \b"));
      }
      continue;
    }

    if (input == '\n') {
      if (serialEcho) Serial.print(F("\r\n"));
      if (commandOverflow) {
        Serial.println(F("error: command too long"));
      } else {
        commandBuffer[commandLength] = '\0';
        if (commandLength != 0) handleCommand(commandBuffer);
      }
      commandLength = 0;
      commandOverflow = false;
      continue;
    }

    if (commandLength + 1 < COMMAND_BUFFER_SIZE) {
      commandBuffer[commandLength++] = input;
      if (serialEcho) Serial.write(input);
    } else {
      commandOverflow = true;
    }
  }
}

void setClockPhase(uint8_t phase) {
  // M is twice CL1. At phase 3, M and CL1 fall on the same update.
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
  const uint8_t row = bitInColumn - 1;
  const Message& message = activeMessages[currentMessage];
  const uint8_t character =
      message.characters[GLYPHS_PER_MESSAGE - 1 - shiftDriver];

  if (message.encoding == MessageEncoding::Ascii) {
    return asciiPixel(static_cast<char>(character), column, row);
  }
  return glyphPixel(character, column, row);
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

void advanceMessage(uint32_t nowUs) {
  if (!every(MESSAGE_PERIOD_US, nowUs, lastMessageUs)) return;
  currentMessage = (currentMessage + 1) % activeMessageCount;
}

void setup() {
  DDRB |= CL1_MASK | CL2_MASK | M_MASK | DATA_MASK;
  PORTB &= ~(CL1_MASK | CL2_MASK | M_MASK | DATA_MASK);
  setClockPhase(0);

  loadDefaultMessages();
  randomState ^= micros();
  randomState ^= static_cast<uint32_t>(analogRead(A0)) << 16;
  Serial.begin(115200);
  Serial.println(F("ready"));
}

void loop() {
  const uint32_t nowUs = micros();
  if (every(CLOCK_PERIOD_US, nowUs, lastClockUs)) {
    clockPhase = (clockPhase + 1) & 0x03;
    setClockPhase(clockPhase);

    // A CL1 falling edge latches the previous frame. Start shifting the next
    // frame immediately so it is complete before the next latch.
    if (clockPhase == 3) {
      advanceMessage(nowUs);
      beginShift(nowUs);
    }
  }

  serviceShift(nowUs);
  serviceSerial();
}

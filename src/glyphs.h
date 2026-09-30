#pragma once

#include <Arduino.h>
#include <avr/pgmspace.h>

// Column-major glyphs: GLYPHS[glyphId][column][row].
// The seven entries in each column are reversed from glyphs.txt so row 0
// matches the physical top of the upside-down LCD module.
constexpr uint8_t GLYPH_WIDTH = 5;
constexpr uint8_t GLYPH_HEIGHT = 7;
constexpr uint8_t GLYPH_COUNT = 146;

using Glyph = bool[GLYPH_WIDTH][GLYPH_HEIGHT];

const Glyph GLYPHS[GLYPH_COUNT] PROGMEM = {
  {
    {false, false, false, false, false, false, false},
    {false, false, false, false, false, false, false},
    {false, false, false, false, false, false, false},
    {false, false, false, false, false, false, false},
    {false, false, false, false, false, false, false}
  },
  {
    {false, true, true, false, true, false, true},
    {true, true, true, true, true, true, true},
    {true, true, true, true, false, true, false},
    {true, true, true, true, true, false, true},
    {true, true, true, true, true, true, false}
  },
  {
    {false, true, false, true, true, true, true},
    {true, true, true, true, true, true, true},
    {true, false, false, false, false, false, false},
    {false, true, true, true, false, true, true},
    {false, true, true, true, true, true, true}
  },
  {
    {false, true, true, true, true, true, true},
    {false, false, false, false, true, false, true},
    {true, false, false, false, false, true, false},
    {false, true, false, false, false, true, false},
    {false, false, true, false, false, true, false}
  },
  {
    {false, false, false, false, true, false, false},
    {true, false, true, true, true, true, true},
    {true, false, true, true, false, true, true},
    {false, false, true, true, true, true, true},
    {true, true, false, true, false, true, true}
  },
  {
    {true, false, true, true, true, true, false},
    {true, true, false, false, true, false, false},
    {true, true, true, true, true, true, true},
    {false, false, false, true, false, true, false},
    {false, true, true, true, true, true, false}
  },
  {
    {false, true, true, true, true, true, true},
    {true, false, true, true, true, true, false},
    {false, false, true, true, true, true, true},
    {true, false, true, true, false, true, true},
    {true, true, true, true, false, true, true}
  },
  {
    {false, true, false, true, true, false, false},
    {true, true, true, true, true, true, false},
    {false, false, false, true, true, true, true},
    {true, false, true, true, true, true, false},
    {true, true, true, false, true, true, true}
  },
  {
    {false, true, true, false, false, true, true},
    {true, true, false, true, false, true, true},
    {true, true, true, true, false, true, true},
    {false, false, false, false, true, false, false},
    {false, false, false, false, true, false, true}
  },
  {
    {true, true, true, true, true, false, true},
    {false, true, false, true, true, true, true},
    {true, false, true, true, true, true, true},
    {true, true, true, true, true, true, true},
    {false, true, true, true, false, true, true}
  },
  {
    {true, true, false, false, false, false, false},
    {true, false, true, true, true, true, true},
    {false, false, true, true, true, true, true},
    {true, false, false, true, true, true, true},
    {true, false, true, false, false, true, false}
  },
  {
    {true, true, false, true, true, false, true},
    {true, true, true, true, true, true, true},
    {true, true, true, false, true, true, false},
    {true, false, false, true, true, true, false},
    {true, true, true, true, true, true, true}
  },
  {
    {true, true, true, true, false, false, false},
    {true, false, true, true, true, true, true},
    {true, false, true, false, false, true, false},
    {true, true, true, true, false, true, true},
    {true, true, true, true, true, false, true}
  },
  {
    {true, true, true, true, true, false, false},
    {false, false, false, true, true, false, true},
    {true, false, false, true, true, true, false},
    {true, false, true, true, true, true, true},
    {false, true, true, false, true, false, true}
  },
  {
    {true, true, true, false, true, true, true},
    {true, true, true, true, true, false, true},
    {true, true, true, true, true, true, false},
    {true, false, true, false, true, false, true},
    {true, true, true, true, true, true, true}
  },
  {
    {true, true, true, true, false, true, false},
    {true, true, true, true, true, true, true},
    {false, true, true, true, true, true, false},
    {false, true, true, true, false, true, false},
    {true, false, true, true, false, true, true}
  },
  {
    {false, false, false, false, true, true, true},
    {true, true, true, true, true, true, true},
    {false, true, true, true, true, true, true},
    {true, true, true, true, true, true, true},
    {false, true, true, false, false, true, true}
  },
  {
    {true, true, true, true, true, true, false},
    {false, true, false, true, true, false, true},
    {true, true, false, true, true, true, true},
    {true, true, true, true, true, true, true},
    {true, true, true, true, true, true, true}
  },
  {
    {false, false, false, false, false, false, false},
    {true, true, true, true, true, true, false},
    {true, true, true, true, true, true, true},
    {true, true, true, false, true, true, true},
    {true, false, true, true, false, false, false}
  },
  {
    {true, false, true, true, false, false, true},
    {true, true, false, true, true, true, true},
    {true, true, true, true, true, true, true},
    {true, false, false, false, false, false, false},
    {true, false, false, true, true, true, true}
  },
  {
    {true, true, false, true, true, false, true},
    {false, true, true, true, true, true, true},
    {true, true, false, false, false, false, true},
    {true, false, true, false, true, true, true},
    {true, true, true, true, true, true, true}
  },
  {
    {false, true, true, false, false, true, true},
    {false, true, true, false, true, true, true},
    {false, true, true, true, true, true, true},
    {false, false, true, true, true, true, true},
    {true, true, true, false, true, true, true}
  },
  {
    {true, true, false, true, false, true, true},
    {false, true, true, false, false, false, true},
    {true, true, false, true, false, false, false},
    {true, true, true, true, true, true, false},
    {false, true, true, true, false, true, true}
  },
  {
    {false, false, true, true, true, true, true},
    {false, true, false, true, true, true, true},
    {false, true, true, true, true, true, true},
    {true, true, false, true, false, true, true},
    {true, true, true, true, true, true, true}
  },
  {
    {true, true, true, false, true, false, true},
    {true, true, true, true, false, true, false},
    {true, true, true, true, true, true, false},
    {true, true, false, true, true, true, true},
    {false, true, true, true, true, true, true}
  },
  {
    {true, true, true, true, false, true, true},
    {true, true, true, true, true, true, true},
    {false, true, false, true, true, true, true},
    {false, false, false, false, true, false, true},
    {false, false, false, false, false, false, false}
  },
  {
    {true, false, false, false, false, true, false},
    {false, true, false, false, false, true, false},
    {false, false, true, false, false, true, false},
    {false, false, false, false, true, false, false},
    {true, false, true, true, true, true, true}
  },
  {
    {false, true, true, true, false, true, false},
    {true, false, true, true, false, true, false},
    {true, false, true, true, true, true, true},
    {true, false, true, true, true, true, false},
    {true, true, true, true, true, false, true}
  },
  {
    {false, false, false, true, true, true, true},
    {false, false, true, true, true, true, true},
    {true, true, true, true, false, true, true},
    {true, false, true, true, true, false, true},
    {false, true, true, false, true, true, true}
  },
  {
    {false, true, true, true, true, true, true},
    {true, true, true, true, true, true, true},
    {true, true, false, false, false, true, true},
    {true, false, false, false, false, true, true},
    {true, true, true, true, true, true, true}
  },
  {
    {false, false, true, false, true, true, false},
    {true, false, true, true, false, true, false},
    {true, true, false, true, false, true, true},
    {true, true, false, false, true, true, true},
    {true, true, false, true, false, true, true}
  },
  {
    {true, true, true, false, false, false, false},
    {true, true, true, true, true, true, false},
    {false, true, false, true, true, true, false},
    {false, true, true, true, true, false, true},
    {true, true, false, true, false, true, true}
  },
  {
    {true, true, true, false, true, true, true},
    {false, true, false, true, true, true, true},
    {true, true, true, true, false, true, false},
    {true, false, true, false, true, true, true},
    {true, true, true, true, true, true, true}
  },
  {
    {true, true, true, false, true, true, true},
    {true, false, true, false, false, false, true},
    {true, false, true, true, true, false, true},
    {false, true, true, true, false, true, false},
    {true, true, true, true, true, false, false}
  },
  {
    {true, true, true, true, true, true, true},
    {true, true, true, true, true, false, true},
    {false, false, true, true, true, true, true},
    {true, true, true, false, true, false, true},
    {true, true, false, true, true, true, true}
  },
  {
    {true, true, true, true, true, false, true},
    {true, true, true, true, true, true, true},
    {true, true, true, true, true, true, true},
    {false, false, false, false, false, false, true},
    {true, true, true, true, false, false, false}
  },
  {
    {true, true, true, true, true, true, true},
    {true, false, true, true, true, true, true},
    {true, true, false, false, false, false, true},
    {true, true, false, false, true, false, true},
    {false, true, true, true, true, true, true}
  },
  {
    {true, true, true, true, true, true, true},
    {false, false, false, false, false, false, true},
    {false, true, true, true, true, true, true},
    {false, true, true, false, true, true, true},
    {true, true, true, true, true, false, true}
  },
  {
    {false, false, false, false, true, true, false},
    {true, false, true, true, true, true, true},
    {true, true, true, true, true, true, true},
    {true, false, false, true, true, true, true},
    {true, false, true, true, true, true, false}
  },
  {
    {true, true, true, true, true, false, false},
    {true, true, true, true, true, true, false},
    {true, false, true, true, true, true, false},
    {false, true, false, true, true, true, true},
    {true, false, false, false, true, true, true}
  },
  {
    {false, true, false, false, false, true, false},
    {true, true, true, true, true, true, true},
    {true, true, true, false, true, true, false},
    {false, true, false, true, true, true, true},
    {true, false, false, true, true, true, false}
  },
  {
    {true, true, true, true, true, true, true},
    {true, false, true, false, true, true, true},
    {true, true, true, true, true, true, false},
    {true, true, false, true, false, true, true},
    {true, true, true, false, true, false, true}
  },
  {
    {false, true, true, true, true, false, false},
    {true, false, true, true, true, true, true},
    {false, false, false, true, true, true, true},
    {true, false, false, false, true, false, true},
    {true, true, true, false, true, true, true}
  },
  {
    {true, false, true, true, false, true, true},
    {true, true, true, true, false, true, false},
    {true, true, true, false, false, false, true},
    {true, true, true, true, false, true, false},
    {false, true, true, true, false, true, true}
  },
  {
    {true, true, true, false, true, true, false},
    {true, false, true, true, true, true, true},
    {false, true, false, true, true, true, true},
    {true, false, false, true, true, true, true},
    {true, true, true, true, true, true, true}
  },
  {
    {true, true, true, true, true, false, true},
    {false, false, false, false, true, true, true},
    {true, true, true, false, false, false, false},
    {true, true, false, true, true, true, true},
    {true, true, true, true, true, true, true}
  },
  {
    {false, true, true, false, true, true, true},
    {true, false, true, false, false, false, false},
    {true, false, true, true, false, false, false},
    {true, false, true, false, true, false, false},
    {false, false, true, false, false, true, false}
  },
  {
    {true, true, true, false, false, false, false},
    {true, true, true, true, false, true, true},
    {true, true, true, true, false, true, true},
    {true, true, false, false, false, true, true},
    {true, false, true, true, true, false, true}
  },
  {
    {false, false, true, true, false, true, true},
    {true, true, true, true, true, false, false},
    {true, false, true, true, true, true, true},
    {true, false, true, false, false, false, true},
    {true, true, true, true, false, true, true}
  },
  {
    {true, true, false, true, false, true, true},
    {true, true, true, true, true, false, true},
    {false, true, true, true, false, false, true},
    {false, true, true, true, true, false, true},
    {true, false, false, true, true, true, true}
  },
  {
    {true, true, false, false, false, true, false},
    {true, true, true, true, true, true, true},
    {true, true, false, false, false, false, false},
    {true, true, true, true, true, false, true},
    {false, true, true, true, true, true, true}
  },
  {
    {false, true, true, true, false, true, true},
    {false, true, true, true, true, true, false},
    {true, false, false, true, true, true, true},
    {true, false, true, false, false, false, false},
    {true, false, true, false, false, false, false}
  },
  {
    {true, true, true, true, true, true, true},
    {true, true, true, true, true, false, true},
    {true, true, true, true, true, true, false},
    {true, false, true, true, true, true, true},
    {false, false, false, false, false, false, true}
  },
  {
    {true, true, true, true, true, true, true},
    {true, true, true, true, true, true, false},
    {true, true, true, true, true, false, false},
    {false, false, true, false, false, true, false},
    {true, true, true, true, true, true, false}
  },
  {
    {false, false, false, false, false, true, true},
    {true, true, true, true, true, true, false},
    {true, false, true, true, true, false, false},
    {true, true, true, false, true, true, false},
    {false, false, true, true, false, true, true}
  },
  {
    {true, true, true, true, true, true, false},
    {true, true, true, true, true, false, true},
    {true, true, true, true, true, true, true},
    {true, true, true, false, true, true, false},
    {true, true, false, true, true, true, false}
  },
  {
    {true, true, true, false, true, true, true},
    {true, true, false, false, false, true, true},
    {true, true, true, true, true, false, true},
    {true, true, true, true, false, true, false},
    {false, true, false, true, true, false, false}
  },
  {
    {false, true, true, true, false, true, false},
    {true, false, true, true, true, true, true},
    {true, true, false, true, true, true, false},
    {true, false, false, false, true, true, true},
    {true, true, false, true, false, true, true}
  },
  {
    {true, true, false, true, true, true, true},
    {true, false, true, true, false, true, false},
    {true, true, true, true, true, true, true},
    {false, true, true, true, true, false, true},
    {false, true, true, true, true, true, false}
  },
  {
    {true, true, true, true, true, true, true},
    {true, true, true, false, true, true, true},
    {false, false, true, true, true, true, true},
    {true, false, false, false, false, false, false},
    {false, true, true, true, true, false, true}
  },
  {
    {true, true, true, true, true, true, true},
    {true, false, true, true, true, true, true},
    {true, false, false, false, false, true, false},
    {true, true, false, false, false, false, true},
    {true, false, true, false, false, false, true}
  },
  {
    {true, false, false, true, false, false, true},
    {true, false, false, false, false, true, false},
    {true, true, false, true, true, true, true},
    {true, true, false, true, true, false, true},
    {false, false, false, true, true, true, true}
  },
  {
    {true, true, true, false, true, false, true},
    {true, true, false, true, true, true, true},
    {true, true, true, false, false, true, false},
    {true, true, true, true, true, true, true},
    {true, false, false, false, true, false, true}
  },
  {
    {true, true, false, true, true, true, true},
    {false, true, false, true, true, true, true},
    {true, true, true, false, true, true, true},
    {true, true, false, false, true, true, true},
    {true, true, true, false, true, true, false}
  },
  {
    {false, true, true, true, true, true, false},
    {false, false, false, true, false, true, true},
    {true, true, true, true, true, true, true},
    {false, false, false, false, false, true, true},
    {true, true, true, false, true, true, true}
  },
  {
    {true, true, true, true, true, false, true},
    {true, true, false, true, true, false, false},
    {true, true, true, true, false, true, false},
    {false, true, true, true, true, true, false},
    {true, false, false, false, false, false, true}
  },
  {
    {false, true, false, true, true, true, false},
    {true, false, true, true, true, true, true},
    {false, true, true, true, true, true, true},
    {true, true, false, true, false, true, false},
    {true, false, true, true, true, true, true}
  },
  {
    {true, true, true, true, true, true, true},
    {true, false, true, true, true, true, true},
    {true, false, false, false, true, true, true},
    {true, true, true, false, true, true, true},
    {true, true, false, true, false, true, true}
  },
  {
    {true, true, true, false, false, false, false},
    {true, true, true, true, true, true, true},
    {true, true, true, false, true, true, true},
    {true, true, true, true, true, true, true},
    {true, false, true, false, true, true, false}
  },
  {
    {false, true, true, true, true, true, true},
    {true, true, true, false, true, false, true},
    {true, true, true, true, true, false, true},
    {true, true, true, true, true, true, true},
    {false, false, false, true, true, true, true}
  },
  {
    {true, false, false, false, false, false, false},
    {true, true, true, true, true, true, true},
    {true, true, true, true, true, true, true},
    {false, false, true, true, true, true, false},
    {false, true, false, true, false, true, true}
  },
  {
    {true, true, true, true, false, true, true},
    {true, true, true, true, true, false, true},
    {false, false, false, true, true, true, true},
    {true, true, true, true, false, false, false},
    {true, true, true, false, false, true, true}
  },
  {
    {true, false, true, true, false, true, true},
    {true, true, false, true, true, true, true},
    {true, true, true, true, false, false, false},
    {true, true, true, false, true, false, true},
    {true, true, true, true, true, true, true}
  },
  {
    {true, true, false, true, true, false, false},
    {true, false, true, true, true, false, true},
    {true, true, false, true, true, true, true},
    {true, false, false, false, true, true, true},
    {true, true, true, true, false, true, true}
  },
  {
    {true, true, true, false, true, false, true},
    {true, false, true, true, false, false, false},
    {true, true, true, false, true, false, false},
    {false, true, true, true, true, true, true},
    {true, false, true, true, true, false, true}
  },
  {
    {false, false, false, true, true, true, true},
    {true, false, true, false, true, true, true},
    {true, false, true, true, true, true, true},
    {false, true, true, false, true, false, true},
    {true, true, true, true, true, true, true}
  },
  {
    {true, true, true, true, false, true, false},
    {true, true, true, true, true, false, true},
    {true, true, true, true, true, true, false},
    {true, true, false, true, true, true, true},
    {false, true, true, true, true, true, true}
  },
  {
    {false, false, false, false, false, false, false},
    {true, true, true, true, false, true, true},
    {true, true, true, true, true, true, true},
    {false, true, true, true, true, true, true},
    {false, false, false, false, true, false, true}
  },
  {
    {true, true, true, true, true, false, true},
    {true, true, true, true, true, true, true},
    {false, false, false, true, true, true, false},
    {true, false, false, true, true, true, true},
    {false, true, false, false, false, true, false}
  },
  {
    {false, true, false, false, false, false, true},
    {true, true, true, false, false, false, true},
    {true, false, false, false, true, true, true},
    {true, true, true, false, true, true, true},
    {true, true, true, true, true, true, true}
  },
  {
    {true, true, true, true, false, true, false},
    {false, true, true, true, true, true, true},
    {true, false, true, true, true, true, true},
    {true, false, true, true, true, false, false},
    {true, false, true, false, true, true, true}
  },
  {
    {true, true, true, true, false, true, true},
    {true, false, true, true, false, true, true},
    {false, true, false, true, false, true, true},
    {true, true, true, true, true, true, true},
    {true, true, false, false, false, false, true}
  },
  {
    {true, true, true, false, false, true, true},
    {false, true, false, true, true, true, true},
    {true, true, false, true, false, true, true},
    {true, true, true, false, true, true, false},
    {true, true, false, false, true, true, true}
  },
  {
    {true, true, true, true, true, true, true},
    {true, true, true, true, true, false, false},
    {true, true, true, true, false, false, false},
    {true, false, true, true, true, true, true},
    {true, false, true, false, false, true, false}
  },
  {
    {true, true, true, true, false, true, true},
    {true, true, true, true, true, false, true},
    {true, true, true, true, true, false, false},
    {false, false, false, true, true, false, true},
    {true, false, false, true, true, true, false}
  },
  {
    {true, false, true, true, true, true, true},
    {false, false, true, false, true, false, true},
    {true, true, true, false, true, true, true},
    {true, true, true, true, true, false, true},
    {true, true, true, true, true, true, false}
  },
  {
    {true, false, true, false, true, false, true},
    {true, true, true, true, true, true, true},
    {true, true, true, true, false, true, false},
    {true, true, true, true, true, true, true},
    {false, true, true, true, true, true, false}
  },
  {
    {false, true, true, true, false, true, false},
    {true, true, true, true, false, true, true},
    {false, false, false, false, true, true, true},
    {true, true, true, true, true, true, true},
    {false, true, true, true, true, true, true}
  },
  {
    {true, true, true, true, true, true, true},
    {true, false, true, false, false, true, true},
    {true, true, true, true, true, true, true},
    {true, false, true, false, true, true, false},
    {true, true, true, false, true, true, true}
  },
  {
    {true, true, true, true, true, true, true},
    {false, false, true, true, true, true, true},
    {false, false, false, false, false, false, false},
    {true, true, true, true, true, true, true},
    {true, true, true, true, true, true, true}
  },
  {
    {false, false, true, true, true, false, false},
    {true, false, true, false, true, true, true},
    {true, true, true, false, true, true, true},
    {true, true, true, true, false, true, false},
    {false, false, true, true, true, true, false}
  },
  {
    {true, true, true, false, false, false, false},
    {true, true, true, false, false, true, true},
    {true, false, true, true, false, true, true},
    {true, true, false, true, true, true, true},
    {true, true, false, true, false, false, false}
  },
  {
    {true, true, true, false, false, false, false},
    {true, true, true, false, false, true, true},
    {true, false, true, true, false, true, true},
    {true, true, false, true, true, true, true},
    {true, true, false, true, false, false, false}
  },
  {
    {true, true, true, false, true, false, true},
    {true, true, true, true, true, true, true},
    {true, true, false, true, true, false, false},
    {true, false, false, true, true, false, true},
    {true, true, false, true, true, true, true}
  },
  {
    {false, true, false, true, true, true, true},
    {true, true, true, false, false, false, false},
    {true, true, true, true, true, true, true},
    {false, false, false, true, true, true, true},
    {true, true, false, true, false, false, false}
  },
  {
    {true, true, true, true, true, true, true},
    {true, false, true, false, true, true, true},
    {true, true, true, true, false, true, true},
    {true, true, true, true, false, false, true},
    {true, true, false, false, true, true, false}
  },
  {
    {true, true, false, true, false, true, true},
    {true, true, true, false, true, true, false},
    {true, true, false, false, true, true, true},
    {true, true, true, true, true, true, true},
    {true, true, true, true, true, false, false}
  },
  {
    {false, true, false, true, true, true, true},
    {true, false, false, false, false, false, true},
    {true, true, true, true, false, false, true},
    {false, true, true, true, false, true, true},
    {true, true, true, false, true, true, false}
  },
  {
    {true, true, true, true, true, true, true},
    {false, false, false, true, true, false, true},
    {true, false, false, true, true, true, false},
    {false, true, true, true, true, true, true},
    {false, false, false, false, true, true, false}
  },
  {
    {true, true, false, true, true, true, true},
    {true, false, true, true, false, true, true},
    {true, true, true, true, true, true, true},
    {true, true, true, true, false, true, true},
    {false, true, true, true, true, true, true}
  },
  {
    {false, false, true, true, true, true, true},
    {true, false, false, false, true, false, false},
    {true, false, false, false, true, false, false},
    {false, false, false, false, false, true, false},
    {true, true, false, true, true, true, true}
  },
  {
    {true, true, true, true, true, true, true},
    {false, false, false, false, false, true, false},
    {true, true, false, false, false, true, true},
    {true, true, true, true, true, true, true},
    {false, false, false, true, true, false, true}
  },
  {
    {true, false, true, true, true, true, false},
    {true, true, true, true, true, true, true},
    {true, true, false, true, false, true, true},
    {true, true, true, false, false, true, true},
    {true, true, true, false, true, false, true}
  },
  {
    {true, true, true, true, true, true, true},
    {true, true, false, true, true, true, true},
    {true, true, true, true, true, true, true},
    {true, true, true, false, false, true, true},
    {true, true, true, true, true, true, true}
  },
  {
    {false, false, false, false, false, true, true},
    {true, true, true, true, false, false, false},
    {true, true, true, true, true, true, true},
    {true, true, true, true, true, false, false},
    {false, true, true, true, false, true, false}
  },
  {
    {true, true, true, true, true, false, true},
    {true, true, false, true, true, true, false},
    {false, false, true, true, false, true, true},
    {true, false, true, false, true, true, true},
    {true, true, true, true, true, true, true}
  },
  {
    {false, false, false, false, false, false, true},
    {true, true, true, true, false, true, true},
    {true, true, true, true, true, true, true},
    {true, false, false, false, false, false, false},
    {true, true, false, true, true, true, true}
  },
  {
    {true, true, true, true, false, true, true},
    {true, true, true, false, true, true, true},
    {true, true, true, true, true, false, false},
    {false, false, true, false, false, true, false},
    {false, false, false, true, false, false, true}
  },
  {
    {false, false, false, true, false, false, true},
    {false, true, true, true, false, true, true},
    {false, true, true, true, true, true, false},
    {true, true, true, true, true, true, true},
    {true, false, true, false, true, true, true}
  },
  {
    {true, true, true, true, false, true, true},
    {true, true, true, true, false, false, true},
    {true, true, false, false, true, true, false},
    {false, true, true, true, false, true, false},
    {true, false, true, true, false, true, false}
  },
  {
    {true, true, true, true, true, true, true},
    {true, true, true, false, true, true, true},
    {true, false, true, true, true, true, true},
    {true, true, false, false, false, true, true},
    {true, false, false, false, true, true, true}
  },
  {
    {false, true, false, true, true, true, true},
    {true, true, false, true, false, true, true},
    {true, true, true, false, true, true, false},
    {true, true, false, false, true, true, true},
    {true, true, true, false, true, true, true}
  },
  {
    {true, true, true, true, true, false, false},
    {true, true, true, true, false, false, false},
    {true, false, true, true, true, true, true},
    {true, false, false, false, false, true, false},
    {true, true, false, true, false, true, true}
  },
  {
    {true, true, true, true, true, false, false},
    {true, true, true, true, false, false, false},
    {true, false, true, true, true, true, true},
    {true, false, false, false, false, true, false},
    {true, true, false, true, false, true, true}
  },
  {
    {true, true, true, true, true, false, true},
    {true, true, true, true, true, false, false},
    {false, false, false, true, true, false, true},
    {true, false, false, true, true, true, false},
    {true, false, true, true, true, true, true}
  },
  {
    {true, true, true, true, true, true, true},
    {true, true, true, false, false, true, false},
    {true, true, true, true, true, true, true},
    {false, false, false, false, false, false, false},
    {true, true, true, true, true, false, true}
  },
  {
    {false, false, true, true, true, true, true},
    {true, true, true, true, true, true, true},
    {false, true, false, true, false, false, false},
    {false, true, true, true, true, false, true},
    {true, true, true, true, false, true, true}
  },
  {
    {false, true, true, true, false, true, true},
    {false, true, true, true, true, true, true},
    {false, false, false, false, true, true, false},
    {true, true, false, false, true, true, true},
    {true, false, true, true, true, true, true}
  },
  {
    {true, false, false, false, false, true, true},
    {false, true, true, false, true, true, true},
    {true, true, false, true, true, false, true},
    {true, true, true, true, true, true, true},
    {false, true, true, true, true, false, true}
  },
  {
    {false, false, true, true, true, true, true},
    {true, false, false, true, true, true, true},
    {false, true, false, false, false, true, false},
    {false, true, false, false, false, true, false},
    {true, false, false, false, false, false, true}
  },
  {
    {true, true, true, false, true, true, true},
    {true, true, true, true, true, true, true},
    {true, false, false, false, false, false, true},
    {false, true, true, false, false, false, true},
    {false, true, true, true, true, true, true}
  },
  {
    {false, false, false, false, true, true, false},
    {true, true, false, true, true, true, true},
    {true, true, true, true, true, true, true},
    {true, true, true, false, true, false, true},
    {false, true, true, true, false, false, true}
  },
  {
    {true, true, true, true, false, true, false},
    {true, true, true, true, true, true, true},
    {true, true, true, false, true, true, true},
    {false, true, true, true, true, false, true},
    {true, true, true, true, false, false, true}
  },
  {
    {true, true, true, true, true, true, true},
    {false, false, false, false, false, false, true},
    {true, true, true, true, true, false, false},
    {true, true, true, true, true, true, true},
    {true, true, true, true, true, true, false}
  },
  {
    {true, false, true, true, true, false, true},
    {false, true, true, true, true, true, false},
    {true, true, true, false, true, true, true},
    {false, false, false, true, true, false, true},
    {true, true, false, true, false, true, true}
  },
  {
    {true, true, true, true, true, true, true},
    {false, false, false, false, false, false, false},
    {false, true, true, true, true, false, true},
    {true, true, true, true, true, true, true},
    {true, true, false, false, false, false, false}
  },
  {
    {true, true, true, false, true, true, true},
    {true, true, true, true, true, false, true},
    {false, true, true, true, false, true, true},
    {false, true, true, true, true, true, false},
    {false, false, false, true, false, false, true}
  },
  {
    {false, false, false, false, true, false, false},
    {true, false, false, false, true, false, false},
    {false, false, true, true, true, false, true},
    {true, false, true, true, true, true, true},
    {true, true, true, true, true, true, true}
  },
  {
    {true, true, false, true, false, true, true},
    {true, true, true, true, true, false, true},
    {true, true, true, true, true, false, false},
    {true, true, true, false, false, true, true},
    {true, false, true, true, true, false, true}
  },
  {
    {true, true, false, true, true, false, true},
    {true, true, false, true, true, true, true},
    {false, true, false, true, false, true, true},
    {true, true, false, true, true, true, true},
    {true, true, false, false, false, false, true}
  },
  {
    {false, true, true, false, false, true, true},
    {true, false, true, false, true, true, true},
    {true, true, true, false, true, false, true},
    {true, true, true, true, false, true, true},
    {true, true, true, false, false, true, true}
  },
  {
    {true, true, true, true, true, false, true},
    {false, true, false, true, true, true, true},
    {false, true, true, false, true, true, true},
    {false, true, true, true, true, true, true},
    {true, true, false, false, true, true, false}
  },
  {
    {true, true, true, false, true, true, true},
    {true, true, true, true, false, true, true},
    {true, true, true, true, false, true, true},
    {true, true, true, false, true, true, true},
    {true, true, true, true, false, false, false}
  },
  {
    {true, true, true, true, true, true, true},
    {true, true, true, true, false, false, true},
    {false, false, true, true, true, true, true},
    {true, false, false, false, false, false, false},
    {true, true, true, true, true, true, true}
  },
  {
    {true, false, false, false, true, true, true},
    {false, true, true, true, true, true, true},
    {true, true, false, true, false, true, false},
    {true, true, false, true, true, true, true},
    {true, false, true, true, true, true, false}
  },
  {
    {true, true, false, true, true, true, false},
    {false, true, false, true, true, true, true},
    {true, false, false, false, false, false, true},
    {true, true, true, true, false, false, true},
    {true, false, true, false, true, true, true}
  },
  {
    {true, true, true, false, false, false, false},
    {true, true, false, true, true, false, true},
    {true, true, true, true, false, true, true},
    {true, true, true, true, true, true, true},
    {true, true, false, true, true, true, true}
  },
  {
    {true, true, false, false, true, true, true},
    {false, false, true, false, false, true, true},
    {false, false, false, true, false, false, false},
    {true, false, false, true, false, false, false},
    {true, true, true, false, false, false, false}
  },
  {
    {true, true, true, true, true, true, true},
    {true, false, true, true, true, true, true},
    {true, true, true, false, false, false, false},
    {true, true, false, true, true, false, false},
    {false, true, false, true, true, true, true}
  },
  {
    {true, false, false, false, false, false, true},
    {true, true, true, true, false, true, true},
    {true, true, true, true, true, true, true},
    {true, true, true, true, true, false, true},
    {false, true, false, true, true, true, false}
  },
  {
    {true, true, true, true, true, true, false},
    {true, true, true, true, true, true, true},
    {true, true, true, true, true, false, true},
    {true, true, false, true, true, true, true},
    {true, true, true, true, true, true, false}
  },
  {
    {false, false, true, true, true, true, true},
    {true, false, false, false, false, false, false},
    {true, true, true, true, true, true, true},
    {true, true, false, false, true, true, true},
    {true, false, true, false, true, true, true}
  },
  {
    {false, false, false, true, true, true, true},
    {true, false, true, true, false, false, false},
    {true, true, true, true, false, true, true},
    {false, false, false, false, true, true, true},
    {true, true, true, true, true, true, false}
  },
  {
    {true, false, true, true, true, true, true},
    {false, false, true, true, true, true, true},
    {true, true, false, false, false, true, true},
    {false, false, true, false, false, true, true},
    {true, false, false, true, false, false, false}
  },
  {
    {true, false, false, true, false, false, false},
    {true, false, true, true, true, false, false},
    {true, true, true, false, false, false, true},
    {true, true, false, true, true, false, true},
    {false, true, false, true, true, true, true}
  },
  {
    {true, false, true, true, true, true, false},
    {true, false, false, true, true, true, true},
    {false, true, true, false, true, true, true},
    {true, false, true, false, true, true, true},
    {true, false, true, false, true, false, true}
  },
};

inline bool glyphPixel(uint8_t glyphId, uint8_t column, uint8_t row) {
  return pgm_read_byte(&GLYPHS[glyphId][column][row]) != 0;
}


# Luminator LCD:MAX controller

This is bench firmware for replacing the Luminator controller while retaining
the original KS0061/HD44100 LCD-driver boards.  The current power-on
diagnostic targets the full 16-driver sign (640 serial outputs).

## Connections

The pins below are deliberately all 5 V Uno GPIO.  Do **not** connect any Uno
pin to the board's VEE line (ribbon pin 3).

| Uno pin | Ribbon signal |
| --- | --- |
| GND | pins 1 and 2 |
| D8 | CL1 latch/frame clock |
| D9 | CL2 shift clock |
| D10 | M LCD-polarity waveform |
| D11 | DATA to DL1 |

The original board must receive its known-good +5 V and VEE supplies on
ribbon pins 4 and 3 respectively.  Verify those supply rails and the four
logic waveforms on a scope before connecting the LCD glass.

## Timing

The code uses the static-drive relationship specified for the compatible
HD44100R: data shifts on CL2 falling edges; data latches on a CL1 falling
edge; M is twice the CL1 frequency and a CL1 falling edge coincides with an M
falling edge.  `M_FREQUENCY_HZ` is 120 Hz, inside the datasheet's approximate
30–500 Hz static-drive range.  It remains a bench setting until verified on
the original sign.

## Power-on pixel diagnostic

On reset, the controller progresses through 624 segment-driver outputs.  It
asserts one additional output every 150 ms until the sign is fully dark, then
releases one output at a time from the start of the same sequence.  A complete
darkening or clearing pass takes about 94 seconds.

This tests physical driver order, not the provisional 5x7 character mapping.
It includes the four as-yet-unidentified non-common outputs on each driver.
The remaining output, Y1, is the static-drive LCD common output and is held at
data 0 as required by the HD44100 timing chart.  If an
asserted data bit makes a pixel light rather than dark, change
`DARK_DATA_LEVEL` near the top of `src/main.cpp` from `true` to `false`.

## USB serial commands

Use LF or CRLF terminated ASCII commands:

```
TEXT C EUCLID AV
CLEAR
PIX 0 2 4 1
PIX 0 2 4 0
TEST 1 0
TEST OFF
```

`PIX` coordinates are character, x (0–4), y (0–6), state.  `TEST` takes a
driver number and physical output slot (both zero-indexed) and lights only
that output; it is useful for mapping the boards before character mapping is
known.  `TEST OFF` returns to the framebuffer.

The default serial order and 40-output mapping are placeholders.  Adjust the
constants near the top of `src/main.cpp` as continuity and pixel tests reveal
the physical order.

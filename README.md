# Luminator LCD:MAX controller

Bench firmware for an Arduino Uno that replaces the Luminator controller while
retaining the original HD44100 LCD-driver boards.

## Connections

| Uno pin | Ribbon signal |
| --- | --- |
| GND | pins 1 and 2 |
| D8 | CL1 latch/frame clock |
| D9 | CL2 shift clock |
| D10 | M LCD-polarity waveform |
| D11 | DATA to DL1 |

Supply the board with its known-good +5 V and VEE rails. Do not connect an Uno
GPIO pin to VEE.

## USB protocol

The Uno appears to the Raspberry Pi as a USB serial device. Open it at 115,200
baud, 8N1. Each LF-terminated command receives an `OK` or `ERR` response.

Messages are staged first, then made visible together by `COMMIT`. A message
contains 16 positions: the route position plus 15 text positions. The sign
rotates its active messages every three seconds.

```text
clear
ascii ABCDEFGHIJKLMNOP
ascii NEXT STOP
commit
```

`ascii ` appends one printable-ASCII message, padding short text with spaces
and truncating after 16 characters. `glyph ` appends one custom-glyph
message with one through 16 IDs from 0 through 145; any remaining positions
are padded with glyph ID 0:

```text
glyph 1,2,3,4
```

`status` reports the active and staged message counts. At most 16 messages
can be active at once.

`random n` creates and immediately commits `n` full-length custom-glyph
messages. `n` must be from 1 through 16. Every generated glyph ID is from 1
through 145, so it never uses the blank glyph 0.

`echo on` enables a terminal-friendly echo of each received command; `echo off`
disables it. Echo is off by default, so the Pi receives only protocol replies.

A Raspberry Pi can send a message set with Python:

```python
import serial
import time

with serial.Serial("/dev/ttyACM0", 115200, timeout=1) as sign:
    time.sleep(2)  # Uno resets when the USB serial port opens.
    sign.write(
        b"clear\\n"
        b"ascii C EUCLID AV\\n"
        b"ascii NEXT STOP\\n"
        b"commit\\n"
    )
    for _ in range(4):
        print(sign.readline().decode().strip())
```

The controller initially displays `ABCDEFGHIJKLMNOP` until a committed
message set replaces it.

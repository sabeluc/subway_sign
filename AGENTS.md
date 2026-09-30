# Alien Subway Sign

## Project description

The Alien Subway Sign is a sculpture based on a salvaged large LCD display from a retired R46 NYC subway car. The inspiration came from riding in an R46 with a malfunctioning LCD controller: instead of normal English signage such as "C - Euclid Ave," the sign displayed dense, alien-looking 5x7 glyphs. As the glyphs changed, they attracted passengers' attention. Video of that sign provided the basis for recreating the glyphs. The sculpture will display them, changing its "message" from time to time.

The performance will also include:

- An LED strip simulating movement through a tunnel past a series of stationary lightbulbs.
- Background audio including doors closing, acceleration synchronized with the LED strip, slowing and stopping, doors opening, and crowd noises.
- Foreground audio made from real conductor announcements processed through a custom English-to-alien translator. Announcements will occur at points in the performance that match their original meaning, but will not be intelligible to the viewer.
- Optionally, a mirrored black plastic "window" in which viewers see themselves in the "train," framed with trim salvaged from an R46.

## Control platform

The sign is large enough that controller size is not a major constraint. A Raspberry Pi is under consideration for sequencing the performance and playing audio; the target model has not been selected. A Pico 2 could serve as a companion for LED timing or a custom LCD interface if needed. These are candidate platforms, not finalized hardware decisions.

## Programming languages

Use Python for the main Raspberry Pi application, including performance sequencing, glyph selection and animation logic, audio playback coordination, and offline audio processing tools. Use a native audio engine for continuous audio playback and mixing rather than timing individual samples in Python.

Use C++ for Pico firmware if a companion microcontroller is needed for precise LED or LCD signaling, with PIO where appropriate. Keep timing-sensitive electrical signaling off Python loops running under Linux. The specific hardware interface remains to be determined through the LCD investigation.

## LCD interface investigation

Controlling the salvaged LCD is the main hardware unknown. Its electronics use older, 1980s-era 5 V logic, including discrete logic gate ICs. The original control box has a security mechanism to prevent unauthorized changes. The security code is available, but attempts to establish communication between the controller and sign, or capture traffic on the controller's outgoing wires, have not yet succeeded.

The sculpture needs arbitrary glyph patterns rather than ordinary English text. The original control boxes are primarily useful for understanding the sign's protocol; retaining them is not a requirement. The interface may transmit pixel patterns or character codes, and this has not been established.

Potential places to take control, from highest to lowest level, are:

1. The protocol between the original controller and the sign, if it supports the required glyph patterns.
2. The sign's receiving circuitry, including wherever character codes may be converted to glyph patterns.
3. The chips that appear to drive the LCDs, whose identities and interfaces still need to be determined.
4. The LCD glass itself, using replacement driver hardware if necessary.

The preferred approach is to retain as much of the working display electronics as practical while gaining control of the glyph patterns. A character-based protocol could require going deeper into the circuitry or changing glyph storage, if accessible. Directly driving the glass remains a possibility, but its electrode mapping and required LCD drive waveforms would first need to be understood. Any connection to modern control hardware must account for the original circuitry's signal levels.

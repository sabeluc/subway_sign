## Current

- Hook up controller directly to sign and see if any control is possible. Sniff signal line using scope. 


## Backlog


- Identify the controller-to-sign electrical interface and investigate why no traffic has been captured.
- Determine whether the sign protocol carries character codes or pixel patterns, and locate any glyph storage.
- Choose the LCD control interface and prototype displaying one custom 5x7 glyph, accounting for the original 5 V logic.
- Add the recreated glyph patterns to the repository and define how messages change during the performance.
- Select the main Raspberry Pi model and determine whether a Pico 2 is needed for display or LED control.
- Select an LED strip and prototype the passing-tunnel-light effect with acceleration and deceleration.
- Collect and edit background audio for doors, acceleration, cruising, braking, and crowds.
- Review conductor snippets and label them by meaning and suitable performance cue.
- Develop the English-to-alien audio transformation and generate sample announcements for listening review.
- Choose speakers, amplifier, and audio output hardware; test the balance between ambience and announcements.
- Define a performance sequence covering station stops, departures, travel, and arrivals.
- Implement a shared timeline for audio, tunnel lighting, and glyph changes.
- Plan power supplies, wiring, and mounting for the display, controller, lights, and audio hardware.
- Configure automatic startup and test repeated performance cycles and recovery after power loss.
- Decide whether to include the mirrored window and prototype its placement and salvaged trim.

## Done

- Document the sculpture concept and LCD interface unknowns in `AGENTS.md`.
- Assemble an initial collection of conductor announcement snippets and a slicing script.
- Ignore `audio/sources/` while keeping `audio/snippets/` eligible for version control.
- Photograph the LCD boards, connectors, and chip markings; document wiring and identify the receiver and display driver chips.

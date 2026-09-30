"""Animate alien glyph messages on the sample train photo.

Setup: python3 -m venv .venv && .venv/bin/python -m pip install -r requirements.txt
Run: .venv/bin/python simulate_sign.py MESSAGE [MESSAGE ...]
Each MESSAGE contains 16 comma-separated glyph IDs.
The source photo is never modified; the animation opens in a browser.
"""

import argparse
import base64
from io import BytesIO
import json
from pathlib import Path
import tempfile
import webbrowser

from PIL import Image, ImageDraw


ROOT = Path(__file__).resolve().parent
PHOTO_PATH = ROOT / "glyphs" / "R46_C_Train_LCD_Exterior_View_small.png"
GLYPHS_PATH = ROOT / "glyphs" / "glyphs.txt"

BACKGROUND = (253, 234, 20)
PIXEL_COLOR = (96, 83, 9)
BOX_X, BOX_Y, BOX_WIDTH, BOX_HEIGHT = 218, 151, 60, 100
GRID_X, GRID_Y = 225, 153
CELL_WIDTH, CELL_HEIGHT, GAP = 8, 13, 1
SMALL_BOX_X, SMALL_BOX_Y = 289, 177
SMALL_BOX_WIDTH, SMALL_BOX_HEIGHT = 38, 50
SMALL_GRID_OFFSET_X, SMALL_GRID_OFFSET_Y = 4, 4
SMALL_CELL_WIDTH, SMALL_CELL_HEIGHT = 4, 5
SMALL_CHARACTER_COUNT = 15
SMALL_BOX_INSET = 1
SMALL_VERTICAL_SHIFT = 1
SMALL_RIGHT_SHIFT_START = 10
SMALL_RIGHT_SHIFT = 1
MESSAGE_DURATION_MS = 3000


def read_glyph(index, path=GLYPHS_PATH):
    """Read a zero-indexed glyph from blank-line-separated blocks."""
    glyphs = []
    rows = []
    for line in path.read_text().splitlines():
        row = line.strip()
        if not row:
            if rows:
                glyphs.append(rows)
                rows = []
            continue
        rows.append(row)
    if rows:
        glyphs.append(rows)
    if not 0 <= index < len(glyphs):
        raise ValueError(f"Glyph index {index} is out of range in {path}")
    rows = glyphs[index]

    if len(rows) != 7 or any(len(row) != 5 for row in rows):
        raise ValueError(f"Glyph {index} in {path} must be 5 columns by 7 rows")
    if any(set(row) - {"x", "."} for row in rows):
        raise ValueError(f"Glyph {index} in {path} must contain only 'x' and '.'")
    return rows


def parse_glyph_ids(value):
    """Parse the route glyph plus 15 small glyph IDs."""
    parts = [part.strip() for part in value.split(",")]
    if len(parts) != SMALL_CHARACTER_COUNT + 1:
        raise argparse.ArgumentTypeError(
            "expected exactly 16 comma-separated glyph IDs"
        )
    try:
        glyph_ids = [int(part) for part in parts]
    except ValueError as error:
        raise argparse.ArgumentTypeError("every glyph ID must be an integer") from error
    if any(glyph_id < 0 for glyph_id in glyph_ids):
        raise argparse.ArgumentTypeError("glyph IDs cannot be negative")
    return glyph_ids


def draw_glyph(draw, glyph, grid_x, grid_y, cell_width, cell_height):
    """Draw dark cells for one glyph at the configured grid origin."""
    for row_index, row in enumerate(glyph):
        for column_index, cell in enumerate(row):
            if cell == "x":
                x = grid_x + column_index * (cell_width + GAP)
                y = grid_y + row_index * (cell_height + GAP)
                draw.rectangle(
                    (x, y, x + cell_width - 1, y + cell_height - 1),
                    fill=PIXEL_COLOR,
                )


def render_preview(glyph_ids):
    """Render one route glyph and 15 small glyphs onto a copy of the photo."""
    if len(glyph_ids) != SMALL_CHARACTER_COUNT + 1:
        raise ValueError("Exactly 16 glyph IDs are required")
    glyphs = [read_glyph(glyph_id) for glyph_id in glyph_ids]
    with Image.open(PHOTO_PATH) as source:
        preview = source.convert("RGB")

    if preview.width < BOX_X + BOX_WIDTH or preview.height < BOX_Y + BOX_HEIGHT:
        raise ValueError("Source photo is too small for the configured sign box")
    if (preview.width < SMALL_BOX_X + SMALL_CHARACTER_COUNT * SMALL_BOX_WIDTH
            or preview.height < SMALL_BOX_Y + SMALL_BOX_HEIGHT):
        raise ValueError("Source photo is too small for the small-character boxes")

    draw = ImageDraw.Draw(preview)
    # Pillow rectangle endpoints are inclusive.
    draw.rectangle(
        (BOX_X, BOX_Y, BOX_X + BOX_WIDTH - 1, BOX_Y + BOX_HEIGHT - 1),
        fill=BACKGROUND,
    )
    draw_glyph(draw, glyphs[0], GRID_X, GRID_Y, CELL_WIDTH, CELL_HEIGHT)

    for position, glyph in enumerate(glyphs[1:], start=1):
        right_shift = SMALL_RIGHT_SHIFT if position >= SMALL_RIGHT_SHIFT_START else 0
        slot_x = SMALL_BOX_X + (position - 1) * SMALL_BOX_WIDTH + right_shift
        box_x = slot_x + SMALL_BOX_INSET
        box_y = SMALL_BOX_Y + SMALL_BOX_INSET + SMALL_VERTICAL_SHIFT
        box_width = SMALL_BOX_WIDTH - 2 * SMALL_BOX_INSET
        box_height = SMALL_BOX_HEIGHT - 2 * SMALL_BOX_INSET
        draw.rectangle(
            (box_x, box_y, box_x + box_width - 1, box_y + box_height - 1),
            fill=BACKGROUND,
        )
        draw_glyph(
            draw,
            glyph,
            slot_x + SMALL_GRID_OFFSET_X,
            SMALL_BOX_Y + SMALL_GRID_OFFSET_Y + SMALL_VERTICAL_SHIFT,
            SMALL_CELL_WIDTH,
            SMALL_CELL_HEIGHT,
        )
    return preview


def image_data_url(image):
    """Encode a rendered frame as an embedded PNG URL."""
    encoded = BytesIO()
    image.save(encoded, format="PNG")
    data = base64.b64encode(encoded.getvalue()).decode("ascii")
    return f"data:image/png;base64,{data}"


def create_animation_page(messages):
    """Create a temporary browser page that loops through rendered messages."""
    frames = [image_data_url(render_preview(message)) for message in messages]
    document = """<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>Alien Subway Sign</title>
  <style>
    html, body { margin: 0; min-height: 100%; background: #111; }
    body { display: grid; place-items: center; }
    img { display: block; max-width: 100vw; max-height: 100vh; object-fit: contain; }
  </style>
</head>
<body>
  <img id="sign" alt="Animated alien subway sign">
  <script>
    const frames = __FRAMES__;
    const sign = document.getElementById("sign");
    let frame = 0;
    sign.src = frames[frame];
    if (frames.length > 1) {
      setInterval(() => {
        frame = (frame + 1) % frames.length;
        sign.src = frames[frame];
      }, __DURATION__);
    }
  </script>
</body>
</html>
"""
    document = document.replace("__FRAMES__", json.dumps(frames))
    document = document.replace("__DURATION__", str(MESSAGE_DURATION_MS))
    with tempfile.NamedTemporaryFile(
        mode="w", suffix=".html", prefix="alien-subway-sign-", delete=False
    ) as page:
        page.write(document)
        return Path(page.name)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description=(
            "Animate one or more 16-glyph messages on the R46 sign photo. "
            "ID 0 is blank; messages change every three seconds."
        )
    )
    parser.add_argument(
        "messages",
        nargs="+",
        type=parse_glyph_ids,
        help="route glyph and 15 text glyphs as comma-separated integers",
    )
    arguments = parser.parse_args()
    try:
        page = create_animation_page(arguments.messages)
    except ValueError as error:
        parser.error(str(error))
    print(f"Opening animation with {len(arguments.messages)} message(s): {page}")
    if not webbrowser.open(page.as_uri()):
        parser.error(f"could not open a browser; open this file manually: {page}")

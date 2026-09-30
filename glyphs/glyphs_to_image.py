import sys
from PIL import Image, ImageDraw
import math

CELL_WIDTH = 40
CELL_HEIGHT = 60
CELL_SPACING = 5   # space between cells inside a glyph
GLYPH_MARGIN = 60    # margin around each glyph and around the entire image
GLYPHS_PER_ROW = 12

def read_glyphs_from_file(filename):
    """
    Reads multiple glyphs from a file. Each glyph is separated by at least one empty line.
    '.' = 1 (white), 'x' = 0 (black)
    Returns a list of glyphs, where each glyph is a list of lists of ints.
    """
    glyphs = []
    current_glyph = []
    
    with open(filename, "r") as f:
        for line in f:
            line = line.strip()
            if line:  # non-empty line
                row = [0 if char == 'x' else 1 for char in line]  # x=0, .=1
                current_glyph.append(row)
            else:
                if current_glyph:
                    glyphs.append(current_glyph)
                    current_glyph = []
        if current_glyph:
            glyphs.append(current_glyph)
    return glyphs

def glyph_size(glyph):
    """Return the width and height of a single glyph in pixels including cell spacing."""
    rows = len(glyph)
    cols = len(glyph[0]) if rows > 0 else 0
    width = cols * CELL_WIDTH + (cols - 1) * CELL_SPACING
    height = rows * CELL_HEIGHT + (rows - 1) * CELL_SPACING
    return width, height

def draw_glyph(draw, glyph, top_left_x, top_left_y):
    """Draw a single glyph at the specified top-left coordinates."""
    for r, row in enumerate(glyph):
        for c, val in enumerate(row):
            x0 = top_left_x + c * (CELL_WIDTH + CELL_SPACING)
            y0 = top_left_y + r * (CELL_HEIGHT + CELL_SPACING)
            x1 = x0 + CELL_WIDTH
            y1 = y0 + CELL_HEIGHT
            color = "black" if val == 0 else "white"
            draw.rectangle([x0, y0, x1, y1], fill=color)

def single_glyph_image(glyph, output_file):
    """Create an image for a single glyph."""
    glyph_w, glyph_h = glyph_size(glyph)
    img_w = glyph_w + GLYPH_MARGIN
    img_h = glyph_h + GLYPH_MARGIN
    img = Image.new("RGB", (img_w, img_h), "white")
    draw = ImageDraw.Draw(img)
    draw_glyph(draw, glyph, GLYPH_MARGIN / 2, GLYPH_MARGIN / 2)
    img.save(output_file)
    print(f"Saved image as {output_file}")

def all_glyphs_image(glyphs, output_file):
    """Create a single image containing all glyphs arranged in rows of 12."""
    # Compute max glyph size for layout (assuming all glyphs same size)
    max_glyph_w = max(glyph_size(g)[0] for g in glyphs)
    max_glyph_h = max(glyph_size(g)[1] for g in glyphs)

    num_glyphs = len(glyphs)
    rows_needed = math.ceil(num_glyphs / GLYPHS_PER_ROW)
    img_w = GLYPHS_PER_ROW * max_glyph_w + (GLYPHS_PER_ROW - 1) * GLYPH_MARGIN + 2 * GLYPH_MARGIN
    img_h = rows_needed * max_glyph_h + (rows_needed - 1) * GLYPH_MARGIN + 2 * GLYPH_MARGIN

    print(f"Drawing {num_glyphs} glyphs...")
    img = Image.new("RGB", (img_w, img_h), "white")
    draw = ImageDraw.Draw(img)

    for idx, glyph in enumerate(glyphs):
        row_num = idx // GLYPHS_PER_ROW
        col_num = idx % GLYPHS_PER_ROW
        top_left_x = GLYPH_MARGIN + col_num * (max_glyph_w + GLYPH_MARGIN)
        top_left_y = GLYPH_MARGIN + row_num * (max_glyph_h + GLYPH_MARGIN)
        draw_glyph(draw, glyph, top_left_x, top_left_y)

    img.save(output_file)
    print(f"Saved image as {output_file}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python script.py <glyph_txt_file> [glyph_index]")
        sys.exit(1)

    input_file = sys.argv[1]
    glyphs = read_glyphs_from_file(input_file)

    if len(sys.argv) > 2:
        # Draw a specific glyph
        glyph_index = int(sys.argv[2])
        if glyph_index < 0 or glyph_index >= len(glyphs):
            print(f"Error: glyph_index must be between 0 and {len(glyphs) - 1}")
            sys.exit(1)
        glyph = glyphs[glyph_index]
        output_file = f"glyph_{glyph_index}.png"
        single_glyph_image(glyph, output_file)
    else:
        # Draw all glyphs in one image
        output_file = "all_glyphs.png"
        all_glyphs_image(glyphs, output_file)

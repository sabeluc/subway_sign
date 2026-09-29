import os
import subprocess

clips = [
    ("j3oEBX74RmY", 114, 140, "rescue_instructions"),
    ("7ExFqDRTDJI", 17, 23, "rodney_welcome"),
    ("AnCL9ANTP7Y", 0, 14, "skipped_stops"),
    ("RfJqxSsuVw4", 0, 20, "three_heads_joke"),
    ("V9ylYC3YdFw", 0, 9, "enthusiastic_conductor_1"),

    ("G2Nm_l-3QbY", 2, 7, "g_train_1"),
    ("G2Nm_l-3QbY", 10, 33, "g_train_2"),
    ("G2Nm_l-3QbY", 33, 44, "g_train_3"),
    ("G2Nm_l-3QbY", 44, 59, "g_train_4"),

    ("7um1f7Sdtic", 0, 59, "4_train_express_to_local"),
    ("Zxdypt1jXAM", 0, 14, "enthusiastic_conductor_2"),

    ("YJiLwrtlzVc", 17, 31, "rodney_thank_you"),
    ("YJiLwrtlzVc", 36, 48, "rodney_safety"),

    ("hgpFudXGqjs", 0, 15, "rodney_3_01"),
    ("hgpFudXGqjs", 15, 26, "rodney_3_02"),
    ("hgpFudXGqjs", 26, 34, "rodney_3_03"),
    ("hgpFudXGqjs", 34, 41, "rodney_3_04"),
    ("hgpFudXGqjs", 41, 62, "rodney_3_05"),
    ("hgpFudXGqjs", 62, 68, "rodney_3_06"),
    ("hgpFudXGqjs", 68, 78, "rodney_3_07"),
    ("hgpFudXGqjs", 78, 103, "rodney_3_08"),
]

SOURCE_DIR = "sources"
OUTPUT_DIR = "snippets"
PADDING = 1.0

os.makedirs(OUTPUT_DIR, exist_ok=True)

for video_id, start, end, label in clips:
    src = os.path.join(SOURCE_DIR, f"{video_id}.wav")

    if not os.path.exists(src):
        print(f"Missing source: {src}")
        continue

    padded_start = max(0, start - PADDING)
    padded_end = end + PADDING
    duration = padded_end - padded_start

    out = os.path.join(
        OUTPUT_DIR,
        f"{video_id}__{label}.wav"
    )

    cmd = [
        "ffmpeg",
        "-y",
        "-ss", str(padded_start),
        "-i", src,
        "-t", str(duration),
        "-vn",
        "-c:a", "pcm_s16le",
        out,
    ]

    print(
        f"{video_id}: "
        f"{start:.1f}-{end:.1f}s "
        f"-> {padded_start:.1f}-{padded_end:.1f}s "
        f"-> {out}"
    )

    subprocess.run(cmd, check=True)

print("Done.")

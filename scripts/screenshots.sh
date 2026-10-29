#!/usr/bin/env bash
# Render the three pages without the device: builds esphome/screenshot-demo.yaml
# for the PC (ESPHome host platform + SDL), runs it in a virtual X display and
# saves docs/images/{overview,climate,homelab}.png, inverted so they look like
# the e-paper (black on white).
#
# Linux only. Needs ESPHome, libsdl2-dev, xvfb, imagemagick.
#   bash scripts/screenshots.sh
set -euo pipefail
cd "$(dirname "$0")/.."

esphome compile esphome/screenshot-demo.yaml
bin=$(find esphome/.esphome/build/reterminal-demo -type f -name program -perm -u+x | head -1)

Xvfb :98 -screen 0 800x480x24 >/dev/null 2>&1 &
xvfb=$!
trap 'kill $app $xvfb 2>/dev/null || true' EXIT
sleep 1
TZ=Europe/Berlin DISPLAY=:98 "$bin" >/dev/null 2>&1 &
app=$!

# Overview is drawn at boot, then the demo moves to the next page every 3 s
# (first switch 3 s after boot); shoot mid-way.
mkdir -p docs/images
sleep 1.5
for name in overview climate homelab; do
  DISPLAY=:98 import -window root -negate -colorspace Gray -depth 8 "docs/images/$name.png"
  sleep 3
done
echo "saved docs/images/{overview,climate,homelab}.png"

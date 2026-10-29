# Changelog

## Unreleased

## v0.2.0 — 2026-10-29

### Added
- **Public on GitHub** under the MIT License, with branches `main`
  (releases) and `dev` (work) and the history squashed into one commit; with
  `THIRD_PARTY_NOTICES.md` for the two fonts and the Ubuntu Font Licence
  text next to the font (`esphome/fonts/UFL.txt`).
- **Screenshots without the device**: `esphome/screenshot-demo.yaml` draws
  the three pages on a PC (ESPHome `host` platform, SDL display) with
  made-up values; `scripts/screenshots.sh` renders them into `docs/images/`.
- README rewritten: highlights, screenshots, install steps, the entities to
  change, an example, layout and development.
- `CLAUDE.md` with the working rules for this repository.

### Fixed
- **Battery Level** (2026-10-29): `device_class: battery`. As a `copy` of
  Battery Voltage it inherited the `voltage` class, and Home Assistant
  warned that `%` is not a voltage unit. Same change made in Home
  Assistant's copy; takes effect with the next flash.

### Changed
- **Synced with the live copy in Home Assistant** (2026-10-29), which had
  moved on since 0.1.0: Homelab page with both Proxmox hosts and Pi-hole
  (`homelab_entities.yaml`), radiator state and open windows on the Climate
  page (`climate_entities.yaml`), shared page header (`ui_header.h`), car
  fuel and range, battery % from a LiPo discharge curve, 6 h sleep below
  15 % battery, no wakes before 06:00, and the combined alarm bar
  (`packages/reterminal_alarms.yaml`).
- **Homelab page**: the second host is titled *Proxmox PVE2* (was *Proxmox RPTU*).

### Removed
- `packages/alert_reterminal.yaml` (replaced by `reterminal_alarms.yaml`)
  and `esphome/reterminal_modules/scripts.yaml` — no longer used in Home
  Assistant.

### Under the hood
- `esphome.project` name and version, so Home Assistant shows the firmware version.
- `secrets.example.yaml` has a valid dummy API key, so the build-server
  check works straight from the repository (ESPHome rejects placeholders and
  all-zero keys). Compiles like the live copy (RAM 34.5 %, flash 58.8 %).

## v0.1.0 — 2026-09-28

### Added
- First import of the live config from the Home Assistant ESPHome add-on: device config, modules, fonts, and the HA packages that feed the display.
- `secrets.example.yaml`, README.

### Changed
- The OTA password now comes from `!secret reterminal_ota_password` instead of being written inline.

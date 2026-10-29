# Working on reterminal-ha-dashboard

ESPHome e-paper dashboard for the Seeed reTerminal E1001, plus the Home
Assistant packages that feed it. **Public repo** (since 2026-10-29).

- `git pull` first — the owner works from more than one PC.
- Work on **`dev`**, push to `dev`. `main` is only for releases, and only when
  the owner asks ("merge to main and make a new release"): merge `dev` into
  `main`, tag `vX.Y.Z`, GitHub release (`gh release create`) with the
  CHANGELOG section as notes.
- Versions: fix = patch, new feature or page change = minor, breaks setups
  (entity IDs others must change) = major. Bump `esphome.project.version` in
  `esphome/reterminal.yaml` and the CHANGELOG heading on release; while
  working on `dev` the version ends in `-dev`.
- Every user-visible change: an entry under *Unreleased* in `CHANGELOG.md`
  (Added / Changed / Fixed / Removed / Under the hood) and the README updated
  to match. Visible page changes: run `bash scripts/screenshots.sh` on the dev
  box and look at the PNGs before committing them.
- **Home Assistant's copy is what gets flashed**:
  `/homeassistant/esphome/reterminal.yaml` + `reterminal_modules/` +
  `fonts/`, and `/config/packages/` for the packages. Keep the repo and HA in
  step. `esphome/screenshot-demo.yaml`, `scripts/` and `docs/` never go to HA.
- **ESPHome checks run on the build server** (CT 117 `esphome-builder` on
  pve_rptu_dev), never locally while pve_rptu_dev is reachable:
  `bash ../claude-setup/scripts/esphome-check.sh esphome/reterminal.yaml`
  (add `config` to skip the compile). It sends the working tree and uses
  `esphome/secrets.example.yaml`. The one local exception is the screenshot
  demo (host platform, dev box only).
- **Push and copy to Home Assistant without asking once the compile check
  passes** (owner, 2026-10-29): commit, push, back up HA's copy into
  `/config/project-backups/esphome/` first, copy the ESPHome files into
  `/homeassistant/esphome/` and check they match. If HA's copy has changes
  the repo doesn't, ask first. Still ask before flashing, and before
  changing anything in `/config/packages/` or elsewhere in HA.
- **Public repo**: no secrets, passwords, tokens or keys in committed files;
  `secrets.example.yaml` holds dummies only. Screenshots use the demo's
  made-up values, never real calendar entries or data.
- **The device and the screenshots may differ on purpose**: the device keeps
  its real labels; the demo overrides them with substitutions (owner,
  2026-10-29). So far `homelab_host2_title`: *Proxmox RPTU* on the device,
  *Proxmox PVE2* in `screenshot-demo.yaml`. Never change the device's label
  to match a screenshot.
- The fonts keep their own licences (`THIRD_PARTY_NOTICES.md`); a new font
  or icon set gets its entry there.
- OTA only while the device is awake: the owner presses a key first.

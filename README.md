# OBS SC2-Switcher

A plugin for OBS Studio that automatically switches scenes and tracks scores for StarCraft II.

## [Download Latest Release](https://github.com/nathaniasSC2/OBS-SC2-Switcher/releases/latest/)

## Installation

### Windows
1. Download the latest `obs-sc2-switcher.dll`.
2. Copy it to your OBS Studio plugins directory, typically:
   `C:\Program Files\obs-studio\obs-plugins\64bit`

### Linux
Copy `obs-sc2-switcher.so` to your OBS plugins directory (e.g., `/usr/lib/obs-plugins/`).

## Usage
In the OBS **Tools** menu, select **SC2-Switcher**.

### Scene Switcher
- Automatically switches scenes based on your current StarCraft II state (In-game, Menus, Replays, etc.).
- All scene assignments are optional and will fall back to "In Game" or "Out of Game" defaults.
- **Observing Scene:** Requires you to have your SC2 username entered in the "Usernames" tab.

### Score Tracker
- Updates a specified OBS text source with your current session score.
- Detection is largely automatic, with occasional prompts for race or player identification (e.g., when playing as/against a Random player or barcode).
- If popups are intrusive, they can be disabled in settings, and scores can be updated manually.

### Game Webhook
- Sends a JSON payload to a specified URL whenever you enter or exit a game.
- Useful for external tools, stream overlays, or bots like [Ladderbet](https://github.com/leigholiver/ladderbet/).

```json
{
  "event": "enter | exit",
  "displayTime": "...",
  "players": [
    {
      "name": "...",
      "type": "...",
      "race": "Terr | Zerg | Prot",
      "result": "Victory | Defeat",
      "isme": "true | false"
    }
  ],
  "scores": {
    "Terr": { "Victory": 0, "Defeat": 0 },
    "Zerg": { "Victory": 0, "Defeat": 0 },
    "Prot": { "Victory": 0, "Defeat": 0 }
  }
}
```

## Remote Streaming PC Setup
If your OBS and StarCraft II are on different computers:
1. Enter the IP address of your SC2 computer in the **SC2 PC IP** box in settings.
2. On your SC2 PC, add `-clientapi 6119` to the SC2 launch arguments in the Battle.net launcher (Options > Game Settings > Additional Command Line Arguments).
3. Verify the API is accessible by visiting `http://[SC2-PC-IP]:6119/ui` from your streaming PC.

## Building from Source

### Dependencies
- **CMake** (3.16+)
- **Qt6** (Widgets, Core, Gui)
- **libobs** & **obs-frontend-api**
- **libcurl**
- **jansson**

### Build Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/nathaniasSC2/OBS-SC2-Switcher.git
   cd OBS-SC2-Switcher
   ```
2. Create a build directory and run CMake:
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build . --config Release
   ```

---
*Maintained by Nathanias. Based on the original work by Leigh Oliver.*

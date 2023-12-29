# Auto Core for Windows 11

Auto Core is a C++ utility designed to streamline task execution for Windows 11 systems. It is a keyboard manager specialized for the numpad keys and quick taskbar access.

## Key Features
- **Numpad Manager:** A keyboard manager for the numpad keys.
- **Taskbak Quick Access:** Launches pinned taskbar programs using winkeys.
- **Journaling Helper:** Streamlines the management of journal documents.
- **Creative Writing:** Generates random prompts for creative inspiration.
- **Music Player Intregation:** Integrates with Spotify and iTunes.

### Setting Up Auto Core
- Set a Windows shortcut to launch Auto Core.
- Pin the shortcut to the first position on the taskbar.

## Key Commands
- `Numkey 0` is a function key.
- `Numkey 1` interfaces with Auto Core.
- `Numkey 0 + 1` closes Auto Core.

### Spotify Integration
- Spotify requires OAuth 2.0 Authorization.
- For an interactive guide, see spotify_link.cc.

## Display Formats
**Timestamp Display:**
- `0:00` or `24:00` for 12:00 AM.
- `01:00` to `09:59` for 1:00 AM to 9:59 AM.
- `10:00` to `9:59` for 10:00 AM to 9:59 PM.
- `22:00` to `24:59` for 10:00 PM to 12:59 AM.

**Datestamp Display:**
- `1-1-24` for January 1, 2024.
- `12-12-24` for December 12, 2024.

**Song Title Format:**
- `[Song Name] [Artist Name] [Album Name] [Duration]`

## Program Design
- Auto Core provides immediate feedback to the user through the console window.
- A common error is requesting a string when there is no active textbox in focus. If this happens, the console will have a copy of any requested strings or failed requests.

## Tip
- An external keyboard manager can be used to remap `numkey 1` as `winkey + 1` for quick launching Auto Core. This can be useful if the program needs to be restarted.
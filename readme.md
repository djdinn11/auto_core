# Auto Core for Windows 11

Auto Core is a C++ utility designed to streamline task execution for Windows 11 systems. It is a keyboard manager specialized for the numpad keys and quick taskbar access.

## Program Design
- Keyboard Manager: Monitors numpad keys (vk codes 96 to 111) for quick command execution.
- Immediate Feedback: Utilizes a console window to display requested strings or report errors.
- Text Input Automation: Sends strings to the active textbox; retains a copy in the console if no textbox is in focus.
- Taskbar Integration: Accessible via winkey shortcuts (winkey + #1-10) for swift launching.
- Music Player Integration: Compatible with Spotify and iTunes, including Spotify's OAuth 2.0 Authorization (refer to spotify_link.cc).
- Journaling and Creativity Tools: Facilitates journal management and generates random creative prompts.
- Additional String Tools: Includes modules for creating timestamped strings or links.
- Optimal Placement: Recommended to be pinned to the first position on the taskbar for easy access.
- External Keyboard Manager Tip: Remap numkey 1 to winkey + 1 for quicker launching.

## Key Commands
- `Numkey 0` is a function key providing two-state support.
- `Numkey 1` interfaces with Auto Core.
- `Numkey 0 + 1` closes Auto Core.
- Other numkeys: Set via `auto_core` module or `config` module

### Configuration
- Modify `auto_core` module for initial settings.
- Check the `config` folder for runtime configuration options.

**Timestamp Display:**
- `00:00` to `09:59` for 12:00 AM to 9:59 AM.
- `10:00` to `9:59` for 10:00 AM to 9:59 PM.
- `22:00` to `23:59` for 10:00 PM to 11:59 PM.

**Datestamp Display:**
- `1-1-24` for January 1, 2024.
- `12-12-24` for December 12, 2024.


# Spotify Module

The Spotify module in Auto Core provides integration with Spotify's services, enabling control over music playback and access to user data. This module is particularly useful for users looking to integrate music playback control into their Auto Core setup.

## Features

- **OAuth 2.0 Authorization**: Utilizes Spotify's OAuth 2.0 Authorization for secure access to user's Spotify account. See `spotify_link.cc` for implementation details.
- **Playback Control**: Offers basic playback controls such as play, pause, and skip for Spotify tracks.
- **User Data Access**: Retrieves user-specific data like currently playing track and playlists.

## Spotify Authorization

To use this module, OAuth 2.0 Authorization is required. This process involves:

1. Redirecting the user to the Spotify Accounts authorization page to log in.
2. Users grant permission to Auto Core to access their Spotify data.
3. Spotify redirects back to your application with an authorization code.
4. Auto Core exchanges this code for an access token.

For detailed implementation, refer to `spotify_link.cc`.

## Polling with `sp_thread`

The `sp_thread` component is a key feature of the Spotify module, designed to keep track of playback changes in real-time. It operates on a detached thread to periodically poll Spotify's Web API. 

### Dynamic Polling Mechanism
- **Regular Polling**: By default, `sp_thread` polls Spotify every 15 seconds to check for playback changes.
- **Adaptive Polling**: The polling interval adapts based on the current playback status. For example, if a song is about to end in 5 seconds, `sp_thread` will schedule the next poll in 5 seconds instead of the standard 15. This approach allows for near real-time updates towards the end of tracks.
- **User Interaction Handling**: When the user changes the song through Auto Core, a condition variable is notified. This notification triggers `sp_thread` to immediately check Spotify for the latest playback status, providing real-time updates in response to user actions.

### Benefits of Adaptive Polling
- **Increased Responsiveness**: This mechanism ensures more timely updates, especially during critical playback changes like track transitions.
- **Efficient Resource Use**: By adjusting the polling interval based on playback status, `sp_thread` optimizes network and computational resources.

## Future Considerations

While the adaptive polling mechanism of `sp_thread` significantly enhances real-time playback detection, future improvements in Spotify's Web API could introduce more efficient methods:

- **Server-side Callback Listeners**: If Spotify introduces server-side callback listeners, real-time detection of playback changes could be implemented more efficiently. This would allow the module to receive instant notifications of playback events without the need for continuous polling.
- **Impact on `sp_thread`**: The introduction of such a feature in Spotify's API would make the current polling mechanism obsolete. In that scenario, `sp_thread` could be adapted or retired in favor of a more direct event-driven approach.

This part of the Spotify module illustrates a commitment to providing a responsive and efficient user experience, adapting to both the capabilities and limitations of the Spotify Web API.


## Usage

- Ensure you have valid Spotify credentials and have authorized Auto Core to access your Spotify account.
- Use provided functions to control playback or retrieve user data.
- Be aware of the 15-second polling interval for playback changes.

## Contributing

- Suggestions and contributions for enhancing the Spotify module, especially regarding OAuth 2.0 implementation and polling efficiency, are welcome.

## License

This module is part of Auto Core and inherits the project's [MIT License](LINK_TO_LICENSE).

## Acknowledgments

- Thanks to Spotify for their comprehensive [Web API](https://developer.spotify.com/documentation/web-api/) which made this module possible.

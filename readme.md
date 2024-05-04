# Auto Core for Windows 11
Auto Core is a C++ utility designed to streamline task execution on Windows 11 systems. Auto Core is a specialized keyboard manager for the numpad keys providing support for quick taskbar access, music player integration, journaling support and inspiration, and automated text insertion.

Auto Core is deeply integrated with Windows 11, utilizing system resources to optimize efficiency and improve performance. It offers real-time feedback through a system console window, minimizing resource usage and boosting program startup times. Additionally, Auto Core streamlines text operations by utilizing the system clipboard and the 'ctrl + v' paste shortcut for quick text insertion into the active textbox.

## Main Features
- **Numpad Keyboard Manager:** Monitors the numpad and media keys to execute predefined tasks, allowing users to customize and streamline their workflows.
- **Automated Text Insertion:** Simplifies typing tasks by automating text insertion into any active textbox via the clipboard and 'ctrl + v' paste shortcut.
- **Taskbar Integration:** Provides quick taskbar access to pinned and non-pinned programs using system shortcuts (winkey + #) and additional support for further taskbar productivity.
- **Music Player Integration:** Provides support for music player integration with iTunes and Spotify.
- **Journaling Support:** Automates file creation and titling of journaling documents.
- **Creative Writing Inspiration:** Follows the 'dice roll' method to generate a random number or prompt for journaling inspiration.
- **System Maintenance:** Provides support for maintenance tasks, including emptying the recycle bin and facilitating browser-based local file management.

## Core Architecture
1. **Low-Level Keyboard Hook**:
   - A low-level keyboard hook monitors numpad keys (vk codes 96 to 111) and other user-defined keys to execute predefined tasks. This hook operates at the system level, allowing for intercepting keyboard input before it reaches any other software, ensuring minimal latency and immediate response.

2. **System Console Window**:
   - The system console window serves as a feedback hub, providing real-time outputs to users. It's optimized for low resource usage, enabling quick startups and reducing the overall system load. This console is essential for debugging and dynamically displaying program statuses or errors.

3. **Clipboard Management for Text Insertion**:
   - Auto Core enhances text handling efficiency by utilizing the system clipboard. This method allows for swift insertion of text into any active textbox using the 'ctrl + v' paste shortcut. Clipboard management is carefully handled to prevent overwriting user data, with mechanisms in place to manage clipboard history and restore previous entries if needed.

4. **Taskbar Integration**:
   - Taskbar integration is achieved through the use of the 'winkey + #' system shortcuts, facilitating immediate access to applications pinned on the taskbar up to the tenth position. For applications not pinned or beyond the first ten positions, Auto Core provides additional management features to customize access according to user preferences.

5. **Music Player Integration**:
   - Auto Core uses COM to integrate with iTunes.
   - Auto Core uses the Spotify Web API.

6. **Local Server for File Access**:
   - A local server is initiated to facilitate file access directly through a web browser. This feature is particularly useful for managing local files remotely or in environments where traditional file access methods are cumbersome or restricted. The server supports various protocols to ensure secure and efficient file handling.

## Folder Structure
- `++` - Project builder and utility scripts.
- `assets` - Graphical resources like icons and images.
- `bin` - Compiled executable (`auto_core.exe`).
- `build` - Intermediate build files including debug symbols.
- `cloud` - Cloud integration scripts, specifically for services like Google Firebase.
- `config` - Runtime configuration files.
- `core` - Core component files of the application.
- `dev` - Legacy codebase.
- `dist` - Modules for project distribution.
- `docs` - Documentation resources.
- `import` - Main program modules.
- `include` - Shared module files.
- `lib` - External libraries and dependencies.
- `link` - User-customized string files for automated text insertion.
- `log` - Log files for debugging and operational logging.
- `server` - Local server setup files.
- `src` - Source code files.
- `star` - User-specific data like login tokens and journal databases.
- `sun` - Program taskbar shortcut.
- `tests` - Testing scripts and test cases.
- `tools` - Standalone scripts for additional functionalities.
- `utils` - Utility and helper files, such as Doxygen configuration.
- `visual` - Visual Studio integration files, such as solutions and project setups.

## Changelog
[Click here to view the changelog](dist/changelog.md)
## License
[Click here to view the license](dist/license.md)
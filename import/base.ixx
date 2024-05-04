/*!
\file base.ixx
\brief Central module for importing essential C++ Standard Library components and setting up namespace aliases and using directives for widespread use throughout the project.
\hardlink
 */
export module base;

// Chrono Utilities
export import <chrono>;

// Filesystem Utilities
export import <filesystem>;

// Threading Utilities
export import <thread>;
export import <mutex>;
export import <condition_variable>;

// Stream Utilities
export import <sstream>; // Note: Depending on the compiler and standard library implementation, you might need to rely on #include for some headers if they are not yet module-aware
export import <fstream>;

// I/O Stream Objects
export import <iostream>;

// String Utilities
export import <string>;

// Formatting and Error Handling
export import <format>;

// STL Containers
export import <array>;
export import <vector>;
export import <unordered_map>;

// Miscellaneous Utilities
export import <functional>;

// Random Number Utilities
export import <random>;


export {
    /*! \defgroup ChronoUtilities Chrono Utilities
     *  \brief Time-based functions and utilities.
     */
    namespace chrono = std::chrono; //!< Grouped under Chrono Utilities.

    /*! \defgroup FilesystemUtilities Filesystem Utilities
     *  \brief Utilities for handling files and directories.
     */
    namespace fs = std::filesystem; //!< Grouped under Filesystem Utilities.
    using std::ios;
    using std::ios_base;

    /*! \defgroup ThreadingUtilities Threading Utilities
     *  \brief Utilities for managing threads and synchronization.
     */
    namespace this_thread = std::this_thread; //!< Grouped under Threading Utilities.
    using std::thread; //!< Multi-threading support.
    using std::mutex; //!< Mutex for thread synchronization.
    using std::condition_variable; //!< Condition variable for thread management.
    using std::unique_lock; //!< Locking mechanism for mutual exclusion.

    /*! \defgroup StreamUtilities Stream Utilities
     *  \brief Stream-based utilities for input and output.
     */
    using ss = std::stringstream; //!< String stream for read/write.
    using iss = std::istringstream; //!< Input string stream.
    using oss = std::ostringstream; //!< Output string stream.
    using wss = std::wostringstream; //!< Wide character output string stream.
    using std::ifstream; //!< File input stream.
    using std::ofstream; //!< File output stream.
    using std::streamsize;

    /*! \defgroup IOStreamObjects I/O Stream Objects
     *  \brief Standard I/O stream objects.
     */
    using std::cerr; //!< Standard error stream.
    using std::cin; //!< Standard input stream.
    using std::cout; //!< Standard output stream.
    using std::wcout; //!< Wide character output stream.
    using std::getline;

    /*! \defgroup StringUtilities String Utilities
     *  \brief Utilities for string manipulation and conversion.
     */
    using std::string; //!< Standard string.
    using std::wstring; //!< Wide character string.
    using std::to_string; //!< Convert numeric values to strings.

    /*! \defgroup FormattingErrorHandling Formatting and Error Handling
     *  \brief Utilities for formatting and error handling.
     */
    using std::format; //!< Format text.
    using std::format_error; //!< Exception for format errors.
    using std::invalid_argument; //!< Exception for invalid arguments.
    using std::vformat; //!< Format text using a list of arguments.
    using std::make_format_args; //!< Helper to create a format argument list.
    using std::forward; //!< Forward arguments.
    using std::endl; //!< Newline and flush for streams.

    /*! \defgroup STLContainers STL Containers
     *  \brief Standard Template Library containers.
     */
    using std::array; //!< Static array.
    using std::vector; //!< Dynamic array.
    using std::unordered_map; //!< Hash table based map.

    /*! \defgroup MiscellaneousUtilities Miscellaneous Utilities
     *  \brief Various utility functions and classes.
     */
    using std::function; //!< General-purpose polymorphic function wrapper.
    using std::setw; //!< Set width for stream manipulations.
    using std::setfill; //!< Set fill character for streams.
    using std::exception; //!< Base class for standard exceptions.

    /*! \defgroup RandomNumberUtilities Random Number Utilities
     *  \brief Utilities for generating random numbers.
     */
    using std::mt19937; //!< Mersenne Twister 19937 generator.
    using std::random_device; //!< Random device to provide seed.
    using std::uniform_int_distribution; //!< Uniform integer distribution.
}
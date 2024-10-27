# App Manager Documentation

## Overview
App Manager is a desktop application designed to help users manage software installations efficiently. It provides a user-friendly interface for selecting applications, downloading them from specified URLs, and saving them with the desired filenames. The application is currently developed for Windows, with ongoing support for macOS and Linux.

## Features
- **Application Management**: Users can view a list of available applications.
- **Download Management**: The application can initiate downloads using URLs defined in a JSON configuration file.
- **Customization**: Users can easily update application parameters through a JSON file without changing the codebase.

## Installation
1. **Download**: Obtain the latest version of App Manager from the official repository or website.
2. **Install**: Follow the installation instructions specific to your operating system (Windows, macOS, or Linux).
3. **Run the Application**: Launch App Manager from your applications menu or desktop shortcut.

## User Interface (UI)
The main interface includes
- **Application List**: Displays all applications defined in the JSON configuration file.
- **Download Button**: Initiates the download for the selected application.
- **Changelog Section**: Provides updates and changes made in the application.
- **Author Information**: Displays information about the application developer.

## Configuration
The application utilizes a JSON configuration file (`MainWindow.json`) to define the applications available for download.
### JSON Configuration FIle Structure
- The JSON file should be located in the application’s directory.
- It contains an array of application objects with properties like name, download URL, and output filename.

## Integration with JSON
For a detailed description of how the JSON configuration integrates into App Manager, refer to the [Support for JSON Configuration](Support-Json.md) document.

## Example Usage
When a user selects an application from the list:

1. The application retrieves the corresponding download URL and output filename from the JSON configuration.
2. It initiates the download process and saves the file using the specified output filename.

## Code Example
Here's how the application fetches the download URL and output filename:
```cpp
QString url = getDefaultDownloadURL("ExampleApp1");
QString outputFile = getDefaultOutputFileName("ExampleApp1");
```

## Error Handling
The application includes error handling for scenarios such as:
- Missing or corrupted JSON configuration files.
- Errors in parsing JSON data.
- Download failures due to invalid URLs.

## User Notifications
Users will receive alerts for any errors that occur during these processes via message boxes.

## Support and Contributions
For support, please contact the App Manager team via the support email provided on the application interface or refer to community forums for help.

## Contributing
Contributions to the App Manager are welcome! Please follow the guidelines outlined in the repository for submitting issues, feature requests, or pull requests.

## License
This project is licensed under the Apache 2.0 License. See the [LICENSE](LICENSE) file for more information.

## Conclusion
App Manager simplifies the process of managing application downloads through an easy-to-use interface and flexible configuration options. Users can tailor their experience by updating the JSON configuration, ensuring that they have the latest software available with minimal effort.
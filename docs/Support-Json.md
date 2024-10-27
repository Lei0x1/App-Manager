# Support for JSON Configuration in App Manager

## Overview
App Manager utilizes a JSON configuration file to define application details, including download URLs and output file names. This document outlines the structure of the JSON file, its integration within the application, and provides examples to help users understand how to configure it effectively.

## JSON Structure
The main configuration file, `MainWindow.json`, contains an array of applications, each defined by specific properties. Here is the structure of the JSON file:
```json
{
  "applications": [
    {
      "name": "App1",
      "defaultUrl": "https://example.com/app1/download",
      "outputFileName": "App1.exe"
    },
    {
      "name": "App2",
      "defaultUrl": "https://example.com/app2/download",
      "outputFileName": "App2.exe"
    }
  ]
}
```

## Key Fields
- **applications**: An array of application objects
  - **name**: The name of the application, used for display in the user interface.
  - **defaultUrl**: The default download URL for the application. This URL is used to fetch the installation files.
  - **outputFileName**: The name of the file that will be saved after the download is completed.

## Integrating JSON in App Manager
The JSON file is loaded when the application starts, populating the application's data structure and user interface elements. Here’s a brief overview of how it works in the application code:

### Required Libraries
To work with JSON in your project, ensure you include the following libraries:

In `MainWindow.cpp`:
```cpp
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
```
In MainWindow.h:
```cpp
#include <QMap>
```

### Loading the Configuration
The `loadConfig()` method in `MainWindow.cpp` is responsible for reading the JSON file and populating the application data:
```cpp
void MainWindow::loadConfig() {
    QFile configFile("MainWindow.json");
    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not open configuration file.");
        return;
    }

    QByteArray jsonData = configFile.readAll();
    configFile.close();

    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        QMessageBox::warning(this, "Error", "Error parsing JSON: " + parseError.errorString());
        return;
    }

    QJsonObject rootObject = document.object();
    QJsonArray appsArray = rootObject.value("applications").toArray();

    for (const QJsonValue &value : appsArray) {
        QJsonObject appObject = value.toObject();
        QString name = appObject.value("name").toString();
        QString defaultUrl = appObject.value("defaultUrl").toString();
        QString outputFileName = appObject.value("outputFileName").toString();

        appListWidget->addItem(name);
        appData[name] = {defaultUrl, outputFileName};
    }
}
```

## Accessing Configuration Data
Once the JSON data is loaded, you can access the download URL and output file name for any application using the following methods in `MainWindow.h`:
```cpp
QString MainWindow::getDefaultDownloadURL(const QString &appName) {
    return appData.value(appName).defaultUrl;
}

QString MainWindow::getDefaultOutputFileName(const QString &appName) {
    return appData.value(appName).outputFileName;
}
```

These methods retrieve the default URL and output file name based on the application name, allowing seamless integration with the download process.

## Example of JSON Usage
### Example JSON File
Here’s an example of a complete `MainWindow.json` file for two applications:
```json
{
  "applications": [
    {
      "name": "ExampleApp1",
      "defaultUrl": "https://example.com/exampleapp1/download",
      "outputFileName": "ExampleApp1.exe"
    },
    {
      "name": "ExampleApp2",
      "defaultUrl": "https://example.com/exampleapp2/download",
      "outputFileName": "ExampleApp2.exe"
    }
  ]
}
```

## Example Usage in Application
When a user selects `ExampleApp1` from the app list, the application retrieves the download URL and output file name as follows:
```cpp
QString url = getDefaultDownloadURL("ExampleApp1");  // "https://example.com/exampleapp1/download"
QString outputFile = getDefaultOutputFileName("ExampleApp1");  // "ExampleApp1.exe"

// Initiating the download process
DownloadThread *downloadThread = new DownloadThread(url, outputFile, this);
connect(downloadThread, &DownloadThread::downloadComplete, this, &MainWindow::onDownloadComplete);
downloadThread->start();
```

## Conclusion
Using JSON for configuration in App Manager allows for easy updates and customization of application parameters without modifying the codebase. Users can simply edit the `MainWindow.json` file to add new applications or update existing ones. For further questions or support, please contact our support team or refer to our community forums.

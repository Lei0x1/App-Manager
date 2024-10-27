# Manual & JSON Configuration Steps

## Manual Configuration

To manually add items to the application, follow these steps:

1. **Locate the Code Section**: Find the section in your `MainWindow.cpp` file where the app list widget is set up.

2. **Add Items Manually**: Uncomment the line where you add items to the `appListWidget`:
    ```cpp
    appListWidget->addItems({"Google Chrome", "Discord"});
    ```
3. **Provide Download URLs**: In the `getDefaultDownloadURL` function, define manual download URLs for the applications:
    ```cpp
    if (appName == "Google Chrome") {
        return "https://dl.google.com/chrome/install/latest/chrome_installer.exe";  // Actual URL for Chrome download
    } else if (appName == "Discord") {
        return "https://discord.com/api/download?platform=win"; // Placeholder URL for Discord
    }
   ```

4. **Set Output File Names**: In the `getDefaultOutputFileName` function, specify the output file names for each application:
    ```cpp
    if (appName == "Google Chrome") {
        return "ChromeSetup.exe";
    } else if (appName == "Discord") {
        return "DiscordSetup.exe";
    }
    return "AppSetup.exe";  // Default name for other apps
    ```

## Json Configuration
To configure the application using JSON, follow these steps:
1. **Include Necessary Libraries**: Ensure you have included the necessary JSON libraries at the beginning of your `MainWindow.cpp` file:
    ```cpp
    #include <QFile>
    #include <QJsonDocument>
    #include <QJsonObject>
    #include <QJsonArray>
    #include <QJsonValue>
    #include <QJsonParseError>
    ```
2. **Create JSON File**: Create a JSON file (e.g., `MainWindow.json`) that contains the configuration for the applications. An example structure could be:
    ```json
    {
        "applications": [
            {
                "name": "Google Chrome",
                "defaultUrl": "https://dl.google.com/chrome/install/latest/chrome_installer.exe",
                "outputFileName": "ChromeSetup.exe"
            },
            {
                "name": "Discord",
                "defaultUrl": "https://discord.com/api/download?platform=win",
                "outputFileName": "DiscordSetup.exe"
            }
        ]
    }
    ```
3. Load JSON Configuration: Implement a method to load the JSON configuration in your `MainWindow` class. The `loadConfig` function already handles this:
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
4. **Verify Application Loading**: Run your application and verify that the apps load correctly from the JSON configuration.
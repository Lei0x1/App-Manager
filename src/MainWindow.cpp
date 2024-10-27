#include "../header/MainWindow.h"
#include "../header/DownloadThread.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QStandardPaths>
#include <QProgressBar>
#include <QGuiApplication>
#include <QScreen>
#include <QShowEvent>
#include <QToolBar>
#include <QTextEdit>

// Support Json
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Set up the app list
    appListWidget = new QListWidget(this);

    // Uncomment the following line to manually add items to the widget
    //appListWidget->addItems({"Google Chrome", "Discord"});

    // Load the application configuration from JSON
    loadConfig();
    
    /*
     * How to add applications manually or using JSON:
     *
     * 1. **Manual Addition**: 
     *    - Uncomment the line: 
     *      `appListWidget->addItems({"Google Chrome", "Discord"});`
     *    - This will directly add the specified applications to the list.
     *
     * 2. **JSON Configuration**: 
     *    - Ensure that the necessary libraries for JSON handling are included:
     *      - The includes are already present at line MainWindow.cpp:14 ("// Support for JSON").
     *    - Create a JSON file (e.g., `MainWindow.json`) with the following structure:
     *      ```json
     *      {
     *          "applications": [
     *              {
     *                  "name": "Google Chrome",
     *                  "defaultUrl": "https://dl.google.com/chrome/install/latest/chrome_installer.exe",
     *                  "outputFileName": "ChromeSetup.exe"
     *              },
     *              {
     *                  "name": "Discord",
     *                  "defaultUrl": "https://discord.com/api/download?platform=win",
     *                  "outputFileName": "DiscordSetup.exe"
     *              }
     *          ]
     *      }
     *      ```
     *    - Modify the JSON structure as needed to add more applications.
     *    - The application list will automatically populate based on the JSON content.
     */

    setCentralWidget(appListWidget);

    initialAppList = appListWidget->findItems("*", Qt::MatchWildcard);

    // Create a navigation bar
    QToolBar *navBar = addToolBar("Navigation");
    QPushButton *homeButton = new QPushButton("Home");
    QPushButton *changelogButton = new QPushButton("Changelog");
    QPushButton *authorButton = new QPushButton("Author");

    // Add buttons to the navigation bar
    navBar->addWidget(homeButton);
    navBar->addWidget(changelogButton);
    navBar->addWidget(authorButton);

    // Initialize the changelog display
    changelogDisplay = new QTextEdit(this);
    changelogDisplay->setReadOnly(true); // Make it read-only
    changelogDisplay->setVisible(false); // Initially hidden

    // Set up a vertical layout to include the app list and changelog display
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(appListWidget);
    mainLayout->addWidget(changelogDisplay); // Add changelog display to layout

    // Create a widget for central area
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Connect button signals to their respective slots
    connect(appListWidget, &QListWidget::itemClicked, this, &MainWindow::onAppClicked);
    connect(homeButton, &QPushButton::clicked, this, &MainWindow::onHomeClicked);
    connect(changelogButton, &QPushButton::clicked, this, &MainWindow::onChangelogClicked);
    connect(authorButton, &QPushButton::clicked, this, &MainWindow::onAuthorClicked);
    
    setWindowTitle("App Manager");
    setFixedSize(800, 500);
}

// Override the showEvent method to center the window
void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event); // Call base class implementation

    // Center the window on the screen
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
}

void MainWindow::onAppClicked(QListWidgetItem *item) {
    // Store app name and get the download URL for the clicked app
    appName = item->text();
    currentDownloadURL = getDefaultDownloadURL(appName);

    // Open the download dialog when an app is clicked
    downloadDialog = new QDialog(this);
    downloadDialog->setWindowTitle("Download " + appName);

    // Set up dialog layout
    QVBoxLayout *layout = new QVBoxLayout(downloadDialog);
    QProgressBar *progressBar = new QProgressBar(downloadDialog);
    progressBar->setRange(0, 100);
    layout->addWidget(progressBar);

    QPushButton *downloadButton = new QPushButton("Download", downloadDialog);
    connect(downloadButton, &QPushButton::clicked, this, [this, progressBar, downloadButton]() {
        QString outputFileName = getDefaultOutputFileName(appName);
        QString downloadsFolder = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
        QString outputPath = downloadsFolder + "/" + outputFileName;  // Full path for saving

        downloadButton->setEnabled(false);  // Disable the download button while downloading
        DownloadThread *downloadThread = new DownloadThread(currentDownloadURL, outputPath);
        connect(downloadThread, &DownloadThread::progressUpdated, progressBar, &QProgressBar::setValue);
        connect(downloadThread, &DownloadThread::downloadComplete, this, [this, downloadThread, downloadButton](bool success) {
            if (success) {
                QMessageBox::information(this, "Download Complete", "File downloaded successfully.");
            } else {
                QMessageBox::warning(this, "Download Error", "Failed to download the file.");
            }
            downloadDialog->accept();
            downloadThread->deleteLater();
            downloadButton->setEnabled(true);  // Re-enable the download button
        });
        downloadThread->start();  // Start the download thread
    });

    QPushButton *cancelButton = new QPushButton("Cancel", downloadDialog);
    connect(cancelButton, &QPushButton::clicked, downloadDialog, &QDialog::reject);

    layout->addWidget(downloadButton);
    layout->addWidget(cancelButton);

    downloadDialog->setLayout(layout);
    downloadDialog->exec();  // Show the dialog modally

    inHomeView = false; // Set to false since we're not in home view anymore
}

void MainWindow::onHomeClicked() {
    if (!inHomeView) {
        appListWidget->clear(); // Clear the current items in the app list widget

        for (QListWidgetItem *item : initialAppList) {
            appListWidget->addItem(new QListWidgetItem(item->text())); // Restore initial items
        }

        inHomeView = true; // Update the state variable
    }
}

void MainWindow::onChangelogClicked() {
    if (changelogDisplay->isVisible()) {
        // If the changelog is already visible, hide it
        changelogDisplay->setVisible(false);
    } else {
        changelogDisplay->clear();  // Clear changelog display if needed

        // Prepare changelog text
        QString changelogText = "Version: 1.0.0\n\n"
                                "Initial release with basic functionalities.\n"
                                "Features:\n"
                                "- App downloading functionality\n"
                                "- Navigation bar for easy access.";

        // Update the changelog display with the text
        changelogDisplay->setPlainText(changelogText);
        changelogDisplay->setVisible(true); // Show the changelog display
    }
}

void MainWindow::onAuthorClicked() {
    if (changelogDisplay->isVisible()) {
        // If the changelog is already visible, hide it
        changelogDisplay->setVisible(false);
    } else {
        changelogDisplay->clear();  // Clear changelog display if needed

        // Prepare changelog text
        QString changelogText = "Author Information\n\n"
                                "Email: author@example.com\n"
                                "GitHub: github.com/author\n"
                                "Description: A passionate developer focused on creating useful applications.\n";

        // Update the changelog display with the text
        changelogDisplay->setPlainText(changelogText);
        changelogDisplay->setVisible(true); // Show the changelog display
    }
}

QString MainWindow::getDefaultDownloadURL(const QString &appName) {

    /* 
     * Manual Configuration Example
     *
     * Use this block to manually define download URLs for specific applications.
     *
     * if (appName == "Google Chrome") {
     *     return "https://dl.google.com/chrome/install/latest/chrome_installer.exe"; 
     * } else if (appName == "Discord") {
     *     return "https://discord.com/api/download?platform=win"; 
     * } else {
     *     return "https://example.com/app6/download"; // Default placeholder URL for other apps
     * }
     *
     * Uncomment the block above to use manual configuration for download URLs.
     */

    // Support for JSON configuration
    return appData.contains(appName) ? appData[appName].defaultUrl : "https://example.com/default";
}

QString MainWindow::getDefaultOutputFileName(const QString &appName) {

    /* 
     * Manual Configuration Example
     *
     * Use this block to manually define output file names for specific applications.
     *
     * if (appName == "Google Chrome") {
     *     return "ChromeSetup.exe";
     * } else if (appName == "Discord") {
     *     return "DiscordSetup.exe"; // Note the spelling correction from "Dicord"
     * }
     * return "AppSetup.exe";  // Default name for other apps
     *
     * Uncomment the block above to use manual configuration for output file names.
     */

    // Support for JSON configuration
    return appData.contains(appName) ? appData[appName].outputFileName : "AppSetup.exe";
}

void MainWindow::onCancelButtonClicked() {
    if (downloadDialog) {
        downloadDialog->reject();  // Close the dialog
    }
}

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
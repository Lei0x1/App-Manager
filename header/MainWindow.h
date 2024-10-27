#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDialog>
#include <QString>
#include <QList>
#include <QTextEdit>
#include <QMap>

struct AppInfo {
    QString defaultUrl;
    QString outputFileName;
};

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
    void showEvent(QShowEvent *event) override; // Declare the showEvent method

private slots:
    void onAppClicked(QListWidgetItem *item);    // Handle app selection
    void onHomeClicked();                        // Handle home button click
    void onChangelogClicked();                   // Handle changelog button click
    void onAuthorClicked();                      // Handle author button click
    void onCancelButtonClicked();                // Handle cancel button click

private:
    void loadConfig();
    QString getDefaultDownloadURL(const QString &appName);
    QString getDefaultOutputFileName(const QString &appName);

    QListWidget *appListWidget;
    QDialog *downloadDialog;
    QString currentDownloadURL;
    QString appName;
    QTextEdit *changelogDisplay;
    QList<QListWidgetItem*> initialAppList;

    // Support Json
    QMap<QString, AppInfo> appData;

    bool inHomeView = true;  // Used in onHomeClicked();
};

#endif // MAINWINDOW_H

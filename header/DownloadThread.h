#ifndef DOWNLOADTHREAD_H
#define DOWNLOADTHREAD_H

#include <QThread>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>

class DownloadThread : public QThread {
    Q_OBJECT
public:
    DownloadThread(const QString &url, const QString &outputPath, QObject *parent = nullptr);
    void run() override;

signals:
    void progressUpdated(int progress);    // Signal to update progress
    void downloadComplete(bool success);   // Signal when download is complete

private:
    QString downloadURL;
    QString outputFilePath;

    void downloadFile();                   // Helper method to handle the download
};

#endif // DOWNLOADTHREAD_H

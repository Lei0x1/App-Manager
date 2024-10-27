#include "../header/DownloadThread.h"
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QEventLoop>

DownloadThread::DownloadThread(const QString &url, const QString &outputPath, QObject *parent)
    : QThread(parent), downloadURL(url), outputFilePath(outputPath) {}

void DownloadThread::run() {
    downloadFile();  // Call the download file function
}

void DownloadThread::downloadFile() {
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(downloadURL)));

    // Connect to signals to monitor progress and finished state
    connect(reply, &QNetworkReply::downloadProgress, this, [this](qint64 bytesReceived, qint64 bytesTotal) {
        if (bytesTotal > 0) {
            int progress = static_cast<int>((static_cast<double>(bytesReceived) / bytesTotal) * 100);
            emit progressUpdated(progress); // Emit progress percentage
        }
    });

    // Wait for the download to finish
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    // Handle download completion
    bool success = false;
    if (reply->error() == QNetworkReply::NoError) {
        QFile file(outputFilePath);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(reply->readAll());
            file.close();
            success = true; // Mark download as successful
        }
    }
    emit downloadComplete(success);
    reply->deleteLater(); // Clean up reply
}
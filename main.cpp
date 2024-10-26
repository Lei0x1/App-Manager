#include <QApplication>
#include "header/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;  // Create an instance of your main window
    window.show();      // Show the main window

    return app.exec();  // Enter the application main loop
}
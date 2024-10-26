/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWS_H
#define UI_MAINWINDOWS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_MainWindow  // This should match your window class name
{
public:
    QDialogButtonBox *buttonBox;  // Dialog box for OK and Cancel buttons
    QLabel *label;  // Label to display centered text in the window

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");  // Set the main window's object name
        MainWindow->setFixedSize(431, 340);  // Set the fixed size of the window

        // Button Box setup: Adds standard OK and Cancel buttons with a horizontal orientation
        buttonBox = new QDialogButtonBox(MainWindow);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(130, 280, 161, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

        // Label setup: Adds a centered label with initial text to the window
        label = new QLabel(MainWindow);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 20, 401, 231));
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignCenter);

        // Calls function to set the translated text and window title
        retranslateUi(MainWindow);

        // Connections for button actions (OK and Cancel)
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, MainWindow, []() {
            // Handle the Ok button click here
        });

        QObject::connect(buttonBox, &QDialogButtonBox::rejected, MainWindow, []() {
            // Handle the Cancel button click here
        });

        // Auto-connects signals and slots by object name
        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)  // Change from QDialog to QMainWindow
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "App Manager", nullptr));  // Set main window title
        label->setText(QCoreApplication::translate("MainWindow", "Test", nullptr));  // Set initial label text
    } // retranslateUi
};

namespace Ui {
    class MainWindow : public Ui_MainWindow {};  // Change class name accordingly
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWS_H

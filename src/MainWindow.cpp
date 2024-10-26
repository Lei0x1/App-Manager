#include "../header/MainWindow.h"

// generated UI header
#include "../header/ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect button signals to the slots for handling clicks
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &MainWindow::onOkClicked);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &MainWindow::onCancelClicked);
}

MainWindow::~MainWindow()
{
    delete ui; // Clean up
}

// Implement the slot functions for handling button clicks
void MainWindow::onOkClicked() {
    // Handle OK button click here
    
}

void MainWindow::onCancelClicked() {
    // Handle Cancel button click here
}

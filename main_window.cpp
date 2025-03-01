#include "main_window.h"
#include "ui_main_window.h"

#include <QMessageBox>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connectSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::connectSlots()
{
    connect(ui->fileExitAction, &QAction::triggered, this, &MainWindow::onFileExitTriggered);

    return true;
}

void MainWindow::closeEvent(QCloseEvent *event)
{

    QMessageBox::StandardButton answer = QMessageBox::question(this, tr("Exiting"), tr("Do you really want to close the application?"));

    if (answer != QMessageBox::StandardButton::Yes)
    {
        event->ignore();
    }
    else
    {
        event->accept();
    }
}

void MainWindow::onFileExitTriggered(bool checked)
{
    (void)checked;

    close();
}

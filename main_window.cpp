#include "main_window.h"
#include "ui_main_window.h"

#include <QMessageBox>
#include <QCloseEvent>
#include <classes/mdisubwindows/tictactoe/tictactoe_local_game_settings_mdisubwindow.h>

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
    connect(ui->fileExitAction, &QAction::triggered, this, &MainWindow::onFileExitActionTriggered);
    connect(ui->gamesTicTacToeLocalAction, &QAction::triggered, this, &MainWindow::onGamesTicTacToeLocalActionTriggered);

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

void MainWindow::onFileExitActionTriggered(bool checked)
{
    (void) checked;

    close();
}

void MainWindow::onGamesTicTacToeLocalActionTriggered(bool checked)
{
    (void) checked;

    TicTacToeLocalGameSettingsMdiSubWindow *w = new TicTacToeLocalGameSettingsMdiSubWindow();
    ui->mainMdiArea->addSubWindow(w);
    w->show();
}

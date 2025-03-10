#include "main_window.h"
#include "ui_main_window.h"

#include <QMessageBox>
#include <QCloseEvent>
#include <classes/mdisubwindows/tictactoe/tictactoe_local_game_settings_mdisubwindow.h>
#include <classes/mdisubwindows/tictactoe/tictactoe_lan_server_settings_mdisubwindow.h>
#include <classes/utils/u_frames.h>
#include <classes/mdisubwindows/rules_viewer.h>

MainWindow *MainWindow::m_mainInstance = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    MainWindow::m_mainInstance = this;

    ui->setupUi(this);

    setIcons();

    connectSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QMdiArea *MainWindow::getMainMdiArea()
{
    return MainWindow::m_mainInstance ? MainWindow::m_mainInstance->ui->mainMdiArea : nullptr;
}

bool MainWindow::connectSlots()
{
    connect(ui->fileExitAction, &QAction::triggered, this, &MainWindow::onFileExitActionTriggered);
    connect(ui->gamesTicTacToeLocalAction, &QAction::triggered, this, &MainWindow::onGamesTicTacToeLocalActionTriggered);
    connect(ui->gamesTicTacToeRulesAction, &QAction::triggered, this, &MainWindow::onGamesTicTacToeRulesActionTriggered);
    connect(ui->gamesTicTacToeLANCreateAction, &QAction::triggered, this, &MainWindow::onGamesTicTacToeLANCreateActionTriggered);

    return true;
}

void MainWindow::setIcons()
{
    bool dark = UFrames::isDarkMode();

    setWindowIcon(QIcon(dark ? ":/application/app_icon_light" : ":/application/app_icon_dark"));

    ui->gamesTicTacToeMenu->setIcon(QIcon(dark ? ":/application/tictactoe_light" : ":/application/tictactoe_dark"));
    ui->gamesTicTacToeLocalAction->setIcon(QIcon(dark ? ":/application/local_light" : ":/application/local_dark"));
    ui->gamesTicTacToeLANMenu->setIcon(QIcon(dark ? ":/application/lan_light" : ":/application/lan_dark"));
    ui->gamesTicTacToeRulesAction->setIcon(QIcon(dark ? ":/application/book_light" : ":/application/book_dark"));
}

void MainWindow::openRulesForm(QString gameName)
{
    RulesViewer *window = new RulesViewer(gameName);
    ui->mainMdiArea->addSubWindow(window);
    UFrames::centreFormInMdiArea(window);
    window->show();
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

    TicTacToeLocalGameSettingsMdiSubWindow *w = new TicTacToeLocalGameSettingsMdiSubWindow(ui->mainMdiArea);
    ui->mainMdiArea->addSubWindow(w);
    UFrames::centreFormInMdiArea(w);
    w->show();
}

void MainWindow::onGamesTicTacToeRulesActionTriggered(bool checked)
{
    (void) checked;

    openRulesForm("tictactoe");
}

void MainWindow::onGamesTicTacToeLANCreateActionTriggered(bool checked)
{
    (void) checked;

    TicTacToeLanServerSettingsMdiSubWindow *w = new TicTacToeLanServerSettingsMdiSubWindow();
    ui->mainMdiArea->addSubWindow(w);
    UFrames::centreFormInMdiArea(w);
    w->show();
}

#include "tictactoe_local_game_mdisubwindow.h"
#include "ui_tictactoe_local_game_mdisubwindow.h"

#include <classes/utils/u_messageboxes.h>
#include <classes/utils/u_frames.h>
#include <classes/objects/tictactoe/match.h>

#define CELL_SIZE 100
#define MARGIN 5

#define REAL_CELL_SIZE (CELL_SIZE - (2 * MARGIN))

TicTacToeLocalGame::TicTacToeLocalGame(const QString &xPlayerName, const QString &oPlayerName, QWidget *parent)
    : QMdiSubWindow(parent)
    , ui(new Ui::TicTacToeLocalGame)
{
    initialize(xPlayerName, oPlayerName);
}

TicTacToeLocalGame::~TicTacToeLocalGame()
{
    delete ui;
}

void TicTacToeLocalGame::initialize(const QString &xPlayerName, const QString &oPlayerName)
{
    //Initialize variables
    m_match = new Match(xPlayerName, oPlayerName, this);

    //Set GUI
    initializeComponents();

    //Initial message
    QString playerName;
    m_match->getPlayerName(m_match->getActualTurn(), playerName);
    ui->infoLabel->setText(tr("%0's turn.").arg(playerName));

    connectAllSlots();
}

void TicTacToeLocalGame::initializeComponents()
{
    //Set flags and attributes
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlag(Qt::WindowMaximizeButtonHint, false);
    setWindowIcon(QIcon(UFrames::isDarkMode() ? ":/application/tictactoe_light" : ":/application/tictactoe_dark"));

    //Content from UI
    QWidget *content = new QWidget(this);
    ui->setupUi(content);
    setWidget(content);

    //Adjust size
    UFrames::adaptSubMdiSizesByContent(this, content->width(), content->height(), true);

    //Add cells
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            qint32 x = (c * CELL_SIZE) + MARGIN;
            qint32 y = (r * CELL_SIZE) + MARGIN;

            m_cells[r][c] = new QGridLabel(r, c, ui->boardLabel);
            m_cells[r][c]->setGeometry(x, y, REAL_CELL_SIZE, REAL_CELL_SIZE);
            connect(m_cells[r][c], &QGridLabel::clicked, this, &TicTacToeLocalGame::onGridLabelClicked);
        }
    }

    //Update graphics
    updateGraphics();
}

void TicTacToeLocalGame::updateGraphics()
{
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            TicTacToePlayerEnum token = m_match->getBoard()->getTokenByPosition(r, c);
            QPixmap pixmap = QPixmap();

            if (token == TicTacToePlayerEnum::Cross)
            {
                pixmap = QPixmap(":/tictactoe/cross").scaled(REAL_CELL_SIZE, REAL_CELL_SIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            }
            else if (token == TicTacToePlayerEnum::Circle)
            {
                pixmap = QPixmap(":/tictactoe/circle").scaled(REAL_CELL_SIZE, REAL_CELL_SIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            }

            m_cells[r][c]->setPixmap(pixmap);
        }
    }
}

void TicTacToeLocalGame::connectAllSlots()
{
    connect(m_match, &Match::actualTurnChangedSignal, this, &TicTacToeLocalGame::onActualTurnChanged);
    connect(m_match, &Match::gameStoppedSignal, this, &TicTacToeLocalGame::onGameStopped);
}

void TicTacToeLocalGame::onGridLabelClicked(QGridLabel *sender)
{
    qDebug() << "Label clicked = " + sender->getGridPosition()->toString();

    if (!m_match->isGameStopped())
    {
        TicTacToePlayerEnum token = m_match->getBoard()->getTokenByPosition(*sender->getGridPosition());

        if (token == TicTacToePlayerEnum::None)
        {
            m_match->getBoard()->insertToken(*sender->getGridPosition(), m_match->getActualTurn());

            updateGraphics();
            m_match->switchTurn();

            TicTacToePlayerEnum gameOverResult = m_match->checkGameOver();

            if (gameOverResult != TicTacToePlayerEnum::None)
            {
                QString title;
                QString message;
                QString playerName;
                QPixmap icon;
                TicTacToePlayerEnum restartsWith;

                if (gameOverResult == (TicTacToePlayerEnum::Circle | TicTacToePlayerEnum::Cross)) //Drawn
                {
                    icon = QPixmap(":/tictactoe/drawn");
                    title = tr("Drawn match");
                    message = tr("Drawn match!\nDo you want to replay?");
                    restartsWith = m_match->getActualTurn();
                }
                else
                {
                    QString resPath =
                        gameOverResult == TicTacToePlayerEnum::Cross ?
                            ":/tictactoe/cross" :
                            ":/tictactoe/circle";
                    icon = QPixmap(resPath);
                    m_match->getPlayerName(gameOverResult, playerName);
                    title = tr("%0 player wins!").arg(gameOverResult == TicTacToePlayerEnum::Cross ? tr("Cross") : tr("Circle"));
                    message = tr("%0 wins this match!\nDo you want to replay?").arg(playerName);
                    restartsWith = !gameOverResult;
                }

                QMessageBox::StandardButton res = UMessageBoxes::showCustomMessageBox(title, message, icon, QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No);

                if (res == QMessageBox::StandardButton::Yes)
                {
                    m_match->restart(restartsWith);
                    updateGraphics();
                }
                else
                {
                    m_match->stopsGame();
                }
            }
        }
        else
        {
            qDebug() << "Cell is busy";
        }
    }
}

void TicTacToeLocalGame::onActualTurnChanged(Match *sender, TicTacToePlayerEnum actualTurn)
{
    (void)sender;

    QString playerName;
    m_match->getPlayerName(actualTurn, playerName);
    ui->infoLabel->setText(tr("%0's turn.").arg(playerName));
}

void TicTacToeLocalGame::onGameStopped(Match *sender)
{
    (void)sender;

    ui->infoLabel->setText(tr("Game over!"));
}

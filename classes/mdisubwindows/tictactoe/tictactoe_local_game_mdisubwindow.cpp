#include "tictactoe_local_game_mdisubwindow.h"
#include "ui_tictactoe_local_game_mdisubwindow.h"

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
    m_match = std::make_unique<Match>(xPlayerName, oPlayerName);

    //Set flags and attributes
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlag(Qt::WindowMaximizeButtonHint, false);

    //Set GUI
    initializeComponents();
}

void TicTacToeLocalGame::initializeComponents()
{
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
                pixmap = QPixmap(":/resources/tictactoe/resources/tictactoe/cross.png").scaled(REAL_CELL_SIZE, REAL_CELL_SIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            }
            else if (token == TicTacToePlayerEnum::Circle)
            {
                pixmap = QPixmap(":/resources/tictactoe/resources/tictactoe/circle.png").scaled(REAL_CELL_SIZE, REAL_CELL_SIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            }

            m_cells[r][c]->setPixmap(pixmap);
        }
    }
}

void TicTacToeLocalGame::onGridLabelClicked(QGridLabel *sender)
{
    qDebug() << "Label clicked = " + sender->getGridPosition()->toString();

    TicTacToePlayerEnum token = m_match->getBoard()->getTokenByPosition(*sender->getGridPosition());

    if (token == TicTacToePlayerEnum::None)
    {
        m_match->getBoard()->insertToken(*sender->getGridPosition(), m_match->getActualTurn());

        updateGraphics();
        m_match->switchTurn();
    }
    else
    {
        qDebug() << "Cell is busy";
    }
}

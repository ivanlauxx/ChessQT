#include "handler.h"
#include "piece.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"
#include "move.h"
#include "take.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <cstdlib>

Handler::Handler(QMainWindow *handlerWindow, QGraphicsScene *handlerScene, int handlerSize, AccountManagement* accs_)
{
    accs = accs_;
    window = handlerWindow;
    window->setWindowTitle("White 0 - 0 Black");

    scene = handlerScene;

    size = handlerSize;
    sizeSquared = size*size;
    sizeSquared2 = size*size*2;

    items = new QGraphicsPixmapItem*[sizeSquared*3]();

    state = new int[sizeSquared] {};
    int pieces[12] = {-5, -2, -9, -3, -5, -1, 1, 5, 3, 9, 2, 5};
    int eachPiece = size / 5;
    int remainder = size % 5;
    int i = 0;
    for (int j = 0; j < 12; ++j)
    {
        if (j == 6)
        {
            i = sizeSquared - size*2;
        }
        if (pieces[j] == -9 || pieces[j] == 9)
        {
            for (int k = 0; k < eachPiece+remainder; ++k)
            {
                state[i] = pieces[j];
                ++i;
            }
        }
        else if (pieces[j] == -1 || pieces[j] == 1)
        {
            for (int k = 0; k < size; ++k)
            {
                state[i] = pieces[j];
                ++i;
            }
        }
        else
        {
            for (int k = 0; k < eachPiece; ++k)
            {
                state[i] = pieces[j];
                ++i;
            }
        }
    }

    initScene();
}

Handler::~Handler()
{
    delete[] items;
    delete[] state;
}

bool Handler::selectPiece(char colour, QGraphicsPixmapItem *piece)
{
    if (colour == turn)
    {
        if (selected)
        {
            for (int i = 0; i < sizeSquared; ++i)
            {
                items[i]->hide();
                items[i+sizeSquared]->hide();
            }
        }
        else
        {
            selected = true;
        }
        selectedPiece = piece;
        return true;
    }
    else if (selected)
    {
        if (items[indexOffset(piece->offset())+sizeSquared]->isVisible())
        {
            int capturedValue = state[indexOffset(piece->offset())];
            score += capturedValue;
            if (capturedValue < 0)
            {
                scoreWhite -= capturedValue;
            }
            else
            {
                scoreBlack += capturedValue;
            }
            window->setWindowTitle("White " +
                                    QString::number(scoreWhite) +
                                    " - " +
                                    QString::number(scoreBlack) +
                                    " Black");
            moveSelected(piece->offset());
            delete piece;
        }
    }
    return false;
}

bool Handler::showMoves(int row, int col, char colour)
{
    if (state[index(row,col)] == 0)
    {
        items[index(row,col)]->show();
        return false;
    }
    else if (state[index(row,col)] < 0)
    {
        if (colour == 'w')
        {
            items[index(row,col)+sizeSquared]->show();
        }
    }
    else
    {
        if (colour == 'b')
        {
            items[index(row,col)+sizeSquared]->show();
        }
    }
    return true;
}

void Handler::moveSelected(QPointF offset)
{
    state[indexOffset(offset)] = state[indexOffset(selectedPiece->offset())];
    state[indexOffset(selectedPiece->offset())] = 0;
    selectedPiece->setOffset(offset);
    for (int i = 0; i < sizeSquared; ++i)
    {
        items[i]->hide();
        items[i+sizeSquared]->hide();
    }
    if (turn == 'w')
    {
        turn = 'b';
    }
    else
    {
        turn = 'w';
    }

    checkWin();
}

void Handler::addToScene(QGraphicsPixmapItem *item, int square, int layer)
{
    scene->addItem(item);
    items[square+layer] = item;
}

void Handler::initScene()
{
    for (int i = 0; i < size; i+=2)
    {
        for (int j = 0; j < size; j+=2)
        {
            QGraphicsPixmapItem *square = new QGraphicsPixmapItem();
            square->setPixmap(QPixmap("../../media/square.png"));
            square->setOffset(j*100, i*100);
            scene->addItem(square);
        }
        for (int j = 1; j < size && i+1 < size; j+=2)
        {
            QGraphicsPixmapItem *square = new QGraphicsPixmapItem();
            square->setPixmap(QPixmap("../../media/square.png"));
            square->setOffset(j*100, (i+1)*100);
            scene->addItem(square);
        }
    }

    for (int row = 0; row < size; ++row)
    {
        for (int col = 0; col < size; ++col)
        {
            addToScene(new Move(col, row, this), index(row,col), 0);
            addToScene(new Take(col, row), index(row,col), sizeSquared);
        }
    }

    for (int row = 0; row < size; ++row)
    {
        for (int col = 0; col < size; ++col)
        {
            if (state[index(row,col)] == 9)
            {
                addToScene(new Queen(col, row, 'w', this), index(row,col), sizeSquared2);
            }
            else if (state[index(row,col)] == -9)
            {
                addToScene(new Queen(col, row, 'b', this), index(row,col), sizeSquared2);
            }
            else if (state[index(row,col)] == 5)
            {
                addToScene(new Rook(col, row, 'w', this), index(row,col), sizeSquared2);
            }
            else if (state[index(row,col)] == -5)
            {
                addToScene(new Rook(col, row, 'b', this), index(row,col), sizeSquared2);
            }
            else if (state[index(row,col)] == 3)
            {
                addToScene(new Bishop(col, row, 'w', this), index(row,col), sizeSquared2);
            }
            else if (state[index(row,col)] == -3)
            {
                addToScene(new Bishop(col, row, 'b', this), index(row,col), sizeSquared2);
            }
            else if (state[index(row,col)] == 2)
            {
                addToScene(new Knight(col, row, 'w', this), index(row,col), sizeSquared2);
            }
            else if (state[index(row,col)] == -2)
            {
                addToScene(new Knight(col, row, 'b', this), index(row,col), sizeSquared2);
            }
            else if (state[index(row,col)] == 1)
            {
                addToScene(new Pawn(col, row, 'w', this), index(row,col), sizeSquared2);
            }
            else if (state[index(row,col)] == -1)
            {
                addToScene(new Pawn(col, row, 'b', this), index(row,col), sizeSquared2);
            }
        }
    }
}

int Handler::getScore()
{
    return score;
}

int Handler::getSize()
{
    return size;
}

int Handler::index(int row, int col)
{
    return col + size * row;
}

int Handler::indexOffset(QPointF offset)
{
    return (offset.x()/100) + size * (offset.y()/100);
}

char Handler::getTurn()
{
    return turn;
}

void Handler::checkWin()
{
    bool isWin = false;
    QString winnerName;
    // If white's score is higher than black's and is above 20, give white the win.
    if (scoreWhite > scoreBlack && scoreWhite >= 20)
    {
        accs->calculateResult(1);
        winnerName = QString::fromStdString(accs->player1.getName());
        isWin = true;
    }
    // If black's score is higher than white's and is above 20, give black the win.
    if (scoreBlack > scoreWhite && scoreBlack >= 20)
    {
        accs->calculateResult(0);
        winnerName = QString::fromStdString(accs->player2.getName());
        isWin = true;
    }

    // If a player has won, show a message box and then return to the login screen.
    if (isWin)
    {
        QMessageBox resign;
        resign.setWindowTitle("Game Over");
        resign.setText(winnerName + " has won the game!");
        resign.exec();
        qobject_cast<MainWindow*>(window->topLevelWidget())->returnToLogin();
        qobject_cast<MainWindow*>(window->topLevelWidget())->setWindowTitle("ChessQt");
    }
}

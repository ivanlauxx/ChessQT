#include "rook.h"

Rook::Rook(int rookX, int rookY, char rookColour, Handler *rookHandler)
{
    x = rookX;
    y = rookY;
    colour = rookColour;
    handler = rookHandler;
    setOffset(x*100, y*100);
    if (colour == 'w')
    {
        setPixmap(QPixmap("../../media/white_rook.png"));
        setTransformationMode(Qt::SmoothTransformation);
    }
    else
    {
        setPixmap(QPixmap("../../media/black_rook.png"));
        setTransformationMode(Qt::SmoothTransformation);
    }
}

void Rook::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (handler->selectPiece(colour, this))
    {
        int border = handler->getSize()-1;
        x = offset().x()/100;
        y = offset().y()/100;
        int row;
        int col;
        // Up
        for (row = y-1; row >= 0; --row)
        {
            if (handler->showMoves(row, x, colour))
            {
                break;
            }
        }
        // Down
        for (row = y+1; row <= border; ++row)
        {
            if (handler->showMoves(row, x, colour))
            {
                break;
            }
        }
        // Left
        for (col = x-1; col >= 0; --col)
        {
            if (handler->showMoves(y, col, colour))
            {
                break;
            }
        }
        // Right
        for (col = x+1; col <= border; ++col)
        {
            if (handler->showMoves(y, col, colour))
            {
                break;
            }
        }
    }
}

#include "queen.h"

Queen::Queen(int queenX, int queenY, char queenColour, Handler *queenHandler)
{
    x = queenX;
    y = queenY;
    colour = queenColour;
    handler = queenHandler;
    setOffset(x*100, y*100);
    if (colour == 'w')
    {
        setPixmap(QPixmap("../../media/white_queen.png"));
        setTransformationMode(Qt::SmoothTransformation);
    }
    else
    {
        setPixmap(QPixmap("../../media/black_queen.png"));
        setTransformationMode(Qt::SmoothTransformation);
    }
}

void Queen::mousePressEvent(QGraphicsSceneMouseEvent *event)
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
        // Up-left
        col = x-1;
        for (row = y-1; row >= 0 && col >= 0; --row)
        {
            if (handler->showMoves(row, col, colour))
            {
                break;
            }
            --col;
        }
        // Up-right
        col = x+1;
        for (row = y-1; row >= 0 && col <= border; --row)
        {
            if (handler->showMoves(row, col, colour))
            {
                break;
            }
            ++col;
        }
        // Down-left
        col = x-1;
        for (row = y+1; row <= border && col >= 0; ++row)
        {
            if (handler->showMoves(row, col, colour))
            {
                break;
            }
            --col;
        }
        // Down-right
        col = x+1;
        for (row = y+1; row <= border && col <= border; ++row)
        {
            if (handler->showMoves(row, col, colour))
            {
                break;
            }
            ++col;
        }
    }
}

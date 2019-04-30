#include "bishop.h"

Bishop::Bishop(int bishopX, int bishopY, char bishopColour, Handler *bishopHandler)
{
    x = bishopX;
    y = bishopY;
    colour = bishopColour;
    handler = bishopHandler;
    setOffset(x*100, y*100);
    if (colour == 'w')
    {
        setPixmap(QPixmap("../../media/white_bishop.png"));
        setTransformationMode(Qt::SmoothTransformation);
    }
    else
    {
        setPixmap(QPixmap("../../media/black_bishop.png"));
        setTransformationMode(Qt::SmoothTransformation);
    }
}

void Bishop::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (handler->selectPiece(colour, this))
    {
        int border = handler->getSize()-1;
        x = offset().x()/100;
        y = offset().y()/100;
        int row;
        int col;
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

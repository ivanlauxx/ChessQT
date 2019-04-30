#include "knight.h"

Knight::Knight(int knightX, int knightY, char knightColour, Handler *knightHandler)
{
    x = knightX;
    y = knightY;
    colour = knightColour;
    handler = knightHandler;
    setOffset(x*100, y*100);
    if (colour == 'w')
    {
        setPixmap(QPixmap("../../media/white_knight.png"));
        setTransformationMode(Qt::SmoothTransformation);
    }
    else
    {
        setPixmap(QPixmap("../../media/black_knight.png"));
        setTransformationMode(Qt::SmoothTransformation);
    }
}

void Knight::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (handler->selectPiece(colour, this))
    {
        int border = handler->getSize();
        x = offset().x()/100;
        y = offset().y()/100;
        // Clockwise
        if (y >= 2 && x <= border-2)
        {
            handler->showMoves(y-2, x+1, colour);
        }
        if (y >= 1 && x <= border-3)
        {
            handler->showMoves(y-1, x+2, colour);
        }
        if (y <= border-2 && x <= border-3)
        {
            handler->showMoves(y+1, x+2, colour);
        }
        if (y <= border-3 && x <= border-2)
        {
            handler->showMoves(y+2, x+1, colour);
        }
        if (y <= border-3 && x >= 1)
        {
            handler->showMoves(y+2, x-1, colour);
        }
        if (y <= border-2 && x >= 2)
        {
            handler->showMoves(y+1, x-2, colour);
        }
        if (y >= 1 && x >= 2)
        {
            handler->showMoves(y-1, x-2, colour);
        }
        if (y >= 2 && x >= 1)
        {
            handler->showMoves(y-2, x-1, colour);
        }
    }
}

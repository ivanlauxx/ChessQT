#include "pawn.h"

Pawn::Pawn(int pawnX, int pawnY, char pawnColour, Handler *pawnHandler)
{
    x = pawnX;
    y = pawnY;
    colour = pawnColour;
    handler = pawnHandler;
    setOffset(x*100, y*100);
    if (colour == 'w')
    {
        setPixmap(QPixmap("../../media/white_pawn.png"));
        setTransformationMode(Qt::SmoothTransformation);
    }
    else
    {
        setPixmap(QPixmap("../../media/black_pawn.png"));
        setTransformationMode(Qt::SmoothTransformation);
    }
}

void Pawn::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (handler->selectPiece(colour, this))
    {
        int border = handler->getSize()-2;
        x = offset().x()/100;
        y = offset().y()/100;
        if (colour == 'w')
        {
            // Up
            if (y >= 1)
            {
                handler->showMoves(y-1, x, colour);
            }
            // Up-left
            if (x >= 1 && y >= 1)
            {
                handler->showMoves(y-1, x-1, colour);
            }
            // Up-right
            if (x <= border && y >= 1)
            {
                handler->showMoves(y-1, x+1, colour);
            }
        }
        else
        {
            // Down
            if (y <= border)
            {
                handler->showMoves(y+1, x, colour);
            }
            // Down-left
            if (x >= 1 && y <= border)
            {
                handler->showMoves(y+1, x-1, colour);
            }
            // Down-right
            if (x <= border && y <= border)
            {
                handler->showMoves(y+1, x+1, colour);
            }
        }
    }
}

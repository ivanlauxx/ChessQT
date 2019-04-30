#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece
{
public:
    Knight(int knightX, int knightY, char knightColour, Handler *knightHandler);
private:
    int x;
    int y;
    char colour;
    Handler *handler;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // KNIGHT_H

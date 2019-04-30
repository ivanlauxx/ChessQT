#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece
{
public:
    Bishop(int bishopX, int bishopY, char bishopColour, Handler *bishopHandler);
private:
    int x;
    int y;
    char colour;
    Handler *handler;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // BISHOP_H

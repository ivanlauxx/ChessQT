#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece
{
public:
    Pawn(int pawnX, int pawnY, char pawnColour, Handler *pawnHandler);
private:
    int x;
    int y;
    char colour;
    Handler *handler;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PAWN_H

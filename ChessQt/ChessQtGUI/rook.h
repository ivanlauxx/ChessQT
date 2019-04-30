#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece
{
public:
    Rook(int rookX, int rookY, char rookColour, Handler *rookHandler);
private:
    int x;
    int y;
    char colour;
    Handler *handler;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // ROOK_H

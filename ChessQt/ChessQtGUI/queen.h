#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece
{
public:
    Queen(int queenX, int queenY, char queenColour, Handler *queenHandler);
private:
    int x;
    int y;
    char colour;
    Handler *handler;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QUEEN_H

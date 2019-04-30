#ifndef PIECE_H
#define PIECE_H

#include "handler.h"

class Piece : public QGraphicsPixmapItem
{
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) = 0;
};

#endif // PIECE_H

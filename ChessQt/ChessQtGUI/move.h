#ifndef MOVE_H
#define MOVE_H

#include "handler.h"

class Move : public QGraphicsPixmapItem
{
public:
    Move(int moveX, int moveY, Handler *moveHandler);
private:
    Handler *handler;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MOVE_H

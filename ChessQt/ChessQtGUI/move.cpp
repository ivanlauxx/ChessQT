#include "move.h"

Move::Move(int moveX, int moveY, Handler *moveHandler)
{
    handler = moveHandler;
    setOffset(moveX*100, moveY*100);
    setPixmap(QPixmap("../../media/move.png"));
    setTransformationMode(Qt::SmoothTransformation);
    this->hide();
}

void Move::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    handler->moveSelected(this->offset());
}

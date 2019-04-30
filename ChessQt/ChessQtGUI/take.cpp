#include "take.h"

Take::Take(int takeX, int takeY)
{
    setOffset(takeX*100, takeY*100);
    setPixmap(QPixmap("../../media/take.png"));
    setTransformationMode(Qt::SmoothTransformation);
    this->hide();
}

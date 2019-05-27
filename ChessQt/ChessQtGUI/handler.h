#ifndef HANDLER_H
#define HANDLER_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "accountmanagement.h"

class Handler
{
public:
    Handler(QMainWindow *handlerWindow, QGraphicsScene *handlerScene, int handlerSize, AccountManagement *accs_, QStatusBar *gameBar, QMenuBar *menuBar_);
    ~Handler();
    bool selectPiece(char colour, QGraphicsPixmapItem *piece);
    bool showMoves(int row, int col, char colour);
    void moveSelected(QPointF offset);
    int getScore();
    int getSize();
    char getTurn();
private:
    QMainWindow *window;
    QGraphicsScene *scene;
    int size;
    int sizeSquared;
    int sizeSquared2;
    AccountManagement *accs;
    QStatusBar *gameBar;
    QMenuBar *menuBar;
    int *state;
    QGraphicsPixmapItem **items;
    char turn = 'w';
    bool selected = false;
    QGraphicsPixmapItem *selectedPiece;
    int score = 0;
    int scoreWhite = 0;
    int scoreBlack = 0;
    void initScene();
    void addToScene(QGraphicsPixmapItem *item, int square, int layer);
    int index(int row, int col);
    int indexOffset(QPointF offset);
    void checkWin();
};

#endif // HANDLER_H

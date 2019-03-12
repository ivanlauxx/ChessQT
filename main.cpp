#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

class Handler;

class Dot :public QGraphicsPixmapItem {
    private:
        QGraphicsScene * m_scene;
        Handler * m_handler;
    public:
        Dot(QGraphicsScene * scene, Handler * handler, int x, int y) {
            m_scene = scene;
            m_handler = handler;
            setPixmap(QPixmap("../media/move.png"));
            setOffset(x, y);
            m_scene->addItem(this);
        }
        void mousePressEvent(QGraphicsSceneMouseEvent * event);
};

class Handler {
    private:
        static int board[25];
        QGraphicsScene * m_scene;
        QGraphicsPixmapItem * m_piece;
        bool moving = false;
        int moving_value;
        QGraphicsPixmapItem * dots[25];
    public:
        Handler(QGraphicsScene * scene) {
            m_scene = scene;
        }
        int * getState() {
            return board;
        }
        void setState(QPointF point) {
            int index = point.x()/100 + point.y()/100*5;
            int old_index = m_piece->offset().x()/100 + m_piece->offset().y()/100*5;
            board[index] = moving_value;
            board[old_index] = 0;
        }
        void setMoving(QGraphicsPixmapItem * piece, int value, int moves[25]) {
            m_piece = piece;
            moving = true;
            moving_value = value;
            for(int i = 0; i < 25; i++) {
                if(moves[i] == 1)
                    dots[i]->show();
                else if(moves[i] == 2) {
                    dots[i]->setPixmap(QPixmap("../media/take.png"));
                    dots[i]->show();
                }
            }
        }
        void movePiece(QGraphicsPixmapItem * dot) {
            if(moving) {
                for(int i = 0; i < 25; i++) {
                    dots[i]->setPixmap(QPixmap("../media/move.png"));
                    dots[i]->hide();
                }
                setState(dot->offset());
                m_piece->setOffset(dot->offset());
                moving = false;
            }
        }
        void initDots() {
            for(int i = 0; i < 25; i++) {
                dots[i] = new Dot(m_scene, this, i * 100 % 500, i / 5 * 100);
                dots[i]->hide();
            }
        }
};
int Handler::board[25] = {
     0,  0,  9,  0,  0,
     0,  0,  9,  0,  0,
     0,  0,  0,  0,  0,
     0,  0, -9,  0,  0,
     0,  0, -9,  0,  0
};

void Dot::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    m_handler->movePiece(this);
}

class Queen :public QGraphicsPixmapItem {
    private:
        QGraphicsScene * m_scene;
        Handler * m_handler;
        int value;
        bool opposite;
    public:
        Queen(QGraphicsScene * scene, Handler * handler, int side, int x, int y) {
            m_scene = scene;
            m_handler = handler;
            if(side == 1) {
                setPixmap(QPixmap("../media/white_queen.png"));
                value = 9;
                opposite = false;
            }
            else {
                setPixmap(QPixmap("../media/black_queen.png"));
                value = -9;
                opposite = true;
            }
            setOffset(x, y);
            m_scene->addItem(this);
        }
        bool isOpposite(int piece) {
            if(piece > 0)
                return opposite;
            else
                return !opposite;
        }
        void mousePressEvent(QGraphicsSceneMouseEvent * event) {
            int * board = m_handler->getState();
            int moves[25] = {0};
            int index = offset().x()/100 + offset().y()/100*5;
            for(int i = index+1; i % 5 != 0; i++) { // Right
                if(board[i] == 0)
                    moves[i] = 1;
                else if(isOpposite(board[i])) {
                    moves[i] = 2;
                    break;
                }
                else
                    break;
            }
            for(int i = index-1; (i+1) % 5 != 0; i--) { // Left
                if(board[i] == 0)
                    moves[i] = 1;
                else if(isOpposite(board[i])) {
                    moves[i] = 2;
                    break;
                }
                else
                    break;
            }
            for(int i = index+5; i <= 24; i+=5) { // Down
                if(board[i] == 0)
                    moves[i] = 1;
                else if(isOpposite(board[i])) {
                    moves[i] = 2;
                    break;
                }
                else
                    break;
            }
            for(int i = index-5; i >= 0; i-=5) { // Up
                if(board[i] == 0)
                    moves[i] = 1;
                else if(isOpposite(board[i])) {
                    moves[i] = 2;
                    break;
                }
                else
                    break;
            }
            for(int i = index+6; i % 5 != 0 && i <= 24; i+=6) { // Right + Down
                if(board[i] == 0)
                    moves[i] = 1;
                else if(isOpposite(board[i])) {
                    moves[i] = 2;
                    break;
                }
                else
                    break;
            }
            for(int i = index-4; i % 5 != 0 && i >= 0; i-=4) { // Right + Up
                if(board[i] == 0)
                    moves[i] = 1;
                else if(isOpposite(board[i])) {
                    moves[i] = 2;
                    break;
                }
                else
                    break;
            }
            for(int i = index+4; (i+1) % 5 != 0 && i <= 24; i+=4) { // Left + Down
                if(board[i] == 0)
                    moves[i] = 1;
                else if(isOpposite(board[i])) {
                    moves[i] = 2;
                    break;
                }
                else
                    break;
            }
            for(int i = index-6; (i+1) % 5 != 0 && i >= 0; i-=6) { // Left + Up
                if(board[i] == 0)
                    moves[i] = 1;
                else if(isOpposite(board[i])) {
                    moves[i] = 2;
                    break;
                }
                else
                    break;
            }
            m_handler->setMoving(this, value, moves);
        }
};

class Init {
    private:
        QGraphicsScene * m_scene;
        Handler * m_handler;
    public:
        Init(QGraphicsScene * scene, Handler * handler) {
            m_scene = scene;
            m_handler = handler;
            int * board = m_handler->getState();
            QGraphicsPixmapItem * background = new QGraphicsPixmapItem;
            background->setPixmap(QPixmap("../media/background.png"));
            m_scene->addItem(background);
            QGraphicsPixmapItem * pieces[4];
            m_handler->initDots();
            int j = 0;
            for(int i = 0; i < 25; i++) {
                if(board[i] == 9) {
                    pieces[j] = new Queen(m_scene, m_handler, 1, i * 100 % 500, i / 5 * 100);
                    j++;
                }
                else if(board[i] == -9) {
                    pieces[j] = new Queen(m_scene, m_handler, 0, i * 100 % 500, i / 5 * 100);
                    j++;
                }
            }
        }
};

int main(int argc, char * argv[]) {

    QApplication application(argc, argv);
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    Handler handler(&scene);
    Init init(&scene, &handler);
    view.show();

    return application.exec();

}

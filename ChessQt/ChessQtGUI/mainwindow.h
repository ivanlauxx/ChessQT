#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMessageBox>
#include "accountmanagement.h"
#include "handler.h"
#include "registrationdialog.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class Tests;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void displayPlayer2(Player p);
    void displayPlayer1(Player p);
    void returnToLogin();

private slots:
    void on_gamePageButton_clicked();
    void on_registrationButton_clicked();
    void on_p1loginButton_clicked();
    void on_p2loginButton_clicked();
    void on_backButton_clicked();
    void on_boardButton_clicked();
    void on_playGameButton_clicked();
    void on_spinBox_valueChanged(int arg1);
    void on_actionResign_triggered();
    void on_backButton_2_clicked();
    void on_swapButton_clicked();
    void enablePlay();

private:
    Ui::MainWindow *ui = nullptr;
    AccountManagement *accs = nullptr;
    QGraphicsScene *scene = nullptr;
    Handler *handler = nullptr;
    int size = 5;
};

#endif // MAINWINDOW_H

#ifndef TESTS_H
#define TESTS_H

#include <QtTest>
#include <QPushButton>
#include <QLineEdit>
#include <QDialogButtonBox>
#include "mainwindow.h"
#include "accountmanagement.h"

class Tests : public QObject
{
    Q_OBJECT

private slots:
    void testConstructor();
    void testRegister();
    void testPlayGame();

private:
    MainWindow testWindow;
    AccountManagement testAcc;
};

#endif // TESTS_H

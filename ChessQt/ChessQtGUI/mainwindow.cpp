#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registrationdialog.h"
#include "accountmanagement.h"
#include "player.h"
#include "logindialog.h"
#include "handler.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    accs = new AccountManagement;
    ui->menuBar->hide();
    ui->gameBar->showMessage("Welcome to ChessQT!");
    ui->playGameButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete accs;
    delete ui;
}

void MainWindow::on_gamePageButton_clicked()
{
    // Moves the stacked widget from main screen to login screen.
    ui->stackedWidget->setCurrentIndex(1);
    accs->playersList = accs->loadList();
}

void MainWindow::on_registrationButton_clicked()
{
    // Opens a new registration dialog box.
    RegistrationDialog regi;
    regi.setModal(true);
    QMessageBox msgBox;
    msgBox.setWindowTitle("Registration");
    if(regi.exec() == RegistrationDialog::Accepted)
    {
        // Gets fields from the registration dialog.
        std::string username = regi.getUsername().toStdString();
        std::string password = regi.getPassword().toStdString();
        if(accs->registration(username, password))
        {
            msgBox.setText("Registration Successful");
            msgBox.exec();
        }
        else
        {
            msgBox.setText("Registration Failed (Duplicate Username)");
            msgBox.exec();
        }
    }
}

void MainWindow::on_p1loginButton_clicked()
{
    // Opens a login dialog.
    accs->player1 = Player();
    LoginDialog login1;
    login1.setModal(true);
    if(login1.exec() == LoginDialog::Accepted)
    {
        // Gets fields from login dialog.
        std::string username = login1.getUsername().toStdString();
        std::string password = login1.getPassword().toStdString();
        // If the account management is able to log the player in...
        if (accs->login(accs->player1, username, password))
        {
            // Display the player's name in the Player 1 section of the menu.
            ui->label_p1name->setStyleSheet("QLabel { color: black; }");
            displayPlayer1(accs->player1);
        }
        else
        {
            // Display login failed in red text in the Player 1 section of the menu.
            ui->label_p1name->setStyleSheet("QLabel { color: red; }");
            ui->label_p1name->setText("Login Failed");
        }
    }

    // If both players are logged in, the "Play Game" button becomes available for clicking.
    if (accs->checkIfPlayers() == true) {
        enablePlay();
    }
}

// Same as on_p1loginButton_clicked(), but for Player 2.
void MainWindow::on_p2loginButton_clicked()
{
    accs->player2 = Player();
    LoginDialog login1;
    login1.setModal(true);
    if(login1.exec() == LoginDialog::Accepted)
    {
        std::string p1u = login1.getUsername().toStdString();
        std::string p1p = login1.getPassword().toStdString();
        if (accs->login(accs->player2, p1u, p1p))
        {
            ui->label_p2name->setStyleSheet("QLabel { color: black; }");
            displayPlayer2(accs->player2);
        }
        else
        {
            ui->label_p2name->setStyleSheet("QLabel { color: red; }");
            ui->label_p2name->setText("Login Failed");
        }
    }

    if (accs->checkIfPlayers() == true) {
        enablePlay();
    }
}

void MainWindow::displayPlayer2(Player p)
{
    QString name = QString::fromStdString(p.getName());
    ui->label_p2name->setText(name);
}

void MainWindow::displayPlayer1(Player p)
{
    QString name = QString::fromStdString(p.getName());
    ui->label_p1name->setText(name);
}

void MainWindow::on_backButton_clicked()
{
    // Moves the stacked widget "up" a page.
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_boardButton_clicked()
{
    ui->textBrowser->clear();
    ui->textBrowser->selectAll();
    ui->textBrowser->setAlignment(Qt::AlignCenter);

    for(Player p : accs->playersList)
    {
        QString line = QString::fromStdString(p.getName()+"\t");
        line.append(QString::number(p.getGamePlayed())+"\t");
        line.append(QString::number(p.getGameWin())+"\t");
        line.append(QString::number(p.getGameLose())+"\t");
        ui->textBrowser->append(line);
    }
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_playGameButton_clicked()
{
    ui->menuBar->show();
    scene = new QGraphicsScene(this);
    handler = new Handler(this, scene, size, accs, ui->gameBar);
    ui->graphicsView->resetMatrix();
    if (size > 5)
    {
        double pixels = size*100;
        double scale = 500/pixels;
        ui->graphicsView->scale(scale, scale);
    }
    ui->graphicsView->setScene(scene);
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    size = arg1;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape && ui->stackedWidget->currentIndex() == 3)
    {
        ui->stackedWidget->setCurrentIndex(1);
        setWindowTitle("ChessQt");
        if (handler->getScore() < 0)
        {
            accs->calculateResult(1);
        }
        else if (handler->getScore() > 0)
        {
            accs->calculateResult(2);
        }
        delete handler;
        handler = nullptr;
        delete scene;
        scene = nullptr;
    }
}

void MainWindow::on_actionResign_triggered()
{
    // Get whose turn it is from the game engine.
    char turn = handler->getTurn();
    QMessageBox resign;

    // If white's turn...
    if (turn == 'w') {
        resign.setText("White has resigned.");
        // Give the win to Black.
        accs->calculateResult(0);
    } else {
        // If black's turn...
        if (turn == 'b') {
            resign.setText("Black has resigned.");
            // Give the win to white.
            accs->calculateResult(1);
        }
    }

    resign.setWindowTitle("Resignation");
    resign.exec();
    // Returns to the login screen.
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 2);
}

void MainWindow::on_backButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
}

void MainWindow::enablePlay() {
    ui->playGameButton->setEnabled(true);
}

void MainWindow::on_swapButton_clicked()
{
    // If the Player 1 and Player 2 are both logged in, swap them.
    if (accs->checkIfPlayers()) {
        accs->swapColours();
        displayPlayer1(accs->player1);
        displayPlayer2(accs->player2);
    }
}

void MainWindow::returnToLogin()
{
    // Moves the stacked widget from the game screen to the main menu.
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 2);
    // Freeing memory previously held by handler and graphics scene.
}

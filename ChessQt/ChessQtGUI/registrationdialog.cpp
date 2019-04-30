#include "registrationdialog.h"
#include "ui_registrationdialog.h"

RegistrationDialog::RegistrationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrationDialog)
{
    ui->setupUi(this);
}

RegistrationDialog::~RegistrationDialog()
{
    delete ui;
}

QString RegistrationDialog::getUsername()
{
    return ui->lineEdit_username->text();
}

QString RegistrationDialog::getPassword()
{
    return ui->lineEdit_password->text();
}

#ifndef REGISTRATIONDIALOG_H
#define REGISTRATIONDIALOG_H

#include <QDialog>

namespace Ui {
    class RegistrationDialog;
}

class RegistrationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationDialog(QWidget *parent = nullptr);
    ~RegistrationDialog();
    QString getUsername();
    QString getPassword();

private:
    Ui::RegistrationDialog *ui;
};

#endif // REGISTRATIONDIALOG_H

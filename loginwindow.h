#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include "dbmanager.h"
namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    void setDBPointer(DBManager& dbAddress);
    ~LoginWindow();

private slots:
    void on_loginButton_clicked();

private:
    Ui::LoginWindow *ui;
    DBManager* dbPointer;
};

#endif // LOGINWINDOW_H

#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "admincp.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::setDBPointer(DBManager& dbAddress)
{
    this->dbPointer = &dbAddress;
}

void LoginWindow::on_loginButton_clicked()
{
    QString username = ui->userTextField->text();
    QString password = ui->passTextField->text();

    if (this->dbPointer->authenticateUser(username, password))
    {
        MainWindow* mw = new MainWindow;
        qDebug() << "Authentication successful.";

        // Gives the main window access to the Database, and makes it visible.
        mw->setDBPointer(this->dbPointer);
        mw->show();

        // Hides current window (login)
        this->hide();
    }
    else
    {
        qDebug() << "Authentication failed.";
    }
}

void LoginWindow::on_cancelButton_clicked()
{
    this->close();

}

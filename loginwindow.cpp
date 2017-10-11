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
    bool isAdmin = false;
    QString username = ui->userTextField->text();
    QString password = ui->passTextField->text();

    // bool isAdmin will be returned by reference only if the user's role is set to '1'.
    // user role of '0' represents a store manager
    if (this->dbPointer->authenticateUser(username, password, isAdmin))
    {
        MainWindow* mw = new MainWindow;
        qDebug() << "Authentication successful.";

        // Gives the main window access to the Database, and makes it visible.
        mw->setDBPointer(this->dbPointer);

        mw->show();

        // Let's the main window know the user's role (store manager or administrator)
        mw->setIsAdmin(isAdmin);

        // Hides current window (login)
        this->hide();
    }
    else
    {
        qDebug() << "Authentication failed.";
    }
}

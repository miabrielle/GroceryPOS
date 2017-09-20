#include "admincp.h"
#include "dbmanager.h"
#include <QApplication>
#include "loginwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow lw;
    DBManager dbManager;
    dbManager.initDB();

    lw.setDBPointer(dbManager);
    lw.show();
    return a.exec();
}

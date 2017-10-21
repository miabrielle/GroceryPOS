#include "addcustomerdialog.h"
#include "ui_addcustomerdialog.h"
#include "customer.h"
#include <QMessageBox>

//constructor
AddCustomerDialog::AddCustomerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCustomerDialog)
{
    ui->setupUi(this);
}

//destructor
AddCustomerDialog::~AddCustomerDialog()
{
    delete ui;
}

//Allows access to the customers table on the main window
void AddCustomerDialog::setCustomersTablePointer(QTableWidget * customersTable)
{
    this->customersTablePointer = customersTable;
}

//Allows access to the database pointer in order to add the new
//customer to the database
void AddCustomerDialog::setDBPointer(DBManager * dbPointer)
{
    this->dbPointer = dbPointer;
}

//When add button is pressed, the program reads in the info from the pop up window and
//adds them to the customers table on the main window of the UI and adds the item to
//the database
void AddCustomerDialog::on_addButton_clicked()
{
    //Instantiates data members for name, id, membership type, and expiration date from UI input boxes
    int customerID = ui->IDText->text().toInt();
    QString customerName = ui->nameText->text();
    QString membershipType = ui->membershipTypeEdit->currentText();
    QString expMonth = ui->ExpMonthEdit->currentText();
    QString expDay = ui->ExpDayEdit->currentText();
    QString expYear = ui->ExpYearEdit->currentText();
    QString expDate = expMonth + '/' + expDay + '/' + expYear;

    if (ui->IDText->text().isEmpty() || ui->nameText->text().isEmpty())
    {
        QMessageBox errorMsgBox;
        errorMsgBox.critical(0,"Error", "You must enter a valid customer ID and name!");
        errorMsgBox.setFixedSize(500,200);
    }
    else
    {
        //Adds all new data to an object of type customer to send to database
        Customer newCustomer(customerID, customerName, membershipType);
        newCustomer.setExpDate(expDate);

        //Adds customer to DB using member function of dbmanager class
        dbPointer->addCustomer(newCustomer);

        //Adds a row to the customers table on the UI
        int addRow = customersTablePointer->rowCount() + 1;
        this->customersTablePointer->setRowCount(addRow);

        //Sets customer ID in table
        QTableWidgetItem *idCell = customersTablePointer->item(addRow - 1, 0);
        if(!idCell)
        {
            idCell = new QTableWidgetItem;
        }
        idCell->setData(0, QVariant(customerID));
        customersTablePointer->setItem(addRow - 1, 0, idCell);

        //Sets customer name in table
        QTableWidgetItem *nameCell = customersTablePointer->item(addRow - 1, 1);
        if(!nameCell)
        {
            nameCell = new QTableWidgetItem;
        }
        nameCell->setData(0, QVariant(customerName));
        customersTablePointer->setItem(addRow - 1, 1, nameCell);

        //Sets customer membership type in the table
        QTableWidgetItem *memberCell = customersTablePointer->item(addRow - 1, 2);
        if(!memberCell)
        {
            memberCell = new QTableWidgetItem;
        }
        memberCell->setData(0, QVariant(membershipType));
        customersTablePointer->setItem(addRow - 1, 2, memberCell);

        //Sets expiration date for customer in table
        QTableWidgetItem *expDateCell = customersTablePointer->item(addRow - 1, 3);
        if(!expDateCell)
        {
            expDateCell = new QTableWidgetItem;
        }
        expDateCell->setData(0, QVariant(expDate));
        customersTablePointer->setItem(addRow - 1, 3, expDateCell);

        //closes pop up window
        this->close();
    }
}

//cancel button allows user to close pop up window
void AddCustomerDialog::on_cancelButton_clicked()
{
    this->close();
}

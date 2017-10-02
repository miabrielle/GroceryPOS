#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <QMainWindow>

class Transaction
{
private:
    QString purchaseDate;
    QString itemName;
    int customerID;
    int quantityPurchased;
    float salePrice;

public:

    Transaction();
    Transaction(int customerID, QString itemName, int quantityPurchased, QString purchaseDate);

    // ================== ACCESSOR FUNCTIONS =============================/
    // Get Functions
    QString getPurchaseDate();
    QString getItemName();
    int getCustomerID();
    int getQuantityPurchased();
    float getSalesPrice();
    float getTransactionTotal();

    // Set functions
    void setPurchaseDate(QString purchaseDate);
    void setItemName(QString itemName);
    void setCustomerID(int customerID);
    void setQuantityPurchased(int quantityPurchased);

};
#endif // TRANSACTION_H

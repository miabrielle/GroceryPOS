#include "transaction.h"


Transaction::Transaction()
{
}

Transaction::Transaction(int customerID, QString itemName, int quantityPurchased, QString purchaseDate)
{
    this->customerID = customerID;
    this->itemName = itemName;
    this->quantityPurchased = quantityPurchased;
    this->purchaseDate = purchaseDate;
}


// ================== ACCESSOR FUNCTIONS =============================/
// Transaction::get Functions
QString Transaction::getPurchaseDate()
{
    return this->purchaseDate;
}

QString Transaction::getItemName()
{
    return this->itemName;
}

int Transaction::getCustomerID()
{
    return this->customerID;
}

int Transaction::getQuantityPurchased()
{
    return this->quantityPurchased;
}


// Transaction::set functions
void Transaction::setPurchaseDate(QString purchaseDate)
{
    this->purchaseDate = purchaseDate;
}

void Transaction::setItemName(QString itemName)
{
    this->itemName = itemName;
}

void Transaction::setCustomerID(int customerID)
{
    this->customerID = customerID;
}

void Transaction::setQuantityPurchased(int quantityPurchased)
{
    this->quantityPurchased = quantityPurchased;
}


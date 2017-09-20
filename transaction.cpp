#include "transaction.h"
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

    float Transaction::getSalesPrice()
    {
        return this->salesPrice;
    }

    float Transaction::getTransactionTotal()
    {
        return this->transactionTotal;
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

    void Transaction::setSalesPrice(float salesPrice)
    {
        this->salesPrice = salesPrice;
    }

    void Transaction::setTransactionTotal(float transactionTotal)
    {
        this->transactionTotal = transactionTotal;
    }

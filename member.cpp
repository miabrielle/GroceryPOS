#include "customer.h"

    // Customer::get Functions
    QString Customer::getCustomerName()
    {
        return this->customerName;
    }
    QString Customer::getExpDate()
    {
        return this->expDate;
    }

    int Customer::getCustomerID()
    {
        return this->CustomerID;
    }

    float Customer::getRebateAmt()
    {
        return this->rebateAmt;
    }
    bool Customer::IsExecutive()
    {
        return this->isExecutive;
    }

    // Set functions
    void Customer::setCustomerName(QString customerName)
    {
        this->customerName = customerName;
    }
    void Customer::setIsExecutive(bool isExec)
    {
        this->isExecutive = isExec;
    }

    void Customer::setExpDate(QString expDate)
    {
        this->expDate = expDate;
    }
    void Customer::setCustomerID(int CustomerID)
    {
        this->CustomerID = CustomerID;
    }

    void Customer::setRebateAmt(float rebateAmt)
    {
        this->rebateAmt = rebateAmt;
    }


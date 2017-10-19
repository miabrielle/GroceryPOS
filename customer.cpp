#include "customer.h"


Customer::Customer() {}

Customer::Customer(int customerID, QString customerName, QString memberType)
{
this->customerID = customerID;
this->customerName = customerName;
this->memberType = memberType;
}

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
    return this->customerID;
}

float Customer::getRebateAmt()
{
    return this->rebateAmt;
}

QString Customer::getMemberType()
{
    return this->memberType;
}

bool Customer::getChangeStatus()
{
    return this->changeStatus;
}

// Set functions
void Customer::setCustomerName(QString customerName)
{
    this->customerName = customerName;
}

void Customer::setExpDate(QString expDate)
{
    this->expDate = expDate;
}
void Customer::setCustomerID(int customerID)
{
    this->customerID = customerID;
}

void Customer::setRebateAmt(float rebateAmt)
{
    this->rebateAmt = rebateAmt;
}

void Customer::setMemberType(QString memberType)
{
    this->memberType = memberType;
}

void Customer::setChangeStatus(bool changeStatus)
{
    this->changeStatus = changeStatus;
}

Customer::~Customer() {}


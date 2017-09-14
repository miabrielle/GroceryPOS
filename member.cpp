#include "Member.h"

    // Member::get Functions
    QString Member::getMemberName()
    {
        return this->memberName;
    }
    QString Member::getExpDate()
    {
        return this->expDate;
    }

    int Member::getMemberID()
    {
        return this->memberID;
    }

    float Member::getRebateAmt()
    {
        return this->rebateAmt;
    }
    bool Member::IsExecutive()
    {
        return this->isExecutive;
    }

    // Set functions
    void Member::setMemberName(QString memberName)
    {
        this->memberName = memberName;
    }
    void Member::setIsExecutive(bool isExec)
    {
        this->isExecutive = isExec;
    }

    void Member::setExpDate(QString expDate)
    {
        this->expDate = expDate;
    }
    void Member::setMemberID(int memberID)
    {
        this->memberID = memberID;
    }

    void Member::setRebateAmt(float rebateAmt)
    {
        this->rebateAmt = rebateAmt;
    }


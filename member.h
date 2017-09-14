#ifndef MEMBER_H
#define MEMBER_H

class Member
{
private:
    QString name;
    int memberID;
    bool isExecutive;
    Qstring expDate;
    float rebateAmt;

public:
 // ================== ACCESSOR FUNCTIONS =============================/
    // Get Functions
    QString getMemberName();
    QString getExpDate();
    int getMemberID();
    float getRebateAmt();

    // Set functions
    void setMemberName(QString name);
    void setExpDate(QString expDate);
    void setMemberID(int memberID);
    void setRebateAmt(float rebateAmt);

    bool IsExecutive(bool isExecutive);
};

#endif // MEMBER_H

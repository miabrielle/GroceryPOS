#ifndef MEMBER_H
#define MEMBER_H
#include <QMainWindow>
class Member
{
private:
    QString memberName;\
    QString expDate;
    int memberID;
    bool isExecutive;
    float rebateAmt;

public:
 // ================== ACCESSOR FUNCTIONS =============================/
    // Get Functions
    Member();
    QString getMemberName();
    QString getExpDate();
    int getMemberID();
    float getRebateAmt();
    bool IsExecutive();

    // Set functions
    void setMemberName(QString memberName);
    void setExpDate(QString expDate);
    void setMemberID(int memberID);
    void setRebateAmt(float rebateAmt);
    void setIsExecutive(bool isExec);

    ~Member();
};

#endif // MEMBER_H

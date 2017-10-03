#ifndef ITEM_H
#define ITEM_H


#include <QMainWindow>

class Item
{
private:
    QString itemName;
    float itemPrice;
    int quantitySold;
    float totalRevenue;

public:
    QString getItemName();
    float getItemPrice();
    int getQuantitySold();
    float getTotalRevenue();

    void setItemName(QString itemName);
    void setItemPrice(float itemPrice);
    void setQuantitySold(int quantitySold);
    void setTotalRevenue(float totalRevenue);
};

#endif // ITEM_H

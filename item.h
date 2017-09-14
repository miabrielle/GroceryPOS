#ifndef ITEM_H
#define ITEM_H

// mia changed something
class Item
{
private:
    QString itemName;
    float itemPrice;
public:
    QString getItemName();
    float getItemPrice();

    void setItemName(QString itemName);
    void setItemPrice(float itemPrice);
};

#endif // ITEM_H

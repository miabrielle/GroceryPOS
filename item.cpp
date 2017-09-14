#include "item.h"

QString Item::getItemName()
{
    return this->itemName;
}

float Item::getItemPrice()
{
    return this->itemPrice;
}

void Item::setItemName(QString itemName)
{
    this->itemName = itemName;
}

void Item::setItemPrice(float itemPrice)
{
    this->itemPrice = itemPrice;
}

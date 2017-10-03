#include "item.h"

QString Item::getItemName()
{
    return this->itemName;
}

float Item::getItemPrice()
{
    return this->itemPrice;
}
int Item::getQuantitySold()
{
    return this->quantitySold;
}
float Item::getTotalRevenue()
{
    return totalRevenue;
}

void Item::setItemName(QString itemName)
{
    this->itemName = itemName;
}

void Item::setItemPrice(float itemPrice)
{
    this->itemPrice = itemPrice;
}
void Item::setQuantitySold(int quantitySold)
{
    this->quantitySold = quantitySold;
}
void Item::setTotalRevenue(float totalRevenue)
{
    this->totalRevenue = totalRevenue;
}

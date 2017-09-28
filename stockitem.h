// File:        stockitem.h
// Author:      Geoffrey Tien
// Date:        2015-07-08
// Description: Declaration of a StockItem class for use with CMPT 225 assignment #4
#pragma once

#define DESC_MAX_LENGTH 30

#include <string>

using namespace std;

class StockItem
{
  private:
    unsigned int sku;   // unique identifier for stock keeping unit, range [10000, 99999] (5 digits)
    string description; // product name, maximum length of 
    double price;       // retail price of product
    unsigned int stock; // number of units in stock

  public:
    // Default constructor
    StockItem();

    // Parameterized constructor
    // Need to specify SKU, description, and price.
    // Stock is defaulted to 0;
    StockItem(unsigned int skuid, string desc, double p);

    // Accessors
    unsigned int GetSKU() const;
    string GetDescription() const;
    double GetPrice() const;
    unsigned int GetStock() const;

    // Mutators
    // boolean return values - return true for successful update, false if argument is invalid (i.e. negative price/stock/SKU)
    // parameters are signed - will convert to unsigned if parameter is valid
    // sku cannot be modified
    bool SetDescription(string newdesc);
    bool SetPrice(double newprice);
    bool SetStock(int amount);

    // overloaded operators
    // return (in)equality on sku field only
    bool operator==(const StockItem& item) const;
    bool operator!=(const StockItem& item) const;
    bool operator>(const StockItem& item) const;
    bool operator<(const StockItem& item) const;
    bool operator>=(const StockItem& item) const;
    bool operator<=(const StockItem& item) const;

    StockItem& operator=(const StockItem& item);
};
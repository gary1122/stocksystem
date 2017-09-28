// File:        stocksystem.h
// Author:      Geoffrey Tien
// Date:        2015-07-08
// Description: Declaration and partial implementation of a StockSystem class for use with CMPT 225 assignment #4
#pragma once

#include "stockitem.h"
#include "redblacktree.h"

class StockSystem
{
  private:
    RedBlackTree<StockItem> records;
    double balance; // how much money you have in the bank

  public:
    // default constructor;
    // begin with a balance of $100,000.00
    StockSystem();

    // returns the balance member
    double GetBalance();

    // Add a new SKU to the system. Do not allow insertion of duplicate sku
    bool StockNewItem(StockItem item);

    // Locate the item with key itemsku and update its description field.
    // Return false if itemsku is not found.
    bool EditStockItemDescription(unsigned int itemsku, string desc);

    // Locate the item with key itemsku and update its description field.
    // Return false if itemsku is not found.
    bool EditStockItemPrice(unsigned int itemsku, double retailprice);

    // Purchase quantity of item at unitprice each, to reach a maximum (post-purchase) on-hand stock quantity of 1000.
    // Return false if balance is not sufficient to make the purchase,
    //   or if SKU does not exist.
    // Otherwise, return true and increase the item's on-hand stock by quantity,
    //   and reduce balance by quantity*unitprice.
    bool Restock(unsigned int itemsku, unsigned int quantity, double unitprice);

    // Sell an item to a customer, if quantity of stock is available and SKU exists.
    // Reduce stock by quantity, increase balance by quantity*price, and return true if stock available.
    // If partial stock (less than quantity) available, sell the available stock and return true.
    // If no stock or sku does not exist, return false.
    bool Sell(unsigned int itemsku, unsigned int quantity);

    // Return a formatted string containing complete stock catalogue information in the following format:
    // <sku> <description> <quantity> <price> <newline>
    string GetCatalogue()
    {
      unsigned int cataloguesize = 0; // create a variable which will be modified by tree's Dump function
      StockItem* catalogue = records.Dump(cataloguesize);
      string strcatalogue = "SKU    DESCRIPTION                      QTY  PRICE\n";
      for (unsigned int i = 0; i < cataloguesize; i++)
      {
        strcatalogue = strcatalogue + std::to_string(static_cast<unsigned long long>(catalogue[i].GetSKU())) + "  " + catalogue[i].GetDescription();
        // pad description to 30 characters if shorter
        if (catalogue[i].GetDescription().length() < 30)
        {
          int padamount = 30 - catalogue[i].GetDescription().length();
          for (int j = 0; j < padamount; j++)
            strcatalogue = strcatalogue + " ";
        }
        strcatalogue = strcatalogue + "  ";
        // pad quantity to 4 places
        if (catalogue[i].GetStock() < 1000) strcatalogue = strcatalogue + " ";
        if (catalogue[i].GetStock() < 100) strcatalogue = strcatalogue + " ";
        if (catalogue[i].GetStock() < 10) strcatalogue = strcatalogue + " ";
        strcatalogue = strcatalogue + std::to_string(static_cast<unsigned long long>(catalogue[i].GetStock())) + "  $" + std::to_string(static_cast<long double>(catalogue[i].GetPrice())) + "\n";
      }
      return strcatalogue;
    }

    // Provides access to internal RedBlackTree.
    // Used for grading.
    // Note that this is dangerous in practice!
    RedBlackTree<StockItem>& GetRecords()
    {
      return records;
    }
};
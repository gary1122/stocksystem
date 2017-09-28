#include "stocksystem.h"

StockSystem::StockSystem()
{
	balance = 100000.00;
}

double StockSystem::GetBalance()
{
	return balance;
}


bool StockSystem::StockNewItem(StockItem item)
{
	return records.Insert(item);
}

bool StockSystem::EditStockItemDescription(unsigned int itemsku, string desc)
{
	Node<StockItem>* get = records.GetRoot();                    //creat a pointer pointing to root of records
	if (get == NULL)                                 //case: records does not contain anything
	{   
		return false;
	}
	else if ( records.Size()==1)                   //case: records contains one item
	{
		if ((get->data).GetSKU() == itemsku)
		{
			return (get->data).SetDescription(desc);
		}
		else {return false;}
	}
	else
	{
		while (get!= NULL) 
		{
			if((get->data).GetSKU() < itemsku)
			{
				get = get->right;
			}
			else if ((get->data).GetSKU() > itemsku)
			{
				get = get->left;
			}
			else if ((get->data).GetSKU() == itemsku)
			{
				return (get->data).SetDescription(desc);
			}
		}
	}

	return false;
}


bool StockSystem::EditStockItemPrice(unsigned int itemsku, double retailprice)
{

		Node<StockItem>* get = records.GetRoot();                    //creat a pointer pointing to root of records
	if (get == NULL)                                 //case: records does not contain anything
	{   
		return false;
	}
	else if ( records.Size()==1)                   //case: records contains one item
	{
		if ((get->data).GetSKU() == itemsku)
		{
			return (get->data).SetPrice(retailprice);
		}
		else {return false;}
	}
	else
	{
		while (get!= NULL) 
		{
			if((get->data).GetSKU() < itemsku)
			{
				get = get->right;
			}
			else if ((get->data).GetSKU() > itemsku)
			{
				get = get->left;
			}
			else if ((get->data).GetSKU() == itemsku)
			{
				return (get->data).SetPrice(retailprice);
			}
		}
	}

	return false;
}

bool StockSystem::Restock(unsigned int itemsku, unsigned int quantity, double unitprice)
{
	Node<StockItem>* get = records.GetRoot();                    //creat a pointer pointing to root of records
	double total = quantity*unitprice;
	while (get!=NULL)
	{
		if ((get->data).GetSKU() == itemsku)
		{
			if (((get->data).GetStock()+quantity) > 1000)               //exceed stock capacity
			{
				return false;
			}
			else if (balance < total)                         //total cost > balance
			{
				return false;
			}
			else
			{
				balance = balance -total;
				return (get->data).SetStock((get->data).GetStock()+quantity);
			}
		}
		else if ((get->data).GetSKU() < itemsku)
		{
			get = get->right;
		}
		else if ((get->data).GetSKU() == itemsku)
		{
			get = get->left;
		}
	}
	return false;             //sku not in the records

	
}


bool StockSystem::Sell(unsigned int itemsku, unsigned int quantity)
{
	Node<StockItem>* get = records.GetRoot();   
	while (get!=NULL)
	{
		if ((get->data).GetSKU() == itemsku)               //check if sku exists
		{
			if ((get->data).GetStock() == 0)               //no stock
			{
				return false;
			}
			if ((get->data).GetStock() <  quantity)
			{
				balance = balance + ((get->data).GetStock())*((get->data).GetPrice());
				return (get->data).SetStock(0);
			}
			else if ((get->data).GetStock() >  quantity)
			{
				balance = balance + quantity*((get->data).GetPrice());
				return (get->data).SetStock(((get->data).GetStock()-quantity));
			}

		}
		else if ((get->data).GetSKU() < itemsku)
		{
			get = get->right;
		}
		else if ((get->data).GetSKU() > itemsku)
		{
			get = get->left;
		}
	}


	return false;
}
/*===========================================================================\\
||                               Product.h                                   ||
|| Author: Royce Ayroso-Ong                                                  ||
|| Email:  rjayroso-ong@myseneca.ca                                          ||
|| ID:     115813180                                                         ||
|| Date:   06/04/2019                                                        ||
\\===========================================================================*/
#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H

#include <iostream>
#include "ErrorState.h"
#include "iProduct.h"

namespace ama
{
	class Product : public iProduct
	{
		const char m_type;
		char m_sku[max_length_sku];
		char m_unit[max_length_unit];
		char* m_pName;
		int m_qtyAvailable;
		int m_qtyNeeded;
		double m_price;
		bool m_taxable;
		ErrorState m_state;

	protected:

		void message(const char* pText);
		bool isClear() const;
		bool isValid(const char* name) const;
		void setName(const char* newName);

	public:
		
		Product(const char type = 'N');
		Product(const char* sku, const char* name, const char* unit, double price = 0, int qtyNeeded = 0, int qtyAvailable = 0, bool taxable = true);
		Product(const Product &other);
		~Product();
		Product& operator=(const Product& other);
		
		int operator+=(int cnt);
		bool operator==(const char* sku) const;
		bool operator>(const char* sku) const;
		bool operator>(const iProduct& other) const;
		int qtyAvailable() const;
		int qtyNeeded() const;
		const char* name() const;
		double total_cost() const;
		double price() const;
		bool isEmpty() const;
		std::istream& read(std::istream& in, bool interractive);
		std::ostream& write(std::ostream& out, int writeMode) const;
	};
}

#endif
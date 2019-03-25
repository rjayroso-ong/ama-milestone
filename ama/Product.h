/* Milestone 3 - Product
   NAME: Royce Ayroso-Ong || ID: rjayroso-ong@myseneca.ca, 115813180 || DATE: 24/03/2019 */
#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H

#include <iostream>
#include "ErrorState.h"

namespace ama
{
	const int max_length_label = 30;
	const int max_length_sku = 7;
	const int max_length_name = 75;
	const int max_length_unit = 10;
	const int write_condensed = 0;
	const int write_table = 1;
	const int write_human = 2;
	const double tax_rate = 0.13;

	class Product
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

		void message(const char* pText);
		bool isClear() const;
		bool isValid(const char* name) const;

	public:
		
		Product(const char type = 'N');
		Product(const char* sku, const char* name, const char* unit, double price = 0, int qtyNeeded = 0, int qtyAvailable = 0, bool taxable = true);
		Product(const Product &other);
		~Product();
		Product& operator=(const Product& other);
		
		int operator+=(int cnt);
		bool operator==(const char* sku) const;
		bool operator>(const char* sku) const;
		bool operator>(const Product& other) const;
		int qtyAvailable() const;
		int qrtyNeeded() const;
		double total_cost() const;
		bool isEmpty() const;
		std::istream& read(std::istream& in, bool interractive);
		std::istream& write(std::istream& out, bool writeMode) const;
	};
}
#endif
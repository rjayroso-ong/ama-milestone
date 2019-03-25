/* Milestone 3 - Product
   NAME: Royce Ayroso-Ong || ID: rjayroso-ong@myseneca.ca, 115813180 || DATE: 24/03/2019 */

#include <iostream>
#include <cstring>
#include "Product.h"

using namespace std;

namespace ama
{
	// message stores pText into the Product's m_state
	void Product::message(const char* pText)
	{
		m_state = pText;
	}

	// isClear returns true if the ErrorState contains no message
	bool Product::isClear() const
	{
		return (m_state.message() != nullptr && strcmp(m_state.message(), "") != 0);
	}

	// isValid returns true if parameter name is not a nullptr and not empty
	bool Product::isValid(const char* name) const
	{
		return (name != nullptr && strcmp(name, "") != 0);
	}

	Product::Product(const char type) : m_type(type)
	{
		// TODO: revise empty state
		// NOTE: the attribute m_pName is used to check if it is in an empty state
		strncpy(m_sku, "", max_length_sku);
		strncpy(m_unit, "", max_length_unit);
		m_pName = nullptr; 
		m_qtyAvailable = -1;
		m_qtyNeeded = -1;
		m_price = -1;
		m_taxable = false;
		m_state = "EMPTY STATE";
	}

	Product::Product(const char* sku, const char* name, const char* unit, double price, int qtyNeeded, int qtyAvailable, bool taxable) : m_type('N')
	{
		// TODO: revamp and re implement both constructors
		// NOTE: allocates enough memory for name
		// NOTE2: if name is valid then set attributes
		if (isValid(name))
		{
			strncpy(m_sku, sku, max_length_sku);
			strncpy(m_unit, unit, max_length_unit);
			strncpy(m_pName, name, max_length_name);
			m_qtyAvailable = qtyAvailable;
			m_qtyNeeded = qtyNeeded;
			m_price = price;
			m_taxable = taxable;
		}
		else
			*this = Product(); // empty state
	}

	Product::Product(const Product &other) : m_type(other.m_type)
	{
		//m_pName = nullptr; // only for deletion later
		*this = other;
	}

	Product::~Product()
	{
		delete[] m_pName;
	}

	Product& Product::operator=(const Product& other)
	{
		// TODO: clean up name before copy?
		strncpy(m_sku, other.m_sku, max_length_sku);
		strncpy(m_unit, other.m_unit, max_length_unit);
		strncpy(m_pName, other.m_pName, max_length_name);
		m_qtyAvailable = other.m_qtyAvailable;
		m_qtyNeeded = other.m_qtyNeeded;
		m_price = other.m_price;
		m_taxable = other.m_taxable;

		return *this;
	}

	int Product::operator+=(int cnt)
	{
		if (cnt > 0)
			m_qtyAvailable += cnt;

		return qtyAvailable();
	}

	bool Product::operator==(const char* sku) const
	{
		return (strcmp(m_sku, sku) == 0);
	}

	bool Product::operator>(const char* sku) const
	{
		return (strcmp(m_sku, sku) > 0);
	}

	bool Product::operator>(const Product& other) const
	{
		return (strcmp(m_pName, other.m_pName) > 0);
	}

	int Product::qtyAvailable() const
	{
		return m_qtyAvailable;
	}

	int Product::qrtyNeeded() const
	{
		return m_qtyNeeded;
	}

	double Product::total_cost() const
	{
		double total = qtyAvailable() * m_price;

		if (m_taxable)
			return  (total + (total * tax_rate));

		return total;
	}

	bool Product::isEmpty() const
	{
		return !isValid(m_pName);
	}

	istream& Product::read(istream& in, bool interractive)
	{
		// TODO: add ErrorState
		// TODO: add isClear checks
		if (interractive)
		{
			char userAns;
			char* pUserName;

			// prompts user for values
			cout << "Sku: ";
			cin >> m_sku;                  // sku

			cout << "Name (no spaces): ";
			cin >> pUserName;                // name // NOTE: might have to define a seperate variable
			strcpy(m_pName, pUserName);

			cout << "Unit: ";
			cin >> m_unit;

			// TODO: fail state - more than just else statement
			cout << "Taxed? (y/n): ";      // taxable status
			cin >> userAns;
			if (userAns == 'Y' || userAns == 'y')
				m_taxable = true;
			else if (userAns == 'N' || userAns == 'n')
				m_taxable = false;
			else
				m_state = "Only (Y)es or (N)o are acceptable!";
				
			cout << "Price: ";             // price
			cin >> m_price;

			cout << "Quantity on hand: ";  // quantity available
			cin >> m_qtyAvailable;

			cout << "quantity needed: ";   // quantity needed
			cin >> m_qtyNeeded;
		}
		else
		{
			// does NOT prompt user for values but instead takes them from stream
			in.get(m_sku, max_length_sku, ',');
			if (in.fail())
			{

			}
			in.ignore();


			/*
			is.get(month, 3, '/');
			if (is.fail())
			{
				tempDate.status(error_input);
				break;
			}
			is.ignore();
			*/
		}

		return in;
	}

	//std::istream& write(std::istream& out, bool writeMode) const;
}
/* Milestone 3 - Product
   NAME: Royce Ayroso-Ong || ID: rjayroso-ong@myseneca.ca, 115813180 || DATE: 24/03/2019 */

#include <iostream>
#include <iomanip>
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
		return (m_state.message() == nullptr);
	}

	/* isValid(const char* name) returns true if parameter name is not a nullptr 
	   and not empty and under 75 characters long                             */
	bool Product::isValid(const char* name) const
	{
		return (name != nullptr && strcmp(name, "") != 0 && strlen(name) <= 75);
	}

	// setName(const char* newName) allocates memory for m_pName and sets it to newName
	void Product::setName(const char* newName)
	{
		int len = strlen(newName) + 1;
		m_pName = new char[len];
		strncpy(m_pName, newName, len);
		m_pName[len - 1] = '\0';
	}

	Product::Product(const char type) : m_type(type)
	{
		strncpy(m_sku, "", max_length_sku);
		strncpy(m_unit, "", max_length_unit);
		m_pName = nullptr; 
		m_qtyAvailable = 0;
		m_qtyNeeded = 0;
		m_price = 0;
		m_taxable = false;
	}

	Product::Product(const char* sku, const char* name, const char* unit, 
					 double price, int qtyNeeded, int qtyAvailable, bool taxable) : m_type('N')
	{
		// NOTE: allocates enough memory for name in the function setName
		
		// if name is valid then set attributes
		if (isValid(name)) 
		{
			strncpy(m_sku, sku, max_length_sku);
			strncpy(m_unit, unit, max_length_unit);
			setName(name);

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
		*this = other;
	}

	Product::~Product()
	{
		delete[] m_pName;
	}

	Product& Product::operator=(const Product& other)
	{
		if (this != &other)
		{
			strncpy(m_sku, other.m_sku, max_length_sku);
			strncpy(m_unit, other.m_unit, max_length_unit);
			setName(other.m_pName);
			m_qtyAvailable = other.m_qtyAvailable;
			m_qtyNeeded = other.m_qtyNeeded;
			m_price = other.m_price;
			m_taxable = other.m_taxable;
		}
		
		return *this;
	}

	// operator+=(int cnt) adds to cnt the quantity available if cnt is positive
	int Product::operator+=(int cnt)
	{
		if (cnt > 0)
			m_qtyAvailable += cnt;

		return qtyAvailable();
	}

	// operator==(const char* sku) returns true if the sku is equal to the other product's sku
	bool Product::operator==(const char* sku) const
	{
		return (strcmp(m_sku, sku) == 0);
	}

	// operator>(const char* sku) returns true if the SKU is greater than the other product's SKU
	bool Product::operator>(const char* sku) const
	{
		return (strcmp(m_sku, sku) > 0);
	}

	// operator>(const Product& other) returns true if the name is greater than the other product's name
	bool Product::operator>(const Product& other) const
	{
		return (strcmp(m_pName, other.m_pName) > 0);
	}

	// qtyAvailable() returns the value of the attribute storing the quantity available
	int Product::qtyAvailable() const
	{
		return m_qtyAvailable;
	}

	// qtyNeeded() returns the value of the attribute storing the quantity needed
	int Product::qtyNeeded() const
	{
		return m_qtyNeeded;
	}

	// total_cost() returns the the cost of all available units, including tax
	double Product::total_cost() const
	{
		double total = qtyAvailable() * m_price;

		if (m_taxable)
			return  (total + (total * tax_rate));

		return total;
	}

	// price() returns the price of the product, including tax if it is taxable
	double Product::price() const
	{
		if (m_taxable)
			return  (m_price + (m_price * tax_rate));
		return m_price;
	}

	bool Product::isEmpty() const
	{
		return !isValid(m_pName);
	}

	istream& Product::read(istream& in, bool interractive)
	{
		char name[max_length_name]; // will later be used to set m_pName if valid

		if (interractive) // prompts user for values
		{
			char userAns;
			bool flag = true;

			while (flag)
			{
				/* NOTE: if flag becomes false then it means it has reached the 
				         end of the while loop                               */
				cout.width(max_length_label);
				cout << right << "Sku: ";
				in >> m_sku;
				if (in.fail())
				{
					in.setstate(ios::failbit);
					break; // stop asking user for inputs
				}

				cout.width(max_length_label);
				cout << right << "Name (no spaces): ";
				in >> name;               
				if (in.fail())
				{
					in.setstate(ios::failbit);
					break; 
				}

				cout.width(max_length_label);
				cout << right << "Unit: ";
				in >> m_unit;
				if (in.fail())
				{
					in.setstate(ios::failbit);
					break;
				}

				cout.width(max_length_label);
				cout << right << "Taxed? (y/n): ";     
				in >> userAns;
				if (userAns == 'Y' || userAns == 'y')
					m_taxable = true;
				else if (userAns == 'N' || userAns == 'n')
					m_taxable = false;
				else
				{
					in.setstate(ios::failbit);
					m_state = "Only (Y)es or (N)o are acceptable!";
					break;
				}

				cout.width(max_length_label);
				cout << right << "Price: ";            
				in >> m_price;
				if (in.fail())
				{
					in.setstate(ios::failbit);
					m_state = "Invalid Price Entry!";
					break;
				}

				cout.width(max_length_label);
				cout << right << "Quantity on hand: "; 
				in >> m_qtyAvailable;
				if (in.fail())
				{
					in.setstate(ios::failbit);
					m_state = "Invalid Quantity Available Entry!";
					break;
				}

				cout.width(max_length_label);
				cout << right << "Quantity needed: ";   
				in >> m_qtyNeeded;
				if (in.fail())
				{
					in.setstate(ios::failbit);
					m_state = "Invalid Quantity Needed Entry!";
					break;
				}

				flag = false; // reached the end of the user inputs
			}
			if (!flag) // did not fail to read any and got to the end of the loop
			{
				*this = Product(m_sku, name, m_unit, m_price, m_qtyNeeded, m_qtyAvailable, m_taxable);
			}
		}
		else // does NOT prompt user for values but instead takes them from stream
		{	
			in.get(m_sku, max_length_sku, ',');
			in.ignore();
			in.get(name, max_length_name, ',');
			in.ignore();
			in.get(m_unit, max_length_unit, ',');
			in.ignore();

			in >> m_price;
			in.ignore();
			in >> m_taxable;
			in.ignore();
			in >> m_qtyAvailable;
			in.ignore();
			in >> m_qtyNeeded;

			*this = Product(m_sku, name, m_unit, m_price, m_qtyNeeded, m_qtyAvailable, m_taxable);
		}

		return in;
	}

	ostream& Product::write(std::ostream& out, int writeMode) const
	{
		if (!isClear()) // contains error message
		{
			// print error message and exit
			out << m_state;
			return out;
		}
			
		if (!isEmpty())
		{
			if (writeMode == write_condensed)
			{
				out << m_type << "," << m_sku << "," << m_pName << ","
					<< m_unit << "," << fixed << setprecision(2) << m_price << "," << m_taxable << ","
					<< m_qtyAvailable << "," << m_qtyNeeded;
			}
			else if (writeMode == write_table)
			{
				// displaying - SKU
				out << " ";
				out.width(max_length_sku);
				out << right << m_sku << " | ";

				// displaying - NAME
				out.width(16);
				if (strlen(m_pName) > 16)
				{
					char tempName[17];
					strncpy(tempName, m_pName, 13);
					tempName[13] = '.';
					tempName[14] = '.';
					tempName[15] = '.';
					tempName[16] = '\0';
					
					out << left << tempName << " | ";
				}
				else
					out << left << m_pName << " | ";
				
				// displaying - UNIT
				out.width(10);
				out << left << m_unit << " | ";

				// displaying - PRICE
				out.width(7);
				out << right << fixed << setprecision(2) << m_price << " | ";

				// displaying - TAX
				out.width(3);
				if (m_taxable)
					out << right <<  "yes" << " | ";
				else
					out << right << "no" << " | ";

				// displaying - QTYA
				out.width(6);
				out << right << qtyAvailable() << " | ";

				// displaying - QTYN
				out.width(6);
				out << right << qtyNeeded() << " |";
			}
			else if (writeMode == write_human)
			{
				out.width(max_length_label);
				out << right << "Sku: " << m_sku << endl;
				out.width(max_length_label);
				out << right << "Name: " << m_pName << endl;
				out.width(max_length_label);
				out << right << "Price: " << fixed << setprecision(2) << m_price << endl;
				out.width(max_length_label);
				out << right << "Price after Tax: " << price() << endl;
				out.width(max_length_label);
				out << right << "Quantity Available: " << qtyAvailable() << " " << m_unit << endl;
				out.width(max_length_label);
				out << right << "Quantity Needed: " << qtyNeeded() << " " << m_unit << endl;
			}
		}

		return out;
	}
}
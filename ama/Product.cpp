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
		return (m_state.message() != nullptr && strcmp(m_state.message(), "") != 0);
	}

	// isValid returns true if parameter name is not a nullptr and not empty and under 75 characters long
	bool Product::isValid(const char* name) const
	{
		return (name != nullptr && strcmp(name, "") != 0 && strlen(name) <= 75);
	}

	void Product::setName(const char* newName)
	{
		int len = strlen(newName) + 1;
		m_pName = new char[len];
		strncpy(m_pName, newName, len);
		m_pName[len - 1] = '\0';
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
		setName(other.m_pName);
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

	int Product::qtyNeeded() const
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
		/*  initialize variables that will store the values of the input stream
			before setting them to our member attributes                     */
		const int tempSize = 99;
		char* pName;
		char sku[max_length_sku], unit[max_length_unit];
		char price[tempSize], taxable[tempSize], qtyA[tempSize], qtyN[tempSize];

		if (interractive) // prompts user for values
		{
			char userAns;
			bool flag = true;

			while (flag)
			{
				cout.width(max_length_label);
				cout << right << "Sku: ";
				cin >> sku;
				if (in.fail())
				{
					in.setstate(ios::failbit);
					break; // stop asking user for inputs
				}
				in.ignore();

				cout << right << "Name (no spaces): ";
				cin >> pName;               
				if (in.fail())
				{
					in.setstate(ios::failbit);
					break; 
				}
				in.ignore();

				cout << right << "Unit: ";
				cin >> unit;
				if (in.fail())
				{
					in.setstate(ios::failbit);
					break;
				}
				in.ignore();

				cout << right << "Taxed? (y/n): ";     
				cin >> userAns;
				if (in.fail())
				{
					in.setstate(ios::failbit);
					m_state = "Only (Y)es or (N)o are acceptable!";
					break;
				}
				in.ignore();
				if (userAns == 'Y' || userAns == 'y')
					m_taxable = true;
				else if (userAns == 'N' || userAns == 'n')
					m_taxable = false;
				else
					m_state = "Only (Y)es or (N)o are acceptable!";

				cout << right << "Price: ";            
				cin >> price;
				if (in.fail())
				{
					in.setstate(ios::failbit);
					m_state = "Invalid Price Entry!";
					break;
				}
				in.ignore();

				cout << right << "Quantity on hand: "; 
				cin >> qtyA;
				if (in.fail())
				{
					in.setstate(ios::failbit);
					m_state = "Invalid Available Entry!";
					break;
				}
				in.ignore();

				cout << right << "Quantity needed: ";   
				cin >> m_qtyNeeded;
				if (in.fail())
				{
					in.setstate(ios::failbit);
					m_state = "Invalid Needed Entry!";
					break;
				}
				in.ignore();

				flag = false; // reached the end of the user inputs
			}
			if (!flag) // did not fail to read any and got to the end of the loop
			{
				*this = Product(sku, pName, unit, atof(price), atoi(qtyN), atoi(qtyA), atoi(taxable));
			}
			// IF CHECK TO SEE IF FAILED, IF SUCCESSFUL THEN SET VALUES
			// TODO: remove in.ignore();?
		}
		else // does NOT prompt user for values but instead takes them from stream
		{
			char name[max_length_name];
			in.get(m_sku, max_length_sku, ',');
			in.ignore();
			in.get(name, max_length_name, ',');
			in.ignore();
			in.get(m_unit, max_length_unit, ',');
			in.ignore();

			in.get(price, tempSize, ',');
			in.ignore();
			in.get(taxable, tempSize, ',');
			in.ignore();
			in.get(qtyA, tempSize, ',');
			in.ignore();
			in.getline(qtyN, tempSize);

			setName(name);
			m_price = atof(price);
			m_taxable = atoi(taxable);
			m_qtyAvailable = atoi(qtyA);
			m_qtyNeeded = atoi(qtyN);
		}

		return in;
	}
	ostream& Product::write(std::ostream& out, bool writeMode) const
	{
		if (!isClear()) // contains error message
		{
			// print error meessage and exit
			out << m_state;
			return out;
		}
			
		if (!isEmpty())
		{
			if (writeMode == write_condensed)
			{
				out << m_type << "," << m_sku << "," << m_pName << ","
					<< m_unit << "," << m_price << "," << m_taxable << "," 
					<< m_qtyAvailable << "," << m_qtyNeeded << endl;
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
					string shortName;
					shortName.assign(m_pName, 13); 
					out << shortName.c_str() << "... | ";
				}
				else
					out << left << m_pName << " | ";
				
				// displaying - UNIT
				out.width(10);
				out << left << m_unit;

				// displaying - PRICE
				out.width(7);
				out << left << setprecision(2) << m_price;

				// displaying - TAX
				out.width(3);
				if (m_taxable)
					out << "yes | ";
				else
					out << "no | "; // FIX the | dividers 

				// displaying - QTYA
				out.width(6);
				out << qtyAvailable() << " | ";

				// displaying - QTYN
				out.width(6);
				out << qtyNeeded() << " |";
			}
			else if (writeMode == write_human)
			{
				out.width(max_length_label);
				out << right << "Sku: " << m_sku << endl;
				out.width(max_length_label);
				out << right << "Name: " << m_pName << endl;
				out.width(max_length_label);
				out << right << "Price: " << setprecision(2) << m_price << endl;
				out.width(max_length_label);
				out << right << "Price after Tax: " << total_cost() << endl;
				out.width(max_length_label);
				out << right << "Quantity Available: " << qtyAvailable() << endl;
				out.width(max_length_label);
				out << right << "Quantity Needed: " << qtyNeeded() << endl;
			}
		}

		return out;
	}
}
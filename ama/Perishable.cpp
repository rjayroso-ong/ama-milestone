/*===========================================================================\\
||                             Perishable.cpp                                ||
|| Author: Royce Ayroso-Ong                                                  ||
|| Email:  rjayroso-ong@myseneca.ca                                          ||
|| ID:     115813180                                                         ||
|| Date:   07/04/2019                                                        ||
\\===========================================================================*/

#include <iostream>
#include "Perishable.h"
#include "AmaApp.h"

using namespace std;

namespace ama
{
	Perishable::Perishable(const char type) : Product(type) 
	{
		m_expiryDate = Date(); // empty state date
	}
	
	ostream& Perishable::write(ostream& out, int writeMode) const
	{
		Product::write(out, writeMode);

		if (m_expiryDate.isGood()) // if m_expiryDate is a valid date
		{
			if (writeMode == write_human)
			{
				out.width(max_length_label);
				out << right << "Expiry Date: " << m_expiryDate << endl;
			}
			else if (writeMode == write_table)
				out << " " << m_expiryDate << " |";
			else if (writeMode == write_condensed)
				out << "," << m_expiryDate;
		}
		
		return out;
	}

	istream& Perishable::read(istream& in, bool interractive)
	{
		Date tempDate;
		Product::read(in, interractive);

		if (interractive && Product::isClear()) // read is successful AND it is interractive mode
		{
			cout.width(max_length_label);
			cout << right << "Expiry date (YYYY/MM/DD): ";
			clearKeyboard();
			in >> tempDate;
			
			
			if (!tempDate.isGood())             // tempDate has errors
			{
				in.setstate(ios::failbit);
				if (tempDate.status() == error_year)
					message("Invalid Year in Date Entry");
				else if (tempDate.status() == error_mon)
					message("Invalid Month in Date Entry");
				else if (tempDate.status() == error_day)
					message("Invalid Day in Date Entry");
				else
					message("Invalid Date Entry");
			}
			else                                // tempDate has NO errors
				m_expiryDate = tempDate;
		}
		else if (!interractive) 
		{
			m_expiryDate.read(in);
			in.ignore();
		}

		return in;
	}
}
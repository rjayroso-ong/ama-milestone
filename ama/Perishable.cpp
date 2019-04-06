/* Milestone 5 - Perishable.cpp
   NAME: Royce Ayroso-Ong || ID: rjayroso-ong@myseneca.ca, 115813180 || DATE: 06/04/2019 */

#include <iostream>
#include "Perishable.h"

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
		if (writeMode == write_human)
		{
			out.width(max_length_label);
			out << right << "Exipry Date: " << m_expiryDate << endl;
		}
		else if (writeMode == write_table)
			out << m_expiryDate << " |";
		else if (writeMode == write_condensed)
			out << "," << m_expiryDate;
		
		return out;
	}

	istream& Perishable::read(istream& in, bool interractive)
	{
		Date tempDate;

		if (interractive)
		{
			cout.width(max_length_label);
			cout << right << "Expiry date (YYYY/MM/DD): ";
			in >> tempDate;
			// NOTE: maybe should change to strcmp(tempDate.status(), no_error) == 0
			if (!tempDate.isGood())                   // tempDate has errors
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
			else                                      // tempDate has NO errors
				m_expiryDate = tempDate;
		}
		else
		{
			m_expiryDate.read(in);
			in.ignore();
		}

		return in;
	}

}
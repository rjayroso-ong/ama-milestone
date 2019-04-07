/*===========================================================================\\
||                             Utilities.cpp                                 ||
|| Author: Royce Ayroso-Ong                                                  ||
|| Email:  rjayroso-ong@myseneca.ca                                          ||
|| ID:     115813180                                                         ||
|| Date:   06/04/2019                                                        ||
\\===========================================================================*/

#include <iostream>
#include "Utilities.h"
#include "Product.h"
#include "Perishable.h"

using namespace std;

namespace ama
{
	// operator+= adds the parameter products total cost to total
	double& operator+=(double& total, const iProduct& prod)
	{
		total += prod.total_cost();
		return total;
	}

	ostream& operator<<(ostream& out, const iProduct& prod)
	{
		return prod.write(out, write_human);
	}

	istream& operator>>(istream& in, iProduct& prod)
	{
		return prod.read(in, true);
	}

	/* createInstance() creates a product or perishable object based on the
	   users parameter tag input and returns it's address                   */
	iProduct* createInstance(char tag)
	{
		iProduct* tempProd = nullptr;

		if (tag == 'N' || tag == 'n')
		{
			tempProd = new Product();
		}
		else if (tag == 'P' || tag == 'p')
		{
			tempProd = new Perishable();
		}
			
		return tempProd;
	}
}

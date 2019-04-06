/* Milestone 3 - Utilities
   NAME: Royce Ayroso-Ong || ID: rjayroso-ong@myseneca.ca, 115813180 || DATE: 24/03/2019 */

#include <iostream>
#include "Utilities.h"
#include "Product.h"

using namespace std;

namespace ama
{
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

	iProduct* createInstance(char tag)
	{
		iProduct* tempProd = nullptr;
		if (tag == 'N' || tag == 'n')
		{
			tempProd = new Product();
		}
		else
			return tempProd;
	}
}

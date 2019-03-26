/* Milestone 3 - Utilities
   NAME: Royce Ayroso-Ong || ID: rjayroso-ong@myseneca.ca, 115813180 || DATE: 24/03/2019 */

#include "Utilities.h"

namespace ama
{
	double& operator+=(double& total, const Product& prod)
	{
		total += prod.total_cost();
		return total;
	}

	std::ostream& operator<<(std::ostream& out, const Product& prod) 
	{
		return prod.write(out, write_human);
	}

	std::istream& operator>>(std::istream& in, Product& prod)
	{
		return prod.read(in, true);
	}
}

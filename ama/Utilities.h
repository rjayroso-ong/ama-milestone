/* Milestone 3 - Utilities
   NAME: Royce Ayroso-Ong || ID: rjayroso-ong@myseneca.ca, 115813180 || DATE: 24/03/2019 */
#ifndef AMA_UTILITIES_H
#define AMA_UTILITIES_H

#include <iostream>
#include "Product.h"

namespace ama
{
	double& operator+=(double& total, const Product& prod);
	std::ostream& operator<<(std::ostream& out, const Product& prod);
	std::istream& operator>>(std::istream& in, Product& prod);
}

#endif


/* Milestone 5 - Perishable.cpp
   NAME: Royce Ayroso-Ong || ID: rjayroso-ong@myseneca.ca, 115813180 || DATE: 06/04/2019 */
#ifndef AMA_PERISHABLE_H
#define AMA_PERISHABLE_H

#include "Date.h"
#include "Product.h"

namespace ama
{
	class Perishable : public Product
	{
		Date m_expiryDate;

	public:

		Perishable(char type = 'P');
		std::ostream& write(std::ostream& out, int writeMode) const;
		std::istream& read(std::istream& in, bool interractive);
	};
}

#endif

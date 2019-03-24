#include <cstring>
#include "Product.h"

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

	Product::Product(const char type) : m_type(type)
	{
		*m_sku = NULL;
		*m_unit = NULL;
		*m_name = NULL;
		m_qtyAvailable = -1;
		m_qtyNeeded = -1;
		m_price = -1;
		m_taxable = false;
		m_state = "EMPTY STATE";
	}

	Product::Product(const char* sku, const char* name, const char* unit, double price = 0, int qtyNeeded = 0, int qty = 0, bool taxable = true) : m_type('N')
	{
		if (true)
		{
			strncpy(m_sku, sku, max_length_sku);
			strncpy(m_unit, unit, max_length_unit);
			strncpy(m_name, name, max_length_name);
			m_qtyAvailable = qty;
			m_qtyNeeded = qtyNeeded;
			m_price = price;
			m_taxable = taxable;
		}
		else
		{
			*m_sku = NULL;
			*m_unit = NULL;
			*m_name = NULL;
			m_qtyAvailable = -1;
			m_qtyNeeded = -1;
			m_price = -1;
			m_taxable = false;
			m_state = "EMPTY STATE";
		}
	}
}
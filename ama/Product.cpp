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

	Product::Product(const char type)
	{

	}
}
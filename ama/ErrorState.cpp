/*===========================================================================\\
||                             ErrorState.cpp                                ||
|| Author: Royce Ayroso-Ong                                                  ||
|| Email:  rjayroso-ong@myseneca.ca                                          ||
|| ID:     115813180                                                         ||
|| Date:   06/04/2019                                                        ||
\\===========================================================================*/
#include <iostream>
#include <cstring>
#include "ErrorState.h"

using namespace std;

namespace ama
{
	ErrorState::ErrorState(const char* errorMessage)
	{
		if (isValidMessage(errorMessage))
			set(errorMessage);
		else 
			m_pMessage = nullptr; // safe empty state
	}

	// isValidMessage returns true if errorMessage is not a nullptr and not an empty string
	bool ErrorState::isValidMessage(const char* errorMessage) const
	{
		return (errorMessage != nullptr && strcmp(errorMessage, "") != 0);
	}

	/* set() returns nothing and sets the inputed parameter errorMessage as 
	   the ErrorState's m_pMessage                                          */
	void ErrorState::set(const char* errorMessage)
	{
		int len = strlen(errorMessage) + 1;
		m_pMessage = new char[len];
		strncpy(m_pMessage, errorMessage, len);
		m_pMessage[len - 1] = '\0';
	}

	ErrorState::~ErrorState()
	{
		delete[] m_pMessage;
	}

	// operator bool() returns true if m_pMessage attribute is a valid message
	ErrorState::operator bool() const
	{
		return isValidMessage(m_pMessage);
	}

	// operator= sets the parameter pText as m_pMessage if it is valid
	ErrorState& ErrorState::operator=(const char* pText)
	{
		if (isValidMessage(pText))
		{
			delete[] m_pMessage;
			set(pText);
		}
		else
			m_pMessage = nullptr; // safe empty state

		return *this;
	}

	// message() sets the parameter pText as m_pMessage if it is valid
	void ErrorState::message(const char* pText)
	{
		if (isValidMessage(pText))
		{
			delete[] m_pMessage;
			set(pText);
		}
		else
			m_pMessage = nullptr; // safe empty state

		/* [06/06/2019]
		   Author's Note: in hindsight i see now that it is very similar to 
		   operator bool's function. In the future i will want to update this */
	}

	// message() with no parameters returns m_pMessage
	const char* ErrorState::message() const
	{
		if (isValidMessage(m_pMessage))
			return m_pMessage;

		return nullptr;
	}

	ostream& operator<<(ostream& os, const ErrorState& msg)
	{
		if (msg)
			os << msg.message();

		return os;
	}
}
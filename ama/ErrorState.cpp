/* Milestone 2 - ErrorState
   NAME: Royce Ayroso-Ong || ID: rjayroso-ong@myseneca.ca, 115813180 || DATE: 17/03/2019 */
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

	// set returns nothing and sets the inputed parameter errorMessage as the ErrorState's m_pMessage
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

	ErrorState::operator bool() const
	{
		return isValidMessage(m_pMessage);
	}

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

	void ErrorState::message(const char* pText)
	{
		if (isValidMessage(pText))
		{
			delete[] m_pMessage;
			set(pText);
		}
		else
			m_pMessage = nullptr; // safe empty state
	}

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
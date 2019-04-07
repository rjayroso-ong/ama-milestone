/*===========================================================================\\
||                             ErrorState.h                                  ||
|| Author: Royce Ayroso-Ong                                                  ||
|| Email:  rjayroso-ong@myseneca.ca                                          ||
|| ID:     115813180                                                         ||
|| Date:   06/04/2019                                                        ||
\\===========================================================================*/
#ifndef AMA_ERRORSTATE_H
#define AMA_ERRORSTATE_H

#include <iostream>

namespace ama
{
	class ErrorState
	{
		char* m_pMessage;

		bool isValidMessage(const char* errorMessage) const;
		void set(const char* errorMessage);

	public:
		explicit ErrorState(const char* errorMessage = nullptr);
		ErrorState(const ErrorState& other) = delete;
		ErrorState& operator=(const ErrorState& other) = delete;
		~ErrorState();
		operator bool() const;
		ErrorState& operator=(const char* pText);
		void message(const char* pText);
		const char* message() const;
	};

	std::ostream& operator<<(std::ostream& os, const ErrorState& msg);
}
#endif
/* Milestone 2 - ErrorState
   NAME: Royce Ayroso-Ong || ID: rjayroso-ong@myseneca.ca, 115813180 || DATE: 17/03/2019 */
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

// NAME: Royce Ayroso-Ong || ID: 115813180 || DATE: 10/03/2019
#ifndef AMA_DATE_H
#define AMA_DATE_H

#include<iostream>

namespace ama 
{
	const int min_year = 2019;
	const int max_year = 2028;

	// ERROR TYPES
	const int no_error = 0;
	const int error_year = 1;
	const int error_mon = 2;
	const int error_day = 3;
	const int error_invalid_operation = 4;
	const int error_input = 5;

	class Date 
	{
		// Formatted as: YYYY/MM/DD
		int m_year;
		int m_month;
		int m_day;
		int m_status;

		// PRIVATE MEMBER FUNCTIONS
		void status(int newSatus);
		int status(int year, int month, int day);
		int mdays(int year, int month) const;
		bool isValidYear(int year) const;
		bool isValidMonth(int month) const;
		bool isValidDay(int year, int month, int day) const;

	public:
		// PUBLIC MEMBER FUNCTIONS
		Date();
		Date(int year,int month,int day);
		int status() const;
		void clearError();
		bool isGood() const;

		// OPERATORS
		Date& operator+=(int days);
		Date& operator++();
		Date operator++(int);
		Date operator+(int days) const;
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;

		std::istream& read(std::istream& is);
		std::ostream& write(std::ostream& os) const;
	};

	std::istream& operator>>(std::istream& is, Date& rhs);
	std::ostream& operator<<(std::ostream& os, const Date& rhs);
}
#endif
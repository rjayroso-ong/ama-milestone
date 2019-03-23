// NAME: Royce Ayroso-Ong || ID: 115813180 || DATE: 10/03/2019
#include <iostream>
#include <string>
#include "Date.h"

using namespace std;

namespace ama 
{
	Date::Date()
	{
		*this = Date(0000, 00, 00); // invalid date will set to default empty state, see below
		clearError(); // resets the satus to no_error
	}

	Date::Date(int year, int month, int day)
	{
		// if the status is no error, i.e. the date is valid
		// NOTE: overloaded status function also sets the status based on the validity of the parameters, see: status(int, int, int)
		if (status(year, month, day) == no_error)
		{
			m_year = year;
			m_month = month;
			m_day = day;
		}
		else 
		{
			// default empty state
			m_year = 0000;
			m_month = 00;
			m_day = 00;
		}
	}

	void Date::status(int newStatus)
	{
		m_status = newStatus;
	}

	// overloaded status function sets the status based on the DATE given and then returns the status
	int Date::status(int year, int month, int day)
	{
		// change status based on the DATE parameters
		if (isValidYear(year) && isValidMonth(month) && isValidDay(year, month, day))
			clearError();
		else if (!isValidYear(year))
			status(error_year);
		else if (!isValidMonth(month))
			status(error_mon);
		else if (!isValidDay(year, month, day))
			status(error_day);
		else
			status(error_input); // if year, month, and day are valid clear error

		return status(); // return status of current object
	}

	int Date::mdays(int year, int mon) const
	{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}
	
	// isValidYear returns true if the year entered is between min_year and max_year inclusive
	bool Date::isValidYear(int year) const
	{
		if (min_year < year && year < max_year)
			return true;
		return false;
	}

	// isValidMonth returns true if the day entered is between 1 and 12 inclusive
	bool Date::isValidMonth(int month) const
	{
		if (1 <= month && month <= 12)
			return true;
		return false;
	}

	// isValidDay returns true if the day entered is valid for the specific month of the year inclusive
	bool Date::isValidDay(int year, int month, int day) const
	{
		if (1 <= day && day <= mdays(year, month))
			return true;
		return false;
	}

	/*======================PUBLIC MEMBER FUNCTIONS==========================*/

	int Date::status() const
	{
		return m_status;
	}

	void Date::clearError()
	{
		status(no_error);
	}

	bool Date::isGood() const
	{
		return (isValidYear(m_year) && isValidMonth(m_month) &&
			isValidDay(m_year, m_month, m_day) && status() == no_error);
	}

	/*=============================OPERATORS=================================*/

	Date& Date::operator+=(int days) 
	{
		if (isGood() && isValidDay(m_year, m_month, (m_day + days)))
		{
			m_day = m_day + days;
			*this = Date(m_year, m_month, m_day);
		}
		else
			status(error_invalid_operation);

		return *this; 
	}

	Date& Date::operator++() // prefux
	{
		if (status() == no_error && isValidDay(m_year, m_month, (m_day + 1)))
			*this = Date(m_year, m_month, (m_day + 1));
		else
			status(error_invalid_operation);

		return *this;
	}

	Date Date::operator++(int rhs) // postfix
	{
		Date tempDate = *this;

		if (status() == no_error && isValidDay(m_year, m_month, (m_day + 1)))
			tempDate = Date(m_year, m_month, m_day++);
		else
			status(error_invalid_operation);

		return tempDate;
	}

	Date Date::operator+(int days) const
	{
		Date tempDate = *this;
		int newDay = m_day + days;

		if (isGood() && isValidDay(m_year, m_month, newDay))
			tempDate.m_day = newDay;
		else
			tempDate.status(error_invalid_operation);

		return tempDate;
	}

	bool Date::operator==(const Date& rhs) const
	{
		if (m_year == rhs.m_year &&
			m_month == rhs.m_month &&
			m_day == rhs.m_day)
			return true;
		return false;
	}

	bool Date::operator!=(const Date& rhs) const
	{
		if (m_year != rhs.m_year ||
			m_month != rhs.m_month ||
			m_day != rhs.m_day)
			return true;
		return false;
	}

	bool Date::operator<(const Date& rhs) const
	{
		if (m_year <= rhs.m_year && m_month <= rhs.m_month && m_day < rhs.m_day)
			return true;
		return false;
	}

	bool Date::operator>(const Date& rhs) const
	{
		if (m_year >= rhs.m_year && m_month >= rhs.m_month && m_day > rhs.m_day)
			return true;
		return false;
	}

	bool Date::operator<=(const Date& rhs) const
	{
		if (m_year <= rhs.m_year && m_month <= rhs.m_month && m_day <= rhs.m_day)
			return true;
		return false;
	}

	bool Date::operator>=(const Date& rhs) const
	{
		if (m_year >= rhs.m_year && m_month >= rhs.m_month && m_day >= rhs.m_day)
			return true;
		return false;
	}

	istream& Date::read(std::istream& is)
	{
		Date tempDate = Date();
		char year[5], month[3], day[3];

		while (1)
		{
			is.get(year, 5);
			if (is.fail())
			{
				tempDate.status(error_input);
				break;
			}
			is.ignore();

			is.get(month, 3, '/');
			if (is.fail())
			{
				tempDate.status(error_input);
				break;
			}
			is.ignore();

			is.get(day, 3, '/');
			if (is.fail())
			{
				tempDate.status(error_input);
				break;
			}

			break;
		} 

		if (tempDate.status() != error_input)

			tempDate = Date(atoi(year), atoi(month), atoi(day));
			
		*this = tempDate;

		return is;
	}

	ostream& Date::write(ostream& os) const
	{
		os.fill('0');
		os.width(4);
		os << right << m_year << "/";

		os.fill('0');
		os.width(2);
		os << right << m_month << "/";

		os.fill('0');
		os.width(2);
		os << right << m_day;
		
		os.fill(' ');
		return os;
	}

	istream& operator>>(istream& is, Date& rhs)
	{
		return rhs.read(is);
	}

	ostream& operator<<(ostream& os, const Date& rhs)
	{
		return rhs.write(os);
	}
}
//Citationand Sources...
//Final Project Milestone 1
//Module : Time
//Filename : Time.cpp
//Version 1.0
//Author	Yuelin Wen
//Revision History
//---------------------------------------------------------- -
//Date      Reason
//2020 / 11 / 12 Preliminary release
//2020 / 11 / 12 Debugged DMA
//---------------------------------------------------------- -
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshops and assignments.
//---------------------------------------------------------- -

#define _CRT_SECURE_NO_WARNINGS
#include "Time.h"
#include "utils.h"
#include <cstring>
using namespace std;
namespace sdds {

	Time& Time::reset()
	{
		m_min = getTime();
		// TODO: insert return statement here
		return *this;
	}

	Time::Time(unsigned int min)
	{
		m_min = min;
	}

	std::ostream& Time::write(std::ostream& ostr) const
	{
		unsigned int hour = m_min / 60;
		unsigned int min = m_min % 60;
		ostr.width(2);
		ostr.fill('0');
		ostr << hour;
		ostr << ":";
		ostr.width(2);
		ostr.fill('0');
		ostr << min;
		// TODO: insert return statement here
		return ostr;
	}

	std::istream& Time::read(std::istream& istr)
	{
		unsigned int hour;
		char ch = '\0';
		unsigned int min;

		istr >> hour;
		istr.get(ch);
		istr >> min;
		if (ch != ':' || istr.fail())
		{
			istr.setstate(ios::failbit);
		}
		else
		{
			m_min = 60 * hour + min;
		}

		Time temp(m_min);
		*this = temp;
		// TODO: insert return statement here
		return istr;
	}

	Time::operator int() const
	{
		return m_min;
	}

	Time& Time::operator*=(int val)
	{
		m_min *= val;
		// TODO: insert return statement here
		return *this;
	}

	Time& Time::operator-=(const Time& D)
	{

		if (m_min < D.m_min)
		{
			m_min += 24 * 60;
		}
		m_min -= D.m_min;
		// TODO: insert return statement here
		return *this;
	}

	Time Time::operator-(const Time& ROperand) {
		Time LOperand = *this;
		LOperand -= ROperand;
		return LOperand;
	}

	std::ostream& operator<<(std::ostream& os, const Time& T)
	{
		T.write(os);
		// TODO: insert return statement here
		return os;
	}

	std::istream& operator>>(std::istream& istr, Time& T)
	{
		T.read(istr);
		// TODO: insert return statement here
		return istr;
	}

}
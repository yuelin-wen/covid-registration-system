//Citationand Sources...
//Final Project Milestone 4
//Module : Time
//Filename : Time.cpp
//Version 1.0
//Author	Yuelin Wen
//Revision History
//---------------------------------------------------------- -
//Date      Reason
//2020 / 11 / 15 Preliminary release
//2020 / 11 / 15 Debugged DMA
//---------------------------------------------------------- -
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshops and assignments.
//---------------------------------------------------------- -
#define _CRT_SECURE_NO_WARNINGS
#include "CovidPatient.h"
#include <iostream>
#include <cstring>
using namespace std;
namespace sdds {
	int nextCovidTicket = 1;


	CovidPatient::CovidPatient() :Patient(nextCovidTicket, fileIO())
	{

		nextCovidTicket++;
	}

	char CovidPatient::type() const
	{
		return 'C';
	}

	std::ostream& CovidPatient::csvWrite(std::ostream& ostr) const
	{
		Patient::csvWrite(ostr);
		// TODO: insert return statement here
		return ostr;
	}

	std::istream& CovidPatient::csvRead(std::istream& istr)
	{
		Patient::csvRead(istr);
		nextCovidTicket = Patient::number() + 1;
		// TODO: insert return statement here
		return istr;
	}

	std::ostream& CovidPatient::write(std::ostream& ostr) const
	{
		if (fileIO())
		{
			csvWrite(ostr);
		}
		else
		{
			ostr << "COVID TEST\n";
			Patient::write(ostr);
			ostr << "\n";
		}
		// TODO: insert return statement here
		return ostr;
	}

	std::istream& CovidPatient::read(std::istream& istr)
	{
		if (fileIO())
		{
			csvRead(istr);
		}
		else
		{
			Patient::read(istr);
		}
		// TODO: insert return statement here
		return istr;
	}




}
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
#include <iostream>
#include <cstring>
#include "TriagePatient.h"
using namespace std;
namespace sdds {
	int nextTriageTicket = 1;
	TriagePatient::TriagePatient() :Patient(nextTriageTicket, fileIO())
	{
		m_symptom = nullptr;
		nextTriageTicket++;
	}

	TriagePatient::~TriagePatient()
	{
		delete[] m_symptom;
	}

	char TriagePatient::type() const
	{
		return 'T';
	}

	std::ostream& TriagePatient::csvWrite(std::ostream& ostr) const
	{
		Patient::csvWrite(ostr);
		ostr << "," << m_symptom;
		// TODO: insert return statement here
		return ostr;
	}

	std::istream& TriagePatient::csvRead(std::istream& istr)
	{
		char symptom[512];
		if (m_symptom != nullptr)
		{
			delete[] m_symptom;
		}

		Patient::csvRead(istr);
		istr.ignore(1000, ',');
		istr.get(symptom, 511, '\n');
		m_symptom = nullptr;
		m_symptom = new char[strlen(symptom) + 1];
		strcpy(m_symptom, symptom);
		nextTriageTicket = Patient::number() + 1;
		// TODO: insert return statement here
		return istr;
	}

	std::ostream& TriagePatient::write(std::ostream& ostr) const
	{
		if (fileIO())
		{
			csvWrite(ostr);
		}
		else
		{
			ostr << "TRIAGE";
			ostr << "\n";
			Patient::write(ostr);
			ostr << "\n";
			ostr << "Symptoms: ";
			ostr << m_symptom;
			ostr << "\n";
		}

		// TODO: insert return statement here
		return ostr;
	}

	std::istream& TriagePatient::read(std::istream& istr)
	{
		if (fileIO())
		{
			csvRead(istr);
		}
		else
		{
			char symptom[512];
			if (m_symptom != nullptr)
			{
				delete[] m_symptom;
			}
			Patient::read(istr);
			cout << "Symptoms: ";
			istr.get(symptom, 511, '\n');
			cin.ignore(1000, '\n');
			m_symptom = nullptr;
			m_symptom = new char[strlen(symptom) + 1];
			strcpy(m_symptom, symptom);
		}

		// TODO: insert return statement here
		return istr;
	}

}
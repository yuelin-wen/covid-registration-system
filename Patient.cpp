//Citationand Sources...
//Final Project Milestone 3
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
#include <iostream>
#include <cstring>
#include "Patient.h"
#include "utils.h"
using namespace std;
namespace sdds {
	/*Patient::Patient(){}*/
	Patient::Patient(int TicketNumber, bool fileIOflag)
	{
		m_number = 0;
		m_Ticket = new Ticket(TicketNumber);
		m_fileIOflag = fileIOflag;
		//fileIO(fileIOflag);
		m_name = nullptr;
	}
	Patient::~Patient()
	{
		delete m_Ticket;
		delete[] m_name;
		m_name = nullptr;
	}


	bool Patient::fileIO() const
	{
		return m_fileIOflag;
	}

	void Patient::fileIO(bool flag)
	{
		m_fileIOflag = flag;
	}

	bool Patient::operator==(char ch) const
	{
		return ch == type();
	}

	bool Patient::operator==(const Patient& P)
	{
		return type() == P.type();
	}

	void Patient::setArrivalTime()
	{
		m_Ticket->resetTime();
	}
	Patient::operator Time() const
	{
		return m_Ticket->operator sdds::Time();
	}

	int Patient::number() const
	{
		return m_Ticket->number();
	}
	std::ostream& Patient::csvWrite(std::ostream& ostr) const
	{
		ostr << type() << "," << m_name << "," << m_number << ",";
		m_Ticket->csvWrite(ostr);
		// TODO: insert return statement here
		return ostr;
	}
	std::istream& Patient::csvRead(std::istream& istr)
	{
		char name[51];
		if (m_name != nullptr)
		{
			delete[] m_name;
		}
		m_name = nullptr;
		istr.get(name, 51, ',');
		istr.ignore(1000, ',');
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);
		istr >> m_number;
		istr.ignore(1000, ',');
		m_Ticket->csvRead(istr);
		// TODO: insert return statement here
		return istr;
	}
	std::ostream& Patient::write(std::ostream& ostr) const
	{
		m_Ticket->write(ostr);
		ostr << "\n" << m_name << ", OHIP: " << m_number;

		// TODO: insert return statement here
		return ostr;
	}
	std::istream& Patient::read(std::istream& istr)
	{
		char name[52];
		int number;
		bool flag = 0;

		if (m_name != nullptr)
		{
			delete[] m_name;
		}

		m_name = nullptr;

		cout << "Name: ";
		istr.get(name, 52);
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);
		cout << "OHIP: ";
		do
		{
			istr >> number;
			if (!cin.fail())
			{
				if (number >= 100000000 && number <= 999999999)
				{
					flag = 1;
				}
				else
				{
					cout << "Invalid value enterd, retry[100000000 <= value <= 999999999]: ";
				}
			}
			else
			{
				cout << "Bad integer value, try again: ";
				cin.clear();

			}
			cin.ignore(1000, '\n');
		} while (flag == 0);
		m_number = number;

		// TODO: insert return statement here
		return istr;
	}
}
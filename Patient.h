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
#include <iostream>
#include "IOAble.h"
#include "Ticket.h"
#ifndef SDDS_PATIENT_H_
#define SDDS_PATIENT_H_
namespace sdds {
	class Patient : public IOAble {
		char* m_name;
		int m_number;
		Ticket* m_Ticket;
		bool m_fileIOflag;
	public:
		Patient(int TicketNumber = 0, bool fileIOflag = false);
		~Patient();
		Patient& operator=(Patient& P) = delete;
		virtual char type()const = 0;
		bool fileIO()const;
		void fileIO(bool flag);
		bool operator==(char ch)const;
		bool operator==(const Patient& P);
		void setArrivalTime();
		operator Time()const;
		int number()const;

		std::ostream& csvWrite(std::ostream& ostr)const;
		std::istream& csvRead(std::istream& istr);
		std::ostream& write(std::ostream& ostr)const;
		std::istream& read(std::istream& istr);


	};
	//bool operator==(const Patient& A, const Patient& B);
}
#endif // !SDDS_PATIENT_H_



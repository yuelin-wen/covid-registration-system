//Citationand Sources...
//Final Project Milestone 2
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

#ifndef SDDS_IOABLE_H_
#define SDDS_IOABLE_H_
#include <iostream>
namespace sdds {
	class IOAble {
	public:
		virtual std::ostream& csvWrite(std::ostream& ostr)const = 0;
		virtual std::istream& csvRead(std::istream& istr) = 0;
		virtual std::ostream& write(std::ostream& ostr)const = 0;
		virtual std::istream& read(std::istream& istr) = 0;
		virtual ~IOAble();
	};
	std::ostream& operator<<(std::ostream& os, const IOAble& I);
	std::istream& operator>>(std::istream& istr, IOAble& I);
}
#endif // !SDDS_IOABLE_H_

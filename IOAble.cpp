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

#include <iostream>
#include "IOAble.h"
using namespace std;
namespace sdds {


	std::ostream& operator<<(std::ostream& os, const IOAble& I)
	{
		I.write(os);
		// TODO: insert return statement here
		return os;
	}
	std::istream& operator>>(std::istream& istr, IOAble& I)
	{
		I.read(istr);
		// TODO: insert return statement here
		return istr;
	}
	IOAble::~IOAble()
	{
	}
}
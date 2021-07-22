//Citationand Sources...
//Final Project Milestone 1
//Module : Menu
//Filename : Menu.cpp
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
#include "utils.h"
#include "Menu.h"
#include <cstring>
#include <iostream>
using namespace std;
namespace sdds {

	Menu::Menu(const char* text, int NoOfSelections)
	{
		if (text != nullptr)
		{
			m_text = nullptr;
			m_text = new char[strlen(text) + 1];
			strcpy(m_text, text);
		}
		m_noOfSel = NoOfSelections;

	}

	Menu::~Menu()
	{
		delete[] m_text;
		m_text = nullptr;
	}

	std::ostream& Menu::display(std::ostream& ostr) const
	{
		ostr << "\n0- Exit" << "\n";
		ostr << "> ";
		// TODO: insert return statement here
		return ostr;
	}

	int& Menu::operator>>(int& Selection)
	{
		int opt;
		bool flag = 0;
		cout << m_text;
		display();

		do
		{
			cin >> opt;
			if (!cin.fail())
			{
				if (opt >= 0 && opt <= m_noOfSel)
				{
					flag = 1;
				}
				else
				{
					cout << "Invalid value enterd, retry[0 <= value <= 3]: ";
				}
			}
			else
			{
				cout << "Bad integer value, try again: ";
				cin.clear();
				cin.ignore(1000, '\n');
			}



		} while (flag == 0);
		Selection = opt;
		// TODO: insert return statement here
		return Selection;
	}

}
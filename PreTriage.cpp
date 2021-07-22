//Citationand Sources...
//Final Project Milestone 5
//Module : PreTriage
//Filename : PreTriage.cpp
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
#include <fstream>
#include <cstring>
#include "Patient.h"
#include "Menu.h"
#include "utils.h"
#include "PreTriage.h"
#include "CovidPatient.h"
#include "TriagePatient.h"
using namespace std;
namespace sdds {
	PreTriage::PreTriage(const char* dataFilename) :
		m_averCovidWait(15),
		m_averTriageWait(5),
		m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2),
		m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2)

	{
		m_dataFilename = nullptr;
		m_dataFilename = new char[strlen(dataFilename) + 1];
		strcpy(m_dataFilename, dataFilename);
		load();
	}
	PreTriage::~PreTriage()
	{
		ofstream csvfileout(m_dataFilename);
		csvfileout << m_averCovidWait << "," << m_averTriageWait << endl;
		cout << "Saving Average Wait Times," << endl;
		cout << "   COVID Test: " << m_averCovidWait << endl;
		cout << "   Triage: " << m_averTriageWait << endl;
		cout << "Saving m_lineup..." << endl;
		for (int i = 0; i < m_lineupSize; i++)
		{
			m_lineup[i]->csvWrite(csvfileout) << endl;
			cout << i + 1 << "- ";
			m_lineup[i]->csvWrite(cout) << endl;
		}
		for (int i = 0; i < m_lineupSize; i++)
		{
			delete m_lineup[i];
			m_lineup[i] = nullptr;
		}
		delete[] m_dataFilename;
		m_dataFilename = nullptr;
		cout << "done!\n";
	}
	void PreTriage::run(void)
	{
		int selection;
		while (m_appMenu >> selection)
		{
			switch (selection) {
			case 1:
				reg();
				break;
			case 2:
				admit();
				break;
			case 0:
				break;
			default:
				cout << "This will never happen!!!!" << endl;
				break;
			}
		}
		//cout << "goodbye!" << endl;
	}

	void PreTriage::reg()
	{
		if (m_lineupSize >= maxNoOfPatients)
		{
			cout << "Line up full!\n";
		}
		else
		{
			int selection;
			bool flag = true;
			while (flag)
			{
				m_pMenu >> selection;
				switch (selection) {
				case 1:
					m_lineup[m_lineupSize] = new CovidPatient();
					break;
				case 2:
					m_lineup[m_lineupSize] = new TriagePatient();
					break;
				case 0:
					break;
				default:
					cout << "This will never happen!!!!" << endl;
					break;
				}
				flag = false;
			}
			m_lineup[m_lineupSize]->setArrivalTime();
			cout << "Please enter patient information: " << endl;
			m_lineup[m_lineupSize]->fileIO(false);
			m_lineup[m_lineupSize]->read(cin);
			cout << endl << "******************************************\n";
			m_lineup[m_lineupSize]->write(cout);
			cout << "Estimated Wait Time: ";
			cout << getWaitTime(*m_lineup[m_lineupSize]) << endl << "******************************************" << endl << endl;
			m_lineupSize++;
		}
	}
	void PreTriage::admit()
	{
		int selection, num = -999;
		char type = ' ';
		bool flag = true;
		while (flag)
		{
			m_pMenu >> selection;
			switch (selection) {
			case 1:
				type = 'C';
				break;
			case 2:
				type = 'T';
				break;
			case 0:
				break;
			default:
				cout << "This will never happen!!!!" << endl;
				break;
			}
			flag = false;
		}
		num = indexOfFirstInLine(type);
		if (num != -999)
		{
			cout << endl << "******************************************" << endl;
			m_lineup[num]->fileIO(false);
			cout << "Calling for ";
			m_lineup[num]->write(cout);
			cout << "******************************************" << endl << endl;
			setAverageWaitTime(*m_lineup[num]);
			removePatientFromLineup(num);
		}
	}

	const Time PreTriage::getWaitTime(const Patient& p) const
	{
		int num = 0;
		int waitTime = 0;

		if (p.type() == 'C')
		{
			for (int i = 0; i < m_lineupSize; i++)
			{
				if (m_lineup[i]->type() == 'C')
				{
					num++;
				}
			}
			waitTime = num * m_averCovidWait;
		}
		else if (p.type() == 'T')
		{
			for (int i = 0; i < m_lineupSize; i++)
			{
				if (m_lineup[i]->type() == 'T')
				{
					num++;
				}
			}
			waitTime = num * m_averTriageWait;
		}
		return Time(waitTime);
	}

	void PreTriage::setAverageWaitTime(const Patient& p)
	{
		if (p.type() == 'C')
		{
			m_averCovidWait = ((getTime() - (Time)p) + (m_averCovidWait * (p.number() - 1))) / p.number();
		}
		else if (p.type() == 'T')
		{
			m_averTriageWait = ((getTime() - (Time)p) + (m_averTriageWait * (p.number() - 1))) / p.number();
		}
	}
	void PreTriage::removePatientFromLineup(int index)
	{
		removeDynamicElement(m_lineup, index, m_lineupSize);
		//delete m_lineup[index];
	}
	void PreTriage::load()
	{
		ifstream csvfile;
		csvfile.open(m_dataFilename);
		Patient* lineup = nullptr;
		char ch;
		cout << "Loading data..." << endl;
		csvfile >> m_averCovidWait;
		csvfile.ignore(1000, ',');
		csvfile >> m_averTriageWait;
		csvfile.ignore(1000, '\n');

		for (int i = 0; i < maxNoOfPatients && csvfile; i++)
		{
			ch = ' ';
			csvfile >> ch;
			csvfile.ignore(1000, ',');
			if (ch == 'C')
			{
				lineup = new CovidPatient();
			}
			else if (ch == 'T')
			{
				lineup = new TriagePatient();
			}
			if (lineup != nullptr)
			{
				lineup->fileIO(true);
				lineup->csvRead(csvfile);
				lineup->fileIO(false);
				m_lineup[i] = lineup;
				lineup = nullptr;
				m_lineupSize++;
			}
		}

		if (csvfile)
		{
			cout << "Warning: number of records exceeded " << maxNoOfPatients << endl;
		}
		if (m_lineupSize == 0)
		{
			cout << "No data or bad data file!\n\n";
		}
		else
		{
			cout << m_lineupSize << " Records imported...\n\n";
		}
	}
	int PreTriage::indexOfFirstInLine(char type) const
	{
		int index = -999;
		bool found = false;
		for (int i = 0; i < m_lineupSize && !found; i++)
		{
			if (m_lineup[i]->type() == type)
			{
				index = i;
				found = true;
			}
		}
		return index;
	}

}


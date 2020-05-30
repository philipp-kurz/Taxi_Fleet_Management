#include "CFleet.h"
#include "stdafx.h"

using namespace std;

CFleet::CFleet()
{	
	m_plan = new CPlanning;
}


CFleet::~CFleet()
{
	delete m_plan;
}

void CFleet::StartProject()
{
	setlocale(LC_CTYPE, "English");
	int selection=5;
	while (selection != 0) {
		system("CLS");
		cout << "Taxi Fleet Management\n=====================\n\n" << "1. Book a ride\n" << "2. Cancel a ride\n" << "3. Show taxi locations\n";
		cout << "4. Schedule\n" << "0. Quit\n" << "\nPlease select an option: ";

		string line;
		getline(cin, line);
		stringstream(line) >> selection;

		system("CLS");
		cout << "Taxi Fleet Management\n=====================\n";

		switch (selection) {
		case 1: // Book a ride
			int s_start, a_start, s_destination, a_destination, departure;
			cout << "\nBooking a ride!\n\n" << "Your location:\n";
			cout << "Avenue: ";
			getline(cin, line);
			stringstream(line) >> a_start;
			cout << "Street: ";
			getline(cin, line);
			stringstream(line) >> s_start;
			cout << "\nYour destination: \n";
			cout << "Avenue: ";
			getline(cin, line);
			stringstream(line) >> a_destination;
			cout << "Street: ";
			getline(cin, line);
			stringstream(line) >> s_destination;
			cout << "\nDeparture time: ";
			getline(cin, line);
			stringstream(line) >> departure;

			bool res;
			res = m_plan->bookRide(a_start, s_start, a_destination, s_destination, departure);
			if (res == false) cout << "\nUnfortunately, the booking was impossible!\n\n";
			break;
		case 2: // Cancel ride
			m_plan->printPlanning();
			cout << "\nWhich ride do you want to cancel?\n";
			cout << "Ride number: ";
			int rideNr;
			getline(cin, line);
			stringstream(line) >> rideNr;
			m_plan->deleteRide(rideNr);
			break;
		case 3: // Print taxi locations
			cout << "\nPoint in time: ";
			int timestamp;
			getline(cin, line);
			stringstream(line) >> timestamp;
			m_plan->printPositions(timestamp);
			system("pause");
			break;
		case 4: // Schedule
			m_plan->printPlanning();
			system("pause");
			break;
		case 0: // Quit
			break;
		default:
			cout << "\nPlease enter a valid number!\n";
			break;
		}
	}	
	
	system("PAUSE");
}
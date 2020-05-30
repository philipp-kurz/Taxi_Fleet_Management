#include "CPlanning.h"
#include "stdafx.h"
using namespace std;

CPlanning::CPlanning()
{
	m_general[0] = 6;
	CRide ** new_Rides = new CRide*[m_general[0]];
	new_Rides[1] = new CRide(1, 1, 1, 1, 1, 1, 0, 0);
	new_Rides[2] = new CRide(2, 2, 5, 5, 5, 5, 0, 0);
	new_Rides[3] = new CRide(3, 3, 7, 3, 7, 3, 0, 0);
	new_Rides[4] = new CRide(4, 4, 3, 8, 3, 8, 0, 0);
	new_Rides[5] = new CRide(5, 5, 9, 9, 9, 9, 0, 0);
	m_Rides = new_Rides;
}

CPlanning::~CPlanning() {
	delete[] m_Rides;
}

void CPlanning::printPlanning() {
	cout << "\nRideNr   Taxi from          to";
	cout << "               from  to\n";
	for (int i = 1; i <= m_general[0]-1; i++) {
		cout << setw(3) << m_Rides[i]->getRideNr() << " ";
		cout << setw(6) << m_Rides[i]->getTaxiNr() << "  ";
		cout << "  (A" << m_Rides[i]->getStartNode()->getAve() << ";";
		cout << "S" << m_Rides[i]->getStartNode()->getStr() << ")  -->";
		cout << "  (A" << m_Rides[i]->getEndNode()->getAve() << ";";
		cout << "S" << m_Rides[i]->getEndNode()->getStr() << ")        ";
		cout << setw(3) << m_Rides[i]->getStartTime() << " -- ";
		cout << setw(3) << m_Rides[i]->getEndTime();
		cout << endl;
	}
}

int ** CPlanning::deliverStatus(int timestamp) {
	
	int ** positions = 0;
	positions = new int*[5];
	for (int t = 0; t < 5; t++)
	{
		positions[t] = new int[4];
		for (int sec = 0; sec < 4; sec++) positions[t][sec] = 0;
	}
	
	for (int i = 0; i < 5; i++) positions[i][3] = 0;

	for (int ride = 1; ride < m_general[0]; ride++) {
		int taxiNr = m_Rides[ride]->getTaxiNr() - 1;
		if (timestamp >= m_Rides[ride]->getStartTime()
			&& timestamp < m_Rides[ride]->getEndTime()
			&& m_Rides[ride]->getStartTime() >= positions[taxiNr][3]) {
			positions[taxiNr][0] = m_Rides[ride]->getStartNode()->getStr();
			positions[taxiNr][1] = m_Rides[ride]->getStartNode()->getAve();
			positions[taxiNr][2] = 1;
			positions[taxiNr][3] = timestamp;
		}
		else if (timestamp == m_Rides[ride]->getEndTime()
			&& timestamp >= positions[taxiNr][3]) {
			positions[taxiNr][0] = m_Rides[ride]->getEndNode()->getStr();
			positions[taxiNr][1] = m_Rides[ride]->getEndNode()->getAve();
			positions[taxiNr][2] = 1;
			positions[taxiNr][3] = m_Rides[ride]->getEndTime();
		}
		else if (timestamp > m_Rides[ride]->getEndTime()
			&& timestamp > positions[taxiNr][3]) {
			positions[taxiNr][0] = m_Rides[ride]->getEndNode()->getStr();
			positions[taxiNr][1] = m_Rides[ride]->getEndNode()->getAve();
			positions[taxiNr][2] = 0;
			positions[taxiNr][3] = m_Rides[ride]->getEndTime();
		}
	}
	return positions;
}
void CPlanning::printPositions(int timestamp) {

	int** positions = deliverStatus(timestamp);

	cout << "\n\n\n\n\t\t   City plan\n\n\n";
	char str[] = "Street";
	for (int s = 1; s <= 9; s++) {
		if (s >= 2 && s <= 8) cout << str[s-2];
		else cout << " ";
		cout << "   " << s << "     ";

		for (int a = 1; a <= 9; a++) {
			bool isTaxiPos = false;
			for (int taxi = 4; taxi >= 0; taxi--) {
				if (positions[taxi][0] == s && positions[taxi][1] == a) {
					if (positions[taxi][2] == 1) cout << "*";
					else cout << " ";
					cout << taxi + 1;
					isTaxiPos = true;
					break;
				}
			}
			if (isTaxiPos == false) cout << " 0";
			cout << " ";
		}		
		cout << endl << endl;
	}
	cout << "           1  2  3  4  5  6  7  8  9\n\n";
	cout << "                     Avenue\n\n";
	cout << "* = Taxi currently driving\n\n";
	deleteStatus(positions);
}

void CPlanning::deleteStatus(int ** status) {
	for (int t = 0; t < 5; t++)
	{
		delete[] status[t];
	}
	delete[] status;

}

bool CPlanning::bookRide(int a_start, int s_start, int a_destination, int s_destination, int departure) {
	bool res = false;
	int ideal_Taxi = 0;
	int min_Detour = 100;
	int distance = abs(a_start - a_destination) + abs(s_start - s_destination);	

	for (int taxi = 0; taxi < 5; taxi++) {
		
		for (int ride = 1; ride < m_general[0]; ride++) {
			if (m_Rides[ride]->getTaxiNr() - 1 != taxi) continue;
			
			bool additional_Ride = false;
			int distance_towards = abs(m_Rides[ride]->getEndNode()->getAve() - a_start)
				+ abs(m_Rides[ride]->getEndNode()->getStr() - s_start);

			for (int f_afterwards = ride+1; f_afterwards < m_general[0]; f_afterwards++) {
				if (m_Rides[f_afterwards]->getTaxiNr() - 1 != taxi) continue;
				additional_Ride = true;
				int path_afterwards = abs(m_Rides[f_afterwards]->getStartNode()->getAve() - a_destination)
					+ abs(m_Rides[f_afterwards]->getStartNode()->getStr() - s_destination);

				if ((departure - m_Rides[ride]->getEndTime() > distance_towards) && 
					(m_Rides[f_afterwards]->getStartTime() - distance - path_afterwards > departure) &&
					(distance_towards + path_afterwards < min_Detour)) {
					
					ideal_Taxi = taxi;
					min_Detour = distance_towards + path_afterwards;
					res = true;
				}
			}
			if (additional_Ride == false) { 				
				if 	((departure - distance_towards > m_Rides[ride]->getEndTime()) &&
					(distance_towards < min_Detour)) {
					ideal_Taxi = taxi;
					min_Detour = distance_towards;
					res = true;
				}
				ride = m_general[0];
			}
		}
	}
	if (res == true) {
		m_general[0]++;
		CRide * new_Ride = new CRide(m_general[0]-1, ideal_Taxi+1,
			a_start, s_start, a_destination, s_destination, departure,departure + distance);

		CRide ** new_Rides = new CRide*[m_general[0]];
		for (int i = 0; i < m_general[0] - 1; i++) new_Rides[i] = m_Rides[i];
		new_Rides[m_general[0] - 1] = new_Ride;

		delete[] m_Rides;
		m_Rides = new_Rides;
	}
	return res;
}

void CPlanning::deleteRide(int rideNr) {
	int new_index = 1;	
	CRide ** new_Rides = new CRide*[m_general[0]-1];
	for (int i = 1; i < m_general[0]; i++) {
		if (m_Rides[i]->getRideNr() != rideNr) {
			new_Rides[new_index] = m_Rides[i];
			new_index++;
		}
	}
	delete[] m_Rides;
	m_Rides = new_Rides;
	m_general[0]--;
}
#pragma once
#include "CRide.h"


class CPlanning
{
public:
	CPlanning();
	~CPlanning();
	void printPlanning();
	void printPositions(int timestamp);
	bool bookRide(int a_start, int s_start, int a_destination, int s_destination, int departure);
	int ** deliverStatus(int timestamp);
	void deleteStatus(int ** status);
	void deleteRide(int rideNr);
protected:	
	
	CRide ** m_Rides;
	int m_general[1];
};


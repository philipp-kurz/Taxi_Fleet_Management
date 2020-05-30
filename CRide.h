#pragma once
#include "CNode.h"
#include "stdafx.h"

class CRide
{
public:
	CRide(int rideNr, int taxiNr, int a_start, int s_start, int a_destination, int s_destination, int startTime, int endTime);
	~CRide();
	int getRideNr();
	int getTaxiNr();
	CNode * getStartNode();
	CNode * getEndNode();
	int getStartTime();
	int getEndTime();
	
protected:
	int m_RideNr;
	int m_TaxiNr;
	CNode * m_Node_Start;
	CNode * m_Node_End;
	int m_Start_Time;
	int m_End_Time;
};


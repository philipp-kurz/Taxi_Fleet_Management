#include "CRide.h"

CRide::CRide(int rideNr, int taxiNr, int a_start, int s_start, int a_destination, int s_destination, int startTime, int endTime)
{
	m_RideNr = rideNr;
	m_TaxiNr = taxiNr;
	m_Node_Start = new CNode(a_start, s_start);
	m_Node_End = new CNode(a_destination, s_destination);
	m_Start_Time = startTime;
	m_End_Time = endTime;
}


CRide::~CRide()
{
}

int CRide::getRideNr() {
	return m_RideNr;
}

int CRide::getTaxiNr() {
	return m_TaxiNr;
}

CNode * CRide::getStartNode() {
	return m_Node_Start;
}
CNode * CRide::getEndNode() {
	return m_Node_End;
}

int CRide::getStartTime() {
	return m_Start_Time;
}
int CRide::getEndTime() {
	return m_End_Time;
}

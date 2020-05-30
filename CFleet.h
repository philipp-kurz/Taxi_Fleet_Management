#pragma once
#include "CPlanning.h"
class CFleet
{
public:
	CFleet();
	~CFleet();

	void StartProject();
protected:
	CPlanning * m_plan;
};


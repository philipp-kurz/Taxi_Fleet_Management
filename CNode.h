#pragma once
class CNode
{
public:
	CNode(int avenue, int street);
	~CNode();
	int getAve();
	int getStr();
protected:
	int m_Avenue;
	int m_Street;	
};


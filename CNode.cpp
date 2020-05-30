#include "CNode.h"

CNode::CNode(int avenue, int street) {
	m_Avenue = avenue;
	m_Street = street;
}

CNode::~CNode() {
}

int CNode::getAve() {
	return m_Avenue;
}

int CNode::getStr() {
	return m_Street;
}
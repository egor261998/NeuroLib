#include "stdafx.h"
#include "CLayer.h"
#include "CLayerList.h"

VOID CLayerList::CreateLayerList(INT iCount)
{
	this->m_iCount = iCount;
	this->m_pList = new class CLayer[iCount];
}

VOID CLayerList::Delete()
{
	for (INT i = 0; i < this->m_iCount; i++)
		this->m_pList[i].Delete();

	m_iCount = 0;

	delete this->m_pList;
	this->m_pList = NULL;
}

DOUBLE CLayerList::GetError()
{
	DOUBLE fError = 0.0;
	for (INT i = 1; i < this->m_iCount; i++)
		fError += this->m_pList[i].GetError();

	return fError;
}

DOUBLE CLayerList::GetErrorLast()
{
	return this->m_pList[this->m_iCount - 1].GetError();
}

#include "stdafx.h"
#include "CLayer.h"

VOID CLayer::Create(INT iCount)
{
	this->m_iCount = iCount;

	this->m_pValue = new DOUBLE[this->m_iCount];

	this->m_pValueError = new DOUBLE[this->m_iCount];

	for (INT i = 0; i < this->m_iCount; i++)
	{
		this->m_pValue[i] = 0.0;
		this->m_pValueError[i] = 0.0;
	}	
}

VOID CLayer::Delete()
{
	this->m_iCount = 0;

	delete this->m_pValue;
	this->m_pValue = NULL;

	delete this->m_pValueError;
	this->m_pValueError = NULL;
}

DOUBLE CLayer::GetError()
{
	DOUBLE fError = 0.0;
	for (INT i = 0; i < this->m_iCount; i++)
		fError += pow(this->m_pValueError[i],2);

	return fError;
}


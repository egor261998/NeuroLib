#include "stdafx.h"
#include "CMatrix.h"

VOID CMatrix::Create(INT iCountA, INT iCountB)
{
	this->m_iCountA = iCountA;
	this->m_iCountB = iCountB;
	this->m_pValue = new DOUBLE * [iCountA];

	srand((UINT)time(NULL));

	for (INT j = 0; j < iCountA; j++)
	{
		this->m_pValue[j] = new DOUBLE[iCountB];

		for (INT k = 0; k < this->m_iCountB; k++)
			this->m_pValue[j][k] = ((DOUBLE)(rand() % 20)-10) / 100.0;
	}
}

VOID CMatrix::Delete()
{
	for (INT j = 0; j < m_iCountA; j++)
		delete []this->m_pValue[j];

	this->m_iCountA = 0;
	this->m_iCountB = 0;

	delete this->m_pValue;
	this->m_pValue = NULL;
}

VOID CMatrix::Refresh()
{
	srand((UINT)time(NULL));

	for (INT i = 0; i < m_iCountA; i++)
		for (INT j = 0; j < m_iCountB; j++)
		this->m_pValue[i][j] = ((DOUBLE)(rand() % 20) - 10) / 100.0;
}

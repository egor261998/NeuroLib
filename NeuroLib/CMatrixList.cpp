#include "stdafx.h"
#include "CMatrix.h"
#include "CMatrixList.h"

VOID CMatrixList::CreateMatrixList(INT iCount)
{
	this->m_iCount = iCount;

	this->m_pList = new class CMatrix[this->m_iCount];
}

VOID CMatrixList::Delete()
{
	for (INT i = 0; i < this->m_iCount; i++)
		this->m_pList[i].Delete();

	this->m_iCount = 0;

	delete this->m_pList;
	this->m_pList = NULL;
}

VOID CMatrixList::Refresh()
{
	for (INT i = 0; i < this->m_iCount; i++)
		this->m_pList[i].Refresh();
}

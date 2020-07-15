#include "stdafx.h"
#include "Neuro.h"

CNeuro::CNeuro(Func Activation, Func Correct, DOUBLE fKf,BOOL bShift, INT iLayerCount, INT *iLayer)
{
	
	this->m_bShift = bShift;

	this->m_Layers.CreateLayerList(iLayerCount);

	for (INT i = 0; i < iLayerCount; i++)
	{
		if ((i < this->m_Layers.m_iCount - 1) && this->m_bShift)
		{
			FillLayer(i, iLayer[i] + 1);
			this->m_Layers.m_pList[i].m_pValue[iLayer[i]] = 1.0;
		}
		else
			FillLayer(i, iLayer[i]);
	}	
	this->m_Activation = Activation;
	this->m_Correct = Correct;
	this->m_fKf = fKf;	

	ReCalcMatrix();
}

CNeuro::~CNeuro()
{
	this->m_Layers.Delete();
	this->m_Matrix.Delete();
}

BOOL CNeuro::FillLayer(INT index, INT iCount)
{
	if (!(m_Layers.m_pList && index < m_Layers.m_iCount))
		return FALSE;

	m_Layers.m_pList[index].Create(iCount);
		
	return TRUE;
}

VOID CNeuro::ReCalcMatrix()
{
	if ((m_Layers.m_iCount - 1) > 0)
		m_Matrix.CreateMatrixList(m_Layers.m_iCount - 1);

	for (INT i = 0; i < m_Matrix.m_iCount; i++)
	{
		if (i < (m_Matrix.m_iCount - 1) && this->m_bShift)
			m_Matrix.m_pList[i].Create(m_Layers.m_pList[i].m_iCount, m_Layers.m_pList[i + 1].m_iCount - 1);
		else
			m_Matrix.m_pList[i].Create(m_Layers.m_pList[i].m_iCount, m_Layers.m_pList[i + 1].m_iCount);
	}
}

DOUBLE* CNeuro::CalcNeuro(INT argc, DOUBLE* ValueList)
{
	auto pLayerFirst = &m_Layers.m_pList[0];

	if (!this->m_bShift)
	{
		if (argc != pLayerFirst->m_iCount || !ValueList)
		{
			return NULL;
		}
	}
	else
	{
		if (argc != (pLayerFirst->m_iCount-1) || !ValueList)
		{
			return NULL;
		}
	}

	for (INT i = 0; i < argc; i++)
		pLayerFirst->m_pValue[i] = ValueList[i];

	for (INT i = 0; i < m_Matrix.m_iCount; i++)
	{
		auto pLayerA = &m_Layers.m_pList[i];
		auto pLayerB = &m_Layers.m_pList[i + 1];
		auto pMatrix = &m_Matrix.m_pList[i];
		for (INT j = 0; j < pMatrix->m_iCountB; j++)
		{
			DOUBLE fValue = 0.0;

			for (INT k = 0; k < pMatrix->m_iCountA; k++)
				fValue += pLayerA->m_pValue[k] * pMatrix->m_pValue[k][j];

			pLayerB->m_pValue[j] = m_Activation(fValue);
		}
	}

	return m_Layers.m_pList[m_Layers.m_iCount - 1].m_pValue;
}

INT CNeuro::GetCountAnswer()
{
	return m_Layers.m_pList[m_Layers.m_iCount - 1].m_iCount;
}

BOOL CNeuro::CalcNeuroError(INT argc, DOUBLE* ValueList)
{
	auto pLayerLast = &m_Layers.m_pList[m_Layers.m_iCount - 1];

	if (argc != pLayerLast->m_iCount || !ValueList)
		return FALSE;

	for (INT i = 0; i < argc; i++)
		pLayerLast->m_pValueError[i] = (ValueList[i] - pLayerLast->m_pValue[i]);

	for (INT i = m_Matrix.m_iCount - 1; i >= 1; i--)
	{
		auto pLayerA = &m_Layers.m_pList[i];
		auto pLayerB = &m_Layers.m_pList[i + 1];
		auto pMatrix = &m_Matrix.m_pList[i];
		int shift = 0;
		if (this->m_bShift)
			shift++;
		for (INT j = 0; j < pMatrix->m_iCountA- shift; j++)
		{
			DOUBLE fValue = 0.0;
			
			for (INT k = 0; k < pMatrix->m_iCountB; k++)
				fValue += pLayerB->m_pValueError[k] * pMatrix->m_pValue[j][k];

			pLayerA->m_pValueError[j] = fValue;
		}
	}

	return TRUE;
}

DOUBLE CNeuro::GetError()
{
	return this->m_Layers.GetError();
}

DOUBLE CNeuro::GetErrorLast()
{
	return this->m_Layers.GetErrorLast();
}

VOID CNeuro::CalcNeuroCorrect()
{
	for (INT i = m_Matrix.m_iCount - 1; i >= 0; i--)
	{
		auto pLayerA = &m_Layers.m_pList[i];
		auto pLayerB = &m_Layers.m_pList[i + 1];
		auto pMatrix = &m_Matrix.m_pList[i];

		for (INT j = 0; j < pMatrix->m_iCountB; j++)
			for (INT k = 0; k < pMatrix->m_iCountA; k++)			
				pMatrix->m_pValue[k][j] += m_fKf * pLayerB->m_pValueError[j] * m_Correct(pLayerB->m_pValue[j]) * pLayerA->m_pValue[k];
	}
}

CMatrix* CNeuro::GetMatrix(INT index)
{
	return &this->m_Matrix.m_pList[index];
}

CLayer* CNeuro::GetLayer(INT index)
{
	return &this->m_Layers.m_pList[index];
}

INT CNeuro::GetCountLayers()
{
	return this->m_Layers.m_iCount;
}

INT CNeuro::GetCountMatrix()
{
	return this->m_Matrix.m_iCount;
}

VOID CNeuro::RefreshMatrix()
{
	for (INT i = 0; i < m_Matrix.m_iCount; i++)
		m_Matrix.m_pList[i].Refresh();
}

VOID CNeuro::SetFKF(DOUBLE fKf)
{
	this->m_fKf = fKf;
}

INT CNeuro::GetMatrixWeightSize()
{
	INT iCount = 0;

	for (int i = 0; i < m_Matrix.m_iCount; i++)
	{
		CMatrix* pMatrix = GetMatrix(i);

		iCount += pMatrix->m_iCountA * pMatrix->m_iCountB;
	}

	return iCount;
}

VOID CNeuro::GetMatrixWeight(INT iSize, DOUBLE *pBuf)
{
	INT iCount = 0;

	for (int i = 0; i < m_Matrix.m_iCount; i++)
	{
		CMatrix* pMatrix = GetMatrix(i);
		
		for (int iCountA = 0; iCountA < pMatrix->m_iCountA; iCountA++)
		{
			for (int iCountB = 0; iCountB < pMatrix->m_iCountB; iCountB++)
			{
				if (iSize == iCount)
					return;

				pBuf[iCount] = pMatrix->m_pValue[iCountA][iCountB];
				iCount++;
			}
		}
	}
}

VOID CNeuro::SetMatrixWeight(INT iSize, DOUBLE* pBuf)
{
	INT iCount = 0;

	for (int i = 0; i < m_Matrix.m_iCount; i++)
	{
		CMatrix* pMatrix = GetMatrix(i);

		for (int iCountA = 0; iCountA < pMatrix->m_iCountA; iCountA++)
		{
			for (int iCountB = 0; iCountB < pMatrix->m_iCountB; iCountB++)
			{
				if (iSize == iCount)
					return;

				pMatrix->m_pValue[iCountA][iCountB] = pBuf[iCount];
				iCount++;
			}
		}
	}
}


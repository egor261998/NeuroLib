#pragma once
#include "CLayer.h"
#include "CMatrix.h"
#include "CLayerList.h"
#include "CMatrixList.h"
#include "CFunction.h"

class _declspec(dllexport) CNeuro
{
private:
	typedef DOUBLE(*Func)(DOUBLE x);

	CLayerList		m_Layers;
	CMatrixList		m_Matrix;
	Func			m_Activation;
	Func			m_Correct;
	DOUBLE			m_fKf;
	BOOL			m_bShift;

public:
	CNeuro(Func Activation, Func Correct, DOUBLE fKf, BOOL bShift, INT iLayerCount, INT* iLayer);
	~CNeuro();

private:
	BOOL			FillLayer(INT index, INT iCount);
	VOID			ReCalcMatrix();
public:
	INT				GetCountMatrix();
	CMatrix*		GetMatrix(INT index);

	INT				GetCountLayers();
	CLayer*			GetLayer(INT index);

	INT				GetCountAnswer();
	DOUBLE*			CalcNeuro(INT argc, DOUBLE* ValueList);

	BOOL			CalcNeuroError(INT argc, DOUBLE* ValueList);
	DOUBLE			GetError();
	DOUBLE			GetErrorLast();
	VOID			CalcNeuroCorrect();

	VOID			RefreshMatrix();

	VOID			SetFKF(DOUBLE fKf);
	
	INT				GetMatrixWeightSize();
	VOID			GetMatrixWeight(INT iSize, DOUBLE* pBuf);
	VOID			SetMatrixWeight(INT iSize, DOUBLE* pBuf);
};


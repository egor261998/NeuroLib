#pragma once
class _declspec(dllexport) CLayer
{
public:
	INT			m_iCount = 0;
	DOUBLE*		m_pValue = NULL;
	DOUBLE*		m_pValueError = NULL;

	VOID		Create(INT iCount);
	VOID		Delete();

	DOUBLE		GetError();
};


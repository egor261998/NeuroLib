#pragma once
class _declspec(dllexport) CLayerList
{
public:
	INT			m_iCount = 0;
	CLayer*		m_pList = NULL;

	VOID		CreateLayerList(INT iCount);
	VOID		Delete();

	DOUBLE		GetError();
	DOUBLE		GetErrorLast();
};


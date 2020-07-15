#pragma once
class _declspec(dllexport) CMatrixList
{
public:
	INT			m_iCount = 0;
	CMatrix*	m_pList = NULL;

	VOID		CreateMatrixList(INT iCount);
	VOID		Delete();

	VOID		Refresh();
};


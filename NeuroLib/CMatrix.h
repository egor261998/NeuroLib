#pragma once
class _declspec(dllexport) CMatrix
{
public:
	INT			m_iCountA = 0;
	INT			m_iCountB = 0;
	DOUBLE**	m_pValue = NULL;

	VOID		Create(INT iCountA, INT iCountB);
	VOID		Delete();

	VOID		Refresh();
};


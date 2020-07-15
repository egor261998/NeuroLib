#pragma once
class _declspec(dllexport) CFunction
{
public:
	static DOUBLE Sigmoid(DOUBLE x);
	static DOUBLE SigmoidDx(DOUBLE x);
	static DOUBLE Liner_01(DOUBLE x);
	static DOUBLE Liner_01Dx(DOUBLE x);
	static DOUBLE Bent_identity(DOUBLE x);
	static DOUBLE Bent_identityDx(DOUBLE x);
	static DOUBLE SoftPlus(DOUBLE x);
	static DOUBLE SoftPlusDx(DOUBLE x);
	static DOUBLE Softsign(DOUBLE x);
	static DOUBLE SoftsignDx(DOUBLE x);
	static DOUBLE Identical(DOUBLE x);
	static DOUBLE IdenticalDx(DOUBLE x);
	static DOUBLE Parabola(DOUBLE x);
	static DOUBLE ParabolaDx(DOUBLE x);
};


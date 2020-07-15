#include "stdafx.h"
#include "CFunction.h"

DOUBLE CFunction::Sigmoid(DOUBLE x)
{
	return 1.0 / (1.0 + exp(-x));
}

DOUBLE CFunction::SigmoidDx(DOUBLE x)
{
	return x * (1.0 - x);
}

DOUBLE CFunction::Liner_01(DOUBLE x)
{
	if (x > 1)
		return 1.0 + 0.01 * (x - 1);

	if (x < 0)
		return 0.01 * x;

	return x;
}

DOUBLE CFunction::Liner_01Dx(DOUBLE x)
{
	if (x > 1)
		return 0.01;

	if (x < 0)
		return 0.01;

	return 1;
}

DOUBLE CFunction::Bent_identity(DOUBLE x)
{
	return (sqrt(x * x + 1.0) - 1.0) / 2.0 + x;
}

DOUBLE CFunction::Bent_identityDx(DOUBLE x)
{
	return x/(2.0*sqrt(x*x+1))+1;
}

DOUBLE CFunction::SoftPlus(DOUBLE x)
{
	return log(1.0 + exp(x));
}

DOUBLE CFunction::SoftPlusDx(DOUBLE x)
{
	return 1.0 / (1.0 + exp(-x));
}

DOUBLE CFunction::Softsign(DOUBLE x)
{
	return x/(1.0+fabs(x));
}

DOUBLE CFunction::SoftsignDx(DOUBLE x)
{
	return  x / pow(1.0 + fabs(x),2);
}


DOUBLE CFunction::Identical(DOUBLE x)
{
	return x ;
}

DOUBLE CFunction::IdenticalDx(DOUBLE x)
{
	UNREFERENCED_PARAMETER(x);

	return  1.0;
}

DOUBLE CFunction::Parabola(DOUBLE x)
{
	return x*x;
}

DOUBLE CFunction::ParabolaDx(DOUBLE x)
{
	return  2.0*x;
}
#ifndef _HIPERBOLIC_H_
#define _HIPERBOLIC_H_
#include "../core/Function.h"
#include <math.h>

class HiperbolicFunction: public Function
{
private:
	double beta;
protected:
	
public:
	/**
	 * Constroi a função hiperbólica e informa a contante real associada ao 
	 * nível de inclinação da função
	 */
	HiperbolicFunction(double beta)
	{
		this->beta = beta;
	}
	
	virtual double execute(double x)
	{
		double ep = pow(M_E, - beta * x);
		return (1.0 - ep) / (1.0 + ep);
	}
	
	virtual const char* getName()
	{
		static char name[] = "hiperbolica";
		return name;
	}
};

#endif /* _HIPERBOLIC_H_ */
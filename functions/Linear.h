#ifndef _LINEAR_H_
#define _LINEAR_H_
#include "../core/Function.h"

class LinearFunction: public Function
{
private:
	
protected:
	
public:
	virtual double execute(double x)
	{
		return x;
	}
	
	
	virtual const char* getName()
	{
		static char name[] = "linear";
		return name;
	}
};

#endif /* _LINEAR_H_ */
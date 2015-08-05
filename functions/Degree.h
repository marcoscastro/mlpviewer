#ifndef _DEGREE_H_
#define _DEGREE_H_
#include "../core/Function.h"

class DegreeFunction: public Function
{
private:
	
protected:
	
public:
	virtual double execute(double x)
	{
		if(x >= 0)
			return 1;
		else
			return 0;
	}
	
	virtual const char* getName()
	{
		static char name[] = "degrau";
		return name;
	}
};

#endif /* _DEGREE_H_ */
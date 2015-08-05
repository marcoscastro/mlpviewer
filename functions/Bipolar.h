#ifndef _BIPOLAR_H_
#define _BIPOLAR_H_
#include "../core/Function.h"

class BipolarFunction: public Function
{
private:
	
protected:
	
public:
	virtual double execute(double x)
	{
		if(x >= 0)
			return 1;
		else
			return -1;
	}
	
	virtual const char* getName()
	{
		static char name[] = "bipolar";
		return name;
	}
};

#endif /* _BIPOLAR_H_ */
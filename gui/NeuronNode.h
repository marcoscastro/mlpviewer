#ifndef _NEURON_H_
#define _NEURON_H_
#include "Node.h"

class NeuronNode: public Node
{
private:
	int functionType;
	std::vector<Image*>& funcImgs;
protected:
public:
	enum FunctionType
	{
		Linear = 0,
		Degrau,
		Bipolar,
		Logistic,
		Hiperbolic
	};
public:
	NeuronNode(Image* img, std::vector<Image*>& funcImgs);
	virtual bool IsIn(const Point& p);
	virtual void draw(Graphics* g);
	
	inline int getFunctionType()
	{
		return functionType;
	}
	
	inline void setFunctionType(int functionType)
	{
		this->functionType = functionType;
	}
};

#endif /* _NEURON_H_ */
#ifndef _OUTPUTSIGNAL_H_
#define _OUTPUTSIGNAL_H_
#include "../core/Signal.h"
#include <iostream>

/**
 * Classe que imprime o sinal de saida de um neurônio
 * 
 */
class OutputSignal: public Signal
{
private:
	double value;
protected:
	virtual void receive(Connection* connection, double value)
	{
		this->value = value;
		std::cout << "Saida: " << value << std::endl;
	}
	virtual double getValue()
	{
		return value;
	}
public:
	OutputSignal()
	{
		value = 0;
	}
};

#endif /* _OUTPUTSIGNAL_H_ */
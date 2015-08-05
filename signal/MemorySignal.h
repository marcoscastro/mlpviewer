#ifndef _MEMORYSIGNAL_H_
#define _MEMORYSIGNAL_H_
#include "../core/Signal.h"

/**
 * Classe que armazena o sinal de saida de um neurônio
 * 
 */
class MemorySignal: public Signal
{
private:
	double value;
protected:
	virtual void receive(Connection* connection, double value)
	{
		this->value = value;
	}
	virtual double getValue()
	{
		return value;
	}
public:
	MemorySignal()
	{
		value = 0;
	}
	double getOutput()
	{
		return value;
	}
};

#endif /* _MEMORYSIGNAL_H_ */
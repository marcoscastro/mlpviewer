#ifndef _INPUTSIGNAL_H_
#define _INPUTSIGNAL_H_
#include "../core/Signal.h"

/**
 * Classe que representa um valor X do sinal de entrada de um neurônio
 * 
 */
class InputSignal: public Signal
{
private:
	double value;
protected:
	virtual void receive(Connection* connection, double value)
	{
		propagate(); //  discard received value
	}
	virtual double getValue()
	{
		return value;
	}
public:
	InputSignal(): value(value) {}
	
	InputSignal(double value)
	{
		setValue(value);
	}
	
	void setValue(double value)
	{
		this->value = value;
	}
};

#endif /* _INPUTSIGNAL_H_ */
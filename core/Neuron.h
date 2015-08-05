#ifndef _NEURON_H_
#define _NEURON_H_
#include "Signal.h"
#include "Function.h"
#include <vector>
#include <map>

class Neuron: public Signal
{
private:
	Function * function; // função de ativação do neurônio
	unsigned int connectedCount; // quantos sinais estão conectados a esse
	double u; // total do processamento
	unsigned int processedCount; // quantidade de sinais processados
protected:
	/**
	 * Soma todos as entradas, aplica a função e emite o sinal 
	 */
	virtual void receive(Connection* connection, double value);
	
	/**
	 * retorna o valor do processamento aplicado à função de ativação
	 */
	virtual double getValue()
	{
		return function->execute(u);
	}
	
	/**
	 * adiciona na lista de sinais de entrada
	 */
	virtual void onConnect(Signal* signal);
	
	/**
	 * remove da lista de sinais de entrada
	 */
	virtual void onDiconnect(Signal* signal);
public:
	/**
	 * Inicializa variáveis
	 */
	Neuron();
	
	/**
	 * Informa a função de ativação do neurônio
	 */
	inline void setFunction(Function * function)
	{
		this->function = function;
	}
	
	/**
	 * Retorna a função de ativação
	 */
	inline Function* getFunction()
	{
		return function;
	}
};

#endif /* _NEURON_H_ */
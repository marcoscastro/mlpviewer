#include "Neuron.h"
#include <algorithm>

Neuron::Neuron()
{
	function = NULL;
	u = 0;
	processedCount = 0;
	connectedCount = 0;
}

void Neuron::onConnect(Signal* signal)
{
	connectedCount++;
}

void Neuron::onDiconnect(Signal* signal)
{
	connectedCount--;
}

void Neuron::receive(Connection* connection, double value)
{
	double w  = connection->getWeight();
	// recebeu um novo sinal, então zera o processamento anterior
	if(processedCount == connectedCount)
	{
		processedCount = 0;
		u = 0;
	}
	u += value * w;
	processedCount++;
	// verifica se já processou todos os sinais
	if(processedCount == connectedCount)
		propagate();
}
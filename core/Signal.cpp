#include "Signal.h"
#include <stdlib.h>

void Signal::propagate()
{
	double value = getValue();
	// propagate
	std::list<Connection*>::iterator it;
	for(it = connections.begin(); it != connections.end(); it++)
	{
		(*it)->getDestination()->receive((*it), value);
	}
}

Signal::~Signal()
{
	std::list<Connection*>::iterator it;
	for(it = connections.begin(); it != connections.end(); it++)
		delete (*it);
}

void Signal::receive(Connection* connection, double value)
{
	// propagate
	std::list<Connection*>::iterator it;
	for(it = connections.begin(); it != connections.end(); it++)
	{
		(*it)->getDestination()->receive((*it), value);
	}
}

void Signal::connect(Signal * signal, double weight)
{
	Connection* connection = this->findConnection(signal);
	if(connection != NULL)
	{
		// já está conectado, atualiza somente o peso
		connection->setWeight(weight);
		return;
	}
	connections.push_back(new Connection(this, signal, weight));
	signal->onConnect(this);
}

void Signal::disconnect(Signal * signal)
{
	std::list<Connection*>::iterator it;
	for(it = connections.begin(); it != connections.end(); it++)
	{
		if((*it)->getDestination() == signal)
		{
			(*it)->getDestination()->onDiconnect(this);
			delete (*it);
			connections.erase(it);
			return;
		}
	}
}

Connection* Signal::findConnection(Signal* signal)
{
	std::list<Connection*>::iterator it;
	for(it = connections.begin(); it != connections.end(); it++)
	{
		if((*it)->getDestination() == signal)
			return *it;
	}
	return NULL;
}

void Signal::setWeight(Signal* signal, double weight)
{
	Connection* connection = this->findConnection(signal);
	if(connection == NULL)
		return;
	connection->setWeight(weight);
}

double Signal::getWeight(Signal* signal)
{
	Connection* connection = this->findConnection(signal);
	if(connection == NULL)
		return 0.0;
	return connection->getWeight();
}





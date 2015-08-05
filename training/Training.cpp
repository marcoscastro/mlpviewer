#include "Training.h"
#include <queue>
#include <iostream>

void Training::addSignal(Signal* signal)
{
	signals.push_back(signal);
}

void Training::initialize()
{
	std::map<Signal*, int> mp;
	std::queue<Signal*> qq;
	for(unsigned int i = 0; i < signals.size(); i++)
		qq.push(signals[i]);
	while(!qq.empty())
	{
		Signal* signal = qq.front();
		qq.pop();
		mp[signal]++;
		const std::list<Connection*>& ls = signal->getConnections();
		// neurônio da última camada
		if(ls.size() == 1 && mp[signal] == 1)
		{
			Connection * connection = (*ls.begin());
			if(connection->getDestination()->getConnections().size() == 0)
			{
				outputNeurons.push_back(signal);
				savedOutputs.push_back(connection->getDestination());
				MemorySignal * memSignal = new MemorySignal();
				outputs.push_back(memSignal);
				signal->disconnect(connection->getDestination());
				signal->connect(memSignal, 1.0);
			}
		}
		else
		{
			std::list<Connection*>::const_iterator it;
			for(it = ls.begin(); it != ls.end(); it++)
			{
				backList[(*it)->getDestination()].push_back(*it);
				qq.push((*it)->getDestination());
			}
		}
	}
}

void Training::execute(std::map<Signal*, double> expected)
{
	for(unsigned int i = 0; i < signals.size(); i++)
	{
		signals[i]->propagate();
	}
	for(unsigned int i = 0; i < outputs.size(); i++)
	{
		std::cout << "Saida " << (i + 1) << ": " << outputs[i]->getOutput() << std::endl;
		std::cout << "Esperado " << (i + 1) << ": " << expected[savedOutputs[i]] << std::endl;
	}
}

void Training::output()
{
	//TODO Generated function
}

void Training::finalize()
{
	for(unsigned int i = 0; i < outputs.size(); i++)
	{
		outputNeurons[i]->disconnect(outputs[i]);
		outputNeurons[i]->connect(savedOutputs[i], 1.0);
		delete outputs[i];
	}
	outputs.clear();
	outputNeurons.clear();
	savedOutputs.clear();
	backList.clear();
}

Training::~Training()
{
	finalize();
}


#include <stdio.h>
#include <stdlib.h>
#include "../core/Neuron.h"
#include "../functions/Degree.h"
#include "../functions/Bipolar.h"
#include "../functions/Logistic.h"
#include "../functions/Hiperbolic.h"
#include "../functions/Linear.h"
#include "../signal/InputSignal.h"
#include "../signal/OutputSignal.h"
#include "../training/Training.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

typedef struct input_t
{
	double value;
	double weight;
} input_t;

int test_training(int argc, char *argv[])
{
	int nCount, sgCount, sCount, T = 0;
	vector<InputSignal*> entradas;
	vector<OutputSignal*> saidas;
	vector<Neuron*> neuronios;
	while(scanf("%d %d %d", &nCount, &sgCount, &sCount) != EOF)
	{
		T++;
		printf("Teste: %s - %d\n", __FILE__, T);
		for(int i = 0; i < nCount; i++)
		{
			int n;
			string fn;
			cin >> n >> fn;
			Neuron * neuronio = new Neuron();
			neuronios.push_back(neuronio);
			Function * f = NULL;
			if(fn == "degrau")
				f = new DegreeFunction();
			else if(fn == "bipolar")
				f = new BipolarFunction();
			else if(fn == "logistica")
			{
				double beta;
				scanf("%lf", &beta);
				f = new LogisticFunction(beta);
			}
			else if(fn == "hiperbolica")
			{
				double beta;
				scanf("%lf", &beta);
				f = new HiperbolicFunction(beta);
			}
			else // linear
				f = new LinearFunction();
			neuronio->setFunction(f);
		}
		for(int i = 0; i < sgCount; i++)
		{
			InputSignal * signal;
			signal = new InputSignal();
			entradas.push_back(signal);
		}
		for(int i = 0; i < sCount; i++)
		{
			string acao;

			cin >> acao;
			if(acao == "entrada")
			{
				double peso;
				int n1, n2;
				cin >> n1 >> peso >> n2;
				Signal *signal = entradas[n1 - 1];
				signal->connect(neuronios[n2 - 1], peso);
			}
			else if(acao == "conectar")
			{
				double peso;
				int n1, n2;
				cin >> n1 >> peso >> n2;
				Signal *signal = neuronios[n1 - 1];
				signal->connect(neuronios[n2 - 1], peso);
			}
			else if(acao == "saida")
			{
				int n;
				cin >> n;
				Signal *signal = neuronios[n - 1];
				OutputSignal * output = new OutputSignal();
				signal->connect(output, 1.0);
				saidas.push_back(output);
			}
		}
		string s;
		int n;
		cin >> s >> n;
		Training * training = new Training();
		bool added = false;
		std::map<Signal*, double> saidas_esperadas;
		for(int i = 0; i < n; i++)
		{
			for(unsigned int j = 0; j < entradas.size(); j++)
			{
				double valor;
				cin >> valor;
				entradas[j]->setValue(valor);
				if(!added)
					training->addSignal(entradas[j]);
			}
			cin >> s; // saidas
			saidas_esperadas.clear();
			for(unsigned int j = 0; j < saidas.size(); j++)
			{
				double valor;
				cin >> valor;
				saidas_esperadas[saidas[j]] = valor;
			}
			if(!added)
				training->initialize();
			added = true;
			training->execute(saidas_esperadas);
		}
		printf("\n");

		for(unsigned int j = 0; j < neuronios.size(); j++)
		{
			delete neuronios[j]->getFunction();
			delete neuronios[j];
		}
		neuronios.clear();
		for(unsigned int j = 0; j < entradas.size(); j++)
			delete entradas[j];
		entradas.clear();
		for(unsigned int j = 0; j < saidas.size(); j++)
			delete saidas[j];
		saidas.clear();
	}
	return 0;
}

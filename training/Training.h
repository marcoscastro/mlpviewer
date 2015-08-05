#ifndef _TRAINING_H_
#define _TRAINING_H_
#include <vector>
#include <map>
#include "../core/Signal.h"
#include "../signal/MemorySignal.h"


/**
 * Classe que treina a rede neural
 */
class Training
{
private:
	std::vector<Signal*> signals;
	
	// processing
	std::vector<MemorySignal*> outputs;
	std::vector<Signal*> savedOutputs;
	std::vector<Signal*> outputNeurons;
	std::map<Signal*, std::list<Connection*> > backList;
protected:
	
public:
	~Training();
	/**
	 * Adiciona todos os sinais de entrada da rede
	 */
	void addSignal(Signal* signal);
	
	/**
	 * Monta as camadas para permitir a rápida atualização dos pesos
	 */
	void initialize();
	
	/**
	 * Executa o treinamento para a amostra atual
	 */
	void execute(std::map<Signal*, double>);
	
	/**
	 * Conclui o treinamento e restaura as saidas
	 */
	void finalize();
	
	/**
	 * Imprime a rede no formato do arquivo de entrada
	 */
	void output();
};

#endif /* _TRAINING_H_ */
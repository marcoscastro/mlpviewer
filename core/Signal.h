#ifndef _SIGNAL_H_
#define _SIGNAL_H_
#include <list>
#include <map>

class Signal;

/**
 * Classe ponte para conectar um sinal a outro com informação de peso
 */
class Connection
{
private:
	Signal * source;
	Signal * destination;
	double weight;
public:
	Connection(Signal * source, Signal * destination, double weight)
	: source(source), destination(destination), weight(weight)
	{}

	/**
	 * Obtém o sinal de origem
	 */
	inline Signal * getSource()
	{
		return source;
	}
	
	/**
	 * Obtém o sinal de destino
	 */
	inline Signal * getDestination()
	{
		return destination;
	}
	
	/**
	 * Obtém o peso da conexão
	 */
	inline double getWeight()
	{
		return weight;
	}
	
	/**
	 * Ajusta a peso da conexão
	 */
	inline void setWeight(double weight)
	{
		this->weight = weight;
	}	
};

/**
 * Classe que emite um sinal na rede
 */
class Signal
{
private:
	/**
	 * lista de conexões que saem deste sinal
	 */
	std::list<Connection*> connections;
protected:
	/**
	 * Recebe o sinal de uma conexão
	 */
	virtual void receive(Connection* connection, double value);
	
	/**
	 * Devolve o valor calculado do sinal
	 */
	virtual double getValue() = 0;
	
	/**
	 * Evento de que algum sinal se conectou a esse
	 */
	virtual void onConnect(Signal * signal){}
	
	/**
	 * Evento em que um sinal foi desconectado
	 */
	virtual void onDiconnect(Signal * signal){}
public:
	virtual ~Signal();
	
	/**
	 * Propaga o sinal para a próxima conexão
	 */
	void propagate();
	
	/**
	 * Conecta esse sinal a outro 
	 */
	void connect(Signal * signal, double weight);
	
	/**
	 * Desconecta esse sinal de outro informado
	 */
	void disconnect(Signal * signal);
	
	/**
	 * Procura uma conexão ao sinal informado
	 */
	Connection* findConnection(Signal * signal);
	
	/**
	 * Obtém a lista com todas as conexões de saida desse sinal
	 */
	inline const std::list<Connection*>& getConnections()
	{
		return connections;
	}
	
	/**
	 * Ajusta o peso de uma conexão
	 */
	void setWeight(Signal* signal, double weight);
	
	/**
	 * Obtém o peso de uma conexão
	 */
	double getWeight(Signal* signal);
};

#endif /* _SIGNAL_H_ */
#ifndef _FUNCTION_H_
#define _FUNCTION_H_

class Function
{
private:
	
protected:
	
public:
	/**
	 * Executa a função e retorna o valor calculado usando a 
	 * variável x
	 */
	virtual double execute(double x) = 0;
	virtual const char* getName() = 0;
};

#endif /* _FUNCTION_H_ */
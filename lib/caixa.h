// A classe Caixa simulará uma caixa tipo supermercado

#ifndef CAIXA_H
#define CAIXA_H


class Caixa 
{
	public:
		Caixa(double = 10000);

		double getSaldo();
		void setSaldo(double);

	private:
		double saldo;

};




#endif
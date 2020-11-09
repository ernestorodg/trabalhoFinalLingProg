// A classe Caixa simulará uma caixa tipo supermercado

#ifndef CAIXA_H
#define CAIXA_H


#include "dataBank.h"

class Caixa 
{
	public:
		Caixa(double = 10000);
		~Caixa();

		double getSaldo();
		void setSaldo(double);
		int getProduct(std::string);
		int cancelLastProduct();

	 	void executeDataBaseCommand(int);


	private:
		double saldo;
		DataBank bancoDados;
		// std::vector <std::vector<int>> items; 
		std::vector<std::vector<int>> items; 

};




#endif
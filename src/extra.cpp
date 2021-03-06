// Em extra.cpp se definem algumas funcoes usadas como auxiliares.
#include <iostream>
#include <string>
#include <vector>


#include "extra.h"


// Recebe uma string qualquer.
// Retorna true se a string recebida for um numero (sem espaçamentos no meio). Caso contrario retorna false.
bool isNumeric(std::string str) {
   for (unsigned int indice_auxiliar = 0; indice_auxiliar < str.length(); indice_auxiliar++)
      if (isdigit(str[indice_auxiliar]) == false)
         return false; 
   return true;
};




// Função recebe uma string e separa em números e strings
// devolve um vetor de strings
// Devolve o número na primeira posição e o resto da string na segunda
// Apaga os espaçamentos
std::vector<std::string> separateNumberFromString(std::string input)
{
	// Apaga todos os espaçamentos
	std::string product = input;
	std::string amount = "";
	std::string auxiliar = "";
	std::vector <std::string> output(2);


	while (product.find(" ") != std::string::npos)
		product.erase(product.find(" "), 1);	

	amount = product;

	// Apago todos os números
	for (unsigned int auxiliarIndex = 0; auxiliarIndex < product.length(); auxiliarIndex++)
	{		

		if (isdigit(product.at(auxiliarIndex)))
		{
			product.erase(auxiliarIndex, 1);
			auxiliarIndex--;
		}

	}

	// elimino a possibilidade de ter uma entrada do tipo "25 PRO25DUTO "
	if (input.find(product) == std::string::npos)
	{
		output[0] = "";
		output[1] = "";

		return (output);
	}
	else 	// corta product da string de entrada, sobrará somente números
		amount = amount.erase(amount.find(product), product.length());



	// trata uma entrada do tipo PRODUTO 25 25
	if (input.find(amount) == std::string::npos)
	{
		output[0] = "";
		output[1] = "";

		return (output);
	}


	output[0] = amount;
	output[1] = product;

	return (output);
} ;


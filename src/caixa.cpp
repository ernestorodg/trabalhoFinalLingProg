// Implementação da classe Caixa

#include <vector>

#include "caixa.h"
#include "interface.h"	
#include "menu.h"
#include "extra.h"


Caixa::Caixa(double novoSaldo) : saldo(novoSaldo), bancoDados("meuBanco.db"), items(0) {}
Caixa::~Caixa()
{
	bancoDados.closeDataBank();
}


double Caixa::getSaldo() { return saldo; };
void Caixa::setSaldo(double novoSaldo) {saldo = novoSaldo;};


// Recebe a entrada do caixa, que deve ser uma string na forma " QUANTIDADE PRODUTO"
// Retorna 0 se ocorreu certo
// Retorna -1 se a entrada for inválida
int Caixa::getProduct(std::string input)
{
	int myID = 0;
	std::vector <std::vector<int>> auxiliarVector; 
	std::vector <int> tupla(2);
	// Vetor que receberá a quantidade do produto e o nome do produto
	std::vector <std::string> myInput(2);
	myInput = separateNumberFromString(input);

	if (myInput[0] == "")
	{
		if (myInput[1] == "")
			return (-1);
		else 
			tupla[1] = 1;
	}
	else
	{
		if (myInput[1] != "")
		{
			tupla[1] = stoi(myInput[0]); // Atribuindo a quantidade inserida
		}
		else 
			return (-1);
	}


	myID =  bancoDados.lookForProduct(myInput[1]);

	if (myID == 0) 
	{
		// produto nao existe
		std::cout << "Erro: O produto não foi encontrado." << std::endl;
		return (0);
	}

	// Avaliar a quantidade do produto disponível:
	if (bancoDados.getProductAmount(myID) < tupla[1])
	{
		// produto nao existe
		std::cout << "Erro: A quantidade exigida é maior do que a disponível." << std::endl;
		return (0);
	}


	else // produto existe
	{
		tupla[0] = myID;
		bancoDados.updateDataBank(2, myID, std::to_string(bancoDados.getProductAmount(myID) - tupla[1]));


		bancoDados.showPropertiesByID(myID);
		std::cout << std::endl;
		saldo += (bancoDados.getProductPrice(myID) * tupla[1]);
		items.push_back(tupla); // Guarda a quantidade e o produto que acabaram de ser compradas
		// auxiliarVector.push_back(amount);
	}


	return (0);
	// se tem, printa os outros detalhes e atualiza o saldo
	// se nao tem, printa que nao tem

};

int Caixa::cancelLastProduct()
{
	// Consulta o banco de dados para ver se tem esse produto
	int myID = 0;

	if (items.size() == 0)
	{
		std::cout << "Erro: Nenhum item foi comprado." << std::endl;
		return (-1);
	}	

	myID =  items[items.size() - 1][0];

	if (myID == 0) // produto nao existe
		std::cout << "Erro: O produto não foi encontrado." << std::endl;

	else // produto existe
	{
		// atualizar produto
		saldo -= bancoDados.getProductPrice(myID) * items[items.size() - 1][1];
		// atualizar banco de dados
		bancoDados.updateDataBank(2, myID, std::to_string(bancoDados.getProductAmount(myID) 
															+ items[items.size() - 1][1]));

		items.pop_back();

	}

	return (0);

};



void Caixa::executeDataBaseCommand(int numericInput)
{
	std::string literalInput;
	std::string inputDataBank;
	Menu menu;
	int inputNumericID;
	int auxiliar = numericInput;


	while (auxiliar != -1)
	{
		// ++++++++++++++++++++++++++++++++++
		// Menu:

		switch (auxiliar){
			case 1:					
				bancoDados.showDataBank();
				break;

			case 2:
				std::cout << "Digite o nome do produto procurado: ";
				literalInput = menu.defineLiteralInput();
				auxiliar =  bancoDados.lookForProduct(literalInput);

				if (auxiliar == 0) // produto nao existe
				{
					// criar um novo produto: requer pedir ao usuário os dados do produto
					std::cout << "O produto não foi encontrado." << std::endl;


				}					
				else // produto existe
				{
					// atualizar produto
					std::cout << "Campos: 1 - Nome; 2 - Quantidade ; 3 - Descrição ; 4 - Preço" << std::endl;
					std::cout << "Campo que deseja atualizar: ";
					numericInput = menu.defineNumericInput();
					std::cout << std::endl;
					std::cout << "Novo valor: ";
					inputDataBank = menu.defineLiteralInput();
					std::cout << std::endl;
					bancoDados.updateDataBank(numericInput, auxiliar, inputDataBank);

				}


				break;

			case 3:
				std::cout << "Digite o nome do produto a ser adicionado: ";
				literalInput = menu.defineLiteralInput();
				auxiliar =  bancoDados.lookForProduct(literalInput);

				if (auxiliar == 0) // produto nao existe
				{
					std::cout << "O produto " << literalInput << " não foi encontrado." << std::endl;
					std::cout << "Criando novo produto..." << std::endl;
					// criar um novo produto: requer pedir ao usuário os dados do produto
					
					// ID NOME QUANTIDADE DESCRICAO PRECO

					inputNumericID = bancoDados.getFirstEmptyID();
					bancoDados.insertOnDataBank(std::to_string(inputNumericID),
																		literalInput , 
																"0" , "0" , "0");
					std::cout << "Digite o preço: ";
					numericInput = menu.defineNumericInput();
					bancoDados.updateDataBank(4, inputNumericID, std::to_string(numericInput));

					std::cout << "Digite a descrição do produto: ";
					literalInput = menu.defineLiteralInput();
					bancoDados.updateDataBank(3, inputNumericID, literalInput);

					std::cout << "Digite a quantidade do produto que será adicionada: ";
					numericInput = menu.defineNumericInput();
					bancoDados.updateDataBank(2, inputNumericID, std::to_string(numericInput));


				}					
				else // produto existe
				{
					std::cout << "Em quanto vai aumentar o estoque? ";
					numericInput = menu.defineNumericInput();
					std::cout << std::endl;
					bancoDados.updateDataBank(2, 
										auxiliar, 
						std::to_string(bancoDados.getProductAmount(auxiliar) + numericInput));



				}
				break;
			case 4:
				// std::cout << "Digite o ID do produto a ser deletado: ";
				// inputNumericID = menu.defineNumericInput();

				std::cout << "Digite o nome do produto a ser removido: ";
				literalInput = menu.defineLiteralInput();
				auxiliar =  bancoDados.lookForProduct(literalInput);


				if (auxiliar == 0) // produto nao existe
				{
					std::cout << "O produto " << literalInput << " não foi encontrado." << std::endl;
				}					
				else // produto existe
				{
					bancoDados.deleteRowFromDataBank(auxiliar);

				}

				break;

			default:
				break;
		};
	

	menu.showDataBankMenu();

	auxiliar = menu.defineNumericInput();

	};

};


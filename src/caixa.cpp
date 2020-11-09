// Implementação da classe Caixa

#include <vector>

#include "caixa.h"
#include "interface.h"	
#include "menu.h"


Caixa::Caixa(double novoSaldo) : saldo(novoSaldo), bancoDados("meuBanco.db"), items(0) {}

double Caixa::getSaldo() { return saldo; };
void Caixa::setSaldo(double novoSaldo) {saldo = novoSaldo;};



void Caixa::getProduct(std::string productName)
{
	// Consulta o banco de dados para ver se tem esse produto
	int myID = 0;
	std::vector<int> auxiliarVector(2); 



	myID =  bancoDados.lookForProduct(productName);

	if (myID == 0) // produto nao existe
		std::cout << "Erro: O produto não foi encontrado." << std::endl;

	else // produto existe
	{
		// atualizar produto
		bancoDados.showPropertiesByID(myID);
		std::cout << std::endl;
		saldo += bancoDados.getProductPrice(myID);
		items.push_back(myID);
		auxiliarVector.push_back(myID);
		// auxiliarVector.push_back(amount);
	}

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

	myID =  items[items.size() - 1];

	if (myID == 0) // produto nao existe
		std::cout << "Erro: O produto não foi encontrado." << std::endl;

	else // produto existe
	{
		// atualizar produto
		saldo -= bancoDados.getProductPrice(myID);
		items.pop_back();
		// auxiliarVector.push_back(amount);
	}

	return (0);

};



void Caixa::executeDataBaseCommand(int numericInput)
{
	std::string inputCashier;
	std::string inputDataBank;
	Menu menu;
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
				inputCashier = menu.defineLiteralInput();
				auxiliar =  bancoDados.lookForProduct(inputCashier);

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
				inputCashier = menu.defineLiteralInput();
				auxiliar =  bancoDados.lookForProduct(inputCashier);

				if (auxiliar == 0) // produto nao existe
				{
					std::cout << "O produto " << inputCashier << " não foi encontrado." << std::endl;
					std::cout << "Criando novo produto..." << std::endl;
					// criar um novo produto: requer pedir ao usuário os dados do produto
					
					bancoDados.insertOnDataBank( "100",
											// std::to_string(bancoDados.getFirstEmptyID()), 
																		 inputCashier , 
																		 	"0" , "0" , "0");


				}					
				else // produto existe
				{
					// atualizar produto
					// bancoDados.updateDataBank()
					// bancoDados.updateDataBank(teste, auxiliar, );

				}
				break;


			default:
				break;
		};
	

	menu.showDataBankMenu();

	auxiliar = menu.defineNumericInput();

	};

};


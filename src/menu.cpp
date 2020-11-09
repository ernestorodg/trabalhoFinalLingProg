// Implementação da classe Menu
#include <iostream>
#include <iomanip>


#include "menu.h"
#include "extra.h"


#define ESPACAMENTO						10

Menu::Menu() {}


void Menu::showCashierMenu() 
{
		std::cout << "EXIT Para sair do programa."
				  << "		DATABASE Para acessar o banco de dados."
				  << "		CANCEL Para cancelar o último produto." 
				  << std::endl;
		std::cout << "Digite o nome do produto para a compra" << std::endl;

};



void Menu::showDataBankMenu() 
{
		std::cout << "1: Mostrar todos os produtos." << std::endl;
		std::cout << "2: Modificar um produto." << std::endl;
		std::cout << "3: Adicionar produto ao estoque." << std::endl;
		std::cout << "2: Modificar o preço de um produto." << std::endl;
		std::cout << "3: ." << std::endl;
		std::cout << "Outros: Sair" << std::endl;
		std::cout << "Escolha alguma das opcoes acima a ser efetuada: ";

};

// Espera o usuário digitar a entrada e trata ela segundo alguma verificação
// devolve
int Menu::defineNumericInput()
{
	std::getline(std::cin, entrada);
	
	// Eh feita uma verificao caso o usuario coloque uma string ou não!
	// verifica se a entrada eh um numero
	if (isNumeric(entrada))
		return std::stoi(entrada);
	else 
		return (-1);
}

std::string Menu::defineLiteralInput()
{
	std::getline(std::cin, entrada);
	
	// Eh feita uma verificao caso o usuario coloque uma string ou não!
	return (entrada);
}


void Menu::teste()
{
	std::cout << "Isto eh um teste" << std::endl;
};







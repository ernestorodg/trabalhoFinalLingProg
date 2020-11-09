#include <iostream> 
#include <sqlite3.h> 
#include <string> 
#include <iomanip>
#include <fstream>


#include "dataBank.h"
#include "extra.h"
#include "menu.h"
#include "caixa.h"
#include "interface.h"

#define OK   							0


int main() 
{ 
	int auxiliar = 0; 	// Guarda o valor a ser usado no menu
	std::string inputCashier; 	// Guarda o valor que o usuario colocar
	std::string inputDataBank;
	int numericInputDataBank = 0;

	Menu menu;
	Caixa caixa(10000);

	// Abre o banco de dados meuBanco.db
	DataBank meuBanco("meuBanco.db");

	// meuBanco.updateDataBank();
	// meuBanco.deleteRowFromDataBank();

 //    Interface::cleanScreen();
 //    Interface::saveScreen();	
 //    Interface::cleanScreen();
 //   	Interface::setCursorToBegin();
	// std::cout << "Testando ANSI: ";
	// inputCashier = menu.defineLiteralInput();
 // 	std::cout << std::endl;
 //    Interface::restoreScreen();

	// Limpa a tela

    Interface::cleanScreen();
   	Interface::setCursorToBegin();
    menu.showCashierMenu();

	while (inputCashier != "EXIT")
	{
		// Vou tentar colocar isso aqui em outro lugar usando ansi
	    std::cout << "\n\t\t\t\t\tSaldo atual: " << caixa.getSaldo() << std::endl;

		inputCashier = menu.defineLiteralInput();

		if (inputCashier  == "CANCEL")
		{
			// cancela o ultimo produto
			caixa.cancelLastProduct();
			std::cout << "CANCEL" << std::endl;
		}
		else if (inputCashier == "EXIT")
		{
			// Sai do programa, fecha o banco de dados
		}
		else if (inputCashier == "DATABASE")
		{
			Interface::saveCursorPosition();
		    Interface::saveScreen();	
		    Interface::cleanScreen();
		   	Interface::setCursorToBegin();

		   	menu.showDataBankMenu();

			numericInputDataBank = menu.defineNumericInput();
		 	std::cout << std::endl;

		 	caixa.executeDataBaseCommand(numericInputDataBank);

		    Interface::restoreScreen();
			Interface::restoreCursorPosition();

		}
		else // Enquanto nenhuma das opções acima for escolhida o programa pede o produto
		{
			auxiliar = caixa.getProduct(inputCashier);		
			if (auxiliar == -1)
				std::cout << "Erro: entrada inválida. Por favor, certifique-se de que "
						  << "a entrada é do tipo \"PRODUTO QUANTIDADE\" ou \"QUANTIDADE PRODUTO\"" 
						  << std::endl;
		}
	}




	// // meuBanco.closeDataBank();



	return (OK);
} 
	

// Funcoes do programa

// 2. Adicionar produto ao estoque: O usuário define um produto e uma quantidade a ser adicionada
// ao estoque. Caso o produto não exista no banco de dados, o usuário será convidado a inserir
// um preço e código identificador do produto para que ele possa ser adicionado ao estoque.
// O banco de dados será modificado através de uma função em SQL, segundo os parâmetros
// passados pelo usuário. O retorno será na forma de uma mensagem de confirmação de registro
// ou erro. Após a confirmação, o produto poderá ser visualizado por meio da Opção 1.


// 3. Remover quantidade de um determinado produto: O usuário passa um código de produto e
// uma quantidade a ser retirada do banco de dados, sem afetar o fluxo de caixa. O programa em
// C++ trata a entrada e chama uma função SQL para modificar o banco de dados. O ambiente
// SQL retorna uma confirmação ou um erro que será repassada ao usuário através da interface
// em C++.

// 4. Deletar registro de produto do estoque: o usuário entra com um código de produto que será
// repassado a uma função em SQL que removerá o produto selecionado do banco de dados. O
// usuário será informado do sucesso ou falha da operação e, quando necessário, receberá um
// aviso de erro.

// 5. Realizar venda: o programa recebe do usuário um identificador e uma quantidade para cada
// produto da venda. Caso todos os identificadores e quantidades correspondam com o que existe
// no estoque, as quantidades serão debitadas do banco de dados e o valor da transação será
// creditada no caixa. O programa em C++ tratará as entradas e chamará uma função SQL
// para realizar as modificações no banco de dados. O ambiente SQL retorna uma confirmação
// ou erro que por sua vez serão tratados no programa em C++ e exibidos ao usuário.
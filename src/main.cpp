#include <iostream> 
#include <sqlite3.h> 
#include <string> 
#include <iomanip>
#include <fstream>


#include "dataBank.h"
#include "extra.h"
#include "menu.h"
#include "caixa.h"

#define OK   							0


int main() 
{ 
	int auxiliar = 0;
	int escolhaNumerica = 0; 	// Guarda o valor a ser usado no menu
	std::string escolhaLiteral; 	// Guarda o valor que o usuario colocar
	std::string segundaEscolhaLiteral;

	Menu menu;

	// Abre o banco de dados meuBanco.db
	DataBank meuBanco("meuBanco.db");


	meuBanco.insertOnDataBank("6", "BORRACHA", "5", "UTEIS", "1");
	// meuBanco.updateDataBank();


	std::vector <std::string> vetorAuxiliar;
	// vetorAuxiliar= meuBanco.getRows();

	meuBanco.getFirstEmptyID();

	meuBanco.showDataBank();

	// meuBanco.deleteRowFromDataBank();


	// meuBanco.closeDataBank();
	while (escolhaNumerica != -1)
	{
		// ++++++++++++++++++++++++++++++++++
		// Menu:
		std::cout << "\n\n\n\n\n\n\n" << std::endl;


		menu.showMenu();
		escolhaNumerica = menu.defineNumericInput();
		switch (escolhaNumerica){
			case 1:					
				meuBanco.showDataBank();
				break;

			case 2:
				std::cout << "Digite o nome do produto procurado: ";
				escolhaLiteral = menu.defineLiteralInput();
				auxiliar =  meuBanco.lookForProduct(escolhaLiteral);

				if (auxiliar == 0) // produto nao existe
				{
					// criar um novo produto: requer pedir ao usuário os dados do produto


				}					
				else // produto existe
				{
					// atualizar produto
					std::cout << "Campos: 1 - Nome; 2 - Quantidade ; 3 - Descrição ; 4 - Preço" << std::endl;
					std::cout << "Campo que deseja atualizar: ";
					escolhaNumerica = menu.defineNumericInput();
					std::cout << std::endl;
					std::cout << "Novo valor: ";
					segundaEscolhaLiteral = menu.defineLiteralInput();
					std::cout << std::endl;
					meuBanco.updateDataBank(escolhaNumerica, auxiliar, segundaEscolhaLiteral);

				}


				break;

			case 3:
				// std::cout << "Digite o nome do produto procurado: ";
				// std::getline(std::cin, escolhaLiteral);
				// auxiliar =  meuBanco.lookForProduct(escolhaLiteral);

				// if (auxiliar == 0) // produto nao existe
				// {
				// 	int teste = 0;

				// 	// criar um novo produto: requer pedir ao usuário os dados do produto
				// 	std::cout << "Nome - 1 ; Quantidade - 2 ; Descrição - 3 ; Preço - 4" << std::endl;
				// 	std::cout << "Digite o campo a ser mudado, entre os citados acima: ";
				// 	std::getline(std::cin, escolhaLiteral);

				// 	// Testando a inserção:
				// 	if (isNumeric(escolhaLiteral))
				// 		teste = std::stoi(escolhaLiteral);
				// 	else 
				// 	{
				// 		std::cout << "O valor inserido não é permitido...Retornando ao menú" 
				// 				  << std::endl;
					
				// 		break;
				// 	}

				// 	meuBanco.updateDataBank(teste, auxiliar, );



				// }					
				// else // produto existe
				// {
				// 	// atualizar produto
				// 	// meuBanco.updateDataBank()
				// }
				break;


			default:
				break;
		};
	};

	// +++++++++++++++++++++++++++++
	// Fim do programa


	std::cout << "Saindo do programa..." << std::endl;

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
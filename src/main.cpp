#include <iostream> 
#include <sqlite3.h> 
#include <string> 
#include <iomanip>
#include <fstream>


#include "dataBank.h"
#include "extra.h"


#define OK   							0


int main() 
{ 
	int escolhaFinal = 0; 	// Guarda o valor a ser usado no menu
	std::string escolha; 	// Guarda o valor que o usuario colocar



	// Abre o banco de dados meuBanco.db
	DataBank meuBanco("meuBanco.db");



	// meuBanco.createTable();


	// meuBanco.insertOnDataBank();

	meuBanco.showDataBank();

	// meuBanco.deleteRowFromDataBank();


	// meuBanco.closeDataBank();
	while (escolhaFinal != -1)
	{
		// ++++++++++++++++++++++++++++++++++
		// Menu:
		std::cout << "\n\n\n\n\n\n\n" << std::endl;



		std::cout << "1: Mostrar todos os produtos." << std::endl;
		std::cout << "2: ." << std::endl;
		std::cout << "3: ." << std::endl;
		std::cout << "Outros: Sair" << std::endl;
		std::cout << "Escolha alguma das opcoes acima a ser efetuada: ";
		std::getline(std::cin, escolha);


		// Eh feita uma verificao caso o usuario coloque uma string:
		if (isNumeric(escolha))
			escolhaFinal = std::stoi(escolha);
		else 
			escolhaFinal = -1;


		// +++++++++++++++++++++++++++++++++
		// Acoes que o programa ira executar
    

		std::cout << "\n\n\n\n\n\n\n" << std::endl;

		switch (escolhaFinal){
			case 1:					
				meuBanco.showDataBank();
				break;

			case 2:


				break;

			case 3:

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

// 1 Exibir o estoque de produtos: Exibe todos os itens registrados, códigos, preços e quantidades
// disponíveis. Uma função em SQL é executada e retornará uma estrutura de dados ao programa
// em C++. O programa em C++ exibe a estrutura de dados.


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
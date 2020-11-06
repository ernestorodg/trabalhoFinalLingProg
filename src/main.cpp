#include <iostream> 
#include <sqlite3.h> 
#include <string> 
#include <iomanip>
#include <fstream>


#include "dataBank.h"

using namespace std; 



// // A função callback eh executada para cada linha na tabela
// static int callback(void* data, int argc, char** argv, char** azColName) 
// { 
// 	// fprintf(stderr, "%s: ", (const char*)data); 
// 	std::cout << "Essa função foi chamada" << std::endl;

// 	for (int indice_auxiliar = 0; indice_auxiliar < argc; indice_auxiliar++) 
// 	{ 
// 		// azColName eh um vetor de strings que contém o nome do atributo (coluna) do banco de dados

// 		// argv eh um vetor de strings que contém o valor desse atributo na linha que está sendo lida
// 		// printf("%s = %s\n", azColName[indice_auxiliar], argv[indice_auxiliar] ? argv[indice_auxiliar] : "NULL"); 

// 		std::cout << std::setw(10) << azColName[indice_auxiliar] 
// 					<< std::setw(10) << argv[indice_auxiliar]
// 					<< std::endl;
// 	} 

// 	printf("\n"); 
// 	return 0; 
// } 



int main() 
{ 
	// sqlite3* DB; // Crio o objeto banco de dados

	DataBank meuBanco("meuBanco.db");

	meuBanco.createTable();


	meuBanco.insertOnDataBank();

	meuBanco.showDataBank();

	meuBanco.deleteRowFromDataBank();


	meuBanco.closeDataBank();


	// char* messaggeError; //
	// int exit = sqlite3_open("meuBanco.db", &DB); // abro o banco de dados, se nao existe crio



	// string line;
	// string myQuery = "";
	// ifstream myfile ("./sqlCmd/create_table.txt");
	// if (myfile.is_open())
	// {
	// 	while ( getline (myfile,line) )
	// 	{
	// 		myQuery += line;
	// 	}
	// myfile.close();
	// }
	// else cout << "O arquivo não pôde ser aberto." << endl; 
	// // myQuery += '\n';



	// exit = sqlite3_exec(DB, myQuery.c_str(), NULL, 0, &messaggeError); // Executa a query no banco de dados 

	// if (exit != SQLITE_OK) { 
	// 	std::cerr << "Erro criando a tabela..." << std::endl; 
	// 	sqlite3_free(messaggeError); 
	// } 
	// else
	// 	std::cout << "Tabela criada com sucesso!" << std::endl; 

	// string query = "SELECT * FROM PRODUTOS;"; // seleciono tudo da tabela PRODUTOS,

	// cout << "Estado da tabela antes de inserir: " << endl; 

	// sqlite3_exec(DB, query.c_str(), callback, NULL, NULL); // Executo a mensagem de query na tabela 

	// myQuery = ("INSERT INTO PRODUTOS VALUES(1, 'BANANA', 30, 'FRUTA', 5);"
	// 		"INSERT INTO PRODUTOS VALUES(2, 'MANGA', 20, 'FRUTA', 4);"
	// 		"INSERT INTO PRODUTOS VALUES(3, 'ABACAXI', 24, 'FRUTA', 6);"); 


	// // Executa a string de insercao
	// exit = sqlite3_exec(DB, myQuery.c_str(), NULL, 0, &messaggeError); 

	// if (exit != SQLITE_OK) 
	// { 
	// 	std::cerr << "Erro ao inserir na tabela..." << std::endl; 
	// 	sqlite3_free(messaggeError); 
	// } 
	// else
	// 	std::cout << "Gravação feita com sucesso!" << std::endl; 

	// cout << "Estado da tabela após inserção" << endl; 
	// // Callback atualmente está printando tudo
	// sqlite3_exec(DB, query.c_str(), callback, NULL, NULL); 


	// // Deleta o ID = 2
	// myQuery = "DELETE FROM PRODUTOS WHERE ID = 2;"; 
	// exit = sqlite3_exec(DB, myQuery.c_str(), NULL, 0, &messaggeError); 
	// if (exit != SQLITE_OK) { 
	// 	std::cerr << "Error DELETE" << std::endl; 
	// 	sqlite3_free(messaggeError); 
	// } 
	// else
	// 	std::cout << "Record deleted Successfully!" << std::endl; 


	// cout << "Estado da tabela após deletar o item 2" << endl; 
	// sqlite3_exec(DB, query.c_str(), callback, NULL, NULL); 

	// sqlite3_close(DB); 


	return (0); 
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
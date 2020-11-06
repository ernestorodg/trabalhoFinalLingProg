#include <iostream> 
#include <sqlite3.h> 
#include <string> 
#include <iomanip>
#include <fstream>


#include "dataBank.h"


DataBank::DataBank(const char *nomeBancoDados)
{
	// if (nomeBancoDados == "")
	// 	std::cout << "Nome do banco de dados indefinido" << std::endl;

	setDataBank(nomeBancoDados);
}; // Construtor padrão




// A função callback eh executada para cada linha na tabela
int DataBank::printRows(void* data, int argc, char** argv, char** azColName) 
{ 
	// fprintf(stderr, "%s: ", (const char*)data); 
	std::cout << "Essa função foi chamada" << std::endl;

	for (int indice_auxiliar = 0; indice_auxiliar < argc; indice_auxiliar++) 
	{ 
		// azColName eh um vetor de strings que contém o nome do atributo (coluna) do banco de dados
		// argv eh um vetor de strings que contém o valor desse atributo na linha que está sendo lida
		// printf("%s = %s\n", azColName[indice_auxiliar], argv[indice_auxiliar] ? argv[indice_auxiliar] : "NULL"); 

		std::cout << std::setw(10) << azColName[indice_auxiliar] 
					<< std::setw(10) << argv[indice_auxiliar]
					<< std::endl;
	} 

	printf("\n"); 
	return 0; 
} 


// Recebe o nome do banco de dados a ser aberto
void DataBank::setDataBank(const char *nomeBancoDados)
{
	int verificacao = 0;
	verificacao = sqlite3_open(nomeBancoDados, &dataBank);

	std::cout << "Verificacao: " << verificacao << std::endl;

};


// Fechar banco de dados; retorna um inteiro para verificação
int DataBank::closeDataBank()
{
	return sqlite3_close(dataBank); 	
};


// Para modificar a tabela que será criada é necessário configurar 
// o arquivo create_table em sqlCmd
int DataBank::createTable()
{
	int exit = 0;
	char* messaggeError; 

	std::string line = "";
	std::string myQuery = "";

	// Opening file create_table in sqlCmd folder
	// This file contains the needed command to create an SQLite Table
	std::ifstream myFile ("./sqlCmd/create_table.txt");
	if (myFile.is_open())
	{
		while (getline (myFile, line))
		{
			myQuery += line;
		}

	// Closing the file. It is not necessary once read
	myFile.close();
	}
	else std::cout << "O arquivo não pôde ser aberto." << std::endl; 

	// Executa a query no banco de dados 
	exit = sqlite3_exec(dataBank, myQuery.c_str(), NULL, 0, &messaggeError); 

	if (exit != SQLITE_OK) { 
		std::cerr << "Erro criando a tabela..." << std::endl; 
		sqlite3_free(messaggeError); 
	} 
	else
		std::cout << "Tabela criada com sucesso!" << std::endl; 

	return (exit);
}


int DataBank::insertOnDataBank()
{
	// int exit = sqlite3_open("meuBanco.db", &dataBank); // abro o banco de dados, se nao existe crio
	std::string myQuery = "";
	char* messaggeError; 
	int exit = 0;


	std::string query = "SELECT * FROM PRODUTOS;"; // seleciono tudo da tabela PRODUTOS,

	std::cout << "Estado da tabela antes de inserir: " << std::endl; 

	sqlite3_exec(dataBank, query.c_str(), printRows, NULL, NULL); // Executo a mensagem de query na tabela 

	myQuery = ("INSERT INTO PRODUTOS VALUES(1, 'BANANA', 30, 'FRUTA', 5);"
			"INSERT INTO PRODUTOS VALUES(2, 'MANGA', 20, 'FRUTA', 4);"
			"INSERT INTO PRODUTOS VALUES(3, 'ABACAXI', 24, 'FRUTA', 6);"); 


	// Executa a string de insercao
	exit = sqlite3_exec(dataBank, myQuery.c_str(), NULL, 0, &messaggeError); 

	if (exit != SQLITE_OK) 
	{ 
		std::cerr << "Erro ao inserir na tabela..." << std::endl; 
		sqlite3_free(messaggeError); 
	} 
	else
		std::cout << "Gravação feita com sucesso!" << std::endl; 

	return (exit);

}


int DataBank::showDataBank()
{
	int exit = 0;

	// Callback atualmente está printando tudo
	std::string query = "SELECT * FROM PRODUTOS;"; // seleciono tudo da tabela PRODUTOS,

	exit = sqlite3_exec(dataBank, query.c_str(), printRows, NULL, NULL); 

	return exit;

}


int DataBank::deleteRowFromDataBank()
{
	int exit = 0;
	char* messaggeError; 

	// Deleta o ID = 2
	std::string myQuery = "DELETE FROM PRODUTOS WHERE ID = 2;";

	exit = sqlite3_exec(dataBank, myQuery.c_str(), NULL, 0, &messaggeError); 
	if (exit != SQLITE_OK) 
	{ 
		std::cerr << "Error DELETE" << std::endl; 
		sqlite3_free(messaggeError); 
	} 
	else
		std::cout << "Record deleted Successfully!" << std::endl; 


	std::string query = "SELECT * FROM PRODUTOS;"; // seleciono tudo da tabela PRODUTOS,

	std::cout << "Estado da tabela após deletar o item 2" << std::endl; 
	exit = sqlite3_exec(dataBank, query.c_str(), printRows, NULL, NULL); 

	return exit;
}








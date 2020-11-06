#include <iostream> 
#include <sqlite3.h> 
#include <string> 
#include <iomanip>
#include <fstream>


#include "dataBank.h"


#define COLUMNS_LENGTH				15


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

	// for (int auxiliar_index = 0; auxiliar_index < argc; auxiliar_index++) 
	// 	std::cout << std::setw(COLUMNS_LENGTH) << azColName[auxiliar_index] 
	// 				<< std::endl;


	for (int auxiliar_index = 0; auxiliar_index < argc; auxiliar_index++) 
	{ 
		// azColName eh um vetor de strings que contém o nome do atributo (coluna) do banco de dados
		// argv eh um vetor de strings que contém o valor desse atributo na linha que está sendo lida
		// printf("%s = %s\n", azColName[auxiliar_index], argv[auxiliar_index] ? argv[auxiliar_index] : "NULL"); 

		std::cout << std::setw(COLUMNS_LENGTH) << argv[auxiliar_index];
	} 
	std::cout << std::endl;

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

// Recebe os dados do produto a ser inserido na tabela SQL
int DataBank::insertOnDataBank(std::string productID, std::string productName, 
								std::string amount, std::string type,
								std::string price)
{

	// int exit = sqlite3_open("meuBanco.db", &dataBank); // abro o banco de dados, se nao existe crio
	std::string myQuery = "";
	char* messaggeError; 
	int exit = 0;


	std::string query = "SELECT * FROM PRODUTOS;"; // seleciono tudo da tabela PRODUTOS,

	myQuery = ("INSERT INTO PRODUTOS VALUES("+ productID +", '" 
												+ productName + "'," 
												+ amount + " , '" 
												+ type + "', " 
												+ price + ");");


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


// Atualiza um produto no Banco de dados
int DataBank::updateDataBank()
{
	int exit = 0;
	char* messaggeError; 

	// ID NOME QUANTIDADE DESCRICAO PRECO


	// Modificar o valor de DESCRICAO em ID,
	// Podem ser vários ao mesmo tempo também:
	// UPDATE Customers SET DESCRICAO = 'FRUTA', PRECO = 6 WHERE ID = 3;
	std::string myQuery = "UPDATE PRODUTOS SET PRECO = 5 WHERE ID = 3;";

	exit = sqlite3_exec(dataBank, myQuery.c_str(), NULL, 0, &messaggeError); 
	if (exit != SQLITE_OK) 
	{ 
		std::cerr << "Erro ao tentar atualizar..." << std::endl; 
		sqlite3_free(messaggeError); 
	} 
	else
		std::cout << "Linha atualizada com sucesso!" << std::endl; 


	// std::string query = "SELECT * FROM PRODUTOS;"; // seleciono tudo da tabela PRODUTOS,

	// std::cout << "Estado da tabela após deletar o item 2" << std::endl; 
	// exit = sqlite3_exec(dataBank, query.c_str(), printRows, NULL, NULL); 

	return exit;
}




// Para uma inserção controlada, é necessário saber qual o primeiro ID vazio.
// getFirstEmptyID() retorna o primeiro ID vazio no banco de dados.
int DataBank::getFirstEmptyID()
{
	std::string query = "SELECT * FROM PRODUTOS;"; // seleciono tudo da tabela PRODUTOS,
	int exit = 0;


	std::cout << "Estado da tabela após deletar o item 2" << std::endl; 
	exit = sqlite3_exec(dataBank, query.c_str(), extractDataBank, &records, NULL); 

	for (unsigned int indice_auxiliar_primeiro = 0; indice_auxiliar_primeiro < records.size(); indice_auxiliar_primeiro++)
	{
		for (unsigned int indice_auxiliar_segundo = 0; indice_auxiliar_segundo < records[indice_auxiliar_primeiro].size(); indice_auxiliar_segundo++)
		{
			// for (unsigned int indice_auxiliar_terceiro = 0; indice_auxiliar_terceiro < records[indice_auxiliar_terceiro].size(); indice_auxiliar_terceiro++)
	
			std::cout << records[indice_auxiliar_primeiro][indice_auxiliar_segundo] << std::endl;

		}
	}

	std::cout << "Experimentando coisinhas... tamanho do records - numero de linhas: " << records.size() << std::endl;
	for (unsigned int indice_auxiliar_primeiro = 0; indice_auxiliar_primeiro < records.size(); indice_auxiliar_primeiro++)
	{
	
			std::cout << records[0][indice_auxiliar_primeiro] << std::endl;

	}



	// std::cout << (*meuVetor) << std::endl;

	return exit;
}




Records DataBank::getRecords()
{
	return records;
}

// A função extractDataBank() extrai toda a informação (cada linha) 
// do banco de dados e coloca num vetor de vetores de strings para facilitar o acesso.
int DataBank::extractDataBank(void *data, int argc, char **argv, char **azColName)
{
  Records* records = static_cast<Records*>(data);
  try {
    records->emplace_back(argv, argv + argc);
  }
  catch (...) {
  	std::cout << "Erro extraindo dados..." << std::endl;
    // Aborta para não propagar o erro através de sqlite3
    return 1;
  }
  return 0;
}




// int sqlite3_exec(
//   sqlite3*,                                  /* An open database */
//   const char *sql,                           /* SQL to be evaluated */
//   int (*callback)(void*,int,char**,char**),  /* Callback function */
//   void *,                                    /* 1st argument to callback */
//   char **errmsg                              /* Error msg written here */
// );


/////////////////////////////////////////////

// #include <vector>
// #include <string>
// #include <iostream>
// #include "sqlite3.h"
// using namespace std;

// sqlite3* db;

// using Record = std::vector<std::string>; //Record eh um vetor de strings
// using Records = std::vector<Record>;// Records eh um vetor de Record

// int select_callback(void *data, int num_fields, char **argv, char **azColName)
// {
//   Records* records = static_cast<Records*>(data);
//   try {
//     records->emplace_back(argv, argv + num_fields);
//   }
//   catch (...) {
//     // abort select on failure, don't let exception propogate thru sqlite3 call-stack
//     return 1;
//   }
//   return 0;
// }

// Records select_stmt(const char* stmt)
// {
//   Records records;  
//   char *errmsg;
//   int ret = sqlite3_exec(db, stmt, select_callback, &records, &errmsg);
//   if (ret != SQLITE_OK) {
//     std::cerr << "Error in select statement " << stmt << "[" << errmsg << "]\n";
//   }
//   else {
//     std::cerr << records.size() << " records returned.\n";
//   }

//   return records;
// }

// void sql_stmt(const char* stmt)
// {
//   char *errmsg;
//   int ret = sqlite3_exec(db, stmt, 0, 0, &errmsg);
//   if (ret != SQLITE_OK) {
//     std::cerr << "Error in select statement " << stmt << "[" << errmsg << "]\n";
//   }
// }

// int main()
// {
//   if (sqlite3_open("test.db", &db) != SQLITE_OK) {
//     std::cerr << "Could not open database.\n";
//     return 1;
//   }

//   Records records = select_stmt("SELECT * FROM test");
//   sqlite3_close(db);

//   for (auto& record : records) {
//     // do something with your records
//   }

//   return 0;
// }

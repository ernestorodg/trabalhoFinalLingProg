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




int DataBank::showDataBank() 
{ 

	updateRecords(); // Atualiza os dados em records

	for (unsigned int x = 0; x < records.size(); x++)
	{
		for (unsigned int y = 0; y < records[x].size(); y++)
		{
			// for (unsigned int indice_auxiliar_terceiro = 0; indice_auxiliar_terceiro < records[indice_auxiliar_terceiro].size(); indice_auxiliar_terceiro++)

			std::cout << std::setw(COLUMNS_LENGTH) 
						<< records[x][y] 
						<< std::setw(COLUMNS_LENGTH);

		}
		std::cout << std::endl;
	}

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


	// std::string query = "SELECT * FROM PRODUTOS;"; // seleciono tudo da tabela PRODUTOS,

	// std::cout << "Estado da tabela após deletar o item 2" << std::endl; 
	// exit = sqlite3_exec(dataBank, query.c_str(), NULL, NULL, NULL); 

	return exit;
}


// Atualiza um produto no Banco de dados
// Com index eh escolhido o que vai ser modificado
int DataBank::updateDataBank(int index, int productID, std::string newValue)
{
	int exit = 0;
	char* messaggeError; 

	std::vector <std::string> columns {"ID", "NOME", "QUANTIDADE", "DESCRICAO", "PRECO"}; 

	std::string productIDStr = std::to_string(productID);


	std::string myQuery = "UPDATE PRODUTOS SET " + columns[index] + " = " + newValue + 
								  " WHERE ID = " + productIDStr + ";";
	exit = sqlite3_exec(dataBank, myQuery.c_str(), NULL, 0, &messaggeError); 


	if (exit != SQLITE_OK) 
	{ 
		std::cerr << "Erro ao tentar atualizar..." << std::endl; 
		sqlite3_free(messaggeError); 
	} 
	else
		std::cout << "Linha atualizada com sucesso!" << std::endl; 

	return exit;

}




// Para uma inserção controlada, é necessário saber qual o primeiro ID vazio.
// getFirstEmptyID() retorna o primeiro ID vazio no banco de dados.
int DataBank::updateRecords()
{
	records.clear();
	std::string query = "SELECT * FROM PRODUTOS;"; // seleciono tudo da tabela PRODUTOS,
	int exit = 0;
	exit = sqlite3_exec(dataBank, query.c_str(), extractDataBank, &records, NULL); 
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

int DataBank::getFirstEmptyID()
{
	updateRecords();
	int x = 0;

	for (x = 0; x < static_cast<int>(records.size()); x++)
	{
		if (std::stoi(records[x][0]) != x)
			return x;
	}

	return (x);
};


// lookForProduct() retorna a ID do produto procurado (a procura eh feita pelo nome do produto)
// Caso não exista, retorna zero
int DataBank::lookForProduct(std::string productName)
{
	// ID NOME QUANTIDADE DESCRICAO PRECO

	updateRecords();
	int x = 0;

	for (x = 0; x < static_cast<int>(records.size()); x++)
	{
		if (records[x][1] == productName)
			return (x + 1);
	}

	return (0);
}
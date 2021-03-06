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
	// int verificacao = 0;
	sqlite3_open(nomeBancoDados, &dataBank);
	// std::cout << "Verificacao: " << verificacao << std::endl;

};


// Fechar banco de dados; retorna um inteiro para verificação
int DataBank::closeDataBank()
{
	return sqlite3_close(dataBank); 	
};



std::string DataBank::openSqlCmd(std::string sqlFile)
{
	std::string myQuery = "";
	std::string line = "";

	std::ifstream myFile (sqlFile);
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

	return myQuery;
};


// Para modificar a tabela que será criada é necessário configurar 
// o arquivo create_table em sqlCmd
int DataBank::createTable()
{
	int exit = 0;
	char* messaggeError; 
	std::string myQuery = "";

	// Opening file create_table in sqlCmd folder
	// This file contains the needed command to create an SQLite Table
	myQuery = openSqlCmd("./sqlCmd/create_table.sql");

	if (myQuery == "")
		return (-1);

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

	// Opening file insert_row in sqlCmd folder
	// This file contains the needed command to create an SQLite Table
	myQuery = openSqlCmd("./sqlCmd/insert_row.sql");

	myQuery.replace(myQuery.find("productID"), std::string("productID").length(), productID);
	myQuery.replace(myQuery.find("productName"), std::string("productName").length(), productName);
	myQuery.replace(myQuery.find("amount"), std::string("amount").length(), amount);
	myQuery.replace(myQuery.find("type"), std::string("type").length(), type);
	myQuery.replace(myQuery.find("price"), std::string("price").length(), price);

	// // The code above make the same than the code ahead
	// myQuery = ("INSERT INTO PRODUTOS VALUES("+ productID +", '" 
	// 											+ productName + "'," 
	// 											+ amount + " , '" 
	// 											+ type + "', " 
	// 											+ price + ");");



	exit = sqlite3_exec(dataBank, myQuery.c_str(), NULL, 0, &messaggeError); 
	
	if (messaggeError != NULL)
		std::cout << messaggeError << std::endl;


	if (exit != SQLITE_OK) 
	{ 
		std::cerr << "Erro ao inserir na tabela..." << std::endl; 
		sqlite3_free(messaggeError); 
	} 
	else
		// std::cout << "Gravação feita com sucesso!" << std::endl; 
		std::cout << std::endl; 

	return (exit);

}




int DataBank::deleteRowFromDataBank(int ID)
{
	int exit = -1;
	char* messaggeError; 
	std::string myQuery = "";

	exit = lookInRecords(ID);
	if (exit == -1)
		return (exit);

	// Opening file delete_row in sqlCmd folder
	// This file contains the needed command to create an SQLite Table
	myQuery = openSqlCmd("./sqlCmd/delete_row.sql");

	myQuery.replace(myQuery.find("myID"), std::string("myID").length(), std::to_string(ID));

	// std::string myQuery = "DELETE FROM PRODUTOS WHERE ID = " + std::to_string(ID) + ";";

	exit = sqlite3_exec(dataBank, myQuery.c_str(), NULL, 0, &messaggeError); 
	if (exit != SQLITE_OK) 
	{ 
		std::cerr << "Error DELETE" << std::endl; 
		sqlite3_free(messaggeError); 
	} 
	else
		// std::cout << "Linha apagada com sucesso!" << std::endl; 
		std::cout << "Linha apagada com sucesso!" << std::endl; 


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
	std::string myQuery = "";

	std::vector <std::string> columns {"ID", "NOME", "QUANTIDADE", "DESCRICAO", "PRECO"}; 

	std::string productIDStr = std::to_string(productID);


	myQuery = openSqlCmd("./sqlCmd/update_row.sql");

	myQuery.replace(myQuery.find("productType"), std::string("productType").length(), columns[index]);
	myQuery.replace(myQuery.find("newValue"), std::string("newValue").length(), newValue);
	myQuery.replace(myQuery.find("productIDStr"), std::string("productIDStr").length(), productIDStr);


	// std::string myQuery = "UPDATE PRODUTOS SET " + columns[index] + " = '" + newValue + 
	// 							  "' WHERE ID = " + productIDStr + ";";


	exit = sqlite3_exec(dataBank, myQuery.c_str(), NULL, 0, &messaggeError); 

	if (exit != SQLITE_OK) 
	{ 
		std::cerr << "Erro ao tentar atualizar..." << std::endl; 
		sqlite3_free(messaggeError); 
	} 
	else
		// std::cout << "Linha atualizada com sucesso!" << std::endl; 
		std::cout << std::endl; 

	return exit;

}






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
	
	try 
	{
		records->emplace_back(argv, argv + argc);
	}
	catch (...) 
	{
		// Aborta para não propagar o erro através de sqlite3
		std::cout << "Erro extraindo dados..." << std::endl;
		return 1;
	}

	return 0;
}


// Para uma inserção controlada, é necessário saber qual o primeiro ID vazio.
// getFirstEmptyID() retorna o primeiro ID vazio no banco de dados.
int DataBank::getFirstEmptyID()
{
	updateRecords();
	bool found = true;
	int y;
	int x;

	for (x = 1; x < static_cast<int>(records.size()) + 1; x++)
	{
		for (y = 0; y < static_cast<int>(records.size()); y ++)
		{
			// std::cout << "Comparando " << std::stoi(records[y][0]) << " e " << x << std::endl;
			if (std::stoi(records[y][0]) ==  x)
			{
				found = false;
				break;
			}

		}
		if (found == true)
			return (x);
		else
			found = true;

	}
	return (x);
};


// lookForProduct(std::string) retorna a ID do produto procurado (a procura eh feita pelo nome do produto)
// Caso não exista, retorna zero
// Argumentos:
// std::string productName: Nome do produto procurado
int DataBank::lookForProduct(std::string productName)
{
	// ID NOME QUANTIDADE DESCRICAO PRECO

	updateRecords();
	int x = 0;

	for (x = 0; x < static_cast<int>(records.size()); x++)
	{
		if (records[x][1] == productName)
			return (std::stoi(records[x][0])); // Retorna o ID do produto
	}

	return (0);
}

// lookInRecords(std::string) retorna a posição do produto no vetor Records
// Caso não exista, retorna -1
// Argumentos:
// std::string productID: ID do produto 
int DataBank::lookInRecords(int productID)
{
	// ID NOME QUANTIDADE DESCRICAO PRECO
	updateRecords();
	int x = 0;

	for (x = 0; x < static_cast<int>(records.size()); x++)
	{
		if (records[x][0] == std::to_string(productID))
			return (x); // Retorna a posição do produto no vetor Records
	}

	return (-1);
}

// Mostra as propriedades do produto cuja ID foi passada: DESCRICAO PRECO
void DataBank::showPropertiesByID(int productID)
{
	// ID NOME QUANTIDADE DESCRICAO PRECO
	updateRecords();
	int position = lookInRecords(productID);
	int x = 0;


	if (position != -1)
	{
		for (x = 3; x < static_cast<int>(records[position].size()); x++)
		{
			std::cout << std::setw(COLUMNS_LENGTH) << records[position][x];
		}
		std::cout << std::endl;
	}
	else 
		std::cout << "\tErro: Produto não existe.";

}

// Devolve o preço de um determinado produto segundo o ID passado no primeiro argumento.
int DataBank::getProductPrice(int productID)
{
	// ID NOME QUANTIDADE DESCRICAO PRECO
	updateRecords();
	int position = lookInRecords(productID);

	if (position != -1)
			return std::stoi(records[position][4]);
	else 
		std::cout << "\tErro: Produto não existe.";

	return (0);
}

// Devolve o preço de um determinado produto segundo o ID passado no primeiro argumento.
int DataBank::getProductAmount(int productID)
{
	// ID NOME QUANTIDADE DESCRICAO PRECO
	updateRecords();
	int position = lookInRecords(productID);

	if (position != -1)
			return std::stoi(records[position][2]);
	else 
		std::cout << "\tErro: Produto não existe.";

	return (0);
}

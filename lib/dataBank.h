/*
**	Esta classe implementa um banco de dados SQLite com 
**	capacidade de uma tabela somente.
**
**
**
*/


#include <iostream>
#include <string>
#include <sqlite3.h>
#include <vector>

#ifndef DATA_BANK_H
#define DATA_BANK_H


using Record = std::vector<std::string>; //Record eh um vetor de strings
using Records = std::vector<Record>; // Records eh um vetor de Record

class DataBank
{
	public:
		DataBank(const char *); // Construtor padrão

		static int extractDataBank(void*, int, char**, char**); 

		void setDataBank(const char *);
		int createTable();
		int insertOnDataBank(std::string , std::string , std::string , std::string , std::string );
		int showDataBank();
		int deleteRowFromDataBank(int);
		int closeDataBank();
		int updateDataBank(int, int, std::string);
		int getFirstEmptyID();
		int updateRecords();
		int lookInRecords(int);
		void showPropertiesByID(int);
		int getProductPrice(int);
		int getProductAmount(int);


		int lookForProduct(std::string);

		std::string openSqlCmd(std::string);

		Records getRecords();

	protected:

	private:
		sqlite3* dataBank; // Crio o objeto banco de dados
		Records records; // É um objeto que irá armazenar tudo no banco de dados


};


#endif
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
		int printRows();
		int createTable();
		int insertOnDataBank(std::string , std::string , std::string , std::string , std::string );
		int showDataBank();
		int deleteRowFromDataBank();
		int closeDataBank();
		int updateDataBank(int, int, std::string);
		int getFirstEmptyID();
		int updateRecords();
		
		int lookForProduct(std::string);

		Records getRecords();

	protected:

	private:
		sqlite3* dataBank; // Crio o objeto banco de dados
		Records records; // É um objeto que irá armazenar tudo no banco de dados


};


#endif
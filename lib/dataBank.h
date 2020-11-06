#include <iostream>
#include <string>
#include <sqlite3.h>


#ifndef DATA_BANK_H
#define DATA_BANK_H


class DataBank
{
	public:
		DataBank(const char *); // Construtor padrão

		static int printRows(void*, int, char**, char**);

		void setDataBank(const char *);

		int createTable();
		int insertOnDataBank();
		int showDataBank();
		int deleteRowFromDataBank();


		int closeDataBank();



	protected:

	private:
		sqlite3* dataBank; // Crio o objeto banco de dados

};


#endif
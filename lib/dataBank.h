#include <iostream>
#include <string>
#include <sqlite3.h>


#ifndef DATA_BANK_H
#define DATA_BANK_H


class DataBank
{
	public:
		int printDB(void*, int, char**, char**);


	protected:

	private:
		sqlite3* DB; // Crio o objeto banco de dados

};


#endif
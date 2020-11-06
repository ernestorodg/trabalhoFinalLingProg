#include <iostream> 
#include <sqlite3.h> 
#include <string> 
#include <iomanip>


#include "dataBank.h"




// A função callback eh executada para cada linha na tabela
int DataBank::printDB(void* data, int argc, char** argv, char** azColName) 
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

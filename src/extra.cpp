// Em extra.cpp se definem algumas funcoes usadas como auxiliares.


#include "extra.h"


// Recebe uma string qualquer.
// Retorna true se a string recebida for um numero (sem espaçamentos no meio). Caso contrario retorna false.
bool isNumeric(std::string str) {
   for (unsigned int indice_auxiliar = 0; indice_auxiliar < str.length(); indice_auxiliar++)
      if (isdigit(str[indice_auxiliar]) == false)
         return false; 
   return true;
};

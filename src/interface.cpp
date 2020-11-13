// Implementação da classe Interface
#include <cstdio>


#include "interface.h"
	

Interface::Interface(){}


// Testes interessantes para quem quiser experimentar com o terminal
// void Interface::test()
// {
//     // printf("%c[%dmHELLO!\n", 0x1B, 32); // coloca a cor em verde
//     printf("%c[%dK HELLO!\n", 0x1B, 0); // Limpa a linha desde o cursor até o fim

//     printf("%c[%dK HELLO!\n", 0x1B, 1); // Limpa a linha desde o cursor até o inicio
//     printf("%c[%dK HELLO!\n", 0x1B, 2); // Limpa a linha toda
//     printf("%c[%dJ HELLO!\n", 0x1B, 2); // Apaga a tela

// };


void Interface::cleanScreen()
{
    // printf("%c[%dmHELLO!\n", 0x1B, 32); // coloca a cor em verde
    printf("%c[%dJ", 0x1B, 2); // Apaga a tela

};

void Interface::setCursorToBegin()
{
    // printf("%c[%dmHELLO!\n", 0x1B, 32); // coloca a cor em verde
    printf("%c[%d;%dH", 0x1B, 0, 0); // Apaga a tela

};

void Interface::saveScreen()
{
    printf("%c[?%dh", 0x1B, 47); // Salva a tela 
}

void Interface::restoreScreen()
{
    printf("%c[?%dl", 0x1B, 47); // Retorna à tela salva 	
}

void Interface::saveCursorPosition()
{
    printf("%c%d", 0x1B, 7); // Salva a tela 
}


void Interface::restoreCursorPosition()
{
    printf("%c%d", 0x1B, 8); // Retorna à tela salva    
}

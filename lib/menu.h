// A classe Menu simulará uma caixa tipo supermercado

#ifndef MENU_H
#define MENU_H


class Menu 
{
	public:
		Menu();

		void showMenu();
		int defineNumericInput();
		std::string defineLiteralInput();


	
	private:
		std::string entrada;
};




#endif
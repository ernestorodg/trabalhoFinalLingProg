// A classe Menu simulará uma caixa tipo supermercado

#ifndef MENU_H
#define MENU_H


class Menu 
{
	public:
		Menu();

		void showCashierMenu(); 
		void showDataBankMenu();
		int defineNumericInput();
		std::string defineLiteralInput();
		void teste();


	
	private:
		std::string entrada;
};




#endif
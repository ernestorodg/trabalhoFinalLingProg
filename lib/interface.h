// A classe Interface fará a interface da caixa

#ifndef INTERFACE_H
#define INTERFACE_H


class Interface 
{
	public:
		Interface();

		static void test();
		static void cleanScreen();
		static void saveScreen();
		static void restoreScreen();
		static void setCursorToBegin();
		static void saveCursorPosition();
		static void restoreCursorPosition();


};




#endif
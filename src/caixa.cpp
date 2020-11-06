// Implementação da classe Caixa

#include "caixa.h"
		

Caixa::Caixa(double novoSaldo) : saldo(novoSaldo) {}

double Caixa::getSaldo() { return saldo; };
void Caixa::setSaldo(double novoSaldo) {saldo = novoSaldo;};

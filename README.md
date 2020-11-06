Ernesto Rodríguez González
Daniel Becker
Trabalho final da disciplica de Linguagens de Programação.

***************
Programa testado e feito em Ubuntu

Pre-requisitos:

Ter sqlite3:
	Para verificar a existência de sqlite3 no seu computador:
		Execute
		$ 



***************
Execute 



$ make 

para compilar o programa.

***************

Uma vez compilado, o programa estará disponível no diretório, com o nome "exercicio"

Para executar o programa, digite

./exercicio

***************


Uma vez inicializado, o programa irá ler o arquivo de texto "arquivo.txt" para atualizar o catalogo de filmes.


Caso o arquivo não seja encontrado, irá aparecer uma mensagem na tela e o catálogo será incializado sem filmes.

*****************

Para facilitar a avaliação do programa, são feitos alguns exemplos de inserção sem interação do usuário no início. Caso não seja desejado usar isto, por favor, comente desde a linha 24 até a linha 60 do arquivo main.cpp


O programa aceita 10 filmes no máximo. Caso se queira mudar, basta colocar um inteiro diferente no construtor da classe Catalogo.

*****************

Uma vez executado o programa, irá ser pedido uma ação a ser realizada.

Para a opção 1, um filme já inicializado com a opção 6 será salvo no catálogo. A inserção de filmes é de forma ordenada. Ordenação da forma: números > maiusculas > minusculas.

Ao escolher a opção 2, o programa exigirá um nome de filme para eliminar. Caso o nome digitado não exista na lista, o usuário será avisado. 

Ao escolher a opção 3, o programa exigirá um nome de filme para procurar. Caso o nome digitado não exista na lista, o usuário será avisado. Caso o nome exista, será imprimido na tela a informação do filme.

Ao escolher a opção 4, o programa exigirá um nome de filme para procurar. Caso o nome digitado não exista na lista, o usuário será avisado. Caso o nome exista, será pedido para o usuário inserir a opção que deseja. Entre as opções estão: mudar nome, mudar produtora e mudar nota. 

Ao escolher a opção 5, o programa mostrará todos os filmes no catálogo.

Ao escolher a opção 6, o programa exigirá os dados referentes a um filme. Após a inicialização, caso se deseje inserir o filme no catálogo, deve ser executada a opção 1 de forma imediata.


Ao escolher a opção 7, o programa mostrará quais são os filmes com a maior nota.



Uma vez finalizado o programa (quando o usuário tomar a opção de sair), o arquivo será reescrito com o catálogo. Caso o usuário force a saída do programa (usando ctrl. + c, por exemplo), o arquivo não será reescrito e nenhuma modificação será feita.

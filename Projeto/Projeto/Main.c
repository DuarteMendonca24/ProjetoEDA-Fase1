/**
* @file Funcoes.c
* @author Duarte Mendonça
* @email durtemendonca1234@gmail.com
* @date 1/04/2022
* @brief Manipulação de Listas Ligadas Simples
*/

#include"Dados.h"

int main() {

#pragma region operacao1

	//Criar a Operação 1

	Operacao* headoperacao = NULL;

	Operacao* novaOperacao = criaOperacao(1);

	Maquina* novaMaquina = criaMaquina(1, 4);
	novaOperacao->listamaquinas = insereMaquina(novaOperacao->listamaquinas, novaMaquina);

	novaMaquina = criaMaquina(2, 8);
	novaOperacao->listamaquinas = insereMaquina(novaOperacao->listamaquinas, novaMaquina);
	headoperacao = insereOperacaoOrdenada(headoperacao, novaOperacao);

#pragma endregion
	
#pragma region operacao2

	//Criar a Operação 2

	novaOperacao = criaOperacao(2);

	novaMaquina = criaMaquina(7, 2);
	novaOperacao->listamaquinas = insereMaquina(novaOperacao->listamaquinas, novaMaquina);

	novaMaquina = criaMaquina(2, 8);
	novaOperacao->listamaquinas = insereMaquina(novaOperacao->listamaquinas, novaMaquina);

	headoperacao = insereOperacaoOrdenada(headoperacao, novaOperacao);
	
#pragma endregion
	
#pragma region funcoes

	//Procura se a Operacao 2 existe e insere uma maquina

	novaMaquina = criaMaquina(7, 2);
	Operacao* aux = procuraOperacao(headoperacao, 2);
	if (aux != NULL) 	aux->listamaquinas = insereMaquina(aux->listamaquinas, novaMaquina);

	//Remove a Operacao 1
	//headoperacao = removeOperacaoRecursivo(headoperacao, 1);

	//Calcular o maximo e minimo de tempo para completar um job

	int somamin = 0;
	int somamax = 0;
	Operacao* listamin = NULL;
	Operacao* listamax = NULL;
	listamin = minTempo(headoperacao, &somamin);
	listamax = maxTempo(headoperacao, &somamax);

	//Calcular a media de tempo para completar a Operacao 2

	float media1;
	media1 = media(headoperacao, 2);

	//Procura uma maquina e altera o seu conteudo se existir

	Maquina* aux1 = procuraMaquina(headoperacao, 2, 1);
	if (aux != NULL) alteraMaquina(headoperacao, 1, 1, 1, 5);

#pragma endregion

#pragma region ficheiros

	FILE* fp = NULL;

	//Leitura de um ficheiro de texto
	lerFicheiros(fp, "Teste.txt");

	//Escrita de um ficheiro de texto
	escreverFicheiros(headoperacao, fp, "Dados.txt");

#pragma endregion
	
return 0;
}
/**
* @file Dados.h
* @author Duarte Mendonça
* @email durtemendonca1234@gmail.com
* @date 1/04/2022
* @brief  Definições Globais para Lista Ligadas Simples
*/

#ifndef Dados
#define Dados

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#pragma warning( disable : 4996 )//evita MSG ERROS: _CRT_SECURE_NO_WARNINGS


#pragma region Estruturas
typedef struct Maquina {
	int num, unitempo;
	struct Maquina* next;

}Maquina;

typedef struct Operacao {
	int cod;
	Maquina* listamaquinas;
	struct Operacao* next;

}Operacao;

#pragma endregion

#pragma region Maquinas
Maquina* criaMaquina(int num, int unitempo);
Maquina* insereMaquina(Maquina* h, Maquina* novamaquina);
Maquina* procuraMaquina(Operacao* h, int cod, int num);
void alteraMaquina(Maquina* h, int num, int cod, int novonum, int novounitempo);

#pragma endregion

#pragma region Operacao
Operacao* criaOperacao(int cod);
Operacao* procuraOperacao(Operacao* h, int cod);
//Operacao* RemoveOperacao(Operacao* h, int cod);
Operacao* minTempo(Operacao* headoperacao, int* soma);
Operacao* maxTempo(Operacao* headoperacao, int* soma);
Operacao* removeOperacaoRecursivo(Operacao* h, int cod);
Operacao* insereOperacaoOrdenada(Operacao* h, Operacao* novaoperacao);
float media(Operacao* headoperacao, int cod);
int contaOperacoes(Operacao* h);


#pragma endregion

#pragma region Ficheiros

void lerFicheiros(FILE* fp, char nome[100]);
void escreverFicheiros(Operacao* h, FILE* fp, char nome[100]);

#pragma endregion

#endif

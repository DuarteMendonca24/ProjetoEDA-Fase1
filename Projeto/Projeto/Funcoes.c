/**
* @file Funcoes.c
* @author Duarte Mendonça
* @email durtemendonca1234@gmail.com
* @date 1/04/2022
* @brief Metodos para manipular Listas Ligadas Simples
*/

#include"Dados.h"

#pragma region Funcoes

#pragma region Maquinas
/*
* @brief Criacao de uma nova maquina
* @param[in]    num			número da maquina a criar
* @param[in]    unitempo	unidades de tempo da maquina
* @param[out]	newmaquina	Apontador da Nova maquina
*/
Maquina* criaMaquina(int num, int unitempo) {
	Maquina* newmaquina = (Maquina*)malloc(sizeof(Maquina));
	if (newmaquina == NULL) return NULL;
	newmaquina->num = num;
	newmaquina->unitempo = unitempo;
	newmaquina->next = NULL;
	return newmaquina;
}

/*
* @brief Criacao de uma nova maquina
* @param[in]  h				inico da lista de maquinas
* @param[in]  novamaquina	nova maquina a inserir maquina
* @param[out] h				apontador para novo inicio da lista de maquinas
*/
Maquina* insereMaquina(Maquina* h, Maquina* novamaquina) {
	if (h == NULL) h = novamaquina;
	else {
		novamaquina->next = h;
		h = novamaquina;
	}
	return h;
}


/*
* @brief Procurar uma maquina
* @param[in]  h				inico da lista de maquinas
* @param[in]  cod			codigo da operacao onde a maquina esta inserida
* @param[in]  num			numero da maquina a procurar
* @param[out] NULL,aux2		NULL se nao encontrarmos, aux2(apontador para maquina que queriamos encontrar)
*/
Maquina* procuraMaquina(Operacao* h, int cod, int num) {
	Operacao* aux1;
	Maquina* aux2;
	if (h == NULL) return NULL;
	else {
		aux1 = procuraOperacao(h, cod);
		if (aux1 == NULL) return NULL;
		else {
			aux2 = aux1->listamaquinas;
			if (aux2 == NULL) return NULL;
			else {
				while (aux2) {
					if (aux2->num == num) return aux2;
					aux2 = aux2->next;
				}
			}
		}
	}

	return NULL;
}

/*
* @brief Alteracao do conteudo de uma maquina
* @param[in] h				inico da lista de maquinas
* @param[in] cod			codigo da operacao onde a maquina esta inserida
* @param[in] num			numero da maquina a procurar
* @param[in] novonum		novo numero da maquina
* @param[in] novounitempo	novoa unidade de tempo
* @param[out]				void
*/
void alteraMaquina(Maquina* h, int num, int cod, int novonum, int novounitempo) {
	Maquina* aux = procuraMaquina(h, cod, num);
	aux->num = novonum;
	aux->unitempo = novounitempo;
}

#pragma endregion 

#pragma region Operacoes 
/**
*@brief Cria nova Operacao.
*@param [in] cod         Código da Operacao
*@param[out] newoperacao Nova Operacao
*/
Operacao* criaOperacao(int cod) {
	Operacao* newoperacao = (Operacao*)malloc(sizeof(Operacao));
	if (newoperacao == NULL) return NULL;//pode não haver memória
	newoperacao->cod = cod;
	newoperacao->listamaquinas = NULL;
	newoperacao->next = NULL;
	return newoperacao;
}

/**
* @brief Insere Operacao ordenado pelo código
* @param [in] h		       Inicio da Lista
* @param [in] novaoperacao Nova Operacao a inserir
* @param[out] h			   Inicio da Lista
*/
Operacao* insereOperacaoOrdenada(Operacao* h, Operacao* novaoperacao) {
	if (procuraOperacao(h, novaoperacao->cod) != NULL) return h;
	if (h == NULL) {
		h = novaoperacao; //insere diretamente se a lista estiver vazia
	}

	else {
		Operacao* aux = h;
		Operacao* auxant = NULL;
		while (aux && aux->cod < novaoperacao->cod) {
			auxant = aux;
			aux = aux->next;
		}
		if (auxant == NULL) { //insere se houver só um elemento na lista
			novaoperacao->next = h;
			h = novaoperacao;
		}

		else { // insere em qualquer lugar na lista segundo a condicao
			auxant->next = novaoperacao;
			novaoperacao->next = aux;
		}
	}
	return h;
}

/**
* @brief Verifica se Operacao existe. Se existir devolve endereço da Operacao!
* @param [in] h		    Inicio da Lista
* @param [in] cod	    código da Operacao a procurar
* @param[out] aux,NULL	Apontador para Operacao encontrada
*/
Operacao* procuraOperacao(Operacao* h, int cod) {
	Operacao* aux = h;
	if (aux == NULL) return h;
	else {
		while (aux) {
			if (aux->cod == cod) return aux;   //Procura operacao através do codigo na estrutura

			aux = aux->next;    //avança para a proxima estrutura se ainda nao tiver encontrado a que procura
		}
	}
	return NULL;
}

/*Operacao* removeOperacao(Operacao* h, int cod) {
	if (h == NULL) return NULL;

	else if (h->cod == cod) {
		Operacao* aux = h;
		h = h->next;
		free(aux);
	}

	else {
		Operacao* aux = h;
		Operacao* auxant = NULL;

		while (aux && aux->cod != cod) {
			auxant = aux;
			aux = aux->next;
		}

		if(aux != NULL){
			auxant->next = aux->next;
			free(aux);
		}
	}
	return h;
}*/

/*
* @brief Remove Operacao recursivo
* @param[in]  h			inicio da lista de operacoes
* @param[in]  cod       codigo a encontrar para a operacao a remover
* @param[out] h         NULL se a lista for vazia; h com a operacao ja removida
*/
Operacao* removeOperacaoRecursivo(Operacao* h, int cod) {
	Operacao* aux = NULL;
	if (h == NULL) return NULL;

	else if (h->cod == cod) {
		Operacao* aux = h;
		h = h->next;
		free(aux);
	}

	else {
		h->next = removeOperacaoRecursivo(h->next, cod);
	}
	return h;
}

/**
* @brief Determinação da quantidade mínima de unidades de tempo necessárias para completar o job e listagem das respetivas operações
* @param [in] headoperacao	  Inicio da Lista
* @param[out] headminop	      Soma dos minimos de tempo de cada operacao
*/
Operacao* minTempo(Operacao* headoperacao, int* soma) {
	Operacao* headminop = NULL;
	Operacao* aux = headoperacao;
	Maquina* aux2 = headoperacao->listamaquinas;
	Maquina* maqmincopia = (Maquina*)malloc(sizeof(Maquina));
	Operacao* operacaocopia = (Operacao*)malloc(sizeof(Operacao));
	int min = aux->listamaquinas->unitempo;
	maqmincopia = criaMaquina(aux2->num, aux2->unitempo);

	while (aux) {

		while (aux2) {

			if (aux2->unitempo < min) {
				min = aux2->unitempo;
				maqmincopia = criaMaquina(aux2->num, aux2->unitempo);

			}

			aux2 = aux2->next;
		}

		*soma = *soma + min;

		operacaocopia = criaOperacao(aux->cod);
		operacaocopia->listamaquinas = insereMaquina(operacaocopia->listamaquinas, maqmincopia);
		headminop = insereOperacaoOrdenada(headminop, operacaocopia);

		aux = aux->next;

		if (aux != NULL) {
			aux2 = aux->listamaquinas;
			min = aux->listamaquinas->unitempo;
		}
	}

	return headminop;
}

/**
* @brief Determinação da quantidade maxima de unidades de tempo necessárias para completar o job e listagem das respetivas operações
* @param [in] headoperacao	 Inicio da Lista
* @param[out] headmaxop      Soma dos minimos de tempo de cada operacao
*/
Operacao* maxTempo(Operacao* headoperacao, int* soma) {
	Operacao* headmaxop = NULL;
	Operacao* aux = headoperacao;
	Maquina* aux2 = headoperacao->listamaquinas;
	Maquina* maqmaxcopia = (Maquina*)malloc(sizeof(Maquina));
	Operacao* operacaocopia = (Operacao*)malloc(sizeof(Operacao));
	int max = aux->listamaquinas->unitempo;
	maqmaxcopia = criaMaquina(aux2->num, aux2->unitempo);

	while (aux) {

		while (aux2) {

			if (aux2->unitempo > max) {
				max = aux2->unitempo;
				maqmaxcopia = criaMaquina(aux2->num, aux2->unitempo);

			}

			aux2 = aux2->next;
		}

		*soma = *soma + max;

		operacaocopia = criaOperacao(aux->cod);
		operacaocopia->listamaquinas = insereMaquina(operacaocopia->listamaquinas, maqmaxcopia);
		headmaxop = insereOperacaoOrdenada(headmaxop, operacaocopia);

		aux = aux->next;

		if (aux != NULL) {
			aux2 = aux->listamaquinas;
			max = aux->listamaquinas->unitempo;
		}
	}

	return headmaxop;
}

/**
* @brief  Determinação da quantidade média de unidades de tempo necessárias para completar uma operação,considerando todas as alternativas possíveis
* @param [in] headoperacao		      Inicio da Lista
* @param [in] cod	                  código da Operacao
* @param[out] somatempo/somamaquina	  Media
*/
float media(Operacao* headoperacao, int cod) {

	Maquina* aux = procuraOperacao(headoperacao, cod)->listamaquinas;
	float somamaquina = 0, somatempo = 0;

	while (aux != NULL) {

		somamaquina++;
		somatempo += aux->unitempo;
		aux = aux->next;

	}

	return(somatempo / somamaquina);
}

/**
* @brief  Conta quantas operacoes existem
* @param [in] headoperacao    Inicio da Lista
* @param[out] count           Numero de operacoes
*/
int contaOperacoes(Operacao* h) {
	Operacao* aux = h;
	int count = 0;

	if (aux == NULL) return NULL;

	while (aux) {

		count++;
		aux = aux->next;

	}

	return count;

}
#pragma endregion

#pragma region Ficheiros

/**
* @brief  Ler de um ficheiro de texto
* @param [in] fp              FilePointer
* @param [in] nome            Nome do Ficheiro
* @param[out]                 void
*/
void lerFicheiros(FILE* fp, char nome[100]) {
	char c[100];

	//handler de ficheiro de entrada
	fp = fopen(nome, "r"); // abrir ficheiro em modo leitura

	//se houve algum problema...
	if (fp == NULL) {
		perror("Erro ao abrir o ficheiro\n");
		getche();
		return(-1);
	}


	int l = 1;		//conta linhas lidas
	int linOper = 0;
	while (fscanf(fp, "%[^\n] ", c) != EOF) {	//lê até ao fim da linha
		printf("File:\n%s\n", c);
		if (l == 1)
		{
			int proc, maq, oper;
			int x = sscanf(c, "%dx%dx%d", &proc, &oper, &maq);
			printf("Proc: %d, Oper: %d, Maq: %d\n", proc, oper, maq);
			l++;
			continue;
		}
		if (l == 2) {
			char s[40];
			int numOper;
			int x = sscanf(c, "%s%*c%d", s, &numOper);	//%*c...encontra o char e não guarda!!!
			printf("Proc: %s, Oper: %d\n", s, numOper);
			l++;
			linOper = numOper;
			continue;
		}
		if (linOper > 0) {
			int m, t;
			char* field;
			field = strtok(c, "-");
			while (field != NULL) {
				printf("%s\n", field);
				field = strtok(NULL, "-");
			}
			//sscanf(c, "%*c%d%*c%d", &m, &t);
			//printf("Maq: %d, Tempo: %d\n", m, t);
			linOper--;
			continue;
		}
	}
	fclose(fp);

}

/**
* @brief  Escrever num ficheiro de texto
* @param [in] h               headOperacao
* @param [in] fp              FilePointer
* @param [in] nome            Nome do Ficheiro
* @param[out]                 void
*/
void escreverFicheiros(Operacao* h, FILE* fp, char nome[100]) {

	Operacao* aux = h;
	int linha = 1, count = 0;
	char tabela[100] = "8x7x8";

	fp = fopen(nome, "w"); // abrir ficheiro em modo leitura

	//se houve algum problema...
	if (fp == NULL) {
		perror("Erro ao abrir o ficheiro\n");
		getche();
		return(-1);
	}

	while (aux) {

		if (linha == 1) {

			fprintf(fp, "%s\n", tabela);
			linha++;
			continue;

		}
		if (linha == 2) {

			count = contaOperacoes(aux);
			fprintf(fp, "1 %d\n", count);
			linha++;
			//aux = aux->next;
			continue;

		}
		if (count > 0) {

			while (aux->listamaquinas) {

				if (aux->listamaquinas->next == NULL) {

					fprintf(fp, "(%d,%d)\n", aux->listamaquinas->num, aux->listamaquinas->unitempo);
					break;
				}
				else {

					fprintf(fp, "(%d,%d)-", aux->listamaquinas->num, aux->listamaquinas->unitempo);
					aux->listamaquinas = aux->listamaquinas->next;

				}


			}

			count--;
			aux = aux->next;
			continue;

		}

	}
	fclose(fp);
}

#pragma endregion

#pragma endregion
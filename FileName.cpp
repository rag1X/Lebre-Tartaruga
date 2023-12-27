#include "lab.h"

typedef struct JOGADOR
{
	char nome[20];
	//outras coisas do jogador
}jogador;
void espera()
{
	gotoxy(0, 22);
	system("pause");
}
typedef struct BARALHO
{
	char* cartas;
	int size;
	int maxSize;
}baralho;

void initBaralho(baralho* myB, int maxSize)
{
	myB->size = 0;
	myB->maxSize = maxSize;
	myB->cartas = (char*)malloc(myB->maxSize + 1 * sizeof(char));
	if (myB->cartas == NULL) { return; }
	int i = 0;
	for (i = 0; i < myB->maxSize; i++)
	{
		myB->cartas[i] = '0';
	}
	myB->size = myB->maxSize;
}
void initBaralho81(baralho* myB, int maxSize)
{
	myB->size = 0;
	myB->maxSize = maxSize;
	myB->cartas = (char*)malloc(myB->maxSize * sizeof(char));
	if (myB->cartas == NULL) { return; }
	int i = 0;
	//L, T, W, w, R, C
	for (i = 0; i < myB->maxSize; i++)
	{
		if (i < 18) { myB->cartas[i] = 'L'; }
		if (i >= 18 && i < 35) { myB->cartas[i] = 'T'; }
		if (i >= 35 && i < 48) { myB->cartas[i] = 'W'; }
		if (i >= 48 && i < 51) { myB->cartas[i] = 'w'; }
		if (i >= 51 && i < 66) { myB->cartas[i] = 'R'; }
		if (i >= 66) { myB->cartas[i] = 'C'; }
	}
	myB->size = myB->maxSize;
}

void printBaralho81(baralho myB)
{
	int i = 0;
	printf("(");
	for (i = 0; i < 80; i++)
	{
		printf("%c,", myB.cartas[i]);
	}
	printf("%c,", myB.cartas[i]);
	printf(")");
}
void saveBaralho81(FILE* fp, baralho myB)
{
	int i = 0;
	fprintf(fp, "(");
	for (i = 0; i < 80; i++)
	{
		fprintf(fp, "%c,", myB.cartas[i]);
	}
	fprintf(fp, "%c,", myB.cartas[i]);
	fprintf(fp, ")");
}
void readBaralho81(FILE* fp, baralho* myB)
{
	int i = 0;
	fgetc(fp);//descarto o (
	for (i = 0; i < 80; i++) {
		myB->cartas[i] = fgetc(fp);
		fgetc(fp);//descarto as ,
	}
	myB->cartas[i] = fgetc(fp);
	fgetc(fp);//descarto o )
}
void baralharBaralho81(baralho* myB)
{
	int i = 0;

	for (i = 0; i < myB->size; i++)
	{
		trocaChars(&(myB->cartas[i]), &(myB->cartas[rand() % 81]));
	}
}
void freeBaralho(baralho* myB)
{
	if (myB->cartas != NULL)
	{
		free(myB->cartas);
	}
}
void showbaralho81(char montedecartas[])
{

}

void jogoNovo()
{
	printf("\tescolhi a A");

	baralho myBaralho;

	initBaralho81(&myBaralho, 81);        //inicializar o baralho de 81 cartas
	gotoxy(2, 3);         printBaralho81(myBaralho);

	baralharBaralho81(&myBaralho);
	FILE* fp = NULL;
	fopen_s(&fp, "baralho81.txt", "w");
	if (fp)
	{
		saveBaralho81(fp, myBaralho);
		fclose(fp);
	}

	freeBaralho(&myBaralho);
}
void carregarJogo()
{
	baralho myBaralho;

	initBaralho81(&myBaralho, 81);        //inicializar o baralho de 81 cartas
	gotoxy(2, 3);         printBaralho81(myBaralho);

	baralharBaralho81(&myBaralho);


	FILE* fp = NULL;
	fopen_s(&fp, "baralho81.txt", "w");
	if (fp)
	{
		saveBaralho81(fp, myBaralho);
		fclose(fp);
	}

	freeBaralho(&myBaralho);
}

char menu()
{
	setlocale(LC_ALL, "");        //Escrever caracteres especiais
	char opt = '0';
	do
	{
		system("cls");       //limpa o ecrã
		gotoxy(10, 8); printf("Menu");

		gotoxy(10, 10); printf("A - Partida Nova");
		gotoxy(10, 11); printf("B - Continuar Jogo");
		gotoxy(10, 12); printf("C - Regras de Jogo");
		gotoxy(10, 13); printf("D - Sair");

		gotoxy(0, 15); printf("Escolha uma opção");
		(void)scanf("%c", &opt);    //para ignorar o numero de caracteres devolvidos
	} while (opt != 'A' && opt != 'B' && opt != 'C' && opt != 'D');

	setlocale(LC_ALL, "C");
	return opt;
}
void paginainicial()
{
	system("cls");

	gotoxy(10, 10); printf("A lebre e a tartaruga");
	gotoxy(10, 12); printf("by André Silva");
	espera();
}

int main()
{
	initRandom();
	setFullScreen(true);
	setColor(MY_COLOR_CYAN, MY_COLOR_GRAY);

	paginainicial();

	char opt = 'o';
	opt = menu();
	switch (opt)
	{
	case 'A':
		jogoNovo();
		break;
	case 'B':
		printf("\tA iniciar jogo salvo");
		carregarJogo();

		break;
	case 'C':
		printf("\tA carregar regras");
		espera();
		break;
	case 'D':
		printf("\tA fechar progama");
		espera();
		break;
	default:
		printf("\tERRO");
		break;
	}
	espera();

	return 0;        //no error
}
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define TAM 10

int inst;
int TRun;

typedef struct
{
	char nome[30];
	int id;
	int tamanho;
} APP;

typedef struct
{
	APP Info;
	int prox;
} No;

typedef struct
{
	int IL;
	int Disp;
	No V[TAM];
} LLSE;

void gotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void welcome()
{
	int i;
	printf("  _       __________    __________  __  _________\n");
	printf(" | |     / / ____/ /   / ____/ __ \\/  |/  / ____/\n");
	printf(" | | /| / / __/ / /   / /   / / / / /|_/ / __/   \n");
	printf(" | |/ |/ / /___/ /___/ /___/ /_/ / /  / / /___   \n");
	printf(" |__/|__/_____/_____/\\____/\\____/_/  /_/_____/   \n");
	gotoXY(18, 7);
	printf("loading");
	for(i = 0; i < 3; i++)
	{
		printf(".");
		Sleep(500);
	}
}

void principal()
{

	printf(" ___  ___  ___  _____ _   _   ___  ___ _____ _   _ _   _ \n");
	printf(" |  \\/  | / _ \\|_   _| \\ | |  |  \\/  ||  ___| \\ | | | | |\n");
	printf(" | .  . |/ /_\\ \\ | | |  \\| |  | .  . || |__ |  \\| | | | |\n");
	printf(" | |\\/| ||  _  | | | | . ` |  | |\\/| ||  __|| . ` | | | |\n");
	printf(" | |  | || | | |_| |_| |\\  |  | |  | || |___| |\\  | |_| |\n");
	printf(" \\_|  |_/\\_| |_/\\___/\\_| \\_/  \\_|  |_/\\____/\\_| \\_/\\___/ \n");
	printf("\n\n ________________________________________________________\n |");
	printf("                                                      |\n");
	printf(" |                     1 ---> StoreED                   |\n");
	printf(" |                     2 ---> MyAppsED                  |\n");
	printf(" |                     3 ---> RunED                     |\n");
	printf(" |                     0 ---> EXIT                      |\n");
	printf(" |                                                      |\n");
	printf(" |                                                      |\n");
	printf(" |______________________________________________________|\n");
	gotoXY(23, 16);
	printf("ENTER OPTION:\n");
	gotoXY(36, 16);

}

void menuRun()
{

	printf("\n\n ________________________________________________________\n |");
	printf("                                                      |\n");
	printf(" |           #Para interromper, Digite o ID:            |\n");
	printf(" |            0 ---> Voltar ao Menu:                    |\n");
	printf(" |______________________________________________________|\n");
	gotoXY(23, 9);
	printf("ENTER OPTION:\n");
	gotoXY(36, 9);

}

void menuStore()
{

	printf("\n\n ________________________________________________________\n |");
	printf("                                                      |\n");
	printf(" |           #Para instalar, Digite o ID:               |\n");
	printf(" |            0 ---> Voltar ao Menu:                    |\n");
	printf(" |______________________________________________________|\n");
	gotoXY(23, 18);
	printf("ENTER OPTION:\n");
	gotoXY(36, 18);

}

void menuApps()
{

	printf("\n\n ________________________________________________________\n |");
	printf("                                                      |\n");
	printf(" |             #Para Executar, Digite o ID:             |\n");
	printf(" |              0 ---> Voltar ao Menu:                  |\n");
	printf(" |             -2 ---> Desintalar                       |\n");
	printf(" |______________________________________________________|\n");
	gotoXY(23, 9);
	printf("ENTER OPTION:\n");
	gotoXY(36, 9);

}

int AlocaNo(LLSE Vet[])
{
	int i;
	if(Vet[0].Disp == -1)
	{
		return -2;
	}
	i = Vet[0].Disp;
	Vet[0].Disp = Vet[0].V[Vet[0].Disp].prox;
	return i;

}

void Inserir(APP Temp, LLSE vetor[])
{
	int i, op;
	int indice;
	int indant;
	int indprox;

	indice = AlocaNo(vetor);

	if(indice == -2)
	{
		int tempo = clock();
		printf("LISTA CHEIA!");
		while(clock() - tempo < 1000);
		return;
	}


	if(vetor[0].V[vetor[0].IL].Info.tamanho == 0)
	{
		vetor[0].V[vetor[0].IL].Info = Temp;


		vetor[0].V[vetor[0].IL].prox = -1;

		return;
	}


	for(i = vetor[0].IL; i < TAM; i = vetor[0].V[i].prox)
	{


		if(i == -1)
		{
			break;
		}


		if(Temp.tamanho <= vetor[0].V[i].Info.tamanho && i == vetor[0].IL)
		{
			op = 1;
			break;
		}


		if(Temp.tamanho >= vetor[0].V[i].Info.tamanho && vetor[0].V[i].prox == -1) // ultimo da lista
		{
			op = 2;
			indant = i;
			break;
		}


		if(Temp.tamanho >= vetor[0].V[i].Info.tamanho && Temp.tamanho <= vetor[0].V[vetor[0].V[i].prox].Info.tamanho)
		{
			indant = i;
			indprox = vetor[0].V[i].prox;
			break;
		}
	}


	if(indice != -2)
	{
		if(op == 1)
		{


			vetor[0].V[indice].Info = Temp;


			vetor[0].V[indice].prox = vetor[0].IL;


			vetor[0].IL = indice;

		}
		else if(op == 2)
		{


			vetor[0].V[indice].Info = Temp;

			vetor[0].V[indant].prox = indice;

			vetor[0].V[indice].prox = -1;

		}
		else if(op != 1 && op != 2)
		{
			vetor[0].V[indice].Info = Temp;

			vetor[0].V[indant].prox = indice;

			vetor[0].V[indice].prox = indprox;
		}
	}
}
void liberaNo(LLSE  vetor[], int ind)
{
	vetor[0].V[ind].prox = vetor[0].Disp;
	vetor[0].Disp = ind;
}
void Remover(int id, LLSE vetor[])
{
	int i;
	int op, indant, indprox;

	for(i = vetor[0].IL; i < TAM; i = vetor[0].V[i].prox)
	{
		if(i == -1)
		{
			break;
		}
		if(id == vetor[0].V[i].Info.id && i == vetor[0].IL && vetor[0].V[i].prox == -1)
		{
			op = 3;
			break;
		}

		if(id == vetor[0].V[i].Info.id && i == vetor[0].IL)
		{
			op = 1;
			break;
		}


		if(id == vetor[0].V[vetor[0].V[i].prox].Info.id && vetor[0].V[vetor[0].V[i].prox].prox == -1)
		{
			op = 2;
			indprox = vetor[0].V[i].prox;
			break;
		}


		if(id == vetor[0].V[i].Info.id && i != vetor[0].IL && vetor[0].V[i].prox != -1)
		{

			indprox = vetor[0].V[i].prox;
			break;
		}
		indant = i;
	}

	if(op == 1)
	{
		vetor[0].IL = vetor[0].V[i].prox;
		liberaNo(vetor, i);
	}
	else if(op == 2) //no fim
	{
		vetor[0].V[i].prox = -1;
		liberaNo(vetor, indprox);
	}
	else if(op == 3)
	{
		vetor[0].V[i].Info.tamanho = 0;
		vetor[0].IL = i;
		liberaNo(vetor, i);
	}
	else if(op != 1 && op != 2 && op != 3) //no meio
	{
		vetor[0].V[indant].prox = indprox;
		liberaNo(vetor, i);
	}

}

int imprimir(LLSE Vetor[])
{

	int  k, l, i = 0;
	if(Vetor[0].V[Vetor[0].IL].Info.tamanho == 0)
	{
		return 0;
	}
	k = Vetor[0].IL;
	for(l = Vetor[0].IL; l < TAM + 3; l = Vetor[0].V[l].prox)
	{

		if(l == -1)
		{
			break;
		}
		printf("    %d       %dMB       %s", Vetor[0].V[k].Info.id, Vetor[0].V[k].Info.tamanho, Vetor[0].V[k].Info.nome );
		k = Vetor[0].V[k].prox;
		i++;
	}
	return i;
}
void StoreEDF(LLSE VStore[], LLSE VMyapps[], int quant)
{
	int i, z;
	int op, verif = 0;
	int evit = 0;

	APP Temp;

	do
	{
		system("cls");
		printf("\n\n    ______________________________________________\n ");
		printf("   ID       TAM       NOME\n\n");
		imprimir(VStore);
		printf("    ____________________________________________\n");
		menuStore();
		scanf("%d", &op);
		system("cls");

		if(op == 0)
		{
			return;
		}

		verif = 0;

		for(i = VStore[0].IL; i < TAM; i = VStore[0].V[i].prox)
		{

			if(i == -1)
			{
				break;
			}

			if(VStore[0].V[i].Info.id == op)
			{

				evit = 0;
				for(z = VMyapps[0].IL; z < TAM; z = VMyapps[0].V[z].prox)
				{

					if(z == -1)
					{
						break;
					}

					if(VMyapps[0].V[z].Info.id == op  && VMyapps[0].V[z].Info.tamanho != 0)
					{
						evit = 1;
						break;
					}
				}

				if(evit == 1)
				{
					int tempo = clock();
					printf("APP J%c est%c instalado!\n", 160, 160);
					while(clock() - tempo < 1000);
					verif = 1;
					break;
				}

				Temp = VStore[0].V[i].Info;
				Inserir(Temp, VMyapps);
				inst++;
				verif = 1;
				break;
			}
		}

		if(verif == 0)
		{
			int tempo = clock();
			printf("APP nao existe, digite um ID valido! ou 0 para sair:[AGUARDE]");
			while(clock() - tempo < 2000);
			continue;
		}

		if(verif == 1)
		{
			continue;
		}
	}
	while(1);
}

int LerArq(LLSE StoreED[])
{

	int i, qnt = 0;
	APP Temp;
	APP VERIF;
	FILE *point;

	point = fopen("App.txt", "r");

	if(point == NULL)
	{
		printf("Falha ao abrir arquivo\n");
		exit(1);
	}

	for(i = 1; i < TAM; i++)
	{
		if(qnt == 29)
		{
			return qnt;
		}

		fgets(Temp.nome, 30, point);
		fscanf(point, "%d\n", &Temp.id);
		fscanf(point, "%d\n", &Temp.tamanho);
		qnt++;

		if(Temp.id == VERIF.id)
		{
			fclose(point);
			return qnt;
		};

		Inserir(Temp, StoreED);
		VERIF = Temp;
	}

	fclose(point);
	return qnt;
}
void Inicializar(LLSE StoreED[], LLSE MyAppsED[], LLSE RunED[])
{
	int i, j;

	for(i = 0; i < TAM; i++)
	{
		StoreED->V[i].Info.tamanho = 0;
		StoreED->V[i].Info.id = 0;
		MyAppsED->V[i].Info.tamanho = 0;
		MyAppsED->V[i].Info.id = 0;
		RunED->V[i].Info.tamanho = 0;
		RunED->V[i].Info.id = 0;
	}

	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 10; j++)
		{
			MyAppsED->V[i].Info.nome[j] = ' ';
		}
	}
	for(i = 0; i < TAM; i++)
	{
		StoreED->V[i].prox = i + 1;
		MyAppsED->V[i].prox = i + 1;
		RunED->V[i].prox = i + 1;
	}

	StoreED->V[TAM - 1].prox = -1;
	MyAppsED->V[TAM - 1].prox = -1;
	RunED->V[TAM - 1].prox = -1;
	StoreED->Disp = 0;
	MyAppsED->Disp = 0;
	RunED->Disp = 0;
	StoreED->IL = 0;
	MyAppsED->IL = 0;
	RunED->IL = 0;
}

int IndRem(int app, LLSE vetor[])
{
	int i;

	for(i = vetor[0].IL; i < TAM; i = vetor[0].V[i].prox)
	{

		if(i == -1)
		{
			break;
		}

		if(app == vetor[0].V[i].Info.id)
		{
			return i;
		}
	}

	return -1;
}

void MyAppsEDF(LLSE VMyapps[], LLSE VRun[], int quant)
{
	int  j, id, it, app, aux;
	APP Temp;
	int p;
	do
	{
		system("cls");
		menuApps();

		printf("\n");
		printf("   ##Apps Instalados:\n");
		p = imprimir(VMyapps);
		if(p == 0)
		{
			printf("   -Nenhum app instalado");
		}
		gotoXY(36, 9);
		scanf("%d", &id);

		switch(id)
		{
		case 0:
			return;

		case -2:
			gotoXY(23, 9);
			printf("Digite o ID do jogo para desinstalar:");
			scanf("%d", &app);

			do
			{

				aux = IndRem(app, VMyapps);

				if(aux != -1)
				{
					break;
				}

				if(aux == -1)
				{
					system("cls");
					int tempo = clock();
					printf("Digite um id valido!");
					while(clock() - tempo < 1000);
					scanf("%d", &app);
				}

			}
			while(1);

			Remover(app, VMyapps);
			inst--;


			if(IndRem(app, VRun) == -1)
			{
				continue;
			}
			Remover(app, VRun);
			TRun--;
			continue;
		}

		it = 0;

		for(j = VRun[0].IL; j < TAM; j = VRun[0].V[j].prox)
		{

			if(VRun[0].V[VRun[0].IL].Info.tamanho == 0)
			{
				break;
			}

			if(j == -1)
			{
				break;
			}

			if(VRun[0].V[j].Info.id == id)
			{
				system("cls");
				int tempo = clock();
				printf("App ja esta rodando!\n");
				while(clock() - tempo < 2000);
				it = 1;
			}
		}

		if(it == 1)
		{
			continue;
		}

		it = 0;

		for(j = VMyapps[0].IL; j < TAM; j = VMyapps[0].V[j].prox)
		{
			if(j == -1)
			{
				break;
			}

			if(VMyapps[0].V[j].Info.id == id)
			{
				it = 1;
				Temp = VMyapps[0].V[j].Info;
				Inserir(Temp, VRun);
				TRun++;
				break;
			}
		}

		if(it == 0)
		{
			system("cls");
			int tempo = clock();
			printf("ID inexistente!\nDigite uma ID valida.");
			while(clock() - tempo < 2000);
			continue;
		}

	}
	while(1);
	system("cls");
}

void RunEDF(LLSE VRun[], int TRun)
{
	int x, id, verif;
int p;
	do
	{

		system("cls");
		menuRun();
		printf("\n");
		printf("   ##Apps Instalados:\n");
		p = imprimir(VRun);
		if(p == 0)
		{
			printf("   -Nenhum app rodando");
		}
		gotoXY(36, 9);
		scanf("%d", &id);

		if(id==0)
		{
			return;
		}

		verif = 0;

		for(x = VRun[0].IL; x < TAM; x = VRun[0].V[x].prox)
		{
			if(x == -1)
			{
				break;
			}

			if(VRun[0].V[x].Info.id == id)
			{
				verif = 1;
				Remover(id, VRun);
				TRun--;
				break;
			}
		}

		if(verif == 0)
		{
			system("cls");
			int tempo = clock();
			printf("ID inexistente!");
			while(clock() - tempo < 2000);
			continue;
		}

	}
	while(1);

}

void program()
{
	int quant;
	int resp;
	LLSE StoreED[1];
	LLSE MyAppsED[1];
	LLSE RunED[1];

	Inicializar(StoreED, MyAppsED, RunED);

	quant = LerArq(StoreED);
	quant--;
	welcome();
	system("cls");
	do
	{
		system("cls");
		principal();
		scanf("%d", &resp);
		system("cls");
		switch(resp)
		{
		case 1:
			StoreEDF(StoreED, MyAppsED, quant);
			break;
		case 2:
			MyAppsEDF(MyAppsED, RunED, quant);
			break;
		case 3:
			RunEDF(RunED, TRun);
			break;
		case 0:
			gotoXY(40, 10);
			printf("\t~#Finalizando");
			int i;
			for( i = 0; i < 3; i++)
			{
				printf(".");
				Sleep(500);
			}
			return;
		}

	}
	while(1);
	return;
}

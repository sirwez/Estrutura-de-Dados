#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define TAM 10

int inst;
int TotRun;

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
	int indice_anterior;
	int indice_proximo;

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
			indice_anterior = i;
			break;
		}


		if(Temp.tamanho >= vetor[0].V[i].Info.tamanho && Temp.tamanho <= vetor[0].V[vetor[0].V[i].prox].Info.tamanho)
		{
			indice_anterior = i;
			indice_proximo = vetor[0].V[i].prox;
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

			vetor[0].V[indice_anterior].prox = indice;

			vetor[0].V[indice].prox = -1;

		}
		else if(op != 1 && op != 2)
		{
			vetor[0].V[indice].Info = Temp;

			vetor[0].V[indice_anterior].prox = indice;

			vetor[0].V[indice].prox = indice_proximo;
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
	int op, indice_anterior, indice_proximo;

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
			indice_proximo = vetor[0].V[i].prox;
			break;
		}


		if(id == vetor[0].V[i].Info.id && i != vetor[0].IL && vetor[0].V[i].prox != -1)
		{

			indice_proximo = vetor[0].V[i].prox;
			break;
		}
		indice_anterior = i;
	}

	if(op == 1)
	{
		vetor[0].IL = vetor[0].V[i].prox;
		liberaNo(vetor, i);
	}
	else if(op == 2) //no fim
	{
		vetor[0].V[i].prox = -1;
		liberaNo(vetor, indice_proximo);
	}
	else if(op == 3)
	{
		vetor[0].V[i].Info.tamanho = 0;
		vetor[0].IL = i;
		liberaNo(vetor, i);
	}
	else if(op != 1 && op != 2 && op != 3) //no meio
	{
		vetor[0].V[indice_anterior].prox = indice_proximo;
		liberaNo(vetor, i);
	}

}

void imprimir(LLSE Vetor[])
{

	int  k, l;
	if(Vetor[0].V[Vetor[0].IL].Info.tamanho == 0)
	{
		return;
	}
	k = Vetor[0].IL;
	for(l = Vetor[0].IL; l < TAM + 3; l = Vetor[0].V[l].prox)
	{

		if(l == -1)
		{
			break;
		}
		printf("        %d -- %dMB -- %s \n\n", Vetor[0].V[k].Info.id, Vetor[0].V[k].Info.tamanho, Vetor[0].V[k].Info.nome );
		k = Vetor[0].V[k].prox;
	}
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
		printf("\n\n    ________________________________________________________\n ");
		printf("                                                      \n");
		imprimir(VStore);
		printf("                                                      \n");
		printf("    ______________________________________________________\n");

		printf("\n\n        Digite o ID ou 0 para sair:");
		scanf("%d", &op);


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

int EncontrarIndiceRemover(int app, LLSE vetor[])
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
	int  j, id, flag, app, aux;
	APP Temp;

	do
	{
		printf("ID:  Tamaho:  Nome:");
		printf(" Digite um ID para executar um APP");
		printf(" 0:Voltar ao menu principal");
		printf(" -2:Desinstalar um APP");

		imprimir(VMyapps);
		scanf("%d", &id);

		switch(id)
		{
		case 0:
			return;

		case -2:

			printf("Digite o ID do jogo para desisntalar:");
			scanf("%d", &app);

			do
			{

				aux = EncontrarIndiceRemover(app, VMyapps);

				if(aux != -1)
				{
					break;
				}

				if(aux == -1)
				{

					int tempo = clock();
					printf("Digite um id valido!:");
					while(clock() - tempo < 1000);
					scanf("%d", &app);
				}

			}
			while(1);

			Remover(app, VMyapps);
			inst--;


			if(EncontrarIndiceRemover(app, VRun) == -1)
			{
				continue;
			}
			Remover(app, VRun);
			TotRun--;
			continue;
		}

		flag = 0;

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
				int tempo = clock();
				printf("App ja esta rodando!\n");
				while(clock() - tempo < 2000);
				flag = 1;
			}
		}

		if(flag == 1)
		{
			continue;
		}

		flag = 0;

		for(j = VMyapps[0].IL; j < TAM; j = VMyapps[0].V[j].prox)
		{
			if(j == -1)
			{
				break;
			}

			if(VMyapps[0].V[j].Info.id == id)
			{
				flag = 1;
				Temp = VMyapps[0].V[j].Info;
				Inserir(Temp, VRun);
				TotRun++;
				break;
			}
		}

		if(flag == 0)
		{
			int tempo = clock();
			printf("ID inexistente!Digite uma ID v%clida", 160);
			while(clock() - tempo < 2000);
			continue;
		}

	}
	while(1);
}

void RunEDF(LLSE VRun[], int TotRun)
{
	int x, id, verif;

	do
	{
		
		printf("ID:  Tamaho:  Nome:");
		imprimir(VRun);
		
		printf(">Digite um ID para interromper um APP");
		
		printf(">0:Voltar ao menu principal");
		
		scanf("%d", &id);

		switch(id)
		{

		case 0:
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
				TotRun--;
				break;
			}
		}

		if(verif == 0)
		{
			int tempo = clock();
			printf("ID inexistente!");
			while(clock() - tempo < 2000);
			continue;
		}

	}
	while(1);

}

int main()
{
	int quant;
	char resp;
	LLSE StoreED[1];
	LLSE MyAppsED[1];
	LLSE RunED[1];

	Inicializar(StoreED, MyAppsED, RunED);

	quant = LerArq(StoreED);
	quant--;
welcome();
	do
	{

		scanf(" %c", &resp);

		switch(resp)
		{
		case 's':
			StoreEDF(StoreED, MyAppsED, quant);
			break;
		case 'm':
			MyAppsEDF(MyAppsED, RunED, quant);
			break;
		case 'r':
			RunEDF(RunED, TotRun);
			break;
		case 'd':
			printf("\t-=-=-=-=-MOBILE-ED FOI FINALIZADO!-=-=-=-=-");
			return 0;
		}

	}
	while(1);
	return 0;
}

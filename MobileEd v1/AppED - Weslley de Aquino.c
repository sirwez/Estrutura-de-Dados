	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <windows.h>
	#include <time.h>
	#include <conio.h>
	#define M 3
	#define TAM 5
	
	typedef struct App
	{
		char nome[15];
		int tam;
	} App;
	
	typedef struct Area
	{
		char nome[15];
	} Area;
	
	int cont = 0;
	int ctrl = 0;
	int C = 0, L = 0;
	int contRum = 0;
	int contMA = 0;
	char ALEATORIO[15];
	
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
	void menu()
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
		printf(" |                     2 ---> Meus AppEd                |\n");
		printf(" |                     3 ---> AppsRumED                 |\n");
		printf(" |                     0 ---> EXIT                      |\n");
		printf(" |                                                      |\n");
		printf(" |                                                      |\n");
		printf(" |______________________________________________________|\n");
		gotoXY(23, 16);
		printf("ENTER OPTION:\n");
		gotoXY(36, 16);
	
	}
	void submenu()
	{
	
		printf("\n\n ________________________________________________________\n |");
		printf("                                                      |\n");
		printf(" |                     1 ---> Meus Apps                 |\n");
		printf(" |                     2 ---> Excluir App               |\n");
		printf(" |                     3 ---> Area de Trabalho          |\n");
		printf(" |                     0 ---> EXIT                      |\n");
		printf(" |                                                      |\n");
		printf(" |______________________________________________________|\n");
		gotoXY(23, 9);
		printf("ENTER OPTION:\n");
		gotoXY(36, 9);
	
	}

		void submenu2()
	{
	
		printf("\n\n ________________________________________________________\n |");
		printf("                                                      |\n");
		printf(" |                     1 ---> Executar                  |\n");
		printf(" |                     2 ---> Rodando                   |\n");
		printf(" |                     3 ---> Pausar                    |\n");
		printf(" |                     0 ---> EXIT                      |\n");
		printf(" |                                                      |\n");
		printf(" |______________________________________________________|\n");
		gotoXY(23, 9);
		printf("ENTER OPTION:\n");
		gotoXY(36, 9);
	
	}
	
	void StoreEd(App dados[], App instalados[], Area matriz[M][M], 	Area reserva[]);
	void InstalarApp(App dados[], App instalados[], Area matriz[M][M], 	Area reserva[]);
	int office (App instalados[], Area matriz[M][M], 	Area reserva[]);
	int Rum(Area matriz[M][M], Area vetRum[]);
	int Running (Area vetRum[]);
	int PauseRum(Area vetRum[]);
	void MyApps(App instalados[]);
	int ExcluirApp(App instalados[], Area matriz[M][M], 	Area reserva[]);
	void atualizarMatriz (Area matriz[M][M], 	Area reserva[]);
	void areatrab(Area reserva[]);
	void attarea (Area matriz[M][M], 	Area reserva[]);
	
	int switch2(App instalados[], Area matriz [M][M], Area reserva[])
	{
		int escolha2;
		do
		{
			system("cls");
			submenu();
			scanf("%d", &escolha2);
			switch(escolha2)
			{
			case 1:
				MyApps(instalados);
				break;
			case 2:
				ExcluirApp(instalados, matriz, reserva);
				break;
			case 3:
				areatrab(reserva);
				break;
			case 0:
				break;
			default:
				printf("Invalid Option");
				break;
			}
			system("cls");
		}
		while(escolha2 != 0);
		return 0;
	}
	int switch3(Area matriz[M][M], Area vetRum[])
	{
		int escolha3;
		do
		{
			submenu2();
			scanf("%d", &escolha3);
			switch(escolha3)
			{
			case 1:
				Rum(matriz, vetRum);
				break;
			case 2:
				Running(vetRum);
				break;
			case 3:
				PauseRum(vetRum);
				break;
			case 0:
				break;
			default:
				printf("Invalid Option");
				break;
			}
			system("cls");
		}
		while(escolha3 != 0);
		return 0;
	}
	
	void arquivo(App dados[], FILE *arq)
	{
		int i = 0;
		int j, t, temp;
		char tempS[15];
	
		if(arq == NULL)
		{
			printf("Erro, não foi possivel abrir o arquivo\n");
			return;
		}
	
		else
		{
			while( (fscanf(arq, "%s %d\n", dados[i].nome, &dados[i].tam)) != EOF )
			{
				if(i == 0)
				{
	
				}
				else
				{
					for( t = 0; t <= cont; t++ )
					{
						for( j = t + 1; j <= cont; j++ )
						{
							if( dados[t].tam > dados[j].tam )
							{
								temp = dados[t].tam;
								dados[t].tam = dados[j].tam;
								dados[j].tam = temp;
	
								strcpy(tempS, dados[t].nome);
								strcpy(dados[t].nome, dados[j].nome);
								strcpy(dados[j].nome, tempS);
							}
						}
					}
				}
				i++;
				cont++;
			}
		}
	}
	
	int main(void)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		WORD saved_attributes;
	
		GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
		saved_attributes = consoleInfo.wAttributes;
	
		FILE *arq;
		App dados[TAM];
		App instalados[TAM];
		Area matriz [M][M];
		Area vetRum[TAM];
		Area reserva[M * M];
	
		int escolha;
		arq = fopen("App.txt", "r");
		arquivo(dados, arq);
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
		welcome();
		SetConsoleTextAttribute(hConsole, saved_attributes);
		system("cls");
		do
		{
			menu();
			scanf("%d", &escolha);
			switch(escolha)
			{
			case 1:
				StoreEd(dados, instalados, matriz, reserva);
				system("cls");
				break;
			case 2:
				system("cls");
				switch2(instalados, matriz, reserva);
				system("cls");
				break;
			case 3:
				system("cls");
				switch3(matriz, vetRum);
				system("cls");
				break;
			case 0:
				break;
			default:
				SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
				printf("Invalid Option");
				SetConsoleTextAttribute(hConsole, saved_attributes);
				break;
			}
		}
		while(escolha != 0);
	
		fclose(arq);
		gotoXY(16, 25);
		return 0;
	}
	void StoreEd(App dados[], App instalados[], Area matriz[M][M], 	Area reserva[])
	{
		int i;
		char choice;
		system("cls");
		printf("\n\n    ________________________________________________________\n ");
		printf("                                                      \n");
		for(i = 0; i < cont; i++)
		{
			printf("        %d - App: %s -- Tamanho:%d\n\n", i + 1, dados[i].nome, dados[i].tam);
		}
		printf("                                                      \n");
		printf("    ______________________________________________________\n");
	
		printf("\n\n        .::Instalar um app? S = Sim, N =  Nao::.");
		scanf(" %c", &choice);
		if(choice == 'S' || choice == 's')
		{
			InstalarApp(dados, instalados, matriz, reserva);
		}
		else
		{
			return;
		}
	
	
	}
	void InstalarApp(App dados[], App instalados[], Area matriz[M][M], 	Area reserva[])
	{
		int choice2;
		int i;
		printf("\n>>Digite o numero referente ao App que deseja instalar:\n");
		scanf("%d", &choice2);
		for(i = 0; i < TAM; i++)
		{
			if(strcmp(instalados[i].nome, dados[choice2 - 1].nome) == 0)
			{
				printf("App ja instalado");
				getch();
				return;
			}
		}
		system("cls");
		//-1 pois na função acima coloquei i+1 para definir o numero do app
		strcpy(instalados[ctrl].nome, dados[choice2 - 1].nome);
		instalados[ctrl].tam = dados[choice2 - 1].tam;
		office(instalados, matriz, reserva);
		ctrl++;
	
	}
	int office (App instalados[], Area matriz[M][M], 	Area reserva[M*M])
	{
	
		if(L == M && C == M)
		{
			printf("Area de Trabalho cheia, mas seu app foi instalado com sucesso!!");
			system("cls");
			return 0;
		}
		else
		{
			if (C < M)
			{
				strcpy(matriz[L][C].nome, instalados[ctrl].nome);
				C++;
			}
			else
			{
				C = 0;
				strcpy(matriz[L][C].nome, instalados[ctrl].nome);
				C++;
				L++;
			}
			contMA++;
		}
		attarea(matriz, reserva);
		return 0;
	}
	int Rum(Area matriz[M][M], Area vetRum[])
	{
		int i, j, var = 0;
		int k = 0;
		char esc;
		char tempo[15];
		if(ctrl == 0)
		{
	
			printf("\n                    Nenhum app instalado                     \n");
		}
		else
		{
			printf("\nEscolha um App para executar:\n");
	
			for(i = 0; i <= L; i++)
			{
				if(i < L)
				{
					for(j = 0; j < M; j++)
					{
						if(k < contMA)
							printf("%s\n", matriz[i][j].nome);
						k++;
					}
				}
				if(i == L)
				{
					for(j = 0; j <= C; j++)
					{
						if(k < contMA)
							printf("%s\n", matriz[i][j].nome);
						k++;
					}
	
				}
	
			}
			printf(">>Digite o nome do App:");
			scanf("%s", tempo);
			for(i = 0; i < L + 1; i++)
			{
				for(j = 0; j < C + 1; j++)
				{
					if(strcmp(matriz[i][j].nome, tempo) == 0)
					{
						strcpy(vetRum[contRum].nome, tempo);
						contRum++;
						var++;
					}
				}
			}
			if(var == 0)
			{
				printf("\n>>404 - App nao encontrado<<\n\n.::Procurar novamente? [S - sim, N - nao]::.\n");
				scanf(" %c", &esc);
				if(esc == 'S' || esc == 's')
				{
					Rum(matriz, vetRum);
				}
				else
				{
					return 0;
				}
			}
		}
		getch();
		system("cls");
		return 0;
	}
	int Running (Area vetRum[])
	{
		int i;
		if(contRum == 0)
		{
			printf("\n                    Nenhum app rodando                     \n");
		}
		else
		{
			printf("\n>>Apps Rodando:\n");
			for(i = 0; i < contRum; i++)
			{
				printf("%s\n", vetRum[i].nome);
			}
		}
		getch();
		return 0;
	}
	int PauseRum(Area vetRum[])
	{
		char tempo[15], esc;
		int var2, ctz, i;
		Area vetReserva[TAM];
		var2 = contRum;
		char nome[TAM] = "Nada";
		ctz = 0; //ver se existe app;
	
		if(contRum == 0)
		{
			printf("\n                    Nenhum app rodando                     \n");
		}
		else
		{
	
			printf(">>Digite o nome do App:");
			scanf("%s", tempo);
			for(i = 0; i < contRum; i++)
			{
				if(strcmp(tempo, vetRum[i].nome) == 0)
				{
					strcpy(vetRum[i].nome, nome);
					var2--;
					ctz++;
				}
			}
	
			if(ctz == 0)
			{
				printf("\n>>404 - App nao encontrado<<\n\n.::Procurar novamente? [S - sim, N - nao]::.\n");
				scanf(" %c", &esc);
				system("cls");
				if(esc == 'S' || esc == 's')
				{
					PauseRum(vetRum);
				}
				else
				{
					return 0;
				}
			}
			else
			{
	
				if(var2 < contRum)
				{
					contRum--;
					for(i = 0; i < contRum + 1; i++)
					{
						if(vetRum[i].nome != nome)
						{
							strcpy(vetReserva[i].nome, vetRum[i].nome);
						}
						else
						{
							strcpy(vetReserva[i].nome, vetRum[i + 1].nome);
						}
					}
					for(i = 0; i < contRum; i++)
					{
						strcpy(vetRum[i].nome, vetReserva[i].nome);
					}
				}
			}
		}
		getch();
		system("cls");
		return 0;
	}
	void MyApps(App instalados[])
	{
		int i;
		system("cls");
	
		printf("\n\n ________________________________________________________\n |");
		printf("                                                      |\n");
		printf(" |                                                      |\n");
		if(ctrl == 0)
			printf(" |   Nenhum app instalado                               |\n");
		else
		{
			for(i = 0; i < ctrl; i++)
			{
				printf(" |     %s - %d                                    |\n", instalados[i].nome, instalados[i].tam);
			}
		}
		printf(" |                                                      |\n");
		printf(" |______________________________________________________|\n");
		getch();
		return;
	}
	int ExcluirApp(App instalados[], Area matriz[M][M], 	Area reserva[])
	{
		char tempo[15], esc;
		int var3, ctz, i, j;
		var3 = ctrl;
		int t, temp;
		char tempS[15];
		ctz = 0;
		printf(">>Digite o nome do App:");
		scanf("%s", tempo);
	
		for(i = 0; i < ctrl; i++)
		{
			if(strcmp(tempo, instalados[i].nome) == 0)
			{
				instalados[i].tam = 10000;
				var3--;
				ctz++;
			}
		}
		if(ctz == 0)
		{
			printf("\n>>404 - App não encontrado<<\n\n.::Procurar novamente? [S - sim, N - nao]::.\n");
			scanf(" %c", &esc);
			system("cls");
			if(esc == 'S' || esc == 's')
			{
				ExcluirApp(instalados, matriz, reserva);
			}
			else
			{
				return 0;
			}
		}
	
		else
		{
	
			if(var3 < ctrl)
			{
				i = 0;
				strcpy(ALEATORIO, tempo);
				atualizarMatriz(matriz, reserva);
				for(t = 0; t < ctrl; t++)
				{
					j = 0;
					if(instalados[t].tam == 10000)
					{
						instalados[t] = instalados[TAM];
					}
					else
					{
						temp = instalados[t].tam;
						instalados[t].tam = instalados[j].tam;  //organiza os numeros
						instalados[j].tam = temp;
	
						strcpy(tempS, instalados[t].nome);
						strcpy(instalados[t].nome, instalados[j].nome); //organiza os nomes
						strcpy(instalados[j].nome, tempS);
					}
					j++;
				}
				ctrl--;
			}
		}
	
		return 0;
	}
	void atualizarMatriz (Area matriz[M][M], 	Area reserva[])
	{
	
		Area reserva2[M * M];
		int i, j;
		int pq = 0;
	
		if(C == 0 && L == 0)
		{
			return;
		}
		else
		{
			for(i = 0; i < M; i++)
			{
				for(j = 0; j < M; j++)
				{
					if(strcmp(ALEATORIO, matriz[i][j].nome) == 0)
					{
						continue;
					}
					else
					{
	
						strcpy(reserva2[pq].nome, matriz[i][j].nome);
						pq++;
					}
				}
			}
			pq = 0;
			for(i = 0; i < M; i++)
			{
				for(j = 0; j < M; j++)
				{
	
					strcpy(matriz[i][j].nome, reserva2[pq].nome);
					pq++;
				}
			}
	
			attarea(matriz, reserva);
			contMA--;
		}
	
	}
	void areatrab(Area reserva[])
	{
		int p = 0;
		while(p < contMA)
		{
			printf("%s\n", reserva[p].nome);
			p++;
		}
		getch();
	}
	void attarea (Area matriz[M][M], Area reserva[])
	{
		int i, j, p = 0;
		for(i = 0; i < M; i++)
			for(j = 0; j < M; j++)
			{
				strcpy(reserva[p].nome, matriz[i][j].nome);
				p++;
			}
	}

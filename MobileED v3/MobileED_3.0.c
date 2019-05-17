#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 20
void lerStore();//Armazena os dados do arquivo store.txt em StoreED
void ShowStore();//Exibe os apps de StoreED
void MeusApps();//Exibe os apps de MeusAppsED
void Running();//Exibe os apps de AppRumED
void menuInicio(); //Exibe o menu principal e a matriz com os apps instalados
void AtualizaMatriz(); //Atualiza a matriz de apps abertos de acordo com MeusAppsED
void inicializarStore();
void inicializarMeusApps();
void inicializarAppRum();
void inicializarFila();
void InstalarApp();//Copia um app para a Fila de Apps e remove-o da StoreED
void AbrirApp(); // Copia um app de MeusAppsED para AppRumED
void DesinstalarApp(); //Remove Apps de MeusAppsED
void PararApp();//Remove um app de AppRumED
void removerDaStore();//remove um app de StoreED
void fila_Apps();//Função que lida com a implementação de fila do programa
void empilhar();//Adiciona apps no fim da pilha AppsPilha
void desempilhar();//Remove um app no fim da pilha

//funções extras
void Configuracao(); //exibe um menu com algumas opcoes
void visor(); //permite alterar esquema de cores
void armazenamento();//Calcula o espaço ocupado pelos apps num dispositivo real
void sobre();

void mostraStore();
void mostraMeusApps();
void MostraAppRum();
void mostraFila();

typedef struct APP {
	int id;
	char nome[12];
	float tam;
} app;

typedef struct llv {
	app vet[size];
	int il;
	int ia; 
	int fl;
	int fa;
	int count;
} LLV;

typedef struct NO {
	app info;
	int prox;
} no;

typedef struct NODE {
	app info;
	int ant;
	int prox;
}node;

typedef struct llse{
	no n[size];
	int disp;
	int il;
	int count;
} LLSE;

typedef struct llde{
	node m[size];
	int disp;
	int il; // il = inicio da lista
	int fl; // fl = fim da lista
	int count;
}LLDE;

typedef struct fila{
	node m[3];
	int il;
	int fl;
	int disp;
	int tamanho;
}FILA;

//variavesis globais
LLV StoreED;
LLSE MeusAppsED;
LLDE AppRumED;
FILA filaED;
LLSE AppsPilha;//Implementação de Pilha
app matrizApps[3][3];//matriz que irá exibir apps na tela principal do mobileED
int colorSwitch;

int main(){
	inicializarStore(&StoreED);
	inicializarMeusApps(&MeusAppsED);
	inicializarAppRum(&AppRumED);
	inicializarMeusApps(&AppsPilha);
	inicializarFila(&filaED);
	lerStore();
	menuInicio();
	system("cls");
	printf("\n\n\n        Obrigado por testar!\n\n\n");
	return 0;
}

void menuInicio(){
	int i,j,k=0;
	colorSwitch = 1;
	char choice;
	 while (choice != 's'){
      system("cls");
      
      AtualizaMatriz();
	  system("cls");
	  if(colorSwitch == 1){
          system("color 0f");
      }
      if(colorSwitch == 2){
		  system("color 3f");
	  }
	  printf("---------------------------------------------------\n");
	  printf("             ** MobileED 2.0 **                    \n");
	  printf("---------------------------------------------------\n\n");
	  printf("\n\n\n\n");
	  
		  for(i=0; i<3; i++){
				for(j=0; j<3; j++) {
					printf("   %s    ",matrizApps[i][j].nome);
					k++;
				}
				if(k > 0)
				   printf("\n\n\n");
	        }
	  
		  
	  printf("\n\n\n\n\n-------------------------------------------------------------------\n");
	  printf("  1- Store || 2 - APPS || 3 - RUN  || 4 - Ajustes || 0 - Desligar\n");
	  printf("-------------------------------------------------------------------\n");
	  printf("Selecione uma das opcoes acima: ");
	  scanf(" %c",&choice);
	
		    if(choice == '1') {
				ShowStore();
			}
			else
			{
				if(choice == '2'){
					MeusApps();
				}
				if(choice == '3'){
					Running();
				}
				if(choice == '4'){
					Configuracao();
				}
				if(choice =='0'){
					return;
				}
			}
    }
	return;
}

void AtualizaMatriz(){
	int i,j,k=0,t=MeusAppsED.il;
	//inicializar a matriz
	for(i=0; i<3; i++){
		for(j=0; j<3; j++) {
			strcpy(matrizApps[i][j].nome,""); 
		}
	}
	//Copiar as informações de MeusAppsED
	if(MeusAppsED.count > 0){
		for(i=0; i<3; i++){
			for(j=0; j<3; j++) {
				strcpy(matrizApps[i][j].nome,MeusAppsED.n[t].info.nome); 
				k++;
				t= MeusAppsED.n[t].prox;
				if(k == MeusAppsED.count)
					break;
			}
			if(k == MeusAppsED.count)
				break;
		}
	}
	return;
}

void ShowStore(){
	int flag;
	int i,id,target;
	
	do{
		if(colorSwitch == 1){
		    system("color 0e");
        } else{
	     if(colorSwitch == 2){
	     	system("color 3e");
	    }
	     }
		flag = 0;
	    system("cls");
	    printf("---------------------------------------------------\n");
		printf("             ** Loja de Aplicativos **          \n");
		printf("---------------------------------------------------\n");
		printf("   id    |    app   |    tamanho do app       \n");
		printf("---------------------------------------------------\n\n");
		if (StoreED.count == 0){
			printf("\n\n\n      Todos os aplicativos ja foram instalados!\n\n");
		} else {
			for(i=StoreED.il; i<=StoreED.fl; i++){
				printf("   %d     %s         %.2f MB\n",StoreED.vet[i].id,StoreED.vet[i].nome,StoreED.vet[i].tam);
			}
			
		}
		printf("\n---------------------------------------------------\n");
		printf("          ||      0 -  VOLTAR         ||      \n");
		printf("---------------------------------------------------\n");
		printf("Selecione o Id do aplicativo que deseja instalar: ");
		scanf("%d",&id);
		if (id == 0) {
		     return;
	    }
	    else {
	    	for(i=StoreED.il; i<=StoreED.fl; i++){
				if (id == StoreED.vet[i].id) {
					target = i;
					flag = 1;
				}
				if(flag == 1)
					break;
			}
			if(flag == 1){
			    fila_Apps(target);
		    } else{
				if(flag == 0){
					system("cls");
					printf("\n\n\n\n\n\n              opcao invalida!\n\n\n\n\n");
					system("pause");
					id = 99;
				}
			}
        }
        
	}while( id != 0);
	return;
}

void MeusApps(){
	int i,id,alvo,choice,flag = 0;
	
	do{
       if(colorSwitch == 1){
	    	system("color 07");
       }
	   if(colorSwitch == 2){
	    	system("color 70");
	   }
	    system("cls");
	    flag =0;
	    printf("---------------------------------------------------\n");
		printf("                 ** Apps Instalados **               \n");
		printf("---------------------------------------------------\n");
		printf("   id  | app   |    tamanho do app       \n");
		printf("---------------------------------------------------\n\n\n");
		if (MeusAppsED.count == 0){
			printf("\n\n\n\n\n        << Nao ha apps instalados no momento >> \n\n\n\n\n\n\n\n");
			printf("\n\n\n---------------------------------------------------\n");
			printf("                ||   0 - MENU    ||                    \n");
			printf("---------------------------------------------------\n");
			printf("Selecione uma opcao acima: ");
			scanf("%d",&id);
		} 
		else{
			flag = 0;
			for(i=MeusAppsED.il; MeusAppsED.n[i].prox!=-2;i=MeusAppsED.n[i].prox){
				printf("   %d     %s      %.2f MB\n",MeusAppsED.n[i].info.id,MeusAppsED.n[i].info.nome,MeusAppsED.n[i].info.tam);
				if(MeusAppsED.n[i].prox==-1)
					break;
			}
		
			printf("\n\n\n---------------------------------------------------\n");
			printf("                ||   0 - MENU    ||                    \n");
			printf("---------------------------------------------------\n");
			printf("Selecione o Id de um dos aplicativos disponiveis: ");
			scanf("%d",&id);
	    
	    	for(i=MeusAppsED.il; MeusAppsED.n[i].prox!=-2;i=MeusAppsED.n[i].prox){
				if (id == MeusAppsED.n[i].info.id) {
					alvo = i;
					flag = 1;
				}
				if(MeusAppsED.n[i].prox==-1 || flag == 1)
					break;
			}
			
		    if(flag == 1){
		        system("cls");
		    	printf("---------------------------------------------------\n");
		    	printf("  App selecionado: %s \n",MeusAppsED.n[alvo].info.nome);
		    	printf("---------------------------------------------------\n\n\n");
		    	printf("     1 - Abrir\n");
		    	printf("     2 - Desinstalar \n\n\n");
		    	printf("---------------------------------------------------\n");
		    	printf("O que voce deseja fazer? ");
		    	scanf("%d",&choice);
		
		    	switch(choice){
		    	    case 1:
		    	    	AbrirApp(alvo);
		    	    	break;
		    	    case 2:
		    	    	DesinstalarApp(alvo);
		    	    	break;
		    	    default:
		    	    	printf("\nOpção invalida!\n");
		    	    	break;
		    	}
			}
			
		}	
	}while(id != 0);
	return;
}

void Running(){
	int i,target,id = 1,flag;
    while( id != 0){
    	flag = 0;
	    system("cls");
	    if(colorSwitch == 1){
	        system("color 0a");
		}else{
	    if(colorSwitch == 2){
			system("color 3a");
		}}
	    printf("---------------------------------------------------\n");
	    printf("          ** Aplicativos abertos **                 \n");
		printf("---------------------------------------------------\n");
		printf("   id  | app   |    tamanho do app       \n");
		printf("---------------------------------------------------\n\n");
		if (AppRumED.count == 0){
			printf("\n\n\n\n\n\n   << Nao ha apps abertos no momento >>   \n\n\n\n\n");
		}
		else{
			for(i=AppRumED.il; AppRumED.m[i].prox!=-2; i= AppRumED.m[i].prox){
				printf("   %d     %s      %.2f MB\n",AppRumED.m[i].info.id,AppRumED.m[i].info.nome,AppRumED.m[i].info.tam);
				if(AppRumED.m[i].prox == -1)
					break;
			}
		}
		printf("\n\n\n\n\n");
		printf("---------------------------------------------------\n");
		printf("                ||   0 - VOLTAR    ||                    \n");
		printf("---------------------------------------------------\n");
		printf("Selecione o Id de um app para fecha-lo: ");
		scanf("%d",&id);
		if (id == 0) {
		     return;
	    }
	    else {
	    	for(i=AppRumED.il; AppRumED.m[i].prox!=-2; i= AppRumED.m[i].prox){
				if (id == AppRumED.m[i].info.id) {
					flag = 1;
					target = i;
					PararApp(target);
				}
				if(AppRumED.m[i].prox == -1 || flag == 1)
					break;
			}
			if(flag == 0){
				system("cls");
				printf("\n\n\n         Opcao errada!                  \n\n\n");
				id = 99;
				system("pause");
			}
	}
	}
	return;
}

void fila_Apps(int t){
    int i,proxDisp,ant,target,flag=0;
    target = t;
    //primeira inserção (fila vazia)
    if(filaED.tamanho == 0){
    	filaED.il=0;
        filaED.disp = 1;
        filaED.m[0].info.id = StoreED.vet[t].id;
        strcpy(filaED.m[0].info.nome,StoreED.vet[t].nome);
        filaED.m[0].info.tam = StoreED.vet[t].tam;
        filaED.tamanho++;
        StoreED.count--;
        removerDaStore(target);
    }
    else{
      //fila ainda possui espaço (inserir no início)
      if(filaED.tamanho < 3){
          for(i = filaED.disp; filaED.m[i].prox!=-2; i=filaED.m[i].prox){
          	if(filaED.m[i].info.id == 0){
				proxDisp = filaED.m[filaED.disp].prox;
				filaED.m[filaED.disp].info.id = StoreED.vet[t].id;
                strcpy(filaED.m[filaED.disp].info.nome,StoreED.vet[t].nome);
                filaED.m[filaED.disp].info.tam = StoreED.vet[t].tam;
                filaED.m[filaED.disp].ant = -1;
                filaED.m[filaED.il].ant = filaED.disp;
                filaED.m[filaED.disp].prox = filaED.il;
                filaED.il = filaED.disp;;
                filaED.disp = proxDisp;
			    filaED.tamanho++;
			    flag = 1;
			    StoreED.count--;
				removerDaStore(target);	  
			  }
			  if(flag == 1 || filaED.m[i].prox == -1)
			  	break;
		  }
	  }else{
      //fila Cheia
      flag = filaED.fl;
	  InstalarApp(flag);
	  ant = filaED.m[filaED.fl].ant;
	  filaED.m[filaED.fl].info.id = 0;
	  filaED.disp = filaED.fl;
	  filaED.fl = ant;
	  filaED.m[filaED.disp].ant = -1;
	  filaED.m[filaED.fl].prox = -1;
	  filaED.tamanho--;
	  fila_Apps(target);
	  }
    }
    return;
}

void removerDaStore(int target){
	int i,j,flag=0;
	if (StoreED.count == 0) {
		inicializarStore(&StoreED);
		return;
	} else {
		if (StoreED.count > 0) {
			for(i=StoreED.il; i<= StoreED.fl; i++){
				if((StoreED.fl - target) < (target-StoreED.il)){
					for(j=target; j<StoreED.fl;j++){
						StoreED.vet[j].id = StoreED.vet[j+1].id;
						strcpy(StoreED.vet[j].nome,StoreED.vet[j+1].nome);
						StoreED.vet[j].tam = StoreED.vet[j+1].tam;
					}
					StoreED.fl--;
				} else{
					if((StoreED.fl - target) > (target-StoreED.il)){
						for(j=target; j>=StoreED.il; j--){
							StoreED.vet[j].id = StoreED.vet[j-1].id;
							strcpy(StoreED.vet[j].nome,StoreED.vet[j-1].nome);
							StoreED.vet[j].tam = StoreED.vet[j-1].tam;
						}
						StoreED.il++;
					}
					else{
						if((StoreED.fl - target) == (target-StoreED.il)){
					        for(j=target; j<StoreED.fl;j++){
					      	    StoreED.vet[j].id = StoreED.vet[j+1].id;
					    	    strcpy(StoreED.vet[j].nome,StoreED.vet[j+1].nome);
					    	    StoreED.vet[j].tam = StoreED.vet[j+1].tam;
					        }
					        StoreED.fl--;
							}
					}
				}
				if (flag!=5)
					break;
			}
		}
	}
	return;
}

void InstalarApp(int t){
	int i,j,flag=0,proxDisp,aux;
	//primeira inserção
	if(MeusAppsED.il == -1){
		MeusAppsED.il = 0;
		MeusAppsED.n[MeusAppsED.il].info.id = filaED.m[t].info.id;
		strcpy(MeusAppsED.n[MeusAppsED.il].info.nome,filaED.m[t].info.nome);
		MeusAppsED.n[MeusAppsED.il].info.tam = filaED.m[t].info.tam;
		MeusAppsED.disp = 1;
		MeusAppsED.n[MeusAppsED.il].prox = -1;
		MeusAppsED.count++;
		flag = 1;
	}
	else{
	//Inicia a inserção em MeusAppsED
		for((i = MeusAppsED.il); (MeusAppsED.n[i].prox !=-2); (i = MeusAppsED.n[i].prox)){
			//inserção no inicio
			if(filaED.m[t].info.tam > MeusAppsED.n[i].info.tam){
				flag = 1;
				if(i == MeusAppsED.il){
					proxDisp = MeusAppsED.n[MeusAppsED.disp].prox;
					MeusAppsED.n[MeusAppsED.disp].info.id = filaED.m[t].info.id;
					strcpy(MeusAppsED.n[MeusAppsED.disp].info.nome,filaED.m[t].info.nome);
					MeusAppsED.n[MeusAppsED.disp].info.tam = filaED.m[t].info.tam;
					MeusAppsED.n[MeusAppsED.disp].prox = MeusAppsED.il;
					MeusAppsED.il = MeusAppsED.disp;
					MeusAppsED.disp = proxDisp;					
					MeusAppsED.count++;
					//if (count == size)
					//	MeusAppsED.disp = -2;
				}
				//inserção no meio
				else{
					for (j = MeusAppsED.il; MeusAppsED.n[j].prox != -2; j = MeusAppsED.n[j].prox){
						if(MeusAppsED.n[j].prox == i){
							proxDisp = MeusAppsED.n[MeusAppsED.disp].prox;
							aux = i;
							MeusAppsED.n[MeusAppsED.disp].info.id = filaED.m[t].info.id;
						    strcpy(MeusAppsED.n[MeusAppsED.disp].info.nome,filaED.m[t].info.nome);
						    MeusAppsED.n[MeusAppsED.disp].info.tam = filaED.m[t].info.tam;
						    MeusAppsED.n[j].prox = MeusAppsED.disp;
						    MeusAppsED.n[MeusAppsED.disp].prox = aux;
						   
						    MeusAppsED.disp = proxDisp;			    
						    MeusAppsED.count++;
						    break;
						}
				}
			}
			if (flag == 1 || MeusAppsED.n[i].prox == -1)
				break;
			}
		}
		
		//inserção no fim
		if (flag == 0){
			for(j=MeusAppsED.il; MeusAppsED.n[j].prox != -2; j= MeusAppsED.n[j].prox){
				if(MeusAppsED.n[j].prox == -1){
					proxDisp = MeusAppsED.n[MeusAppsED.disp].prox;
					MeusAppsED.n[MeusAppsED.disp].info.id = filaED.m[t].info.id;
					strcpy(MeusAppsED.n[MeusAppsED.disp].info.nome,filaED.m[t].info.nome);
					MeusAppsED.n[MeusAppsED.disp].info.tam = filaED.m[t].info.tam;
					MeusAppsED.n[j].prox = MeusAppsED.disp;
					MeusAppsED.n[MeusAppsED.disp].prox = -1;
					MeusAppsED.disp = proxDisp;
					MeusAppsED.count++;
					flag =2;
				}
				if (flag == 2)
					break;
			}
			
		}
		
    }
	return;
}

void DesinstalarApp(int t){
	int i,j,flag=0,aux;
	//Caso o "AppsPilha" seja escolhido p/ desinstalar, deve-se inicializar a Pilha
	if(MeusAppsED.n[t].info.id == 20){
		inicializarMeusApps(&AppsPilha);
	}
	
	//Verificar se o app esta aberto em AppRumED e, fecha-lo caso esteja.
	for(i=AppRumED.fl; AppRumED.m[i].ant!=-2; i = AppRumED.m[i].ant){
		if(MeusAppsED.n[t].info.id == AppRumED.m[i].info.id){
			aux = i;
			PararApp(aux);
		}
		if(aux == i)
			break;
	}
	
	//Copiar o app escolhido de MeusAppsED para StoreED
	    //** Primeira inserção em StoreED
	if (StoreED.count == 0){
		StoreED.il=0;
		StoreED.fl=0;
		StoreED.vet[0].id = MeusAppsED.n[t].info.id;
		strcpy(StoreED.vet[0].nome,MeusAppsED.n[t].info.nome);
		StoreED.vet[0].tam = MeusAppsED.n[t].info.tam;
		StoreED.count++;
		MeusAppsED.count--;
	} 
	else {
		//**retornar o app para a StoreED apos primeira inserção
		//fim do arranjo != fim da lista && inicio da lista == inicio do arranjo
		if((StoreED.il==StoreED.ia) && (StoreED.fl!=StoreED.fa)){
			for(i=StoreED.il;i<=StoreED.fl;i++){
				if(MeusAppsED.n[t].info.tam > StoreED.vet[i].tam){
					for(j=StoreED.fl+1;j>i;j--){
						StoreED.vet[j].id = StoreED.vet[j-1].id;
						strcpy(StoreED.vet[j].nome,StoreED.vet[j-1].nome);
						StoreED.vet[j].tam = StoreED.vet[j-1].tam;
					}
					StoreED.vet[i].id = MeusAppsED.n[t].info.id;
					strcpy(StoreED.vet[i].nome,MeusAppsED.n[t].info.nome);
					StoreED.vet[i].tam = MeusAppsED.n[t].info.tam;
					StoreED.count++;
					MeusAppsED.count--;
					StoreED.fl++;
					flag=1;
				}
				if(flag==1)
					break;
			}
			if(flag==0){
					StoreED.fl++;
					StoreED.vet[StoreED.fl].id = MeusAppsED.n[t].info.id;
					strcpy(StoreED.vet[StoreED.fl].nome,MeusAppsED.n[t].info.nome);
					StoreED.vet[StoreED.fl].tam = MeusAppsED.n[t].info.tam;
					StoreED.count++;
					MeusAppsED.count--;
				}
		}
		else{
		//fim do arranjo == fim da lista && inicio da lista != inicio do arranjo
		if((StoreED.il!=StoreED.ia) && (StoreED.fl==StoreED.fa)){
			for(i=StoreED.il; i<=StoreED.fl; i++){
				if(MeusAppsED.n[t].info.tam > StoreED.vet[i].tam){
						for(j=StoreED.il-1; j<i-1; j++){
							StoreED.vet[j].id = StoreED.vet[j+1].id;
							strcpy(StoreED.vet[j].nome,StoreED.vet[j+1].nome);
							StoreED.vet[j].tam = StoreED.vet[j+1].tam;
						}
						StoreED.vet[i-1].id= MeusAppsED.n[t].info.id;
						strcpy(StoreED.vet[i-1].nome,MeusAppsED.n[t].info.nome);
						StoreED.vet[i-1].tam = MeusAppsED.n[t].info.tam;
						StoreED.count++;
						MeusAppsED.count--;
						StoreED.il--;
						flag=1;
				}
				if (flag==1)
					break;
			}
			if (flag==0){
				StoreED.il--;
				StoreED.count++;
				MeusAppsED.count--;
				for(i=StoreED.il; i<StoreED.fl; i++){
					StoreED.vet[i].id=StoreED.vet[i+1].id;
					strcpy(StoreED.vet[i].nome,StoreED.vet[i+1].nome);
					StoreED.vet[i].tam = StoreED.vet[i+1].tam;
				}
				StoreED.vet[StoreED.fl].id = MeusAppsED.n[t].info.id;
				strcpy(StoreED.vet[StoreED.fl].nome,MeusAppsED.n[t].info.nome);
				StoreED.vet[StoreED.fl].tam = MeusAppsED.n[t].info.tam;
			}
		}
		else{
			//fim do arranjo != fim da lista && inicio da lista != inicio do arranjo
			if((StoreED.il!=StoreED.ia) && (StoreED.fl!=StoreED.fa)){
				for(i=StoreED.il;i<=StoreED.fl; i++){
					if(MeusAppsED.n[t].info.tam > StoreED.vet[i].tam){
						if((StoreED.fl - i) < i){
							for(j=StoreED.fl+1;j>i; j--){
								StoreED.vet[j].id = StoreED.vet[j-1].id;
								strcpy(StoreED.vet[j].nome,StoreED.vet[j-1].nome);
								StoreED.vet[j].tam = StoreED.vet[j-1].tam;
							}
							StoreED.vet[i].id = MeusAppsED.n[t].info.id;
							strcpy(StoreED.vet[i].nome,MeusAppsED.n[t].info.nome);
							StoreED.vet[i].tam = MeusAppsED.n[t].info.tam;
							StoreED.count++;
							MeusAppsED.count--;
							StoreED.fl++;
							flag = 1;
						}
						if((StoreED.fl - i) > i){
							for(j=StoreED.il-1; j<i-1; j++){
								StoreED.vet[j].id = StoreED.vet[j+1].id;
								strcpy(StoreED.vet[j].nome,StoreED.vet[j+1].nome);
								StoreED.vet[j].tam = StoreED.vet[j+1].tam;
							}
							StoreED.vet[i-1].id = MeusAppsED.n[t].info.id;
							strcpy(StoreED.vet[i-1].nome,MeusAppsED.n[t].info.nome);
							StoreED.vet[i-1].tam = MeusAppsED.n[t].info.tam;
							StoreED.count++;
							MeusAppsED.count--;
							StoreED.il--;
							flag = 1;
						}
					}
					if(flag == 1)
							break;
				}
				if(flag == 0){
					StoreED.il--;
					for(i=StoreED.il; i<StoreED.fl;i++){
						StoreED.vet[i].id = StoreED.vet[i+1].id;
						strcpy(StoreED.vet[i].nome,StoreED.vet[i+1].nome);
						StoreED.vet[i].tam = StoreED.vet[i+1].tam;
					}
					StoreED.vet[StoreED.fl].id = MeusAppsED.n[t].info.id;
					strcpy(StoreED.vet[StoreED.fl].nome,MeusAppsED.n[t].info.nome);
					StoreED.vet[StoreED.fl].tam = MeusAppsED.n[t].info.tam;
					StoreED.count++;
					MeusAppsED.count--;
				}
			}
		}
	    }
	}    
	
	//Remover o app de MeusAppsED
	if(MeusAppsED.count == 0){
		inicializarMeusApps(&MeusAppsED);
	}
	else{
		for(i=MeusAppsED.il; MeusAppsED.n[i].prox!=-2; i = MeusAppsED.n[i].prox){
			if(MeusAppsED.n[t].info.id == MeusAppsED.n[i].info.id){
				//remoção no inicio
				if(i == MeusAppsED.il){
					aux = MeusAppsED.n[MeusAppsED.il].prox;
					MeusAppsED.n[MeusAppsED.il].prox = MeusAppsED.disp;
					MeusAppsED.disp = MeusAppsED.il;
					MeusAppsED.il = aux;
					flag = 3;
				}	
				//remoção no meio
				else{
					for(j=MeusAppsED.il;MeusAppsED.n[j].prox != -2; j=MeusAppsED.n[j].prox){
						if(MeusAppsED.n[j].prox == i){
							aux = MeusAppsED.n[i].prox;
							MeusAppsED.n[i].prox = MeusAppsED.disp;
							MeusAppsED.disp = i;
							MeusAppsED.n[j].prox = aux;
							flag = 3;
						}
						if (flag == 3)
							break;
					}
				}				
			}
			//remoção no fim
			if(MeusAppsED.n[i].prox == -1){
				for(j=MeusAppsED.il;MeusAppsED.n[j].prox != -2; j=MeusAppsED.n[j].prox){
					if(MeusAppsED.n[j].prox == i){
						MeusAppsED.n[i].prox = MeusAppsED.disp;
						MeusAppsED.disp = i;
						MeusAppsED.n[j].prox = -1;
						flag = 3;
					}
					if(flag == 3)
						break;
				}
			}
			if(flag == 3)
				break;
		}
	}
	return;
}

void AbrirApp(int t){
	int i,proxDisp,ant,pos,flag=0;
	//verificar se o app selecionado eh parte da pilha
	if(MeusAppsED.n[t].info.id == 20 && AppsPilha.count>0){
		empilhar();
	}else{
		//verificar se o app ja esta aberto
		if(AppRumED.count > 0){
			for(i=AppRumED.fl; AppRumED.m[i].ant!=-2;i=AppRumED.m[i].ant){
				if(MeusAppsED.n[t].info.id == AppRumED.m[i].info.id){
					system("cls");
					printf("\n\n\n        O app ja esta aberto!\n\n\n");
					system("pause");
					return;
				}
				if(AppRumED.m[i].ant == -1)
					break;
			}
		}
		//Primeira inserção
		if(AppRumED.il == -1){
			AppRumED.il = 0;
			AppRumED.fl = 0;
			AppRumED.disp = 1;
			AppRumED.m[0].ant = -1;
			AppRumED.m[0].prox =-1;
			AppRumED.m[0].info.id = MeusAppsED.n[t].info.id;
			strcpy(AppRumED.m[0].info.nome,MeusAppsED.n[t].info.nome);
			AppRumED.m[0].info.tam = MeusAppsED.n[t].info.tam;
			AppRumED.count++;
			if(MeusAppsED.n[t].info.id == 20){
			    empilhar();
			}
		}
		else{
			for(i=AppRumED.il; AppRumED.m[i].prox!= -2; i = AppRumED.m[i].prox){
				if(MeusAppsED.n[t].info.tam > AppRumED.m[i].info.tam){
					flag =1;
					//Inserção no início
					if(i == AppRumED.il){
						proxDisp = AppRumED.m[AppRumED.disp].prox;
						AppRumED.m[AppRumED.il].ant = AppRumED.disp;
						AppRumED.m[AppRumED.disp].prox = AppRumED.il;
						AppRumED.m[AppRumED.disp].info.id = MeusAppsED.n[t].info.id;
						strcpy(AppRumED.m[AppRumED.disp].info.nome,MeusAppsED.n[t].info.nome);
						AppRumED.m[AppRumED.disp].info.tam = MeusAppsED.n[t].info.tam;
						AppRumED.il = AppRumED.disp;
						AppRumED.disp = proxDisp;
						AppRumED.m[AppRumED.il].ant = -1;
						AppRumED.m[AppRumED.disp].ant = -1;
						AppRumED.count++;
						if(MeusAppsED.n[t].info.id == 20){
				            empilhar();
			            }
						
					} else{
						//Inserção no meio
						ant = AppRumED.m[i].ant;
						pos = AppRumED.m[AppRumED.m[i].ant].prox;
						proxDisp = AppRumED.m[AppRumED.disp].prox;
						AppRumED.m[AppRumED.disp].info.id = MeusAppsED.n[t].info.id;
						strcpy(AppRumED.m[AppRumED.disp].info.nome,MeusAppsED.n[t].info.nome);
						AppRumED.m[AppRumED.disp].info.tam = MeusAppsED.n[t].info.tam;
						AppRumED.m[AppRumED.m[i].ant].prox = AppRumED.disp;
						AppRumED.m[i].ant = AppRumED.disp;
						AppRumED.m[AppRumED.disp].ant = ant;
						AppRumED.m[AppRumED.disp].prox = pos;
						AppRumED.disp = proxDisp;
						AppRumED.count++;
						if(MeusAppsED.n[t].info.id == 20){
				            empilhar();
			            }
					}	
				}
				if(flag == 1 || AppRumED.m[i].prox == -1)
						break;
			}
			//inserção no fim
			if(flag == 0){
				proxDisp = AppRumED.m[AppRumED.disp].prox;
				AppRumED.m[AppRumED.disp].ant = AppRumED.fl;
				AppRumED.m[AppRumED.fl].prox = AppRumED.disp;
				AppRumED.m[AppRumED.disp].info.id = MeusAppsED.n[t].info.id;
				strcpy(AppRumED.m[AppRumED.disp].info.nome,MeusAppsED.n[t].info.nome);
				AppRumED.m[AppRumED.disp].info.tam = MeusAppsED.n[t].info.tam;
				AppRumED.fl = AppRumED.disp;
				AppRumED.disp = proxDisp;
				AppRumED.m[AppRumED.disp].ant = -1;
				AppRumED.m[AppRumED.fl].prox = -1;
				AppRumED.count++;
				if(MeusAppsED.n[t].info.id == 20){
				            empilhar();
			    }
		    }
		    
	    }
    }
	return;
}

void PararApp(int t){
	int i,ant,pos,flag=0;
	//Verificar se o app selecionado eh a implementação da pilha
	if(AppRumED.m[t].info.id == 20 || AppsPilha.count>1){
		desempilhar();
	}
	else{
		//caso em que ha apenas 1 app aberto em AppRumED
		if(AppRumED.count == 1){
			inicializarAppRum(&AppRumED);
			if(AppRumED.m[t].info.id == 20){
					desempilhar();
			}
			return;
		}
		else{
			for(i=AppRumED.il; AppRumED.m[i].prox!=-2; i = AppRumED.m[i].prox){
				if(AppRumED.m[t].info.id == AppRumED.m[i].info.id){
					//remoção no inicio
					if(i== AppRumED.il){
						AppRumED.m[AppRumED.disp].ant = AppRumED.il;
						AppRumED.il = AppRumED.m[AppRumED.il].prox;
						AppRumED.m[i].prox = AppRumED.disp;
						AppRumED.disp = i;
						AppRumED.m[i].ant = -1;
						AppRumED.m[AppRumED.il].ant = -1;
						AppRumED.count--;
						flag = 1;
					}
					//remoção no meio
					else{
						ant = AppRumED.m[i].ant;
						pos = AppRumED.m[i].prox;
						AppRumED.m[AppRumED.disp].ant = i;
						AppRumED.m[AppRumED.m[i].ant].prox = pos;
						AppRumED.m[AppRumED.m[i].prox].ant = ant;
						AppRumED.m[i].prox = AppRumED.disp;
						AppRumED.m[i].ant = -1;
						AppRumED.disp = i;
						AppRumED.count--;
						flag = 1;
					}
	                //remoção no fim
					if(AppRumED.m[i].prox == -1){
						pos = AppRumED.fl;
						AppRumED.m[AppRumED.fl].prox = AppRumED.disp;
						AppRumED.m[AppRumED.disp].ant = AppRumED.fl;
						AppRumED.fl = AppRumED.m[AppRumED.fl].ant;
						AppRumED.disp = pos;
						AppRumED.m[AppRumED.disp].ant = -1;
						AppRumED.m[AppRumED.fl].prox = -1;
						AppRumED.count--;
						flag = 1;
					}
				}
				if(AppRumED.m[t].info.id == 20){
					desempilhar();
				}
				if(flag == 1)
					break;
			}
		}
    }
	return;
}

void lerStore(){
	int i,j,id,flag;
	char chartroca[12];
	float tamanho;
	FILE *arq;
	arq = fopen("Store.txt","r");
	if(arq == NULL){
		system("cls"); printf("    \n\nErro de leitura de arquivo!\n\n");
	}
	else{
		StoreED.il = 0;
		while(fscanf(arq,"%d %s %f",&id,chartroca,&tamanho) != EOF) {
			if(StoreED.count == 0){
				StoreED.vet[0].id = id;
				strcpy(StoreED.vet[0].nome,chartroca);
				StoreED.vet[0].tam = tamanho;
				StoreED.count++;
			}
			else{
				flag = 0;
				for(i=0; i<=StoreED.fl;i++){
					if(tamanho > StoreED.vet[i].tam){
						for(j=StoreED.fl+1; j>i; j--){
							StoreED.vet[j].id = StoreED.vet[j-1].id;
							strcpy(StoreED.vet[j].nome,StoreED.vet[j-1].nome);
							StoreED.vet[j].tam = StoreED.vet[j-1].tam;
						}
						StoreED.vet[i].id = id;
						strcpy(StoreED.vet[i].nome,chartroca);
						StoreED.vet[i].tam = tamanho;	
						StoreED.fl++;
						StoreED.count++;
						flag = 1;
					}
					if(flag == 1)
						break;
				}
				if(flag == 0){	
						StoreED.fl++;
						StoreED.vet[StoreED.fl].id = id;
						strcpy(StoreED.vet[StoreED.fl].nome,chartroca);
						StoreED.vet[StoreED.fl].tam = tamanho;
						StoreED.count++;
				}	
				
			}
		}
	}
	
	fclose(arq);
	return;
}

void empilhar(){
	int i,proxDisp;
	int id = 20;
	char nome[12]="AppsPilha";
	float tam = 82.12;
	//Primeira inserção
	if(AppsPilha.il == -1){
		AppsPilha.n[0].info.id = id;
		strcpy(AppsPilha.n[0].info.nome,nome);
		AppsPilha.n[0].info.tam = tam;
		AppsPilha.il=0;
		AppsPilha.disp = 1;
		AppsPilha.count++;
	}
	else{
		for(i = AppsPilha.il; AppsPilha.n[i].prox!=-2;i=AppsPilha.n[i].prox){
			if(AppsPilha.n[i].prox == -1){
				proxDisp = AppsPilha.n[AppsPilha.disp].prox;
				AppsPilha.n[AppsPilha.disp].info.id = id;
				strcpy(AppsPilha.n[AppsPilha.disp].info.nome,nome);
				AppsPilha.n[AppsPilha.disp].info.tam = tam;
				AppsPilha.n[i].prox = AppsPilha.disp;
				AppsPilha.n[AppsPilha.disp].prox = -1;
				AppsPilha.disp = proxDisp;
				AppsPilha.count++;
				break;
			}
		}
	}
	mostraMeusApps(AppsPilha);
	return;
}

void desempilhar(){
	int i;
	if(AppsPilha.count == 1){
		AppsPilha.count--;
		inicializarMeusApps(&AppsPilha);
	}
	else{
		for(i=AppsPilha.il; AppsPilha.n[i].prox!=-2; i = AppsPilha.n[i].prox){
			if(AppsPilha.n[AppsPilha.n[i].prox].prox == -1){
				AppsPilha.n[AppsPilha.n[i].prox].prox = AppsPilha.disp;
				AppsPilha.disp = AppsPilha.n[AppsPilha.n[i].prox].prox;
				AppsPilha.n[i].prox = -1;
				AppsPilha.count--;
				break;
			}
		}
	}
	return;
}

void inicializarStore(LLV *s){
    int i;
    s->il = -1;
    s->ia = 0;
    s->fa = size - 1;
    s->fl = 0;
    s->count = 0;
    for(i=0; i<size; i++){
		s->vet[i].id = 0;
		strcpy(s->vet[i].nome,"");
		s->vet[i].tam = 0;
	}
	return;
}

void inicializarMeusApps(LLSE *L) {
	int i;
	L->il = -1;
	L->disp = 0;
	for(i=0; i<size; i++){
		L->n[i].prox = i + 1;
		L->n[i].info.id = 0;
		strcpy(L->n[i].info.nome,"");
		L->n[i].info.tam = 0;
	}
	L->n[0].prox = -1;
	return;
}

void inicializarAppRum(LLDE *K){
	int i;
	K->il = -1;
	K->disp = 0;
	for(i=0; i<size; i++){
		K->m[i].info.id = 0;
		strcpy(K->m[i].info.nome,"");
		K->m[i].info.tam = 0;
		K->m[i].ant = i-1;
		K->m[i].prox = i+1;
	}
	K->fl = 0;
	K->m[0].prox = -1;
	K->count = 0;
	K->m[size-1].prox = -1;
	return;
}

void inicializarFila(FILA *u){
	int i;
	u->il = -1;
	u->disp = 0;
	u->tamanho = 0;
	for(i=0; i<3; i++){
		u->m[i].info.id =0;
		strcpy(u->m[i].info.nome,"");
		u->m[i].info.tam = 0;
		u->m[i].ant = i - 1;
		u->m[i].prox = i + 1;
	}
	u->fl = 0;
	u->m[0].prox = -1;
	u->m[2].prox = -1;
	return;
}
	
void mostraStore(LLV m){
	int i;
	printf("         StoreED!\n\n");
	printf(" il = %d, fl = %d, StoreED.count = %d\n\n",m.il,m.fl,m.count);
	for(i=m.il; i<= m.fl; i++){
		printf("%d ->  %d %s %.2f\n",i,m.vet[i].id,m.vet[i].nome,m.vet[i].tam);
	}
	printf("\n\n");
	system("pause");
	return;
}
	
void Configuracao(){
	char choice;
	while(choice != '0'){
		system("cls");
		if(colorSwitch == 1){
		    system("color 0e");
			}
        if(colorSwitch == 2){
			system("color 70");
		}
	    printf("---------------------------------------------------\n");
		printf("             ** Configuracao **          \n");
		printf("---------------------------------------------------\n");
		printf("\n\n 1 - Tela\n\n");
		printf(" 2 - Armazenamento\n\n");
		printf(" 3 - Sobre o dispositivo\n\n\n\n");
		printf("---------------------------------------------------\n");
		printf("               0 - MENU \n");
		printf("---------------------------------------------------\n");
		printf("Escolha uma das opcoes acima: ");
		scanf(" %c",&choice);
		switch(choice) {
		case '1':
			visor();
			break;
		case '2':
			armazenamento();
			break;
		case '3':
			sobre();
			break;
		default:
			system("cls");
			printf("\n\n\n\n        Opcao invalida!\n\n\n");
			break;
		}
		
	}
	return;
}

void visor(){
	int choice;
	while(choice != 0){
		system("cls");
		if(colorSwitch == 1){
		    system("color 07");
		}
	    if(colorSwitch == 2){
		    system("color 70");
        }
		printf("---------------------------------------------------\n");
		printf("             ** Temas **          \n");
		printf("---------------------------------------------------\n");
		printf("\n\n\n 1 - Tema escuro\n\n");
		printf(" 2 - Tema claro\n\n\n");
		printf("---------------------------------------------------\n");
		printf("               0 - VOLTAR \n");
		printf("---------------------------------------------------\n");
		printf("Escolha uma das opcoes acima: ");
		scanf("%d",&choice);
		if(choice==1 || choice == 2)
			colorSwitch = choice;
	}
	return;
}

void armazenamento(){
	float storage=0;
	int i;
	char choice;
	if(MeusAppsED.count > 0){
		for(i=MeusAppsED.il; MeusAppsED.n[i].prox != -2; i = MeusAppsED.n[i].prox){
			storage = storage + MeusAppsED.n[i].info.tam;
			if(MeusAppsED.n[i].prox == -1)
				break;
		}
	}
	if(AppsPilha.count > 0){
	    storage = storage + ((float)AppsPilha.count - 1)*82.12;
	}
	while(choice != '0'){
	system("cls");
	printf("---------------------------------------------------\n");
	printf("             ** Armazenamento **          \n");
	printf("---------------------------------------------------\n");
	printf("\n\n Memoria total do sistema: 8192 MB\n\n");
	printf(" Memoria do sistema:  3072 MB\n\n");
	printf(" Aplicativos instalados: %.2f MB\n\n",storage);
	printf(" Memoria livre: %.2f MB\n\n\n\n",5120.00 - storage);
	printf("---------------------------------------------------\n");
	printf("               0 - Voltar \n");
	printf("---------------------------------------------------\n");
	printf("Escolha uma opcao acima: ");
	scanf(" %c",&choice);
	}
	return;
}

void sobre(){
	char choice;
	while(choice != '0'){
		system("cls");
		if(colorSwitch == 1){
		    system("color 07");
		}
	    if(colorSwitch == 2){
		    system("color 70");
        }
		printf("---------------------------------------------------\n");
		printf("          ** Informacao **          \n");
		printf("---------------------------------------------------\n");
		printf("\n\n Aluno: Weslley\n\n");
		printf("---------------------------------------------------\n");
		printf("               0 - VOLTAR \n");
		printf("---------------------------------------------------\n");
		printf("Escolha uma das opcoes acima: ");
		scanf(" %c",&choice);
	}
	return;
}

void mostraMeusApps(LLSE L){
    int i;
    system("cls");
    printf("         MeusAppsED!\n\n");
    printf(" il = %d, disp = %d, count = %d\n\n",L.il, L.disp, L.count);
    for(i = L.il; L.n[i].prox!=-2; i=L.n[i].prox){
        printf("%d -> %d %s %.2f\n",i,L.n[i].info.id,L.n[i].info.nome,L.n[i].info.tam);
        if (L.n[i].prox == -1){
            break;
			}
    }
    printf("\n\n");
    system("pause");
    return;
}

void mostraAppRumED(LLDE N){
    int i;
    system("cls");
    printf("         AppRumED!\n\n");
    printf(" il = %d, fl = %d, disp = %d, count = %d\n\n",N.il,N.fl,N.disp,N.count);
    for(i=N.il; N.m[i].prox != -2; i = N.m[i].prox){
      printf("%d -> %d %s %.2f\n",i,N.m[i].info.id,N.m[i].info.nome,N.m[i].info.tam);
      if(N.m[i].prox == -1)
          break;
    }
    printf("\n\n");
    system("pause");
    return;
}

void mostraFila(FILA N){
	int i,flag=0;
    system("cls");
    printf("         filaED!\n\n");
    printf(" il = %d, fl = %d, disp = %d, tamanho = %d\n\n",N.il,N.fl,N.disp,N.tamanho);
    for(i=N.il; N.m[i].prox != -2; i = N.m[i].prox){
      printf("%d -> %d %s %.2f\n",i,N.m[i].info.id,N.m[i].info.nome,N.m[i].info.tam);
      flag++;
      if(flag == N.tamanho)
          break;
    }
    printf("\n\n");
    system("pause");
    return;
}
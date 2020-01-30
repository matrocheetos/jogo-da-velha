#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int i,j,x,y,ganhador=0,posicaoValida,modoDeJogo;
int matriz[3][3]={0,0,0,0,0,0,0,0,0};

void escolherPosicao(int player){
    posicaoValida=0;
    int caso;
	while(posicaoValida==0){
		switch(player){
			case 0: printf("escolha a posicao [linha x coluna de 1 a 3]: "); caso=1; break;             //PLAYER VS COM
			case 1: printf("PLAYER01) escolha a posicao [linha x coluna de 1 a 3]: "); caso=1; break;   //PLAYER01
            case 2: printf("PLAYER02) escolha a posicao [linha x coluna de 1 a 3]: "); caso=-1; break;  //PLAYER02
            }
		scanf("%i%i",&x,&y);
		if(x>=1 && x<=3 && y>=1 && y<=3 && matriz[x-1][y-1]==0){
			matriz[x-1][y-1]=caso;
			posicaoValida=1;
		}else
			if(matriz[x-1][y-1]==1 || matriz[x-1][y-1]==-1)
				printf("posicao ja ocupada!\n");
			else
				printf("posicao invalida!\n");
	}
}

void matrizPrint(){
	printf("\n");
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			printf("\t%i",matriz[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void verificarSeGanhou(){
	//horizontal
	for(i=0;i<3;i++){
		if(matriz[i][0]==matriz[i][1] && matriz[i][0]==matriz[i][2]){
			if(matriz[i][0]==1){
				ganhador=1;
			}
			if(matriz[i][0]==-1){
				ganhador=2;
			}
		}
	}
	//vertical
	for(j=0;j<3;j++){
		if(matriz[0][j]==matriz[1][j] && matriz[0][j]==matriz[2][j]){
			if(matriz[0][j]==1){;
				ganhador=1;
			}
			if(matriz[0][j]==-1){
				ganhador=2;
			}
		}
	}
	//diagonal
	if((matriz[0][0]==matriz[1][1] && matriz[0][0]==matriz[2][2]) || (matriz[0][2]==matriz[1][1] && matriz[0][2]==matriz[2][0])){
		if(matriz[1][1]==1)
			ganhador=1;
		if(matriz[1][1]==-1)
			ganhador=2;
	}
	//empate
	int empate=1;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(matriz[i][j]==0){
				empate=0;
			}
		}
	}
	if(empate==1 && ganhador==0)
		ganhador=3;
}

void jogadaDoBot(){
	int rep,botJogou=0;
	int riscoColuna[3]={0,0,0},riscoLinha[3]={0,0,0},riscoDiagonal[2]={0,0};
	int oportColuna[3]={0,0,0},oportLinha[3]={0,0,0},oportDiagonal[2]={0,0}; //oport=oportunidade
	int aleatorioColuna,aleatorioLinha;

	//verifica onde ha risco ou oportunidade
	for(i=0;i<3;i++){   //linha e coluna
		for(j=0;j<3;j++){
			if(matriz[i][j]==1){
				riscoLinha[i]++;
				riscoColuna[j]++;
			}else if(matriz[i][j]==-1){
				oportLinha[i]++;
				oportColuna[j]++;
			}
		}
		if(matriz[i][i]==1) //diagonal principal
			riscoDiagonal[0]++;
		else if(matriz[i][i]==-1)
			oportDiagonal[0]++;
	}
	//diagonal secundaria
	if(matriz[0][2]==1)
		riscoDiagonal[1]++;
	else if(matriz[0][2]==-1)
		oportDiagonal[1]++;

	if(matriz[1][1]==1)
		riscoDiagonal[1]++;
	else if(matriz[1][1]==-1)
		oportDiagonal[1]++;

	if(matriz[2][0]==1)
		riscoDiagonal[1]++;
	else if(matriz[2][0]==-1)
		oportDiagonal[1]++;

	//bot escolhe uma posicao
	//com risco:
	for(rep=0;rep<3;rep++){
		if(riscoLinha[rep]==2){  //na linha
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){
					if(matriz[i][j]==0 && botJogou==0){
						matriz[i][j]=-1;
						botJogou=1;
					}
				}
			}
		}
		if(riscoColuna[rep]==2){  //na coluna
			for(j=0;j<3;j++){
				for(i=0;i<3;i++){
					if(matriz[i][j]==0 && botJogou==0){
						matriz[i][j]=-1;
						botJogou=1;
					}
				}
			}
		}
	}
	if(riscoDiagonal[0]==2){  //na diagonal principal
		for(i=0;i<3;i++){
			if(matriz[i][i]==0 && botJogou==0){
				matriz[i][i]=-1;
				botJogou=1;
			}
		}
	}
	if(riscoDiagonal[1]==2 && botJogou==0){  //na diagonal secundaria
		if(matriz[0][2]==0){
			matriz[0][2]=-1;
		}else{
			if(matriz[1][1]==0){
				matriz[1][1]=-1;
			}else{
				if(matriz[2][0]==0){
					matriz[2][0]=-1;
				}
			}
		}
		botJogou=1;
	}

	//com oportunidade:
	for(rep=0;rep<3;rep++){
		if(oportLinha[rep]==2){  //na linha     / || oportLinha[rep]==1
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){
					if(matriz[i][j]==0 && botJogou==0){
						matriz[i][j]=-1;
						botJogou=1;
					}
				}
			}
		}
		if(oportColuna[rep]==2){  //na coluna
			for(j=0;j<3;j++){
				for(i=0;i<3;i++){
					if(matriz[i][j]==0 && botJogou==0){
						matriz[i][j]=-1;
						botJogou=1;
					}
				}
			}
		}
	}
	if(oportDiagonal[0]==2){  //na diagonal principal
		for(i=0;i<3;i++){
			if(matriz[i][i]==0 && botJogou==0){
				matriz[i][i]=-1;
				botJogou=1;
			}
		}
	}
	if(oportDiagonal[1]==2 && botJogou==0){  //na diagonal secundaria
		if(matriz[0][2]==0){
			matriz[0][2]=-1;
		}else{
			if(matriz[1][1]==0){
				matriz[1][1]=-1;
			}else{
				if(matriz[2][0]==0){
					matriz[2][0]=-1;
				}
			}
		}
		botJogou=1;
	}

	//sem oportunidade e sem risco
	if(botJogou==0){
		while(botJogou==0){
			aleatorioLinha = rand()%3;
			aleatorioColuna = rand()%3;
			if(matriz[aleatorioLinha][aleatorioColuna]==0){
				matriz[aleatorioLinha][aleatorioColuna]=-1;
				botJogou=1;
			}
		}
	}
	printf("BOT:");
}

int main(){
    printf("\t\t### JOGO DA VELHA ###\n");
    modoDeJogo=0;
    while(modoDeJogo==0){
        printf("\nselecione o modo de jogo\n1 para singleplayer ou 2 para multiplayer: ");
        scanf("%i",&modoDeJogo);
        if(modoDeJogo!=1 && modoDeJogo!=2){
            printf("\nmodo de jogo invalido!\n");
            modoDeJogo=0;
        }
    }
    //execucao
	srand(time(NULL));
    matrizPrint();
    while(ganhador==0){
        if(modoDeJogo==1)
            escolherPosicao(0);
        else if (modoDeJogo==2)
            escolherPosicao(1);
        matrizPrint();
        verificarSeGanhou();
        if(ganhador!=0)
            break;
        if(modoDeJogo==1)
            jogadaDoBot();
        else if (modoDeJogo==2)
            escolherPosicao(2);
        matrizPrint();
        verificarSeGanhou();
        }

    if(ganhador==1){
        if(modoDeJogo==1)
            printf("voce ganhou!!!\n");
        else if(modoDeJogo==2)
            printf("PLAYER01 ganhou!!\n");
    }
    if(ganhador==2){
        if(modoDeJogo==1)
            printf("o computador ganhou!!\n");
        else if(modoDeJogo==2)
            printf("PLAYER02 ganhou!!\n");
    }
    if(ganhador==3)
        printf("empate!\n");

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//assinatura das funcoes
void inicializarJogo(int tabuleiro[]);
void imprimirTabuleiro(int tabuleiro[]);
void imprimirJogoiIniciado();
void imprimirCasas();
void imprimirVencedor(int vencedor);
int jogar(int tabuleiro[]);
int jogarIA (int tabuleiro[]);
void jogando(int tabuleiro[]);
int fimJogo(int tabuleiro[], int jogadas[]);


//criando variavel global tabuleiro
//de 0 a 5 campo do jogador A
//6 deposito do jogador A
//de 7 a 12 campo do jogador B
//13 deposito do jogador B

//funcao inicializar jogo (model)
void inicializarJogo(int tabuleiro[]){
    for(int i = 0; i < 14; i++){
        tabuleiro[i] = 4;
    }
    tabuleiro[6] = 0;
    tabuleiro[13] = 0;

    //debuger
    /*
    for(int i = 0; i < 14; i++){
        printf("%d",tabuleiro[i]);
    }*/
}

//funcao imprimir tabuleiro (view)
void imprimirTabuleiro(int tabuleiro[]){
    printf("\n\n");
    printf("\t B |");
    for(int i = 12; i > 6; i--){
        printf(" %d ", tabuleiro[i]);
    }
    printf("|\n\t %d |                  | %d \n", tabuleiro[13], tabuleiro[6]);
    printf("\t   |");
    for(int i = 0; i < 6; i++){
        printf(" %d ", tabuleiro[i]);
    }
    printf("| A ");
    printf("\n");
}

void imprimirJogoiIniciado(){
    printf("\n===------- Jogo Mancala Iniciado -------===");
}

void imprimirCasas(){
    printf("\n\t    ");
    for(int i = 0; i < 6; i++){
        printf(" %d ", i);
    }
}

void imprimirVencedor(int vencedor){
    char jogador;
    if(vencedor == 1){
        jogador = 'A';
    } else jogador = 'B';
    printf("O jogador %c Venceu", jogador);
}

void imprimirVezJogador(int turno){
    printf("\nVez do jogador: #%d", turno);
}
int jogar(int tabuleiro[]){

    //entrada de dados
    int escolha = 0;
    int quantidade;
    do{
        printf("\nEscolha a casa que voce deseja jogar: ");
        scanf("%d", &escolha);
    } while(escolha > 5 || tabuleiro[escolha] == 0);

    quantidade = tabuleiro[escolha];
    tabuleiro[escolha] = 0;

    int ultimaCasa;

    for(int i = escolha+1; i < 13; i++){
        if(quantidade == 0) break;
        tabuleiro[i]++;
        quantidade--;
        if(i == 12){
            i = 0;
        }
        ultimaCasa = i;
    }

    if(tabuleiro[ultimaCasa] == 1 && ultimaCasa < 6){
        tabuleiro[6] = tabuleiro[ultimaCasa] + tabuleiro[ultimaCasa+7];
        tabuleiro[ultimaCasa] = 0;
        tabuleiro[ultimaCasa+7] = 0;
    }

    if(ultimaCasa == 6){
        return 1;
    }

    return 0;


}

int jogarIA(int tabuleiro[]){

    int escolha = 0;
    int i = 0;

    int quantidade;
    do{
        i = rand()%12;
        escolha=i;
    } while(escolha < 7 || tabuleiro[escolha] == 0);
    printf("escolha %d", escolha);
    quantidade = tabuleiro[escolha];
    tabuleiro[escolha] = 0;

    int ultimaCasa;

    for(int i = escolha+1; ((i <= 13) && (quantidade != 0)); i++){
        if(ultimaCasa == 0) break;

        if(i == 6)i = 7;

        tabuleiro[i]++;
        quantidade--;

        if(i==13) i=0;

        ultimaCasa = i;
    }

    if(tabuleiro[ultimaCasa] == 1 && ultimaCasa < 13 && ultimaCasa>6){
        tabuleiro[13] = tabuleiro[ultimaCasa] + tabuleiro[ultimaCasa-7];
        tabuleiro[ultimaCasa] = 0;
        tabuleiro[ultimaCasa-7] = 0;
    }

    if(ultimaCasa == 13){
        return 1;
    }

    return 0;


}

void jogando(int tabuleiro[]){

    imprimirJogoiIniciado();

    inicializarJogo(tabuleiro);

    imprimirTabuleiro(tabuleiro);

    int jogadas[2];
    //jogadas jogador A:
    jogadas[0] = 0;
    //jogadas jogador B:
    jogadas[1] = 0;

    int turno = 1;
    //turno: 1 para jogador A e 2 para jogador B
    int jogarDeNovo = 0;

    do{
        imprimirVezJogador(turno);
        imprimirTabuleiro(tabuleiro);
        switch(turno){
            case 1:
                imprimirCasas();
                jogarDeNovo = jogar(tabuleiro);
                if(jogarDeNovo == 0){
                    turno = 2;
                } else turno = 1;
                jogadas[0]++;
                break;
            case 2:
                jogarDeNovo = jogarIA(tabuleiro);
                if(jogarDeNovo == 0){
                    turno = 1;
                } else turno = 2;
                jogadas[1]++;
                break;

        }
    } while(fimJogo(tabuleiro, jogadas) == 0);

    int vencedor = fimJogo(tabuleiro, jogadas);

    imprimirVencedor(vencedor);
}



int fimJogo(int tabuleiro[], int jogadas[]){
    int soma1=0, soma2=0;
    if(jogadas[0]!=20 && jogadas[1]!=20){
        for(int i=0;i<6;i++){
            soma1=soma1+tabuleiro[i];
        }
        for(int i=7;i<13;i++){
            soma2=soma2+tabuleiro[i];
        }
        if(soma1==0 || soma2==0){
            if(tabuleiro[6]>tabuleiro[13]){
                return 1;
            }else return 2;
        } else return 0;
    } else if (tabuleiro[6]>tabuleiro[13]){
                return 1;
            }else return 2;

}

int main()
{
    srand(time(0));

    int tabuleiro[14];
    jogando(tabuleiro);
    return 0;
}


#include <time.h>
#include <stdlib.h>

void main(){
//========================= PARTE 1 - MONTAGEM DO TABULEIRO ====================================
    int tabuleiro[15][15]; //Tabuleiro é representado por uma matriz 15x15

    // Preenchimento da matriz. Espaços LIVRES são representados pelo número 0
    int i, j;
    for(i=0; i<15; i++) {
      for(j=0;j<15;j++) {
            tabuleiro[i][j] = 0;
      }
    }
//================================================================================================
//==================== PARTE 2 ADICIONAR JOGADOR NO TABULEIRO =====================================
    //posicao do jogador é representada por um array com dois valores, linha e coluna
    // O primeiro valor SEMPRE é a linha e o segundo SEMPRE é a coluna
    int posicao[2];
    int linInicial,colInicial;
    srand(time(NULL));

    // Sorteia a posição inicial do jogador
    //Como começa pela borda, o valor da linha inicial só pode ser 0 ou 14
    linInicial = rand() %2;
    if (linInicial==1){ //Se sorteia 1, a linha inicial é a última
            posicao[0]=14;
    }
    else{
            posicao[0]=0; //Se sorteia 1, a linha inicial é a primeira
    }
    //Como começa pela borda, o valor da coluna inicial só pode ser 0 ou 14
    colInicial = rand() %2;

    if (colInicial==1){ //Se sorteia 1, a coluna inicial é a última
            posicao[1]=14;
    }
    else{ //Se sorteia 0, a coluna inicial é a primeira
            posicao[1]=0;
    }

    //Colocar o jogador no tabuleiro
    //O jogador é representado pelo número 3
    tabuleiro[posicao[0]][posicao[1]] = 3;
//================================================================================================
//==================== PARTE 3 DEFINIR POSIÇÃO DE INÍCIO E LINHA DE CHEGADA =====================================

    int linhaVitoria=0; //Indica a linha que o jogador tem que chegar para vencer. É a linha oposta à linha inicial
    if(posicao[0]==0){
            linhaVitoria=14;}
    else if(posicao[0]==14){
        linhaVitoria=0;}

//==================== PARTE 4 ADIÇÃO DAS MINAS AO TABULEIRO =====================================
    int dificuldade; //Número escolhido pelo jogador que representa a % de minas

    printf("Escolha a porcentagem de minas no tabuleiro, digite de 20 a 70: ");
    scanf("%d", &dificuldade);
    getchar(); //limpar Buffer
    //Laço para garantir que a% seja entre 20 e 70
    while(dificuldade<20 || dificuldade>70){
        printf("Numero incorreto entrado. Escolha a porcentagem de minas no tabuleiro, digite de 20 a 70: ");
        scanf("%d", &dificuldade);
        getchar(); //limpar Buffer
    }
    //Calcular o número total de minas no tabuleiro
    int totaldeMinas;
    //Número total de minas no tabuleiro. Desconsidera-se a linha inicial e a de chegada na contagem
    totaldeMinas = dificuldade*0.01 *13*15;


    //Laço para inserir as minas aleatoriamente. Minas são representadas pelo número 1.
    int minasAdicionadas = 0;
    while(minasAdicionadas<totaldeMinas){
        int linMina = rand() %15;
        int colMina = rand() %15;
        //Garante que não se coloque mina na linha que o jogador começa, na linha de vitória, ou onde já há mina.
        if(linMina!=posicao[0] && linMina!=linhaVitoria && tabuleiro[linMina][colMina]!=1){
            tabuleiro[linMina][colMina]=1;
            minasAdicionadas+=1;
        }
    }

//==================== PARTE 5 MONTAGEM DO TABULEIRO DA TELA =====================================
    // Este é o tabuleiro visto pelo jogador na tela, onde lugares não visitados
    char tabuleiroTela[15][15];
    int o, p;
    for(o=0; o<15; o++) {
      for(p=0;p<15;p++) {
            // Na tela, '_' representa um espaço não visitado
            tabuleiroTela[o][p] = '_';
      }
    }


//==================== PARTE 6 LOOP CENTRAL DO JOGO =====================================
    int rodadas=1;
    char jogada;

    while(1){//loop principal do jogo
        //Verifica se o jogador está me cima de uma mina
        if(tabuleiro[posicao[0]][posicao[1]]==1){
            printf("Voce pisou em uma mina. O jogo terminou. Voce sobreviveu por %d rodadas.\n", rodadas);
            break;
        }
        //Verifica se o jogador alcançou a linha oposta do mapa
        if(posicao[0]==linhaVitoria){
            printf("Voce venceu! Voce levou  %d rodadas para atravessar o campo minado. \n", rodadas);
            break;
        }
        //coloca o jogador no tabuleiro, representado pela letra J
        tabuleiroTela[posicao[0]][posicao[1]] = 'J';
        printf("Iniciando a Rodada %d.\n", rodadas);
        printf("Seu objetivo e alcancar a linha oposta a aquela em que voce iniciou o jogo.");
        printf("Aperte w para subir, s para descer, a para esquerda, d direita\n");

        //imprime o tabuleiro atual na tela
        for(int x=0;x<15;x++){
            for(int y=0;y<15;y++){
                printf("%c  ", tabuleiroTela[x][y]);
            }
          printf("\n");
        }


        tabuleiroTela[posicao[0]][posicao[1]] = '_';//Apaga a posição anterior onde o jogador estava
        int teclaValida = 1; //representando um valor booleano (1 falso e 0 verdadeiro)
        while (teclaValida==1){
            char jogada = getchar();
            if (jogada=='w'){
                    if(posicao[0]>0){
                        posicao[0]-=1;
                        teclaValida=0;}}
            else if (jogada=='s'){
                    if(posicao[0]<14){
                        posicao[0]+=1;
                        teclaValida=0;}}
            else if (jogada=='a'){
                    if(posicao[1]>0){
                        posicao[1]-=1;
                        teclaValida=0;}}
            else if (jogada=='d'){
                    if(posicao[1]<14){
                        posicao[1]+=1;
                        teclaValida=0;}}
        }

        rodadas+=1;

    }


   return 0;

}

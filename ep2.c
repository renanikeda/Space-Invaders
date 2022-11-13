
/*
  MAC2166-2018
  AO PREENCHER ESSE CABECLHO COM O MEU NOME E O MEU NUMERO USP,
  DECLARO QUE SOU O UNICO AUTOR E RESPONSAVEL POR ESSE PROGRAMA.
  TODAS AS PARTES ORIGINAIS DESSE EXERCICIO PROGRAMA (EP) FORAM
  DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUCOES
  DESSE EP E QUE PORTANTO NAO CONSTITUEM DESONESTIDADE ACADEMICA
  OU PLAIO.
  DECLARO TAMBEM QUE SOU RESPONSAVEL POR TODAS AS COPIAS DESSE
  PROGRAMA E QUE EU NAO DISTRIBUI OU FACILITEI A SUA DISTRIBUICAO.
  ESTOU CIENTE QUE OS CASOS DE PLAIO E DESONESTIDADE ACADEMICA
  SERAO TRATADOS SEGUNDO OS CRITERIOS DIVULGADOS NA PAINA DA DISCIPLINA.
  ENTENDO QUE EP SEM ASSINATURA NAO SERAO CORRIGIDOS E, AINDA ASSIM,
  PODERAO SER PUNIDOS POR DESONESTIDADE ACADEMICA.

  Nome : Renan Ikeda Fernandes
  NUSP : 10439892
  Turma: Prof.: Leo^nidas de Oliveira Branda~o
  (NAO use acentos e nenhum outro caractere especial nesse codigo)

  Compilar com:
  gcc -fsanitize=address -g -std=c99 -o ep2_mac2166_seunome ep2_mac2166_seunome.c

*/

// !!!!! NAO APAGUE COISA ALGUMA DESSE ESQUELETO !!!!!!

#include <stdio.h>

#define True  1
#define False 0

// Para gerao de numeros pseudo aleatorios
#define CPA_SEMENTE     127
#define CPA_NUM1      16807
#define CPA_NUM2       2836
#define CPA_MOD      127773

// !!!!! PARA TESTAR O JOGO, USE VALORES PEQUENOS, COMO 2 E 3 PARA num_linhas e num_colunas
// VOLTE PARA O ORIGINAL ANTES DE ENTREGAR !!!!
#define MAXCOLUNA_MAXIMA   56
#define MAXLINHA_MAXIMA    19

// Variaveis globais para numero pseudo-aleatorio e para as dimensoes efetivamente a serem usadas para o tabuleiro
long num_pseudoaleatorio = 127; // Usar esse valor para iniciar a geracao dos numeros pseudo-aleatorios
int num_linhas;  // numero de linhas efetivamente usadas
int num_colunas; // numero de colunas efetivamente usadas

// CONSTANTES DE IMPRESSAO NA TELA
#define CANHAO             'A'
#define NAVE               'V'
#define LASER_CANHAO       '^'
#define LASER_NAVE         '.'
#define EXPLOSAO           '*'

// CONSTANTES DE ACOES DE MOVIMENTACAO DOS OBJETOS NO JOGO
#define ESQUERDA           -1  // 'e'
#define DIREITA             1  // 'd'
#define ATIRA               3  // 'l'
#define BAIXO              -2

// CONSTANTES DE RESULTADO DO JOGO
#define VENCEU            True
#define PERDEU            False

// CONSTANTES DOS PONTOS RELACIONADOS A LASERS OU NAVES DESTRUIDAS
#define PONTOS_ACERTOU_LASER 1
#define PONTOS_ACERTOU_NAVE  3

// OUTRAS CONSTANTES: SEMENTE DO GERADOR DE NUMEROS PSEUDO-ALEATORIOS E
// VALORES USADOS NA FUNCAO QUE MOVIMENTA AS NAVES
#define SEMENTE             0
#define ATINGIU_DIREITA     1
#define ATINGIU_ESQUERDA   -1
#define ATINGIU_EMBAIXO    -2

// Simula geracao de numeros pseudo-aleatorios
long proximo_pseudo () { // usa a global num_pseudoaleatorio
  return ((CPA_NUM1 * num_pseudoaleatorio + CPA_NUM2) % CPA_MOD);
  }


// DEMAIS FUNCOES NECESSARIAS PARA O JOGO
// !!!!! SEU TRABALHO COMECA AQUI. COMPLETE TODAS AS FUNCOES !!!!!
// !!!!! MAS NAO MODIFIQUE A ASSINATURA DE NENHUMA DELAS E NEM O QUE JA ESTA FEITO !!!!!

// Passo 0: funcao para imprimir a matriz do jogo. Ela precisa ser
//   modificada para imprimir os '|' nas laterais direita e esquerda
/// (matriz) -> None
//   Imprime a matriz do jogo. Cada posicao da matriz e um caracter e deve
//   ser impresso exatamente com o valor dele.
void imprimeMatriz (char matriz[][MAXCOLUNA_MAXIMA], int numLin, int numCol) {
  int i, j;
  for (i=0; i<numLin+1; i++) {
    for (j=0; j<numCol+1; j++){           // eu utilizei a matriz do 0 até o n-1 (n linhas ou colunas)
      if(j==0)
        printf("|");                   // adicionando "|" antes da primeira coluna
      printf("%c", matriz[i][j]);
      if(j==numCol)
        printf("|\n");                   // adicionando "|" depois da ultima coluna
      }
    }

}


// Passo 1: funcao que cria todos os elementos na matriz do jogo
//   (Deve ser chamada so no inicio do jogo)
/// int, (matriz) -> None
//   Recebe um inteiro com a quantidade de naves a serem criadas
//   e a matriz de caracteres vazia para colocar os elementos no inicio do
//   jogo: o canhao do jogador na linha de baixo, coluna do meio, e as
//   naves na parte superior. As naves devem sempre ficar em duas linhas,
//   horizontalmente separados por uma coluna vazia.
//   Por exemplo, se a quantidade de naves for 4, a parte superior da
//   matriz tem que ficar assim:
//     V V
//     V V
//   Se for 5 tem que ficar assim:
//     V V V
//     V V
//   Se for 6 tem que ficar assim:
//     V V V
//     V V V
void criaElementos (int quantidadeNaves, char matriz[][MAXCOLUNA_MAXIMA]) {
    int i,j, cont;
    if(quantidadeNaves%2 == 0){
        for(i=0; i<2; i++) {
            cont=quantidadeNaves/2;
            for (j=0; j<num_colunas+1 && cont > 0 ; j++){
                if(j%2 == 0){
                    matriz[i][j] = NAVE;
                    cont--;
                }
            }
        }
    }
    if(quantidadeNaves%2 != 0){
        for(i=0; i<2 ; i++) {
            cont=(quantidadeNaves/2);
            for (j=0; j<num_colunas+1 && cont > 0; j++){
                if(j%2 == 0){
                    matriz[i][j] = NAVE;
                    cont--;
                }
            }
        }
        matriz[0][j+1]=NAVE;                  // adicionando mais uma nave na primeira linha no caso que o numero de naves é impar
    }

    matriz[num_linhas][num_colunas/2] = CANHAO;
}

  // ...

   // void criaElementos(int quantidadeNaves, char matriz[][MAXCOLUNA_MAXIMA])


// Passo 2: primeira funcao para mover um dos elementos que emitem lasers.
//   Nesse caso para mover o canhao do jogador.
/// int, (matriz) -> bool
//   Recebe um inteiro com a direcao (valores definidos em ESQUERDA e
//   DIREITA) para mover o canhao do jogador (caractere definido em CANHAO)
//   e a matriz de caracteres do jogo, para mover o canhao nessa direcao.
//   Ao mover tem que observar se atingiu algum laser de alguma nave (caso
//   no qual tem que imprimir um EXPLOSAO no lugar). Nesse caso precisara
//   informar que o canhao foi atingido pois a funcao devolve esse valor.
//
//   Devolve:
//    True se canhao do jogador foi atingido (False se nao)
//
//   Obs.: o movimento do canhao e ciclico quando ele se move alem dos
//   limites laterais da matriz do jogo./
int moveCanhao (int direcao, char matriz[][MAXCOLUNA_MAXIMA]) {
    int i,j,posicao, atingiu=False;
    for (j=0; j<num_colunas+1; j++){                  // encontrando a posicao do canhao naquel momento e guardando em "posicao"
        if(matriz[num_linhas][j] == CANHAO){
            matriz[num_linhas][j]=' ';
            posicao=j;
        }
    }
    if(direcao==ESQUERDA){
        if(posicao==0){
            if(matriz[num_linhas][num_colunas]==LASER_NAVE){
                atingiu=True;
                matriz[num_linhas][num_colunas]=EXPLOSAO;
            }
            else
                matriz[num_linhas][num_colunas]=CANHAO;
        }
        else{
            if(matriz[num_linhas][posicao]==LASER_NAVE){
                atingiu=True;
                matriz[num_linhas][posicao]=EXPLOSAO;
            }
            else
                matriz[num_linhas][posicao-1]=CANHAO;
        }
    }
    if(direcao==DIREITA){
        if(posicao==num_colunas){
            if(matriz[num_linhas][0]==LASER_NAVE){
                matriz[num_linhas][0]=EXPLOSAO;
                atingiu=True;
            }
            else
                matriz[num_linhas][0]=CANHAO;
        }
        else{
            if(matriz[num_linhas][posicao+1]==LASER_NAVE){
                matriz[num_linhas][posicao+1]=EXPLOSAO;
                atingiu = True;
            }
            else
                matriz[num_linhas][posicao+1]=CANHAO;
        }

    }
    return atingiu;
  // ...
  // return ?;

}


// Passo 2: segunda funcao para mover um dos elementos que emitem lasers.
//   Nesse caso para mover as naves.
/// int, (matriz) -> [bool, int, int]
//   Recebe um inteiro com a direcao (valores definidos em ESQUERDA, DIREITA e BAIXO)
//   para mover as naves (caractere definido em NAVE) e a matriz de caracteres do
//   jogo, para mover as naves nessa direcao. Ao mover tem que observar se chegou
//   em algum extremo da matriz, se atingiu o canhao do jogador e se atingiu algum
//   laser do jogador. No primeiro e no segundo caso precisa informar que isso
//   aconteceu e no terceiro caso precisa atualizar a quantidade de naves atingidas
//   porque a funcao devolve esses valores numa lista. No segundo caso tem
//   que colocar o caractere definido em EXPLOSAO e no terceiro caso a nave
//   tem que sumir da matriz.
//
//   Devolve:
//     [True se canhao do jogador foi atingido (False se nao), limite atingido, quantidade de naves atingidas]
//
//   Onde limite atingido tem os seguintes significados:
//   - valor definido em ATINGIU_DIREITA se alguma nave, apos o movimento, chegou em num_colunas
//   - valor definido em ATINGIU_ESQUERDA se alguma nave, apos o movimento, chegou na coluna 0
//   - valor definido em ATINGIU_EMBAIXO se alguma nave, apos o movimento, chegou na linha num_linhas
//   - 0 caso nenhuma das alternativas anteriores tenha acontecido
//
//   Obs.: mesmo que a primeira nave verificada atinja o canhao ou atinja
//   a linha mais baixa da matriz, tem que varrer a matriz **inteira** para
//   atualizar a quantidade de naves atingidas antes de devolver resultados
int moveNaves (int indice, int direcao, char matriz[][MAXCOLUNA_MAXIMA], int *limiteParam, int *navesAtingidasParam) {
  int atingiuCanhao = False;
  int i, j ;
  if(indice%2==0){
    if(*limiteParam==ATINGIU_DIREITA || *limiteParam==ATINGIU_ESQUERDA){

              for(i=(num_linhas); i>=0; i--){
                  for(j=0; j<num_colunas+1; j++){
                      if(matriz[i][j]==NAVE){
                          matriz[i][j] = ' ';
                          if(matriz[i+1][j]==LASER_CANHAO)
                            *navesAtingidasParam += 1;
                          else{
                              if(matriz[i+1][j]==CANHAO){
                                atingiuCanhao = True;
                                matriz[i+1][j] = EXPLOSAO;
                              }
                              else{
                                  matriz[i+1][j] = NAVE;
                                    if(i+2 == num_linhas)
                                        *limiteParam = ATINGIU_EMBAIXO;
                                    else
                                        *limiteParam=0;

                              }
                          }
                      }
                  }
              }


    }
    else{
          if(direcao==DIREITA){
              for(i=0; i<num_linhas+1 ;i++){
                  for(j=num_colunas; j>=0 ;j--){
                      if(matriz[i][j]==NAVE){
                          matriz[i][j] = ' ';
                          if(matriz[i][j+1]==LASER_CANHAO){
                            *navesAtingidasParam += 1;
                            matriz[i][j+1] = ' ';
                            }
                          else{
                              matriz[i][j+1]= NAVE;
                              if(j+1==num_colunas)
                                *limiteParam = ATINGIU_DIREITA;
                          }

                      }
                  }
              }

          }
          if(direcao==ESQUERDA){
            for(i=0; i<num_linhas+1 ;i++){
                for(j=0; j<num_colunas+1 ;j++){
                    if(matriz[i][j]==NAVE){
                        matriz[i][j] = ' ';
                        if(matriz[i][j-1]==LASER_CANHAO){
                            *navesAtingidasParam += 1;
                            matriz[i][j-1]= ' ';
                        }
                        else{
                            matriz[i][j-1]=NAVE;
                            if(j-1 == 0)
                                *limiteParam = ATINGIU_ESQUERDA;
                        }
                    }
                }
            }
          }
        }
    }
  // ...
  // *limiteParam = ?;
  // *navesAtingidasParam = ?;
  return atingiuCanhao;
} // int moveNaves(int direcao, char matriz[][MAXCOLUNA_MAXIMA], int *limiteParam, int *navesAtingidasParam)


// Passo 3: primeira funcao para emitir lasers. Nesse caso, para emitir
// um novo laser pelo canhao do jogador.
/// (matriz) -> [int, int]
//   Recebe a matriz do jogo e emite um novo laser atirado pelo jogador
//   (caractere definido em LASER_CANHAO) uma posicao acima da posicao onde o
//   canhao se encontra. Ao emitir o laser tem que observar: se atingiu alguma
//   nave e se atingiu algum laser de alguma nave. Em todos esses casos o laser
//   recem-emitido ja tem que sumir da matriz (ele nem chega a ser impresso
//   nesse caso) e tem que atualizar a quantidade de naves atingidas e de
//   lasers atingidos pois a funcao devolve esses dois valores numa lista.
//
//   Devolve:
//     [quantidade de naves atingidas, quantidade de lasers atingidos]
int emiteLaserCanhao (char matriz[][MAXCOLUNA_MAXIMA], int *lasersAtingidosParam) {
  int navesAtingidas=0;
  int posicao, j , i;
  for(j=0; j<num_colunas+1; j++){
      if(matriz[num_linhas][j] == CANHAO){
          posicao=j;                            // marcar a posicao do canhao naquele momento
      }
  }
  if(matriz[num_linhas-1][posicao] == LASER_NAVE){     // verificar posicao imediatamente acima
      *lasersAtingidosParam +=1;
      matriz[num_linhas-1][posicao] = ' ';
  }
  else{
      if(matriz[num_linhas-1][posicao] == NAVE){
          navesAtingidas += 1;
          matriz[num_linhas-1][posicao] = ' ';
      }
      else
        matriz[num_linhas-1][posicao] = LASER_CANHAO;
  }

  // ...

  // *lasersAtingidosParam = ?;
  return navesAtingidas;
  }

// Passo 3: segunda funcao para emitir lasers. Nesse caso para emitir
// novos lasers pelas naves.
/// (matriz) -> [bool, int]
//   Recebe a matriz do jogo e emite lasers pelas naves (caractere definido
//   em LASER_NAVE) uma posicao abaixo da posicao da nave que emitiu o
//   laser. Ao emitir o laser tem que observar: se atingiu o canhao do
//   jogador (caso no qual tem que imprimir um EXPLOSAO no lugar) e se
//   atingiu algum laser do jogador. Em todos esses casos, o laser
//   recem-emitido tem que sumir da matriz (ele nem chega a ser impresso
//   nesse caso). No primeiro caso tem que informar que o canhao do jogador
//   foi atingido e no segundo caso tem que atualizar a quantidade de
//   lasers atingidos pois a funcao devolve esses dois valores numa lista.
//
//   Para definir se uma nave deve ou nao emitir laser, "sorteie" um numero
//   (pseudo)aleatorio, usando a funcao 'proximo_pseudo()', e converta em 0
//   (se par) ou 1 (se impar). Se o resultado for 0, nao emita o laser para
//   aquela nave. Se o resultado for 1, emita. Essa verificacao so' deve ser
//   feita para aquelas naves que nao possuem outra imediatamente abaixo e
//   sempre na ordem da esquerda para a direita da matriz.
//
//   Devolve:
//     [True se canhao do jogador foi atingido (False se nao), quantidade de lasers atingidos]
//
//   Obs.1: mesmo que o primeiro laser emitido atinja o canhao, tem que varrer a
//   matriz **inteira** para atualizar a quantidade de lasers atingidos antes voltar
int emiteLasersNaves (char matriz[][MAXCOLUNA_MAXIMA], int *lasersAtingidosParam) {
  int atingiuCanhao=False, i ,j;
  for(i=num_linhas; i>=0; i--){
      for(j=0; j<num_colunas+1 ; j++){
          if(matriz[i][j] == NAVE){
              if(matriz[i+1][j] != NAVE){
                num_pseudoaleatorio = proximo_pseudo();
                  if(matriz[i+1][j] == LASER_CANHAO && num_pseudoaleatorio%2==1){
                    *lasersAtingidosParam += 1;
                    matriz[i+1][j] = ' ';
                  }
                  else {
                    if(matriz[i+1][j] == CANHAO && num_pseudoaleatorio%2==1){
                        matriz[i+1][j]=EXPLOSAO;
                        atingiuCanhao = True;
                    }
                    else{

                        if(num_pseudoaleatorio%2==1){
                            matriz[i+1][j]=LASER_NAVE;

                        }
                    }
                  }

              }
          }
      }
  }
  // ...

  // *lasersAtingidosParam = ?;
  return atingiuCanhao;
  }


// Passo 4: primeira funcao para mover lasers. Nesse caso, para mover os lasers do jogador.
/// (matriz) -> [int, int]
//   Recebe a matriz do jogo e move todos os lasers atirados pelo jogador
//   (caractere definido em LASER_CANHAO) uma posicao para cima na matriz.
//   Ao mover tem que observar: se saiu do limite da matriz, se atingiu
//   alguma nave e se atingiu algum laser de alguma nave. Em todos esses 3
//   casos o laser movido tem que sumir da matriz. Nos dois primeiros
//   casos tem que atualizar a quantidade de naves atingidas e de lasers
//   atingidos pois a funcao devolve esses dois valores numa lista.
//
//   Devolve:
//     [quantidade de naves atingidas, quantidade de lasers atingidos]
int moveLasersCanhao (char matriz[][MAXCOLUNA_MAXIMA], int *lasersAtingidosParam) {
  int navesAtingidas=0,i,j;
  // ...
  for(i=0;i<num_linhas+1;i++){
      for(j=0;j<num_colunas+1;j++){
          if(matriz[i][j]==LASER_CANHAO){
            if(i==0)
                matriz[i][j] = ' ';
            else{
                  matriz[i][j]=' ';
                  if(matriz[i-1][j]==LASER_NAVE){
                    *lasersAtingidosParam +=1;
                    matriz[i-1][j]=' ';
                  }
                  else{
                      if(matriz[i-1][j]==NAVE){
                          navesAtingidas +=1;
                          matriz[i-1][j]=' ';
                      }
                      else
                        matriz[i-1][j]=LASER_CANHAO;
                    }
             }
            }
      }
    }
  // *lasersAtingidosParam = ?;
  return navesAtingidas;
  }


// Passo 4: segunda funcao para mover lasers. Nesse caso, para
// mover os lasers das naves.
/// (matriz) -> [bool, int]
//   Recebe a matriz do jogo e move todos os lasers atirados pelas naves
//   (caractere definido em LASER_NAVE) uma posicao para baixo na matriz.
//   Ao mover tem que observar: se saiu do limite da matriz, se atingiu o
//   canhao do jogador (caso no qual tem que imprimir um EXPLOSAO no lugar)
//   e se atingiu algum laser do jogador. Em todos esses 3 casos, o laser
//   movido tem que sumir da matriz. No segundo caso tem que informar que o
//   canhao do jogador foi atingido e no terceiro caso tem que atualizar a
//   quantidade de lasers atingidos pois a funcao devolve esses dois
//   valores numa lista.
//
//   Devolve:
//     [True se canhao do jogador foi atingido (False se nao), quantidade de lasers atingidos]
//
//   Obs.: mesmo que o primeiro laser verificado atinja o canhao, tem que
//   varrer a matriz **inteira** para atualizar a quantidade de lasers
//   atingidos antes de devolver
int moveLasersNaves (char matriz[][MAXCOLUNA_MAXIMA], int *lasersAtingidosParam) {
  int atingiuCanhao=False,i,j;
  // ...
  for(i=num_linhas;i>=0;i--){            // percorrer de baixo para cima
      for(j=0;j<num_colunas+1; j++){
          if(matriz[i][j]==LASER_NAVE){
            if(i==num_linhas)
                matriz[i][j]= ' ';
            else{
                matriz[i][j]= ' ';
                if(matriz[i+1][j]==LASER_CANHAO){
                    *lasersAtingidosParam += 1;
                    matriz[i+1][j]=' ';
                }
                else{
                    if(matriz[i+1][j]==CANHAO){
                        atingiuCanhao =True;
                        matriz[i+1][j] = EXPLOSAO;
                    }
                    else
                        matriz[i+1][j] = LASER_NAVE;
                }

            }

          }

      }
  }

  // *lasersAtingidosParam = ?;
  return atingiuCanhao;
  }


// Passo 5: funcao que de fato implementa o jogo segundo as regras do enunciado.
//   Ela vai chamar toda as funcoes implementadas nos passos anteriores.
/// int -> [bool, int]
//   Recebe um inteiro que representa a quantidade de naves, implementa de
//   fato o jogo de acordo com as regras do enunciado e devolve uma lista
//   com o resultado do jogo:
//
//   [resultado, pontuacao]
//     resultado e uma variavel booleana que vale True se o jogador venceu ou False se o jogador perdeu.
//
//   Para o jogador vencer:
//   - o jogador precisa destruir todas as naves
//
//   Para o jogador perder:
//   - o jogador precisa ser atingido pelo tiro de alguma nave; ou
//   - alguma nave precisa alcancar a linha num_linhas da matriz do jogo; ou
//   - o jogador precisa ser atingido por alguma nave
//
//   A pontuacao e uma variavel inteira que armazena a quantidade de pontos
//   que o jogador fez, devendo ser acrescida por:
//
//   + PONTOS_ACERTOU_LASER pontos, se o jogador consegue acertar 1 tiro em alguma nave
//   + PONTOS_ACERTOU_NAVE  pontos, se o jogador consegue acertar 1 tiro em algum tiro de alguma nave
//
//   A ordem das acoes no jogo e':
//   - tiros anteriores do jogador se movem
//   - imprime o estado do jogo na tela
//   - usuario informa sua acao (se quer atirar ou mover)
//   - tiros anteriores das naves se movem
//   - naves atiram (de acordo com o sorteio de numeros pseudo-aleatorios)
//   - naves se movem (apenas se for rodada par: direita, baixo ou esquerda)
//
//   Dentro de cada funcao de movimentacao e de emissao de lasers e' necessario
//   verificar se houve colisoes para aumentar a pontuacao, para terminar o jogo
//   ou para limpar a tela removendo os elementos que sumiram por terem passado
//   do limite da tela (tiros que subiram demais e tiros que desceram demais)
//
//   Sempre que o jogo terminar, deve imprimir o estado final da matriz do jogo
  int joga (char matriz[][MAXCOLUNA_MAXIMA], int quantidadeNaves, int *pontosParam, int numLin, int numCol) {
  int resultado, fimDeJogo, pontos=0, rodada, direcaoNaves, i, j, acaocanhao, lasersatingidos=0, navesatingidas=0, limite=0;
    char acao;

  for (i=0; i<numLin+1; i++)
    for (j=0; j<numCol+1; j++)
      matriz[i][j] = ' ';

    criaElementos(quantidadeNaves, matriz);

  resultado       = VENCEU;
  fimDeJogo       = False;
  pontos          = 0;
  rodada          = 1;
  direcaoNaves   = DIREITA;

  while ( !fimDeJogo) {

    navesatingidas += moveLasersCanhao(matriz, &lasersatingidos);
    if( navesatingidas==quantidadeNaves){
        fimDeJogo=True;
        *pontosParam = pontos;
        imprimeMatriz(matriz,numLin,numCol);
        pontos += (navesatingidas * PONTOS_ACERTOU_NAVE) + (lasersatingidos * PONTOS_ACERTOU_LASER);
        *pontosParam = pontos;
        return resultado;
    }
    imprimeMatriz(matriz,numLin,numCol);
    printf("'e' para esquerda, 'd' para direita e 'l' para emitir laser: \n");
    scanf(" %c", &acao);
    if(acao=='l'){
        navesatingidas+=emiteLaserCanhao(matriz,&lasersatingidos);
        if(navesatingidas==quantidadeNaves){
            fimDeJogo=True;
            *pontosParam = pontos;
            imprimeMatriz(matriz,numLin,numCol);
            pontos += (navesatingidas * PONTOS_ACERTOU_NAVE) + (lasersatingidos * PONTOS_ACERTOU_LASER);
            *pontosParam = pontos;
            return resultado;
        }
    }
    if(acao=='e'){
        acaocanhao=ESQUERDA;
        fimDeJogo = moveCanhao(acaocanhao, matriz);
        if(fimDeJogo == True){
            resultado= False;
            *pontosParam = pontos;
            imprimeMatriz(matriz,numLin,numCol);
            pontos += (navesatingidas * PONTOS_ACERTOU_NAVE) + (lasersatingidos * PONTOS_ACERTOU_LASER);
            *pontosParam = pontos;
            return resultado;
        }
    }
    if(acao=='d'){
        acaocanhao=DIREITA;
        fimDeJogo = moveCanhao(acaocanhao, matriz);
        if(fimDeJogo == True){
            resultado= False;
            *pontosParam = pontos;
            imprimeMatriz(matriz,numLin,numCol);
            pontos += (navesatingidas * PONTOS_ACERTOU_NAVE) + (lasersatingidos * PONTOS_ACERTOU_LASER);
            *pontosParam = pontos;
            return resultado;
        }
    }


    fimDeJogo = moveLasersNaves(matriz,&lasersatingidos);
    if(fimDeJogo == True){
        resultado= False;
        *pontosParam = pontos;
        imprimeMatriz(matriz,numLin,numCol);
        pontos += (navesatingidas * PONTOS_ACERTOU_NAVE) + (lasersatingidos * PONTOS_ACERTOU_LASER);
        *pontosParam = pontos;
        return resultado;
    }

    fimDeJogo = emiteLasersNaves(matriz, &lasersatingidos);
    if(fimDeJogo == True){
        resultado= False;
        *pontosParam = pontos;
        imprimeMatriz(matriz,numLin,numCol);
        pontos += (navesatingidas * PONTOS_ACERTOU_NAVE) + (lasersatingidos * PONTOS_ACERTOU_LASER);
        *pontosParam = pontos;
        return resultado;
    }

    fimDeJogo= moveNaves(rodada , direcaoNaves,matriz, &limite, &navesatingidas);
    if(limite==ATINGIU_ESQUERDA)
        direcaoNaves=DIREITA;
    if(limite==ATINGIU_DIREITA)
        direcaoNaves=ESQUERDA;
    if(limite==ATINGIU_EMBAIXO){
        fimDeJogo=True;
        resultado=False;
    }
    rodada += 1 ;

  }
    *pontosParam = pontos;
    imprimeMatriz(matriz,numLin,numCol);
    pontos += (navesatingidas * PONTOS_ACERTOU_NAVE) + (lasersatingidos * PONTOS_ACERTOU_LASER);
    return resultado;
}

// !!!!! NAO MODIFIQUE COISA ALGUMA DA main() !!!!!
// FUNCAO PRINCIPAL QUE SO LE O NUMERO DE LINHAS, DE COLUNAS E A QUANTIDADE
// DE INIMIGOS (VIA TECLADO), PASSA O CONTROLE PARA A FUNCAO "REAL" DO JOGO
// E RECEBE DE VOLTA A PONTUACAO DO JOGADOR PARA IMPRIMIR NA TELA COM O RESULTADO DO JOGO
int main (void) {
  char matriz[MAXLINHA_MAXIMA][MAXCOLUNA_MAXIMA]; // declara matriz de estado do jogo (tabuleiro)
  int quantidadeNaves, resultado, pontos;

  printf(" Digite o tamanho do tabuleiro (linhas x colunas menores que %d x %d): \n", MAXLINHA_MAXIMA, MAXCOLUNA_MAXIMA);
  scanf("%d %d", &num_linhas, &num_colunas); // MAXLINHA_MAXIMA   = 19; MAXCOLUNA_MAXIMA  = 56;
  printf("Digite o numero de naves (numero par maior que 1 e menor que %d): \n", num_colunas-3);
  scanf("%d", &quantidadeNaves);

  resultado = joga(matriz, quantidadeNaves, &pontos, num_linhas, num_colunas);

  if (resultado == VENCEU)
    printf(">>> CONGRATULATIONS! Voce venceu!\n");
  else
    printf(">>> GAME OVER! Voce perdeu!\n");

  printf(">>> Pontuacao: %d\n", pontos);

  return 1;
}

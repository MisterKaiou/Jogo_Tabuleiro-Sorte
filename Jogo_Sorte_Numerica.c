#include<locale.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

#define TAM 15

//Recebe do usuário o tamanho da matriz que será o tabuleiro.
int definirTamanhoTabuleiro(int *pQtdLinhas, int *pQtdColunas, int *pQtdRodadas)
{
    int minLinhas = 5, maxLinhas = 15, minColunas = 5, maxColunas = 15;

    //Repete a escolha da linha enquanto o valor for inválido.
    do
    {
        //Recebe do jogador o número de linhas...
        printf("Digite o numero de linhas do tabuleiro (minimo 5 e maximo 15): ");
        scanf("%i", pQtdLinhas);
        *pQtdLinhas = *pQtdLinhas;

        //E se o valor for inválido(menor que o mínimo ou maior que o máximo) mostra uma mensagem de erro.
        if(*pQtdLinhas < minLinhas || *pQtdLinhas >  maxLinhas)
        {
            printf("O valor escolhido não é valido! Tente novamente!\n\n");
        }

    }

    while (*pQtdLinhas < minLinhas || *pQtdLinhas >  maxLinhas);

    //Repete a escolha da linha enquanto o valor for inválido.
    do
    {
        //Recebe do jogador o número de linhas...
        printf("Digite o numero de colunas do tabuleiro (minimo 5 e maximo 15): ");
        scanf("%i", pQtdColunas);
        *pQtdColunas = *pQtdColunas;

        //E se o valor for inválido(menor que o mínimo ou maior que o máximo) mostra uma mensagem de erro.
        if(*pQtdColunas < minColunas || *pQtdColunas > maxColunas)
        {
            printf("O valor escolhido não é valido! Tente novamente!\n\n");
        }

    }

    while (*pQtdColunas < minColunas || *pQtdColunas > maxColunas);

    //Define a quantidade de rodadas de acordo com as linhas e colunas para a contagem.
    *pQtdRodadas = *pQtdLinhas * *pQtdColunas;

    //Limpa a tela para a impressão tabuleiro que acontecerá em seguida.
    system("cls");

    printf("\n");

    return pQtdLinhas, pQtdColunas, pQtdRodadas;

}

//Limpa as entradas da matriz tabuleiro real, que é o tabuleiro que conterá os números aleatórios.
int limparTabuleiroReal(int tabuleiro[TAM][TAM], int *pQtdLinhas, int *pQtdColunas)
{
    int i, j;

    //Zera todas as entradas da matriz.
    for(i = 0; i < pQtdLinhas; i++)
    {
        for(j = 0; j < pQtdColunas; j++)
        {
            tabuleiro[i][j] = 0;
        }
    }

    return tabuleiro;
}

//Gera os números do tabuleiro real.
int gerarTabuleiroReal(int tabuleiro[TAM][TAM], int *qtdLinhas, int *qtdColunas)
{
    int i, j;
    time_t t;

    srand((unsigned) time(&t));

    //Gera um número aleatório em cada entrada da matriz.
    for(i = 0; i < qtdLinhas; i++)
    {
        for(j = 0; j < qtdColunas; j++)
        {
            tabuleiro[i][j] = 1 + ( rand() % 9 );
        }
    }
    return tabuleiro;
}

//Simplesmente gera uma matriz "falsa" com o tamanho que o usuário escolheu, preenchido com números "0" em cada entrada.
int imprimirTabuleiroFalso(int tabuleiroFalso[TAM][TAM], int *pQtdLinhas, int *pQtdColunas)
{
    //Este tabuleiro é usado para verificação de coordenadas já escolhidas e para manter a estética de ter os números sempre escondidos.

    int i, j, colunaNum, linha = 1;
    char colunaLetra = 'A';

    printf("Este é o tabuleiro, faça sua jogada!\n\n");
    printf("    ");

    for (colunaNum = 0; colunaNum < pQtdColunas; colunaNum++)
    {
        printf("%c ", colunaLetra);
        colunaLetra++;
    }

    printf("\n");

    //Imprime na tela esta matriz falsa.
    for(i = 0; i < pQtdLinhas; i++)
    {
        if (i < 9) {printf("0%i| ", linha);}

        else {printf("%i| ", linha);}

        linha++;

        for(j = 0; j < pQtdColunas; j++)
        {
            tabuleiroFalso[i][j] = 0;

            if (j > 0) {printf("-%i", tabuleiroFalso[i][j]);}

            else {printf("%i", tabuleiroFalso[i][j]);}
        }

        printf("\n");
    }
}

//Contagem de rodadas, atualizada a cada rodada.
void contRodadas(int pQtdRodadas, int pAtualRodada)
{
    //Se o jogador estiver última rodada, indica então que restam zero. Esse código só muda a mensagem que é exibida.
    if (pQtdRodadas - pAtualRodada == 0)
    {
        printf("\nÚltima rodada!");
    }

    else {printf("\nRestam %i rodadas!", pQtdRodadas - pAtualRodada);}

    return;

}

//Função que revelará a função dos jogadores.
void revelarEscolha(int tabuleiroFalso[TAM][TAM], int *pQtdLinhas, int *pQtdColunas, int *escolhaX, int *escolhaY)
{
    int i, j, colunaNum, linha = 1;
    char colunaLetra = 'A';

    printf("\nEsta foi sua escolha!\n\n");
    printf("    ");

    for (colunaNum = 0; colunaNum < pQtdColunas; colunaNum++)
    {
        printf("%c ", colunaLetra);
        colunaLetra++;
    }

    printf("\n");

    //Imprime na tela o tabuleiro falso(tabuleiro que recebe a escolha do jogador).
    for(i = 0; i < pQtdLinhas; i++)
    {
        if (i < 9) {printf("0%i| ", linha);}

        else {printf("%i| ", linha);}

        linha++;

        for(j = 0; j < pQtdColunas; j++)
        {
            if (j > 0)
            {
                printf("-%i", tabuleiroFalso[i][j]);
            }
            else
            {
                printf("%i", tabuleiroFalso[i][j]);
            }
        }
        printf("\n");
    }
}

//Função que imprime na tela os placares atuais.
int Placar(int *pResultadoP1, int *pResultadoP2)
{
    printf("\nO placar esta P1:%i P2:%i\n", pResultadoP1, pResultadoP2);

    return pResultadoP1, pResultadoP2;
}

//Função que é executada para o jogador em desvantagem, mas que ainda tenha chances de ganhar.
void pontoFinal(int *pResultadoP1, int *pResultadoP2, int tabuleiroFalso[TAM][TAM], int tabuleiro[TAM][TAM], int *pQtdLinhas, int *pQtdColunas)
{
    int i, j, k;

    //Loop que verifica qual coordenada ainda não foi escolhida.
    for(i = 0; i < pQtdLinhas; i++)
    {
        for(j = 0; j < pQtdColunas; j++)
        {
            //Checa se a coordenada não foi escolhida(Verificação feita no tabuleiro falso)
            if (tabuleiroFalso[i][j] == 0)
            {
                //Verifica se é o Player 1 que está vencendo.
                if (*pResultadoP1 > *pResultadoP2)
                {
                    //Caso seja, prossegue para dar ao Player 2 o valor desta coordenada.
                    *pResultadoP2 = *pResultadoP2 + tabuleiro[i][j];
                    printf("O Player 2 tirou");

                    //Gera um pouco de suspense :0
                    for (k = 0; k < 3; k++)
                    {
                        printf(".");
                        Sleep(1500);
                    }

                    //Revela quantos pontos o Player 2 recebeu e prossegue para exibir o resultado final.
                    printf(" %i pontos\n", tabuleiro[i][j]);
                    Sleep(1000);
                    Placar(*pResultadoP1, *pResultadoP2);
                }

                //Verifica se é o Player 2 que está vencendo.
                else if (*pResultadoP2 > *pResultadoP1)
                {
                    //Caso seja, prossegue para dar ao Player 1 o valor desta coordenada.
                    *pResultadoP1 = *pResultadoP1 + tabuleiro[i][j];
                    printf("O Player 1 tirou");

                    //Gera um pouco de suspense :0
                    for (k = 0; k < 3; k++)
                    {
                        printf(".");
                        Sleep(1500);
                    }

                    //Revela quantos pontos o Player 1 recebeu e prossegue para exibir o resultado final.
                    printf(" %i pontos\n", tabuleiro[i][j]);
                    Sleep(1500);
                    Placar(*pResultadoP1, *pResultadoP2);
                }
            }
        }
    }
}

//Função que simplesmente exibe quem foi o vencedor.
void resultadoFinal(int *pResultadoP1, int *pResultadoP2)
{
    //Compara resultados e verifica qual jogador terminou com maior pontuação.

    Sleep(700);

    if (pResultadoP1 > pResultadoP2) {printf("\nPlayer 1 GANHOU!!!\n");}

    else if (pResultadoP2 > pResultadoP1) {printf("\nPlayer 2 GANHOU!!!\n");}

    else{printf("\nEMPATE!!\n");}

}

//Função para a escolha do Player 1.
int escolhaPlayer1(int *pEscolhaX, int *pEscolhaY, int *pResultadoP1, int *pAtualRodada, int tabuleiro[TAM][TAM], int tabuleiroFalso[TAM][TAM], int *pQtdLinhas, int *pQtdColunas, int pResultadoP2, int *pQtdRodadas)
{
    //Chama a contagem de rodadas, exibindo ela abaixo do tabuleiro.
    contRodadas(pQtdRodadas, *pAtualRodada);

    do
    {
        do
        {
            //Recebe do Player 1 a linha, e guarda o valor.
            printf("\n\nPlayer 1, escolha a linha: ");
            scanf("%i", pEscolhaX);

            //Verifica se a escolha é válida.
            if (pQtdLinhas < *pEscolhaX)
            {
                printf("\nValor escolhido eh invalido!! Tente novamente...");
            }

            //Repete o comando enquanto não digitar um valor válido.
        }
        while (pQtdLinhas < *pEscolhaX);

        do
        {
            //Recebe do Player 1 a coluna, e guarda o valor.
            printf("\nPlayer 1, escolha a coluna: ");
            scanf("%i", pEscolhaY);

            //Verifica se a escolha é válida.
            if (pQtdColunas < *pEscolhaY)
            {
                printf("\nValor escolhido eh invalido!! Tente novamente...\n");
            }

            //Repete o comando enquanto não digitar um valor válido.
        }
        while (pQtdColunas < *pEscolhaY);

        //Faz a checagem no tabuleiro falso e verifica se aquela coordenada já foi escolhida(Se é diferente de zero).
        if (tabuleiroFalso[*pEscolhaX-1][*pEscolhaY-1] != 0)
        {
            printf("\nValor já escolhido!! Tente novamente...\n");
        }

            //Se a coordenada já foi escolhida, repete toda a aquisição das linhas e colunas.
    }

    while (tabuleiroFalso[*pEscolhaX-1][*pEscolhaY-1] != 0);

    //Atualiza o resultado do Player 1, somando-o com o valor daquela coordenada no tabuleiro real.
    *pResultadoP1 = *pResultadoP1 + tabuleiro[*pEscolhaX-1][*pEscolhaY-1];

    //Atualiza o tabuleiro falso, mudando a coordenada escolhida pelo usuário de zero para o valor contido nessa localização no tabuleiro real.
    tabuleiroFalso[*pEscolhaX-1][*pEscolhaY-1] = tabuleiro[*pEscolhaX-1][*pEscolhaY-1];

    //Atualiza a contagem de rodadas.
    *pAtualRodada = *pAtualRodada + 1;

    //Limpa a tela para revelar o tabuleiro falso com a escolha do usuário já atualizada.
    system("cls");

    //Chama a função que revelará a escolha do Player 1.
    revelarEscolha(tabuleiroFalso, pQtdLinhas, pQtdColunas, *pEscolhaX, *pEscolhaY);

    //Chama a função que revelará o placar atual.
    Placar(*pResultadoP1, pResultadoP2);

    return pResultadoP1, pAtualRodada, pEscolhaX, pEscolhaY;
}

//Função para a escolha do Player 2.
int escolhaPlayer2(int *pEscolhaX, int *pEscolhaY, int *pResultadoP2, int *pAtualRodada, int tabuleiro[TAM][TAM], int tabuleiroFalso[TAM][TAM], int *pQtdLinhas, int *pQtdColunas, int *pResultadoP1, int *pQtdRodadas)
{
    //Chama a contagem de rodadas, exibindo ela abaixo do tabuleiro.
    contRodadas(pQtdRodadas, *pAtualRodada);

    do
    {
        do
        {
            //Recebe do Player 2 a linha, e guarda o valor.
            printf("\n\nPlayer 2, escolha a linha X: ");
            scanf("%i", pEscolhaX);

            //Verifica se a escolha é válida.
            if (pQtdLinhas < *pEscolhaX)
            {
                printf("\nValor escolhido eh invalido!! Tente novamente...");
            }

            //Repete o comando enquanto não digitar um valor válido.
        }
        while (pQtdLinhas < *pEscolhaX);

        do
        {
            //Recebe do Player 2 a coluna, e guarda o valor.
            printf("\nPlayer 2, escolha a linha Y: ");
            scanf("%i", pEscolhaY);

            //Verifica se a escolha é válida.
            if (pQtdColunas < *pEscolhaY)
            {
                printf("\nValor escolhido eh invalido!! Tente novamente...\n");
            }

            //Repete o comando enquanto não digitar um valor válido.
        }
        while (pQtdColunas < *pEscolhaY);

        //Faz a checagem no tabuleiro falso e verifica se aquela coordenada já foi escolhida(Se é diferente de zero).
        if (tabuleiroFalso[*pEscolhaX-1][*pEscolhaY-1] != 0)
        {
            printf("\nValor já escolhido!! Tente novamente...\n");
        }

    //Se a coordenada já foi escolhida, repete toda a aquisição das linhas e colunas.
    }
    while (tabuleiroFalso[*pEscolhaX-1][*pEscolhaY-1] != 0);

    //Atualiza o resultado do Player 2, somando-o com o valor daquela coordenada no tabuleiro real.
    *pResultadoP2 = *pResultadoP2 + tabuleiro[*pEscolhaX-1][*pEscolhaY-1];

    //Atualiza o tabuleiro falso, mudando a coordenada escolhida pelo usuário de zero para o valor contido nessa localização no tabuleiro real.
    tabuleiroFalso[*pEscolhaX-1][*pEscolhaY-1] = tabuleiro[*pEscolhaX-1][*pEscolhaY-1];

    //Atualiza a contagem de rodadas.
    *pAtualRodada = *pAtualRodada + 1;

    //Limpa a tela para revelar o tabuleiro falso com a escolha do usuário já atualizada.
    system("cls");

    //Chama a função que revelará a escolha do Player 2.
    revelarEscolha(tabuleiroFalso, pQtdLinhas, pQtdColunas, *pEscolhaX, *pEscolhaY);

    //Chama a função que revelará o placar atual.
    Placar(pResultadoP1, *pResultadoP2);

    return pResultadoP2, pAtualRodada, pEscolhaX, pEscolhaY;
}

//Função que decide de qual jogador será a última casa do tabuleiro quando o número de jogadas não for igual para todos os jogadores.
void EscolhaCuringa(int *pResultadoP1, int *pResultadoP2, int pQtdRodadas, int *pEscolhaX, int *pEscolhaY, int *pAtualRodada, int tabuleiro[TAM][TAM], int tabuleiroFalso[TAM][TAM], int pQtdLinhas, int pQtdColunas)
{

    //Verifica se a quantidade de rodadas é impar, e se pelo menos um dos jogares está ganhando por menos de 9 pontos.
    //Note que essa função não é executada caso haja empate.
    if (pQtdRodadas % 2 == 1 && (*pResultadoP1 - *pResultadoP2 <= 9 || *pResultadoP2 - *pResultadoP1 <= 9))
    {
        //Se o Player 1 estiver ganhando dentro desse critério, então o Player 2 recebe a casa final.
        if(*pResultadoP1 > *pResultadoP2)
        {
            printf("\nPara manter o jogo justo esta última casa vai para o Player com menor pontuação.\n");
            printf("Esta casa será do Player 2!\n");
            pontoFinal(pResultadoP1, pResultadoP2, tabuleiroFalso, tabuleiro, pQtdLinhas, pQtdColunas);
        }

        //Se o Player 2 estiver ganhando dentro desse critério, então o Player 1 recebe a casa final.
        else if(*pResultadoP2 > *pResultadoP1)
        {
            printf("\nPara manter o jogo justo esta última casa vai para o Player com menor pontuação.\n");
            printf("Esta casa será do  Player 1!\n");
            pontoFinal(pResultadoP1, pResultadoP2, tabuleiroFalso, tabuleiro, pQtdLinhas, pQtdColunas);
        }
    }
}

int main()
{
    setlocale(LC_ALL, "");

    int tabuleiro[TAM][TAM], tabuleiroFalso[TAM][TAM], qtdLinhas, qtdColunas, escolhaX, escolhaY,
        qtdRodadas = 0, resultadoP1 = 0, resultadoP2 = 0, atualRodada = 1;

    definirTamanhoTabuleiro(&qtdLinhas, &qtdColunas, &qtdRodadas);
    limparTabuleiroReal(tabuleiro, qtdLinhas, qtdColunas);
    gerarTabuleiroReal(tabuleiro, qtdLinhas, qtdColunas);
    imprimirTabuleiroFalso(&tabuleiroFalso, qtdLinhas, qtdColunas);

    do
    {

        escolhaPlayer1(&escolhaX, &escolhaY, &resultadoP1, &atualRodada, tabuleiro, tabuleiroFalso, qtdLinhas, qtdColunas, resultadoP2, qtdRodadas);
        escolhaPlayer2(&escolhaX, &escolhaY, &resultadoP2, &atualRodada, tabuleiro, tabuleiroFalso, qtdLinhas, qtdColunas, resultadoP1, qtdRodadas);

        //Mantem o jogo enquanto ainda houverem rodadas restantes(também permite que o loop termine caso esteja na rodada e se ela for impar).
    } while (atualRodada < qtdRodadas);

    EscolhaCuringa(&resultadoP1, &resultadoP2, qtdRodadas, &escolhaX, &escolhaY, &atualRodada, tabuleiro, tabuleiroFalso, qtdLinhas, qtdColunas);
    resultadoFinal(resultadoP1, resultadoP2);

    return 0;
}

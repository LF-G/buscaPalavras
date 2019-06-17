/* DECLARO QUE SOU O UNICO AUTOR E RESPONSAVEL POR ESTE PROGRAMA.
// TODAS AS PARTES DO PROGRAMA, EXCETO AS QUE FORAM FORNECIDAS   
// PELO PROFESSOR OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE     
// SEDGEWICK OU ROBERTS, FORAM DESENVOLVIDAS POR MIM. DECLARO   
// TAMBEM QUE SOU RESPONSAVEL POR TODAS AS COPIAS DESTE PROGRAMA 
// E QUE NAO DISTRIBUI NEM FACILITEI A DISTRIBUICAO DE COPIAS.   
//                                                               
// Autor: Luiz Fernando Antonelli Galati                                                    
// Numero USP: 7557223                                               
// Sigla: LUIZFERN                                     
// Data: 2015-09-21                                             
//                                                               
// Este arquivo faz parte da tarefa E da disciplina MAC0121.
//                                                               
///////////////////////////////////////////////////////////////*/



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>


/* //////////// Protótipos de funções //////////// */

void *mallocc (size_t nbytes);
char *expandePalavra (char *palvr, int Epalvr);
char **expandeDicionario (int Edic);
int insere (char *palvr, int p, int Tdic);
int ehBoa (char *palvr);
int constroiDicionario (FILE *arq);
void imprimeDicionario (FILE *arq, int Tdic);
void liberaDicionario (int Tdic);
void leEImprimePalavras (int Tdic);
FILE *fopenn (const char *filename, const char *mode);
int buscaBinaria1(char *palvr, int Tdic);
int buscaBinaria2 (char *palvr, int Tdic);



/* ////////  Variáveis globais   /////////// */

char **dic;



/* //////// Funções /////////// */


/* Função main. Controla a execução do programa.                    */

int main (int numargs, char *arg[])
{
    int Tdic;
    double start, finish, elapsed;
    FILE *entrada, *saida;
    
    start = (double) clock () / CLOCKS_PER_SEC;
    entrada = fopenn (arg[1], "r");
    dic = mallocc (50 * sizeof (char *));
    Tdic = constroiDicionario (entrada);    
    saida = fopenn (arg[2], "w");
    imprimeDicionario (saida, Tdic);
    finish = (double) clock () / CLOCKS_PER_SEC;
    elapsed = finish - start;
    fprintf (saida, "Tempo gasto na primeira fase: %f segundos.\n", elapsed);
    fclose (entrada);
    fclose (saida);
    leEImprimePalavras (Tdic);
    liberaDicionario (Tdic);    
    
    return 0;
}


/* Recebe uma string filename e uma string mode. Abre o arquivo de nome 
filename no modo descrito pela string mode e retorna um ponteiro para o
arquivo aberto.
   Esta função é uma adaptação da função fopen da biblioteca padrão e foi
criada para evitar a repetição da verificação de erro (ponteiro == NULL)
ao longo das outras funções do programa.                               */

FILE *fopenn (const char *filename, const char *mode)
{
    FILE *arq;
    arq = fopen (filename, mode);
    if (arq == NULL) {
        printf ("Erro na abertura de arquivos.\n");
        exit (EXIT_FAILURE);
    }
    return arq;
}


/* Esta função recebe um número inteiro nbytes, aloca os nbytes na memória e
devolve o endereço do conjunto de bytes alocado. Foi criada para evitar a 
repetição da verificação de erro (ponteiro == NULL) ao longo das outras
funções do programa.                                                       */

void *mallocc (size_t nbytes)
{
   void *ptr;
   ptr = malloc (nbytes);
   if (ptr == NULL) {
      printf ("Erro!\n");
      exit (EXIT_FAILURE);
   }
   return ptr;
}


/* Recebe uma string palvr e o tamanho Epalvr do vetor alocado para abrigar
essa string. Devolve a string palvr alocada num vetor de tamanho Epalvr*2 */

char *expandePalavra (char *palvr, int Epalvr)
{
     char *novaPalvr;
     novaPalvr = mallocc ((Epalvr * 2) * sizeof (char));
     strcpy (novaPalvr, palvr);
     free (palvr);
     return novaPalvr;
}


/* Recebe o tamanho Edic do vetor alocado para abrigar o dicionário. Devolve
o dicionario dic alocado num vetor de tamanho Edic*2                      */

char **expandeDicionario (int Edic)
{
    char **novoDic;
    int i;
    novoDic = mallocc ((Edic * 2) * sizeof (char *));
    for (i = 0; i < Edic; i++)
        novoDic[i] = dic[i];
    free (dic);
    dic = novoDic;
    return dic;
}


/* Recebe uma palavra palvr, um índice p e o tamanho do dicionário Tdic.
Insere a palavra na posição p do dicionário dic e retorna o novo tamanho
do dicionário.                                                         */

int insere (char *palvr, int p, int Tdic)
{ 
     int n, k;
     n = strlen (palvr);         
     for (k = Tdic; k > p; k--)
         dic[k] = dic[k-1];
     dic[p] = mallocc ((n + 1) * sizeof (char)); 
     strcpy (dic[p], palvr);
     Tdic++;
     return Tdic;     
}


/* Recebe uma palavra palvr. Devolve 1 se ela for considerada boa (ou seja,
se começar com uma letra minúscula) e 0 caso contrário.                  */

int ehBoa (char *palvr)
{
    if (islower (palvr[0]))
        return 1;
    return 0;
}


/* Recebe um arquivo arq e constrói o seu dicionário dic.                */

int constroiDicionario (FILE *arq)
{
    int i, p, Tdic, Epalvr, Edic;
    char c;
    char *palvr;
    
    Edic = 50;
    Epalvr = 5;     
    palvr = mallocc ((Epalvr) * sizeof (char)); 
    Tdic = 0;
    c = getc (arq);      
    while (c != EOF) {
        i = 0;
        while (isalnum (c)) {            
            palvr[i] = c;
            if (palvr[i] >= 'A' && palvr[i] <= 'Z')
                palvr[i] = tolower (palvr[i]);
            i++;
            if (i == Epalvr) {
                palvr = expandePalavra (palvr, Epalvr);
                Epalvr *= 2;          
            }
            c = getc (arq);
        }
        palvr[i] = '\0';
        p = buscaBinaria1 (palvr, Tdic);     
        if (ehBoa (palvr) && p != -1) { 
            if (Tdic == Edic) {
                dic = expandeDicionario (Edic);
                Edic *= 2;
            }
            Tdic = insere (palvr, p, Tdic);
        }
        if (c != EOF)
            c = getc (arq);
    }
    free (palvr);
    return Tdic;    
}


/* Recebe um arquivo arq e o tamanho do dicionário Tdic. Imprime o dicionário
dic no arquivo.                                                            */

void imprimeDicionario (FILE *arq, int Tdic)
{
     int i;
     for (i = 0; i < Tdic; i++)
         fprintf (arq, "%s\n", dic[i]);
}


/* Recebe o tamanho do dicionário Tdic e libera todo o espaço alocado
para armazená-lo.                                                  */

void liberaDicionario (int Tdic)
{
     int i;
     for (i = 0; i < Tdic; i++)
         free (dic[i]);
     free (dic);
}


/* Esta função é responsável pela interação com o usuário na segunda fase
do programa. 
   Recebe o tamanho do dicionário Tdic, lê a palavra palvr digitada pelo 
usuário e imprime os índices das duas palavras do dicionário que estão mais
próximas de p, juntamente com as palavras correspondentes a esses índices.
   Se a palavra digitada for lexicograficamente menor do que a primeira do
dicionário, imprime apenas o índice da palavra maior que palvr. Se for
lexicograficamente maior ou igual à última do dicionário, imprime apenas o
índice da palavra menor ou igual a palvr.                                */

void leEImprimePalavras (int Tdic)
{
     int i, Epalvr, m;
     char c;
     char *palvr;
     
     Epalvr = 5;
     palvr = mallocc (5 * sizeof (char));
     
     printf (">");
     c = getc (stdin);     
     while (c != '\n') {
         i = 0;
         while (c != '\n') {
             palvr[i] = c;
             if (palvr[i] >= 'A' && palvr[i] <= 'Z')
                palvr[i] = tolower (palvr[i]);
             i++;
             if (i == Epalvr) {
                 palvr = expandePalavra (palvr, Epalvr);
                 Epalvr *= 2;          
             }
             c = getc (stdin);
         }
         palvr[i] = '\0';
         m = buscaBinaria2 (palvr, Tdic);
         if (m == -1)
             printf ("() (%d, %s)\n", m + 1, dic[m+1]);
         else if (m == Tdic - 1)
             printf ("(%d, %s) ()\n", m, dic[m]);
         else
             printf ("(%d, %s) (%d, %s)\n", m, dic[m], m + 1, dic[m+1]);
         printf (">");
         c = getc (stdin);
     }         
     free (palvr);
}







///////////////////////////////////////////////////////////////*/
//                                                               
// Autor: Luiz Fernando Galati
//                                                  
///////////////////////////////////////////////////////////////*/



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>



/* //////////// Protótipos de funções //////////// */

int buscaBinaria1 (char *palvr, int Tdic);
int buscaBinaria2 (char *palvr, int Tdic);



/* ////////  Variáveis globais   /////////// */

char **dic;



/* //////// Funções /////////// */


/* Recebe uma palavra palvr e o tamanho do dicionário Tdic.  Se a palavra está
no dicionário dic, devolve -1. Caso contrário, devolve a posição em que palvr
deve ser inserida.                                                         */

int buscaBinaria1 (char *palvr, int Tdic)
{
     int e, m, d;
     e = 0;
     d = Tdic - 1;
     while (e <= d) {
         m = (e + d)/2;
         if (strcmp (dic[m], palvr) == 0) 
             return -1;
         if (strcmp (dic[m], palvr) < 0)
             e = m + 1;
         else
             d = m - 1;
     }
     return e;
}


/* Recebe uma palavra palvr e o tamanho do dicionário Tdic.  Se a palavra
está no dicionário dic, devolve m tal que dic[m] == palvr. Caso contrário,
devolve a posição d da palavra imediatamente anterior a palvr. Se não houver
palavra antes de palvr, devolve -1.                                       */

int buscaBinaria2 (char *palvr, int Tdic)
{
     int e, m, d;
     e = 0;
     d = Tdic - 1;
     while (e <= d) {
         m = (e + d)/2;
         if (strcmp (dic[m], palvr) == 0) 
             return m;
         if (strcmp (dic[m], palvr) < 0)
             e = m + 1;
         else
             d = m - 1;
     }
     return d;
}


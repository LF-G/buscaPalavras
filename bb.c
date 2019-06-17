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



/* //////////// Prot�tipos de fun��es //////////// */

int buscaBinaria1 (char *palvr, int Tdic);
int buscaBinaria2 (char *palvr, int Tdic);



/* ////////  Vari�veis globais   /////////// */

char **dic;



/* //////// Fun��es /////////// */


/* Recebe uma palavra palvr e o tamanho do dicion�rio Tdic.  Se a palavra est�
no dicion�rio dic, devolve -1. Caso contr�rio, devolve a posi��o em que palvr
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


/* Recebe uma palavra palvr e o tamanho do dicion�rio Tdic.  Se a palavra
est� no dicion�rio dic, devolve m tal que dic[m] == palvr. Caso contr�rio,
devolve a posi��o d da palavra imediatamente anterior a palvr. Se n�o houver
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


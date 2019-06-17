///////////////////////////////////////////////////////////////*/
//                                                               
// Autor: Luiz Fernando Galati
//                                                  
///////////////////////////////////////////////////////////////*/



/* //////////// Prot�tipos de fun��es acess�veis pelo m�dulo principal //////////// */

int buscaBinaria1(char *palvr, int Tdic);
int buscaBinaria2 (char *palvr, int Tdic);



/* ////////  Vari�veis globais acess�veis pelo m�dulo principal   /////////// */

char **dic;



/* A fun��o buscaBinaria1 recebe uma palavra palvr e o tamanho do dicion�rio
Tdic.  Se a palavra est� no dicion�rio dic, devolve -1. Caso contr�rio, devolve
a posi��o em que palvr deve ser inserida.                                    */

int buscaBinaria1 (char *palvr, int Tdic);


/* A fun��o buscaBinaria2 recebe uma palavra palvr e o tamanho do dicion�rio
Tdic. Se a palavraest� no dicion�rio dic, devolve m tal que dic[m] == palvr.
Caso contr�rio, devolve a posi��o d da palavra imediatamente anterior a palvr.
Se n�o houver palavra antes de palvr, devolve -1.                            */

int buscaBinaria2 (char *palvr, int Tdic);


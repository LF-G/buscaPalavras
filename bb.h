///////////////////////////////////////////////////////////////*/
//                                                               
// Autor: Luiz Fernando Galati
//                                                  
///////////////////////////////////////////////////////////////*/



/* //////////// Protótipos de funções acessíveis pelo módulo principal //////////// */

int buscaBinaria1(char *palvr, int Tdic);
int buscaBinaria2 (char *palvr, int Tdic);



/* ////////  Variáveis globais acessíveis pelo módulo principal   /////////// */

char **dic;



/* A função buscaBinaria1 recebe uma palavra palvr e o tamanho do dicionário
Tdic.  Se a palavra está no dicionário dic, devolve -1. Caso contrário, devolve
a posição em que palvr deve ser inserida.                                    */

int buscaBinaria1 (char *palvr, int Tdic);


/* A função buscaBinaria2 recebe uma palavra palvr e o tamanho do dicionário
Tdic. Se a palavraestá no dicionário dic, devolve m tal que dic[m] == palvr.
Caso contrário, devolve a posição d da palavra imediatamente anterior a palvr.
Se não houver palavra antes de palvr, devolve -1.                            */

int buscaBinaria2 (char *palvr, int Tdic);


#include <stdio.h>
#include "Scanner.h"

/* Imprime un token por linea hasta FIN_ENTRADA. Sirve para probar el scanner solo. */
int main(void) {
    Token t;
    
    do {
        t = GetNextToken();

        switch (t.type) {
            case NUMERO:
                printf("NUMERO %ld\n", t.value);
                break;
            
            case IDENTIFICADOR:
                printf("IDENTIFICADOR %s\n", t.name);
               break;
            
            case FIN_LINEA:
                printf("FIN_LINEA\n");
                break;
            
            case FIN_ENTRADA:
                printf("FIN_ENTRADA\n");
                break;
            
            case ERROR:
                printf("ERROR '%s'\n", t.name);
                break;
            
            default:
                printf("'%c'\n", t.type);
                break;
        }
    } while (t.type != FIN_ENTRADA);
    
    return 0;
}

#include <stdio.h>
 
void alter(int *n) {
    *n= *n + 1 ;
}
 
int main() {
    int x = 24;
    int *endereco= &x; /* o operador '&' (leia-se "referênca") retorna o endereço de uma variável */
 
    printf("%d\n", x); /* mostra x */
    printf("%p\n", endereco); /* mostra o endereço de x */
    alter(&x); /* passa o endereço de x como referência, para alteração */
    printf("%d\n", x); /* mostra o novo valor de x */
    printf("%p %p\n", endereco, &x); /* note que o endereço de x não foi alterado */
 
    return 0;
}
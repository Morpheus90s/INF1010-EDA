typedef struct pilha Pilha;

Pilha* pilha_cria(void);
void PUSH(Pilha* p, int v); 
int POP(Pilha* p); 
void pilha_imprime(Pilha* p);
void pilha_libera(Pilha* p);

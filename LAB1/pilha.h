// Aluno A: Eduardo Canton - 2410837 
// Aluno B: Pedro Augusto - 2321374

typedef struct pilha Pilha;

Pilha* pilha_cria(void);
void PUSH(Pilha* p, int v); 
int POP(Pilha* p); 
void pilha_imprime(Pilha* p);
void pilha_libera(Pilha* p);

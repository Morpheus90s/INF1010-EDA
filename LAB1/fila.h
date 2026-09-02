// Aluno A: Eduardo Canton - 2410837 
// Aluno B: Pedro Augusto - 2321374

typedef struct fila Fila;

Fila* fila_cria(void);
void ARMAZENA(Fila* f, int v); 
int RETIRA(Fila* f); 
void fila_imprime(Fila* f);
void fila_libera(Fila* f);

// Aluno A: Eduardo Canton - 2410837 
// Aluno B: Pedro Augusto - 2321374

typedef struct fila Fila;

Fila* fila_cria(void);
void fila_insere(Fila* f, int id, char categoria);
void fila_remove(Fila* f, int id, char categoria);
void fila_imprime(Fila* f);
void fila_libera(Fila* f);


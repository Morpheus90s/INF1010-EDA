// Aluno A: Eduardo Canton - 2410837 
// Aluno B: Pedro Augusto - 2321374

typedef struct pagina Pagina;
typedef struct b_tree B_Tree;

#define MAX 5

Pagina *cria(int n, int *chaves);
B_Tree *monta(void);
void intervalo(Pagina *pagina, int lim_inf, int lim_sup);
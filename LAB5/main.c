#include <stdio.h>

typedef unsigned char Permissions;

void grantPermission(Permissions *p, int bit) {
    *p = *p | (1 << bit);
}

void revokePermission(Permissions *p, int bit) {
    *p = *p & ~(1 << bit);
}

int hasPermission(Permissions p, int bit) {
    return (p & (1 << bit)) != 0;
}

void showPermissions(Permissions p) {
    const char* nomes_perm[] = {
        "leitura", "escrita", "execução", "apagar", 
        "criar", "compartilhar", "administrar", "configurações"
    };

    printf("{ ");
    for (int i = 0; i < 8; i++) {
        if (hasPermission(p, i)) {
            printf("%s ", nomes_perm[i]);
        }
    }
    printf("}\n");
}

int main() {
    Permissions user1 = 0; 
    Permissions user2 = 0;

    grantPermission(&user1, 0); 
    grantPermission(&user1, 1); 
    grantPermission(&user1, 2); 

    grantPermission(&user2, 0); 
    grantPermission(&user2, 3); 
    grantPermission(&user2, 6); 

    printf("Permissoes do Usuario 1:\n");
    showPermissions(user1);
    
    printf("Permissoes do Usuario 2:\n");
    showPermissions(user2);

    Permissions unionPerm = user1 | user2;
    printf("Permissoes combinadas (uniao):\n");
    showPermissions(unionPerm);

    Permissions interPerm = user1 & user2;
    printf("Permissoes em comum (intersecao):\n");
    showPermissions(interPerm);

    printf("Usuario 1 pode apagar arquivos? %s\n",
           hasPermission(user1, 3) ? "Sim" : "Não");

    return 0;
}
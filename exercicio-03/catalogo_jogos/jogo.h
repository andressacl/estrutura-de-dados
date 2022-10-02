//ADD ID N DEF

typedef struct _jogo Jogo;

Jogo *criar_jogo(char nome[100], char empresa_prod[100], int ano_lan);

int get_ano(Jogo *jogo);
char *get_empresa(Jogo *jogo);

void print_jogo(Jogo *jogo);
void print_nome_jogo(Jogo *jogo);

void apagar_jogo(Jogo **jogo_ref);

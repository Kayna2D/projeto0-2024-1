#define TOTAL 100
#define TOTAL_TAREFA 10
#define MIN_TAREFA 1
#define TAMANHO_DESCRICAO 300
#define TAMANHO_CATEGORIA 100

typedef struct {
    int prioridade;
    char descricao[TAMANHO_DESCRICAO];
    char categoria[TAMANHO_DESCRICAO];
} Tarefa;

typedef enum {OK, MAX_TAREFA,  MAX_PRIORIDADE, SEM_TAREFAS, NAO_ENCONTRADO, ABRIR, FECHAR, ESCREVER, LER, NAO_SALVAR} ERROS;

typedef ERROS (*funcao)(Tarefa[], int*);

ERROS criar(Tarefa tarefas[], int *pos);
ERROS deletar(Tarefa tarefas[], int *pos);
ERROS listar(Tarefa tarefas[], int *pos);
ERROS salvar(Tarefa tarefas[], int *pos);
ERROS carregar(Tarefa tarefas[], int *pos);
ERROS salvartxt(Tarefa tarefas[], int *pos);

void clearBuffer();
void filtrar(Tarefa tarefas[], int *pos, char filtro[]);
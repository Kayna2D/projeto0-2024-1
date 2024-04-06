#include "tarefas.h"
#include <stdio.h>

int main() {
  funcao fs[] = {criar, deletar, listar, salvar, carregar};

  Tarefa tarefas[TOTAL];
  int pos;
  ERROS erro = fs[4](tarefas, &pos);
  if (erro != OK) {
    printf("Erro ao carregar arquivo\n");
    pos = 0;
  }

  int opcao;
  do {
    printf("\nMenu principal\n");
    printf("1 - Criar tarefa\n");
    printf("2 - Deletar tarefa\n");
    printf("3 - Listar tarefas\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");

    scanf("%d", &opcao);
    opcao--;
    if (opcao > 2)
      printf("Opcao invalida\n");
    else if (opcao >= 0) {
      erro = fs[opcao](tarefas, &pos);

      if (opcao == 0) {
        if (erro == MAX_TAREFA)
          printf("Número máximo de tarefas atingido\n");
        else if (erro == MAX_PRIORIDADE) 
          printf("A prioridade deve ser entre 1 e 10\n");
        else
          printf("Tarefa criada com sucesso!\n");
      }
        
      else if (opcao == 1) {
        if (erro == SEM_TAREFAS)
          printf("Não há tarefas para deletar\n");
        else if (erro == NAO_ENCONTRADO)
          printf("Tarefa não encontrada\n");
        else
          printf("Tarefa deletada com sucesso!\n");
      }

      else if (opcao == 2) {
        if (erro == SEM_TAREFAS)
          printf("Sem tarefas cadastradas\n");
      }

    } else
      printf("Sair...\n");

  } while (opcao >= 0);

  fs[3](tarefas, &pos);
  ERROS errosalvar = fs[3](tarefas, &pos);
  if (errosalvar != OK)
    printf("Erro ao salvar arquivo\n");
  else
    printf("Salvo com sucesso!\n");
}

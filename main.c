#include "tarefas.h"
#include <stdio.h>

int main() {
  funcao fs[] = {criar, deletar, listar, salvar, carregar};

  Tarefa tarefas[TOTAL];
  int pos;
  ERROS erro = fs[4](tarefas, &pos);
  if (erro == ABRIR) {
    printf("Erro ao carregar arquivo ou arquivo inexistente.\n");
    pos = 0;
  } else if (erro == LER) {
    printf("Erro na leitura do arquivo.\n");
    pos = 0;
  } else if (erro == NAO_ABRIR)
    printf("Iniciando sem carregar...\n");
  else
    printf("Carregado com sucesso!\n");  


  int opcao;
  do {
    printf("\nMenu principal\n");
    printf("1 - Criar tarefa\n");
    printf("2 - Deletar tarefa\n");
    printf("3 - Listar e exportar tarefas\n");
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
          printf("Numero maximo de tarefas atingido\n");
        else if (erro == MAX_PRIORIDADE) 
          printf("A prioridade deve ser entre 1 e 10\n");
        else
          printf("Tarefa criada com sucesso!\n");
      }
        
      else if (opcao == 1) {
        if (erro == SEM_TAREFAS)
          printf("Não ha tarefas para deletar.\n");
        else if (erro == NAO_ENCONTRADO)
          printf("Tarefa nao encontrada.\n");
        else
          printf("Tarefa deletada com sucesso!\n");
      }

      else if (opcao == 2) {
        if (erro == SEM_TAREFAS)
          printf("Sem tarefas cadastradas.\n");
        else if (erro == NAO_ENCONTRADO)
          printf("Tarefa nao encontrada.\n");
      }

    } else
      printf("Sair...\n");

  } while (opcao >= 0);
  clearBuffer();

  printf("Gostaria de salvar suas tarefas no arquivo binario? (s/n): ");
  if (getchar() == 's')
  {
  fs[3](tarefas, &pos);
  ERROS errosalvar = fs[3](tarefas, &pos);
  if (errosalvar == ESCREVER || errosalvar == ABRIR)
    printf("Erro ao salvar arquivo\n");
  else if (errosalvar == OK) 
    printf("Salvo com sucesso!\n");
  } else {
    printf("Saindo sem salvar...");
  }

}

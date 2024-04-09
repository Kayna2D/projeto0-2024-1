#include "tarefas.h"
#include <stdio.h>
#include <string.h>

ERROS criar(Tarefa tarefas[], int *pos) {
  if (*pos >= TOTAL)
    return MAX_TAREFA;
  int prioridade;
  printf("Entre com a prioridade: ");
  
  scanf("%d", &tarefas[*pos].prioridade);
  clearBuffer();
  if (tarefas[*pos].prioridade < MIN_TAREFA || tarefas[*pos].prioridade > TOTAL_TAREFA) {
    return MAX_PRIORIDADE;
  }
  printf("Entre com a categoria: ");
  scanf("%[^\n]", tarefas[*pos].categoria);
  clearBuffer();
  // fgets(tarefas[*pos].categoria, 100, stdin);
  printf("Entre com a descricao: ");
  scanf("%[^\n]", tarefas[*pos].descricao);
  clearBuffer();
  // fgets(tarefas[*pos].descricao, 300, stdin);

  *pos = *pos + 1;

  return OK;
}

ERROS deletar(Tarefa tarefas[], int *pos) {
  // teste se existem tarefas
  if (*pos == 0)
    return SEM_TAREFAS;

  // verifica se a tarefa escolhida existe
  int pos_deletar;
  printf("Entre com a posicao da tarefa a ser deletada: ");
  scanf("%d", &pos_deletar);
  pos_deletar--; // garantir posicao certa no array
  if (pos_deletar >= *pos || pos_deletar < 0)
    return NAO_ENCONTRADO;

  for (int i = pos_deletar; i < *pos; i++) {
    tarefas[i].prioridade = tarefas[i + 1].prioridade;
    strcpy(tarefas[i].categoria, tarefas[i + 1].categoria);
    strcpy(tarefas[i].descricao, tarefas[i + 1].descricao);
  }

  *pos = *pos - 1;

  return OK;
}

void filtrar(Tarefa tarefas[], int *pos, char filtro[]) {
  for (int i = 0; i < *pos; i++) {
    if (strncmp(filtro, tarefas[i].categoria, TAMANHO_CATEGORIA) == 0){
      printf("Pos: %d\t", i + 1);
      printf("Prioridade: %d\t", tarefas[i].prioridade);
      printf("Categoria: %s\t", tarefas[i].categoria);
      printf("Descricao: %s\n", tarefas[i].descricao);
    }
  }
}

ERROS listar(Tarefa tarefas[], int *pos) {
  if (*pos == 0)
    return SEM_TAREFAS;

  char filtro[TAMANHO_CATEGORIA];
  printf("Entre com a categoria desejada (digite '-' para listar todas): ");
  //fgets(filtro, TAMANHO_CATEGORIA, stdin);
  scanf("%99s", filtro);
  //clearBuffer();

  if (filtro[0] == '-'){
    for (int i = 0; i < *pos; i++) {
      printf("Pos: %d\t", i + 1);
      printf("Prioridade: %d\t", tarefas[i].prioridade);
      printf("Categoria: %s\t", tarefas[i].categoria);
      printf("Descricao: %s\n", tarefas[i].descricao);
    }
  } 
  else {
    filtrar(tarefas, pos, filtro);
  }
  return OK;
}

ERROS salvar(Tarefa tarefas[], int *pos) {
  printf("Gostaria de salvar suas tarefas em um arquivo .txt? (s/n): ");
  if (getchar() == 's'){
    FILE *f = fopen("tarefas.bin", "wb");
    if (f == NULL)
      return ABRIR;
  
    int qtd = fwrite(tarefas, TOTAL, sizeof(Tarefa), f);
    if (qtd == 0)
      return ESCREVER;
  
    qtd = fwrite(pos, 1, sizeof(int), f);
    if (qtd == 0)
      return ESCREVER;
  
    if (fclose(f))
      return FECHAR;
        }

  return OK;
}

ERROS salvartxt(Tarefa tarefas[], int *pos) {
  printf("Gostaria de salvar suas tarefas em um arquivo .txt? (s/n): ");
  if (getchar() == 's'){
    char nome[100];
    printf("Entre com o nome do arquivo: ");
    scanf("%99s.txt", nome);
    FILE *f = fopen(nome, "w");
    if (f == NULL)
      return ABRIR;

    for (int i = 0; i < *pos; i++) {
      int qtd = fprintf(f, "Prioridade: %d | Categoria: %s | Descrição: %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].descricao);
      if (qtd == 0)
        return ESCREVER;
    }

    if (fclose(f))
      return FECHAR;
  } 
  else 
    return NAO_SALVAR;
  return OK;
}

ERROS carregar(Tarefa tarefas[], int *pos) { 
  printf("Gostaria de carregar as tarefas? (s/n): ");
  if (getchar() == 's'){
  FILE *f = fopen("tarefas.bin", "rb");
  if (f == NULL)
    return ABRIR;

  int qtd = fread(tarefas, TOTAL, sizeof(Tarefa), f);
  if (qtd == 0)
    return LER;

  qtd = fread(pos, 1, sizeof(int), f);
  if (qtd == 0)
    return LER;

  if (fclose(f))
    return FECHAR;
  }

  return OK;
}


void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) 
    ;
}

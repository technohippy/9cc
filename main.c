#include <stdio.h>
#include "9cc.h"

extern Token *token;
extern char *user_input;
extern Node *code[100];

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "invalid argc");
    return 1;
  }

  user_input = argv[1];
  token = tokenize();
  program();

  printf(".intel_syntax noprefix\n");
  printf(".globl main\n");
  printf("main:\n");

  int bsize = 0;
  for (LVar *var = locals; var; var = var->next)
    bsize += 8;

  // prologue
  printf("  push rbp\n");
  printf("  mov rbp, rsp\n");
  printf("  sub rsp, %d\n", bsize);

  for (int i = 0; code[i]; i++) {
    gen(code[i]);
    printf("  pop rax\n");
  }

  // epilogue
  printf("  mov rsp, rbp\n");
  printf("  pop rbp\n");
  printf("  ret\n");
  return 0;
}

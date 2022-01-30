#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* Funções do programa */
void adicionar_funcionario();// átila
void buscar_funcionario();// átila
void listar_funcionarios();// marília
void atualizar_funcionario();// irinaldo;
void excluir_funcionario();// marília

/* Funções do sistema */
int last_id();// átila/marília/irinaldo
int increment_id(int id);// átila/marília/irinaldo

/* Constantes */
#define BUFFER_SIZE 1000
#define DATABASE_FILE "database.txt"
#define FUNCIONARIOS_FILE "funcionarios.txt"

int main()
{
  char data[BUFFER_SIZE];
  int acao;

  do {
    system("clear");
    printf("RH-cli\n");
    printf("-------------------------\n");
    printf("1 - Cadastrar Funcionário\n");
    printf("2 - Buscar Funcionário\n");
    printf("3 - Listar Funcionários\n");
    printf("4 - Excluir Funcionário\n");
    printf("0 - Sair\n");
    printf("-------------------------\n");
    scanf("%d", &acao);

    switch (acao)
    {
      case 0:
        system("clear");
        return 0;
      case 1:
        system("clear");
        fgets(data, BUFFER_SIZE, stdin);
        adicionar_funcionario();
        break;
      case 2:
        system("clear");
        fgets(data, BUFFER_SIZE, stdin);
        buscar_funcionario();
        break;
      case 3:
        system("clear");  
        fgets(data, BUFFER_SIZE, stdin);        listar_funcionarios();
        break;
      case 4:
        system("clear");
        fgets(data, BUFFER_SIZE, stdin);
        excluir_funcionario();
        break;    
      default:
        system("clear");
        printf("Opção inválida\n");
        printf("--------------\n");
        printf("Voltando...\n");
        sleep(1);
    }
  } while (acao != acao + 10);

  return 0;
}

void adicionar_funcionario()
{
  char record[BUFFER_SIZE];
  char nome[BUFFER_SIZE];
  char matricula[BUFFER_SIZE];
  char email[BUFFER_SIZE];
  char data_de_admissao[BUFFER_SIZE];
  char salario[BUFFER_SIZE];
  FILE * file;

  int new_id;
  char id[BUFFER_SIZE];

  new_id = last_id() + 1;
  sprintf(id, "%d", new_id);

  printf("Cadastrando funcionário\n");
  printf("-----------------------\n\n");
  printf("Digite: Nome\n");
  fgets(nome, BUFFER_SIZE, stdin);
  nome[strcspn(nome, "\n")] = 0;

  printf("Digite: Matrícula\n");
  fgets(matricula, BUFFER_SIZE, stdin);
  matricula[strcspn(matricula, "\n")] = 0;

  printf("Digite: Email\n");
  fgets(email, BUFFER_SIZE, stdin);
  email[strcspn(email, "\n")] = 0;

  printf("Digite: Data de admisssão\n");
  fgets(data_de_admissao, BUFFER_SIZE, stdin);
  data_de_admissao[strcspn(data_de_admissao, "\n")] = 0;

  printf("Digite: Salario\n");
  fgets(salario, BUFFER_SIZE, stdin);

  snprintf(record, BUFFER_SIZE, "%s;%s;%s;%s;%s;%s", id, matricula, nome, email, data_de_admissao, salario);

  file = fopen(FUNCIONARIOS_FILE, "a");
  fputs(record, file);
  fclose(file);

  increment_id(new_id);

  printf("\nUsuário criado com successo.\n");
  sleep(2);
  system("clear");
  printf("\nVoltando para o menu principal...\n");
  sleep(1);
}

void buscar_funcionario()
{
  char *line_buf = NULL;
  size_t line_buf_size = 0;
  int line_count = 0;
  ssize_t line_size;
  FILE *file = fopen(FUNCIONARIOS_FILE, "r");
  char id[BUFFER_SIZE];
  char *record_id = NULL;
  char record[BUFFER_SIZE];
  int founded = 0;
  char header[6][20] = {
    { "ID" },
    { "MATRÍCULA" },
    { "NOME" },
    { "EMAIL" },
    { "DATA DE ADMISSÃO" },
    { "SALÁRIO" }
  };

  /* obtém todas as linhas do arquivo */
  line_size = getline(&line_buf, &line_buf_size, file);

  printf("Buscando funcionário\n");
  printf("--------------------\n\n");
  printf("Digite: id\n");
  fgets(id, BUFFER_SIZE, stdin);
  
  /* remove caracteres inválidos digitado pelo usuário */
  id[strlen(id) - 1] = 0;

  /* percorre as linhas do arquivo */
  while (line_size >= 0)
  {
    /* incrementada o contador de linhas */
    line_count++;

    /* copia o valor da linha para o registro */
    strcpy(record, line_buf);

    /* obtém o id do resgistro corrente */
    record_id = strtok(line_buf, ";");

    /* verifica se o id fornecido é igual ao item corrente do loop */
    if (strcmp(id, record_id) == 0)
    {
      founded = 1;
      system("clear");
      printf("Funcionário encontrado\n");
      printf("--------------------------\n");

      /* Obtém os campos registro */
      char *token = strtok(record, ";");

      /* Faz a impresão dos campos do funcionário encontrado */
      int i = 0;
      while (token != NULL)
      {
        printf("%s: %s\n", header[i], token);
        token = strtok(NULL, ";");
        i++;
      }

      printf("--------------------------\n\n");
      /* interrompe o bloco de repetição se o registro porque o foi encontrado */
      break;
    }

    /* obtém a próxima linha */
    line_size = getline(&line_buf, &line_buf_size, file);
  }

  /* libera buffer */
  free(line_buf);
  line_buf = NULL;

  /* fecha arquivo */
  fclose(file);

  /* verifica se o registro não foi encontrado */
  if (founded == 0)
  {
    system("clear");
    printf("\n404 - Funcionário não encontrado\n");
    printf("---------------------------------\n\n");
  }

  printf("Enter para voltar\n");
  fgets(id, BUFFER_SIZE, stdin);
}

void listar_funcionarios()
{
  char stop[1];
  char linha[BUFFER_SIZE];
  FILE* file;
  file = fopen(FUNCIONARIOS_FILE, "r");

  char header[6][20] = {
    { "ID" },
    { "MATRÍCULA" },
    { "NOME" },
    { "EMAIL" },
    { "DATA DE ADMISSÃO" },
    { "SALÁRIO" }
  };

  printf("Listagem de funcionários\n");
  
  int i = 0;
  while (fgets(linha, BUFFER_SIZE, file))
  {   
    if(i != 0) {
      linha[strcspn(linha, "\n")] = 0;     

      printf("--------------------------\n");
      /* Obtém os campos registro */
      char *campo = strtok(linha, ";");

      /* Faz a impresão dos campos do funcionário encontrado */
      int n = 0;
      while (campo != NULL)
      {
        printf("%s: %s\n", header[n], campo);
        campo = strtok(NULL, ";");
        n++;
      }       
    }
      
    i++;
  }

  fclose(file);

  printf("----------------------\n\n");
  printf("Enter para voltar\n");
  fgets(stop, BUFFER_SIZE, stdin);
}

void excluir_funcionario()
{
  char stop[1];
  printf("Excluir funcionário\n");
  printf("-------------------\n\n");
  printf("Enter para voltar\n");
  fgets(stop, BUFFER_SIZE, stdin);
}

int last_id()
{
  FILE * file;
  int id;
  char id_str[BUFFER_SIZE];

  file = fopen(DATABASE_FILE, "r");
  fgets(id_str, BUFFER_SIZE, file);
  fclose(file);
  id = atoi(id_str);

  if (id == 0)
  {
      id = 1;
  }

  return id;
}

int increment_id(int id)
{
  FILE * file;
  char id_str[BUFFER_SIZE];

  sprintf(id_str, "%d", id);

  file = fopen(DATABASE_FILE, "w");
  fputs(id_str, file);
  fclose(file);

  return id;
}

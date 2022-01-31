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
    printf("\t\t\t\t\t\t...RH-cli...\n");
    printf("\t\t\t=====================================\n");
    printf("\t\t\t| 1 - Cadastrar Funcionário         |\n");
    printf("\t\t\t| 2 - Buscar Funcionário            |\n");
    printf("\t\t\t| 3 - Listar Funcionários           |\n");
    printf("\t\t\t| 4 - Atualizar Dados do Funcionário|\n");
    printf("\t\t\t| 5 - Excluir Funcionário           |\n");
    printf("\t\t\t| 0 - Sair                          |\n");
    printf("\t\t\t=====================================\n");
    printf("\t\t\tDigite a Opção Desejada:");
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
        fgets(data, BUFFER_SIZE, stdin);        
        listar_funcionarios();
        break;
      case 4:
        system("clear");
        fgets(data, BUFFER_SIZE, stdin);
        atualizar_funcionario();
        break;
      case 5:
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

  line_size = getline(&line_buf, &line_buf_size, file);

  printf("Buscando funcionário\n");
  printf("--------------------\n\n");
  printf("Digite: id\n");
  fgets(id, BUFFER_SIZE, stdin);
  id[strlen(id) - 1] = 0;

  while (line_size >= 0)
  {
    line_count++;
    strcpy(record, line_buf);
    record_id = strtok(line_buf, ";");

    if (strcmp(id, record_id) == 0)
    {
      founded = 1;
      system("clear");
      printf("Funcionário encontrado\n");
      printf("--------------------------\n");

      char *token = strtok(record, ";");
      int i = 0;

      while (token != NULL)
      {
        printf("%s: %s\n", header[i], token);
        token = strtok(NULL, ";");
        i++;
      }

      printf("--------------------------\n\n");
      break;
    }

    line_size = getline(&line_buf, &line_buf_size, file);
  }

  free(line_buf);
  line_buf = NULL;
   fclose(file);

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

      char *campo = strtok(linha, ";");
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
void atualizar_funcionario()
{ 
  char data[BUFFER_SIZE];
  int acao;
  void alterar_nome();
  void alterar_matricula();
  void alterar_email();
  void alterar_data_de_admissao();
  void alterar_salario();
  void menu_Principal();
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

  line_size = getline(&line_buf, &line_buf_size, file);

  printf("Buscando funcionário\n");
  printf("--------------------\n\n");
  printf("Digite: id\n");
  fgets(id, BUFFER_SIZE, stdin);
  id[strlen(id) - 1] = 0;

  while (line_size >= 0)
  {
    line_count++;
    strcpy(record, line_buf);
    record_id = strtok(line_buf, ";");

    if (strcmp(id, record_id) == 0)
    {
      founded = 1;
      system("clear");
      printf("Funcionário encontrado\n");
      printf("--------------------------\n");

      char *token = strtok(record, ";");
      int i = 0;

      while (token != NULL)
      {
        printf("%s: %s\n", header[i], token);
        token = strtok(NULL, ";");
        i++;
      }

      printf("--------------------------\n\n");
      break;
    }

    line_size = getline(&line_buf, &line_buf_size, file);
  }

  free(line_buf);
  line_buf = NULL;
   fclose(file);

  if (founded == 0)
  {
    system("clear");
    printf("\n404 - Funcionário não encontrado\n");
    printf("---------------------------------\n\n");
  }
    do
    {
        printf("\n");
        printf ("\t\t\tO QUE VOCE DESEJA ALTERAR?\n");
        printf ("\t\t\t===============================\n");
        printf ("\t\t\t|\t                           |\n");
        printf("\t\t\t|  1 - Alterar Nome            |\n");
        printf("\t\t\t|  2 - Alterar Matrícula       |\n");
        printf("\t\t\t|  3 - Alterar E-mail          |\n");
        printf("\t\t\t|  4 - Alterar Data de Admissão|\n");
        printf("\t\t\t|  5 - Alterar Salario         |\n");
        printf("\t\t\t|  6 - Menu Principal          |\n");
        printf("\t\t\t|  0 - Sair                    |\n");
        printf ("\t\t\t|                              |\n");
        printf ("\t\t\t===============================\n");
        printf ("\n\n");
        printf("\t\t\tPor favor, selecione uma opcao: ");
        fflush(stdin);
        scanf("%d", &acao);
        system("cls");
        switch(acao)
        { 
        case 0:
            system("clear");
            exit(EXIT_SUCCESS);

        case 1:
            system("clear");
            fgets(data, BUFFER_SIZE, stdin);
            alterar_nome();
            break;
        case 2:
            system("clear");
            fgets(data, BUFFER_SIZE, stdin);
            alterar_matricula();
            break;
        case 3:
            system("clear");
            fgets(data, BUFFER_SIZE, stdin);
            alterar_email();
            break;
        case 4:
            system("clear");
            fgets(data, BUFFER_SIZE, stdin);
            alterar_data_de_admissao();
            break;
        case 5:
            system("clear");
            fgets(data, BUFFER_SIZE, stdin);
            alterar_salario();
            break;   
        case 6:
            system("clear");
            fgets(data, BUFFER_SIZE, stdin);
            menu_Principal();
            break;
        
        default:
           system("clear");
           printf("Opção inválida\n");
           printf("--------------\n");
           printf("Voltando...\n");
           sleep(1);
        }
    }
    while(acao != 0);
    system("cls");
}
void alterar_nome()
{
    char matricula[BUFFER_SIZE];
    int i;
    char nome[BUFFER_SIZE];
    char novo_nome[BUFFER_SIZE];
  
    printf ("Digite o Novo Nome: ");
    fgets(novo_nome,BUFFER_SIZE, stdin);
     for (i=0; i < BUFFER_SIZE; i++)
    {
      if(strcmp(matricula,"\n" ) == 0)
      {
       strcpy(nome, novo_nome);
       break;
      }
    }
  printf("\nNome Atualizado com Successo.\n");
  sleep(2);
  system("clear");
  printf("\nVoltando...\n");
  sleep(1);
  system("clear");
}
void alterar_matricula()
{   
    char matricula[BUFFER_SIZE];
    char nova_matricula[BUFFER_SIZE];
    int i;
    
    printf ("Digite a Nova Matricula: ");
    fgets(nova_matricula, BUFFER_SIZE, stdin);
    for (i=0; i < BUFFER_SIZE; i++)
    {
        if(strcmp(matricula,"\n") == 0)
        {
            strcpy(matricula, nova_matricula);
            break;
        }
    }
  printf("\nMatricula Atualizada com Successo.\n");
  sleep(2);
  system("clear");
  printf("\nVoltando...\n");
  sleep(1);
  system("clear");
}
void alterar_email()
{   
    char matricula[BUFFER_SIZE];
    char email[BUFFER_SIZE];
    char novo_email[BUFFER_SIZE];
    int i;
  
    printf ("Digite o Novo E-mail: ");
    fgets(novo_email, BUFFER_SIZE, stdin);
    for (i=0; i < BUFFER_SIZE; i++)
    {
        if(strcmp(matricula,"\n") == 0)
        {
            strcpy(email, novo_email);
            break;
        }
    }
  printf("\nE-mail Atualizado com Successo.\n");
  sleep(2);
  system("clear");
  printf("\nVoltando...\n");
  sleep(1);
  system("clear");
}
void alterar_data_de_admissao()
{   
    char matricula[BUFFER_SIZE];
    char data_de_admissao[BUFFER_SIZE];
    char nova_data_de_admissao[BUFFER_SIZE];
    int i;
    
    printf ("Digite a Nova_Data_de_Admissao: ");
    fgets(nova_data_de_admissao, BUFFER_SIZE, stdin);
    for (i=0; i < BUFFER_SIZE; i++)
    {
        if(strcmp(matricula,"\n") == 0)
        {
            strcpy(data_de_admissao, nova_data_de_admissao);
            break;
        }
    }
  printf("\nData de Admissão Atualizada com Successo.\n");
  sleep(2);
  system("clear");
  printf("\nVoltando...\n");
  sleep(1);
  system("clear");
}
void alterar_salario()
{   
    char matricula[BUFFER_SIZE];
    char salario[BUFFER_SIZE];
    char novo_salario[BUFFER_SIZE];
    int i;
  
    printf ("Digite o Novo_Salario: ");
    fgets(novo_salario, BUFFER_SIZE, stdin);
    for (i=0; i < BUFFER_SIZE; i++)
    {
        if(strcmp(matricula,"\n") == 0)
        {
            strcpy(salario, novo_salario);
            break;
        }
    }
  printf("\nSalario Atualizado com Successo.\n");
  sleep(2);
  system("clear");
  printf("\nVoltando...\n");
  sleep(1);
  system("clear");
}
void menu_Principal()
{
  system("clear");
  printf("\nVoltando para o menu principal...\n");
  sleep(1);main();
    
}
void excluir_funcionario()
{
  char *line_buf = NULL;
  char stop[1];
  size_t line_buf_size = 0;
  char confirmar[BUFFER_SIZE] = "0";
  int line_count = 0;
  ssize_t line_size;
  FILE *file = fopen(FUNCIONARIOS_FILE, "r");
  FILE *file_new = fopen(FUNCIONARIOS_FILE, "r");
  FILE *fTemp = fopen("replace.tmp", "w");
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

  line_size = getline(&line_buf, &line_buf_size, file);

  printf("Excluir funcionário\n");
  printf("--------------------\n\n");
  printf("Digite: id\n");
  fgets(id, BUFFER_SIZE, stdin);  
  id[strlen(id) - 1] = 0;

  while (line_size >= 0)
  {
    line_count++;

    strcpy(record, line_buf);
    record_id = strtok(line_buf, ";");

    if (strcmp(id, record_id) == 0)
    {
      founded = 1;
      system("clear");
      printf("Você realmente deseja excluir esse funcionário ?\n");
      printf("----------------------------------------------\n");

      char *token = strtok(record, ";");

      int i = 0;
      while (token != NULL)
      {
        printf("%s: %s\n", header[i], token);
        token = strtok(NULL, ";");
        i++;
      }

      printf("--------------------------\n");
      break;
    }

    line_size = getline(&line_buf, &line_buf_size, file);
  }

  if (founded == 0)
  {
    system("clear");
    printf("\n404 - Funcionário não encontrado\n");
    printf("---------------------------------\n\n");
    printf("Enter para voltar\n");
    fgets(stop, BUFFER_SIZE, stdin);
  } 
    else 
  {
    printf("Digite 1 para confirmar ou 0 para cancelar\n");
    fgets(confirmar, BUFFER_SIZE, stdin);
    confirmar[strlen(confirmar) - 1] = 0;

    if (strcmp(confirmar, "1") == 0) {
      printf("Excluindo funcionário\n");
      printf("---------------------\n\n");
      sleep(1);      
      line_size = 0;
      line_count = 0;
      line_size = getline(&line_buf, &line_buf_size, file_new);
      
      while (line_size >= 0)
      {
        line_count++; 

        strcpy(record, line_buf);

        record_id = strtok(line_buf, ";");   
      
        if (strcmp(id, record_id) != 0)
        {        
          fputs(record, fTemp);         
        }

        line_size = getline(&line_buf, &line_buf_size, file_new);
      }

      fclose(fTemp);      
      remove(FUNCIONARIOS_FILE);
      rename("replace.tmp", FUNCIONARIOS_FILE);
      printf("Funcionário excluído con sucesso!\n");
      sleep(2);
    }

    free(line_buf);
    line_buf = NULL;
    fclose(file);
  }
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

// Contribuidores:

// Marília Santos - santosmarilia0@gmail.com
// Irinaldo Pantoja - irinaldo01santos@gmail.com
// Atila Silva - atila.danvi@outlook.com

#include <stdio.h> // printf, scanf, ...
#include <string.h> // strlen, strcmp, ...
#include <stdlib.h> // malloc, free, ...
#include <unistd.h> // getpid, fork, ...

/* Funções do programa */
void adicionar_funcionario(); // Adiciona um funcionário
void buscar_funcionario(); // Busca um funcionário
void listar_funcionarios(); // Lista todos os funcionários
void atualizar_funcionario(); // Atualiza um funcionário
void excluir_funcionario(); // Exclui um funcionário

/* Funções do sistema */
int last_id(); // Retorna o último id cadastrado
int increment_id(int id); // Incrementa o id

/* Constantes */
#define BUFFER_SIZE 1000 // Tamanho do buffer
#define DATABASE_FILE "database.txt" // Nome do arquivo de dados
#define FUNCIONARIOS_FILE "funcionarios.txt" // Nome do arquivo de funcionarios

/* Função main - entry-point */
int main()
{

  char data[BUFFER_SIZE]; // buffer para leitura de dados
  int acao; // acao a ser executada

  do {
    system("clear");
    printf("\t\t\t\t\t\t...RH-cli...\n"); // titulo do programa
    printf("\t\t\t=====================================\n"); // separador
    printf("\t\t\t| 1 - Cadastrar Funcionário         |\n"); // opção 1
    printf("\t\t\t| 2 - Buscar Funcionário            |\n"); // opção 2
    printf("\t\t\t| 3 - Listar Funcionários           |\n"); // opção 3
    printf("\t\t\t| 4 - Atualizar Dados do Funcionário|\n"); // opção 4
    printf("\t\t\t| 5 - Excluir Funcionário           |\n"); // opção 5
    printf("\t\t\t| 0 - Sair                          |\n"); // opção 0
    printf("\t\t\t=====================================\n"); // separador
    printf("\t\t\tDigite a Opção Desejada:"); // mensagem de entrada
    scanf("%d", &acao); // leitura da opção

    // switch para executar a ação desejada
    switch (acao)
    {
      case 0: // sair
        system("clear"); // limpa a tela
        return 0; // encerra o programa
      case 1: // cadastrar funcionario
        system("clear"); // limpa a tela
        fgets(data, BUFFER_SIZE, stdin); // leitura do buffer
        adicionar_funcionario(); // chama a função de adicionar funcionario
        break; // sai do switch
      case 2: // opção 2
        system("clear"); // limpa a tela
        fgets(data, BUFFER_SIZE, stdin); // leitura do buffer
        buscar_funcionario(); //  chama a função de buscar funcionario
        break; // sai do switch
      case 3: // listar funcionarios
        system("clear"); // limpa a tela
        fgets(data, BUFFER_SIZE, stdin); // leitura do buffer
        listar_funcionarios(); // chama a função de listar funcionarios
        break; // sai do switch
      case 4: // atualizar funcionario
        system("clear"); // limpa a tela
        fgets(data, BUFFER_SIZE, stdin); // leitura do buffer
        atualizar_funcionario(); // chama a função de atualizar funcionario
        break; // sai do switch
      case 5: // excluir funcionario
        system("clear"); // limpa a tela
        fgets(data, BUFFER_SIZE, stdin); // leitura do buffer
        excluir_funcionario(); // chama a função de excluir funcionario
        break; // sai do switch
      default: // opção inválida
        system("clear"); // limpa a tela
        printf("Opção inválida\n"); // mensagem de erro
        printf("--------------\n"); // separador
        printf("Voltando...\n"); // mensagem de retorno
        sleep(1); // pausa de 1 segundo
    }
  } while (acao != acao + 10); // enquanto a opção não for 0

  return 0; // encerra o programa
}

// Função para adicionar funcionario
void adicionar_funcionario()
{
  char record[BUFFER_SIZE]; // buffer para leitura de dados
  char nome[BUFFER_SIZE]; // buffer para leitura do dado nome
  char matricula[BUFFER_SIZE]; // buffer para leitura do dado matricula
  char email[BUFFER_SIZE]; // buffer para leitura do dado email
  char data_de_admissao[BUFFER_SIZE]; // buffer para leitura do dado data de admissao
  char salario[BUFFER_SIZE]; // buffer para leitura do dado salario
  FILE * file; // ponteiro para o arquivo

  int new_id; // id do funcionario
  char id[BUFFER_SIZE]; // buffer para leitura do dado id

  new_id = last_id() + 1; // calcula o id do funcionario
  sprintf(id, "%d", new_id); // converte o id para string

  printf("Cadastrando funcionário\n"); // mensagem de entrada
  printf("-----------------------\n\n"); // separador
  printf("Digite: Nome\n"); // mensagem de entrada
  fgets(nome, BUFFER_SIZE, stdin); // leitura do buffer
  nome[strcspn(nome, "\n")] = 0; // remove o \n do final da string

  printf("Digite: Matrícula\n"); // mensagem de entrada
  fgets(matricula, BUFFER_SIZE, stdin); // leitura do buffer
  matricula[strcspn(matricula, "\n")] = 0; // remove o \n do final da string

  printf("Digite: Email\n"); // mensagem de entrada
  fgets(email, BUFFER_SIZE, stdin); // leitura do buffer
  email[strcspn(email, "\n")] = 0; // remove o \n do final da string

  printf("Digite: Data de admisssão\n"); // mensagem de entrada
  fgets(data_de_admissao, BUFFER_SIZE, stdin); // leitura do buffer
  data_de_admissao[strcspn(data_de_admissao, "\n")] = 0; // remove o \n do final da string

  printf("Digite: Salario\n"); // mensagem de entrada
  fgets(salario, BUFFER_SIZE, stdin); // leitura do buffer

  // monta o registro
  snprintf(record, BUFFER_SIZE, "%s;%s;%s;%s;%s;%s", id, matricula, nome, email, data_de_admissao, salario);

  file = fopen(FUNCIONARIOS_FILE, "a"); // abre o arquivo para escrita
  fputs(record, file); // escreve o registro no arquivo
  fclose(file); // fecha o arquivo

  increment_id(new_id); // incrementa o id do funcionario

  printf("\nUsuário criado com successo.\n"); // mensagem de retorno
  sleep(2); // pausa de 2 segundos
  system("clear"); // limpa a tela
  printf("\nVoltando para o menu principal...\n"); // mensagem de retorno
  sleep(1); // pausa de 1 segundo
}

// Função para buscar funcionario
void buscar_funcionario()
{
  char *line_buf = NULL; // buffer para leitura de linha
  size_t line_buf_size = 0; // tamanho do buffer
  int line_count = 0; // contador de linhas
  ssize_t line_size; // tamanho da linha
  FILE *file = fopen(FUNCIONARIOS_FILE, "r"); // ponteiro para o arquivo
  char id[BUFFER_SIZE]; // buffer para leitura do dado id
  char *record_id = NULL; // buffer para leitura do dado id
  char record[BUFFER_SIZE]; // buffer para leitura de registro
  int founded = 0; // flag para registro encontrado
  // cabecalho da tabela
  char header[6][20] = {
    { "ID" },
    { "MATRÍCULA" },
    { "NOME" },
    { "EMAIL" },
    { "DATA DE ADMISSÃO" },
    { "SALÁRIO" }
  };

  line_size = getline(&line_buf, &line_buf_size, file); // leitura da linha

  printf("Buscando funcionário\n"); // mensagem de entrada
  printf("--------------------\n\n"); // separador
  printf("Digite: id\n"); // mensagem de entrada
  fgets(id, BUFFER_SIZE, stdin); // leitura do buffer
  id[strlen(id) - 1] = 0; // remove o \n do final da string

  //  percorre todas as linhas do arquivo
  while (line_size >= 0)
  {
    line_count++; // incrementa o contador de linhas
    strcpy(record, line_buf); // copia o registro para o buffer
    record_id = strtok(line_buf, ";"); // pega o id do registro

    if (strcmp(id, record_id) == 0) // se o id for igual ao id do registro  
    {
      founded = 1; // registro encontrado
      system("clear"); // limpa a tela
      printf("Funcionário encontrado\n"); // mensagem de retorno
      printf("--------------------------\n"); // separador

      char *token = strtok(record, ";"); // pega o id do registro
      int i = 0; // contador de colunas

      while (token != NULL) // enquanto nao chegar ao final do registro
      {
        printf("%s: %s\n", header[i], token); // imprime o dado da coluna
        token = strtok(NULL, ";"); // pega o dado da proxima coluna
        i++; // incrementa o contador de colunas
      }

      printf("--------------------------\n\n"); // separador
      break; // sai do loop
    }

    line_size = getline(&line_buf, &line_buf_size, file); // leitura da linha
  }

  free(line_buf); // libera o buffer
  line_buf = NULL; // zera o buffer
  fclose(file); // fecha o arquivo

  if (founded == 0) // se nao encontrou o registro
  {
    system("clear"); // limpa a tela
    printf("\n404 - Funcionário não encontrado\n"); // mensagem de retorno
    printf("---------------------------------\n\n"); // separador
    sleep(2); // pausa de 2 segundos
    system("clear"); // limpa a tela
    printf("Voltando para o menu principal...\n"); // mensagem de retorno
    sleep(1); // pausa de 1 segundo
  }

  printf("Enter para voltar\n"); // mensagem de retorno
  fgets(id, BUFFER_SIZE, stdin); // leitura do buffer
}

void listar_funcionarios()
{
  char stop[1]; // buffer para leitura de stop
  char linha[BUFFER_SIZE]; // buffer para leitura de linha
  FILE* file; // ponteiro para o arquivo
  file = fopen(FUNCIONARIOS_FILE, "r"); // abre o arquivo para leitura
  //  cabecalho da tabela
  char header[6][20] = {
    { "ID" },
    { "MATRÍCULA" },
    { "NOME" },
    { "EMAIL" },
    { "DATA DE ADMISSÃO" },
    { "SALÁRIO" }
  };

  printf("Listagem de funcionários\n"); // mensagem de entrada

  int i = 0; // contador de colunas
  // percorre todas as linhas do arquivo
  while (fgets(linha, BUFFER_SIZE, file))
  {
    // imprime o dado da coluna
    if(i != 0) { // se nao for a primeira linha
      linha[strcspn(linha, "\n")] = 0; // remove o \n do final da string

      printf("--------------------------\n"); // separador

      char *campo = strtok(linha, ";"); // pega o dado da coluna
      int n = 0; // contador de colunas

      while (campo != NULL) // enquanto nao chegar ao final do registro
      {
        printf("%s: %s\n", header[n], campo); // imprime o dado da coluna
        campo = strtok(NULL, ";"); // pega o dado da proxima coluna
        n++; // incrementa o contador de colunas
      }
    }

    i++; // incrementa o contador de colunas
  }

  fclose(file); // fecha o arquivo

  printf("----------------------\n\n"); // separador
  printf("Enter para voltar\n"); // mensagem de retorno
  fgets(stop, BUFFER_SIZE, stdin); // leitura do buffer
}

// funcao para atualizar um funcionario
void atualizar_funcionario()
{
  char *line_buf = NULL; // buffer para leitura de linha
  char stop[1]; // buffer para leitura de stop
  size_t line_buf_size = 0; // tamanho do buffer
  char confirmar[BUFFER_SIZE] = "0"; // buffer para leitura de confirmacao
  int line_count = 0; // contador de linhas
  ssize_t line_size; // tamanho da linha
  FILE *file = fopen(FUNCIONARIOS_FILE, "r"); // abre o arquivo para leitura
  FILE *file_new = fopen(FUNCIONARIOS_FILE, "r"); // abre o arquivo para leitura
  FILE *fTemp = fopen("replace.tmp", "w"); // abre o arquivo temporario para escrita
  char id[BUFFER_SIZE]; // buffer para leitura de id
  char *record_id = NULL; // buffer para pegar o id do registro
  char record[BUFFER_SIZE]; // buffer para pegar o registro
  int founded = 0; // flag para registro encontrado
  // cabecalho da tabela
  char header[6][20] = {
    { "ID" },
    { "MATRÍCULA" },
    { "NOME" },
    { "EMAIL" },
    { "DATA DE ADMISSÃO" },
    { "SALARIO" }
  };

  char nome[BUFFER_SIZE]; // buffer para leitura de nome
  char matricula[BUFFER_SIZE]; // buffer para leitura de matricula
  char email[BUFFER_SIZE]; // buffer para leitura de email
  char data_de_admissao[BUFFER_SIZE]; // buffer para leitura de data de admissao
  char salario[BUFFER_SIZE]; // buffer para leitura de salario

  line_size = getline(&line_buf, &line_buf_size, file); // leitura da linha

  printf("Buscar funcionário para editar\n"); // mensagem de entrada
  printf("--------------------\n\n"); // separador
  printf("Digite: id\n"); // mensagem de entrada
  fgets(id, BUFFER_SIZE, stdin); // leitura do buffer
  id[strlen(id) - 1] = 0; // remove o \n do final da string

  // percorre todas as linhas do arquivo
  while (line_size >= 0)
  {
    line_count++; // incrementa o contador de linhas

    strcpy(record, line_buf); // copia a linha para o registro
    record_id = strtok(line_buf, ";"); // pega o id do registro

    if (strcmp(id, record_id) == 0) // se o id for igual ao id do registro
    {
      founded = 1; // registro encontrado
      break; // sai do loop
    }

    line_size = getline(&line_buf, &line_buf_size, file); // leitura da linha
  }

  if (founded == 0) // se nao encontrou o registro
  {
    system("clear"); // limpa a tela
    printf("\n404 - Funcionário não encontrado\n"); // mensagem de retorno
    printf("---------------------------------\n\n"); // separador
    sleep(2); // pausa de 2 segundos
    system("clear"); // limpa a tela
    printf("Voltando para o menu principal...\n"); // mensagem de retorno
    sleep(1); // pausa de 1 segundo
  }
    else // se encontrou o registro
  {
    system("clear"); // limpa a tela
    printf("Editando funcionário\n"); // mensagem de entrada
    printf("---------------------\n\n"); // separador
    line_size = 0; // zera o contador de linhas
    line_count = 0; // zera o contador de linhas
    line_size = getline(&line_buf, &line_buf_size, file_new); // leitura da linha

    // percorre todas as linhas do arquivo
    while (line_size >= 0)
    {
      line_count++; // incrementa o contador de linhas

      strcpy(record, ""); // zera o registro

      strcpy(record, line_buf); // copia a linha para o registro

      record_id = strtok(line_buf, ";"); // pega o id do registro

      if (strcmp(id, record_id) == 0) // se o id for igual ao id do registro 
      {
        char *token = strtok(record, ";"); // pega o dado da coluna
        int i = 0; // contador de colunas

        // percorre todas as colunas do registro
        while (token != NULL)
        {
          // se a coluna for o nome
          if(strcmp(header[i], "NOME") == 0) {
            printf("Edite o %s:\n", header[i]); // mensagem de entrada
            fgets(nome, BUFFER_SIZE, stdin); // leitura do buffer
            nome[strcspn(nome, "\n")] = 0; // remove o \n do final da string
          }

          // se a coluna for a matricula
          if(strcmp(header[i], "MATRÍCULA") == 0) {
            printf("Edite o %s:\n", header[i]); // mensagem de entrada
            fgets(matricula, BUFFER_SIZE, stdin); // leitura do buffer
            matricula[strcspn(matricula, "\n")] = 0; // remove o \n do final da string
          }

          // se a coluna for o email
          if(strcmp(header[i], "EMAIL") == 0) {
            printf("Edite o %s:\n", header[i]); // mensagem de entrada
            fgets(email, BUFFER_SIZE, stdin); // leitura do buffer
            email[strcspn(email, "\n")] = 0; // remove o \n do final da string
          }

          // se a coluna for a data de admissao
          if(strcmp(header[i], "DATA DE ADMISSÃO") == 0) {
            printf("Edite o %s:\n", header[i]); // mensagem de entrada
            fgets(data_de_admissao, BUFFER_SIZE, stdin); // leitura do buffer
            data_de_admissao[strcspn(data_de_admissao, "\n")] = 0; // remove o \n do final da string
          }

          // se a coluna for o salario
          if(strcmp(header[i], "SALARIO") == 0) {
            printf("Edite o %s:\n", header[i]); // mensagem de entrada
            fgets(salario, BUFFER_SIZE, stdin); // leitura do buffer
          }

          token = strtok(NULL, ";"); // pega o dado da coluna

          i++; // incrementa o contador de colunas

          // monta o registro
          snprintf(record, BUFFER_SIZE, "%s;%s;%s;%s;%s;%s", id, matricula, nome, email, data_de_admissao, salario);
        }
      }

      fputs(record, fTemp); // escreve o registro no arquivo temporario

      line_size = getline(&line_buf, &line_buf_size, file_new); //
    }

    fclose(fTemp); // fecha o arquivo temporario
    remove(FUNCIONARIOS_FILE); // remove o arquivo antigo
    rename("replace.tmp", FUNCIONARIOS_FILE); //

    free(line_buf); // libera o buffer
    line_buf = NULL; // zera o ponteiro
    fclose(file); // fecha o arquivo antigo

    printf("Funcionário editado con sucesso!\n"); // mensagem de retorno
    sleep(4); // pausa de 4 segundos
    printf("----------------------\n\n"); // separador
    printf("Enter para voltar\n"); // mensagem de retorno
    fgets(stop, BUFFER_SIZE, stdin); // leitura do buffer
  }
}

// funcao para remover um funcionario
void excluir_funcionario()
{
  char *line_buf = NULL; // buffer de leitura
  char stop[1]; // buffer de leitura
  size_t line_buf_size = 0; // tamanho do buffer
  char confirmar[BUFFER_SIZE] = "0"; // buffer de leitura
  int line_count = 0; // contador de linhas
  ssize_t line_size; // tamanho da linha
  FILE *file = fopen(FUNCIONARIOS_FILE, "r"); // abre o arquivo
  FILE *file_new = fopen(FUNCIONARIOS_FILE, "r"); // abre o arquivo
  FILE *fTemp = fopen("replace.tmp", "w"); // abre o arquivo temporario
  char id[BUFFER_SIZE]; // buffer de leitura do id
  char *record_id = NULL; // buffer de leitura do id
  char record[BUFFER_SIZE]; // buffer de leitura do registro
  int founded = 0; // flag de registro encontrado
  // cabeçalho da tabela
  char header[6][20] = {
    { "ID" },
    { "MATRÍCULA" },
    { "NOME" },
    { "EMAIL" },
    { "DATA DE ADMISSÃO" },
    { "SALÁRIO" }
  };

  line_size = getline(&line_buf, &line_buf_size, file); // leitura da linha

  printf("Excluir funcionário\n"); // mensagem de entrada
  printf("--------------------\n\n"); // separador
  printf("Digite: id\n"); // mensagem de entrada
  fgets(id, BUFFER_SIZE, stdin); // leitura do buffer
  id[strlen(id) - 1] = 0; // remove o \n do final da string

  // percorre todas as linhas do arquivo
  while (line_size >= 0)
  {
    line_count++; // incrementa o contador de linhas

    strcpy(record, line_buf); // copia a linha para o registro
    record_id = strtok(line_buf, ";"); // pega o id do registro

    // se o id for igual ao digitado
    if (strcmp(id, record_id) == 0)
    {
      founded = 1; // flag de registro encontrado
      system("clear"); // limpa a tela
      printf("Você realmente deseja excluir esse funcionário ?\n"); // mensagem de entrada
      printf("----------------------------------------------\n"); // separador

      char *token = strtok(record, ";"); // pega o dado da coluna

      int i = 0; // contador de colunas

      // percorre todas as colunas do registro
      while (token != NULL)
      {
        printf("%s: %s\n", header[i], token); // imprime o dado da coluna
        token = strtok(NULL, ";"); // pega o dado da coluna
        i++; // incrementa o contador de colunas
      }

      printf("--------------------------\n"); // separador
      break; // sai do loop
    }

    line_size = getline(&line_buf, &line_buf_size, file); // leitura da linha
  }

  // se o registro foi encontrado
  if (founded == 0)
  {
    system("clear"); // limpa a tela
    printf("\n404 - Funcionário não encontrado\n"); // mensagem de retorno
    printf("---------------------------------\n\n"); // separador
    printf("Enter para voltar\n"); // mensagem de retorno
    fgets(stop, BUFFER_SIZE, stdin); // leitura do buffer
  }
    else // se o registro foi encontrado
  {
    printf("Digite 1 para confirmar ou 0 para cancelar\n"); // mensagem de entrada
    fgets(confirmar, BUFFER_SIZE, stdin); // leitura do buffer
    confirmar[strlen(confirmar) - 1] = 0; // remove o \n do final da string

    // se o usuario confirmar a exclusao
    if (strcmp(confirmar, "1") == 0) {
      printf("Excluindo funcionário\n"); // mensagem de entrada
      printf("---------------------\n\n"); // separador
      sleep(1); // pausa de 1 segundo
      line_size = 0; // zera o tamanho da linha
      line_count = 0; // zera o contador de linhas
      line_size = getline(&line_buf, &line_buf_size, file_new); // leitura da linha

      // percorre todas as linhas do arquivo
      while (line_size >= 0)
      {
        line_count++; // incrementa o contador de linhas

        strcpy(record, line_buf); // copia a linha para o registro

        record_id = strtok(line_buf, ";"); // pega o id do registro

        if (strcmp(id, record_id) != 0) // se o id for diferente do id do registro
        {
          fputs(record, fTemp); // escreve o registro no arquivo temporario
        }

        line_size = getline(&line_buf, &line_buf_size, file_new); // leitura da linha
      }

      fclose(fTemp); // fecha o arquivo temporario
      remove(FUNCIONARIOS_FILE); // remove o arquivo
      rename("replace.tmp", FUNCIONARIOS_FILE); // renomeia o arquivo temporario para o arquivo principal
      printf("Funcionário excluído con sucesso!\n"); // mensagem de retorno
      sleep(2); // pausa de 2 segundos
    }

    free(line_buf); // libera o buffer
    line_buf = NULL; // zera o buffer
    fclose(file); // fecha o arquivo
  }
}

// funcao para pegar último indice
int last_id()
{
  FILE * file; // arquivo
  int id; // id
  char id_str[BUFFER_SIZE]; // buffer de leitura do id

  file = fopen(DATABASE_FILE, "r"); // abre o arquivo
  fgets(id_str, BUFFER_SIZE, file); // leitura do buffer
  fclose(file); // fecha o arquivo
  id = atoi(id_str); // converte o id para inteiro

  if (id == 0) // se o id for 0
  {
    id = 1; // atribui 1 ao id
  }

  return id; // retorna o id
}

// funcao para incrementar indice
int increment_id(int id)
{
  FILE * file; // arquivo
  char id_str[BUFFER_SIZE]; // buffer de leitura do id

  sprintf(id_str, "%d", id); // converte o id para string

  file = fopen(DATABASE_FILE, "w"); // abre o arquivo
  fputs(id_str, file); // escreve o id no arquivo
  fclose(file); // fecha o arquivo

  return id; // retorna o id
}

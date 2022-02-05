# rh-cli

![logo](/rh-cli.png "rh-cli")

 
## Sistema de Gerenciamento de Funcionários em C
 
### Funcionalidades
 
* Cadastrar funcionário
* Buscar funcionário
* Atualizar funcionário
* Excluir funcionário
* Listar funcionários

## Demo
![prompt](/rh-cli-prompt.gif "rh-cli")
 
### Arquitetura:
 
![diagrama](/arquitetura.png "Arquitetura da aplicação")
 
### Banco de Dados:
 
Para realizar funções de manipulação de registros foi desenvolvido uma mini abstração de banco de dados. Consiste em utilizar o sistema de arquivos do sistema operacional para gerenciá-los.
 
Foi criado um sistema de índices para preservar a unicidade dos registros.
 
A priori teríamos a matrícula como identificador. Mas pensando em atender a migração de matrículas
deixamos o campo livre para digitação. Mas isso não impede que o id seja usado para a mesma função.
 
### Programa:
 
O programa foi fragmentado em função do tipo void que são chamadas no entry-point da aplicação através de um bloco de repetição while que fica escutando as operações desejadas pelo usuário.
 
Cada funcionalidade tem uma função específica e lhe é atribuído um código de referência.
 
## Como executar ?
 
É preciso que o path root do projeto tenha permissões de escrita.
 
### Requerimentos:
 
* C
* GCC ou similar
* Bibliotecas
 * stdio.h
 * string.h
 * stdlib.h
 * unistd.h
 
*** PS: Programa portável. Pode ser compilado e executado em qualquer plataforma. Não possui bibliotecas dependentes de um sistema operacional específico.
 
### Compilando:
 
   $ gcc main.c -o main.o
 
### Executando:
 
   $ ./main.o
 
## Contribuidores:
 
Marília Santos - santosmarilia0@gmail.com
 
Irinaldo Pantoja - irinaldo01santos@gmail.com
 
Atila Silva - atila.danvi@outlook.com
 
## Referências:
 
https://www.tutorialspoint.com
https://www.geeksforgeeks.org/c-programming-language
https://www.w3schools.in/c-tutorial
 
![diagrama](/gimme-code-gimme.gif "Arquitetura da aplicação")

# Fim !!!
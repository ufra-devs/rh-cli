# rh-cli

## Sistema de Gerenciamento de Funcionários em C

### Funcionalidades

* Cadastrar funcionário
* Buscar funcionário
* Atualizar funcionário
* Exclluir funcionário
* Listar funcionários

### Arquitetura:

![diagrama](/arquitetura.png "Arquitetura da aplicação")

### Banco de Dados:

Para realizar funções de manipulação de registros foi desenvolvido uma mini abstração de banco de dados. Que consiste em utilizar o sistema de arquivos do sistema operacional para gerencia-los.

Foi criado um sistemas de índices para preservar a unicidade dos registros.

A priori teríamos a matrícula como identificador. Mas pensando em atender a migração de matrículas
deixamos o campo livre para digitação. Mas isso não impede que o id seja usado para a mesma função.

### Programa:

O programa foi fragmentado em funções do tipo void que são chamadas no entry-point da aplicação através de um bloco de repetição while que fica escutando as operações desejadas pelo usuário.

Cada funcionalidade tem uma função especifica e lhe é atribuida um código de referência.

## Como executar ?

É preciso que o path root do projeto tenha permissões de escrita.

### Requirimentos:

* C
* GCC ou similar
* Biliotecas
  * stdio.h
  * string.h
  * stdlib.h
  * unistd.h

*** PS: Programa portável. Pode ser compilado e executado em qualquer plataforma. Não possuí biblotecas dependetes de um sistema operacional específico.

### Compilando:

    $ gcc main.c -o main.o

### Executando:

    $ ./main.o

## Contribuidores:

Marília Santos - santosmarilia0@gmail.com

Irinaldo Pantoja - irinaldo01santos@gmail.com

Atila Silva - atila.danvi@outlook.com

## Referências:

// TODO

# Fim !!!

![diagrama](/gimme-code-gimme.gif "Arquitetura da aplicação")
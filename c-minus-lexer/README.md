# C- Lexer Project

Este projeto implementa um analisador léxico para a linguagem C- utilizando a ferramenta Flex/Lex. O analisador é responsável por reconhecer os tokens da linguagem, detectar erros e gerar uma saída formatada que inclui informações sobre a linha, coluna, lexema e tipo do token identificado.

## Estrutura do Projeto

O projeto é organizado da seguinte forma:

```
c-minus-lexer
├── src
│   └── c_minus_lexer.l       # Implementação do analisador léxico
├── tests
│   ├── test_case_1.cm        # Programa de teste correto
│   └── test_case_error.cm     # Programa de teste com erros
├── report
│   └── report.md              # Relatório do projeto
├── Makefile                   # Instruções para compilação
└── README.md                  # Documentação do projeto
```

## Instruções de Compilação e Execução

Para compilar o projeto, utilize o Makefile incluído no diretório raiz. Execute o seguinte comando no terminal:

```
make
```

Isso irá gerar o analisador léxico e os executáveis necessários para os testes.

Para executar o analisador léxico, utilize o seguinte comando:

```
./c_minus_lexer < caminho_do_arquivo.cm
```

Substitua `caminho_do_arquivo.cm` pelo caminho do arquivo que deseja analisar.

## Testes Realizados

O projeto inclui dois arquivos de teste na pasta `tests`:

1. **test_case_1.cm**: Este arquivo contém um programa de teste correto que utiliza todos os tipos de tokens da linguagem C-. Ele serve para validar o funcionamento do analisador léxico.

2. **test_case_error.cm**: Este arquivo contém um programa de teste que inclui pelo menos 5 erros distintos. Ele é utilizado para verificar a capacidade do analisador léxico em detectar e reportar erros.

## Conclusão

Este projeto fornece uma implementação básica de um analisador léxico para a linguagem C-. Através dos testes realizados, foi possível validar a funcionalidade do analisador e sua capacidade de detectar erros lexicais.
# Compilador C- - Sistema Completo de Análise

**Autores:** Guilherme Fabricio Brito da Rosa, Harisson de Carvalho Alvarenga, Raul Soares de Carvalho

## 📋 Visão Geral

Este projeto implementa um compilador completo para a linguagem C- com:
- **Análise Léxica** (Flex)
- **Análise Sintática** (Bison) 
- **Análise Semântica** com tabela de símbolos
- **Geração de Código Intermediário** (três endereços)

## 🎯 Características da Linguagem C-

### Tipos de Dados
- `int`, `float`, `char`, `void`
- `struct` (registros)
- Arrays multidimensionais

### Funcionalidades
- Funções com recursão
- Estruturas de controle: `if`, `else`, `while`
- Operadores aritméticos e relacionais
- Comentários `/* */`

## 🏗️ Arquitetura do Sistema

```
compiler_c-/
├── c-minus/
│   ├── lexer/
│   │   ├── lexer.l              # Analisador léxico principal
│   │   ├── c-minus-lexer.l      # Lexer standalone
│   │   └── arquivos gerados     # lex.yy.c, scanner.yy.c
│   ├── parser/
│   │   └── parser.y             # Analisador sintático (Bison)
│   └── semantic/                # Sistema semântico
│       ├── semantic.c/h         # Análise semântica
│       ├── symbol_table.c/h     # Tabela de símbolos com hash
│       ├── code_generator.c/h   # Geração de código
│       └── utils.c/h            # Utilitários
├── tests/
│   ├── lexer/                   # Testes do analisador léxico
│   ├── parser/                  # Testes do analisador sintático
│   └── semantic/                # Testes da análise semântica
├── agente_semantico.c           # Interface interativa
├── scriptRunLexer.sh            # Script para executar lexer
├── ScriptRunParser.sh           # Script para executar parser
├── Makefile                     # Sistema de build
└── *.ir                         # Arquivos de código intermediário gerados
```

## ⚙️ Dependências

```bash
sudo apt update
sudo apt install flex bison gcc
```

## 🚀 Como Usar

### Compilar Tudo
```bash
make all
```

### Sistema Semântico (Principal)
```bash
# Interface interativa do agente semântico
make run-agent

# Análise automática de todos os testes semânticos
make test-semantic

# Testes individuais por arquivo
make test-basico           # programa_basico.txt
make test-arrays           # programa_arrays.txt
make test-funcoes          # programa_funcoes.txt
make test-structs          # programa_structs.txt
make test-erros            # programa_com_erros.txt
make test-complexo         # programa_complexo.txt
```

### Analisadores Léxico/Sintático (Standalone)
```bash
# Nota: Os scripts requerem ajustes para a estrutura atual
# O foco principal do projeto é o sistema semântico
```

## ✅ Funcionalidades Implementadas

### 1. **Tabela de Símbolos**
- Hash table com 211 posições
- Resolução de colisões por encadeamento
- Gerenciamento de escopo hierárquico
- Armazenamento de tipos, endereços e metadados

### 2. **Análise Semântica**
- Verificação de tipos em operações
- Detecção de variáveis não declaradas
- Validação de compatibilidade de tipos
- Conversão implícita (int ↔ float)
- Verificação de redeclarações

### 3. **Geração de Código Intermediário**
- Código de três endereços padrão
- Geração automática de temporários (`t0, t1, t2...`)
- Labels para controle de fluxo (`L0, L1, L2...`)
- Suporte a arrays multidimensionais
- Estruturas de controle (if/while)

### 4. **Arquivos de Teste Disponíveis**
- `programa_basico.txt`: Estruturas básicas
- `programa_arrays.txt`: Arrays 1D e 2D  
- `programa_structs.txt`: Estruturas de dados
- `programa_funcoes.txt`: Chamadas de função
- `programa_com_erros.txt`: Detecção de erros
- `programa_complexo.txt`: Exemplo completo

## 📊 Exemplo de Saída

### Tabela de Símbolos
```
=== TABELA DE SÍMBOLOS ===
Nome            Tipo       DataType   Escopo Linha  Endereço 
================================================================
x               var        int        0      3      1         
y               var        int        0      4      2         
main            func       int        0      2      0         
================================================================
```

### Código de Três Endereços
```
=== CÓDIGO INTERMEDIÁRIO DE TRÊS ENDEREÇOS ===
  1: x = 5
  2: y = 3
  3: resultado = soma(x, y)
  4: a = 10.5
  5: b = 20.3
  6: media_val = media(a, b)
```

## 🔧 Agente Semântico Interativo

O agente oferece menu com opções para:
- Escanear arquivos semânticos
- Ler conteúdo de arquivos
- Executar análises individuais
- Executar análise completa
- Exibir estatísticas do projeto

## 🎓 Status do Projeto

### ✅ Requisitos Atendidos
- [x] Tabela de símbolos com hash table
- [x] Gerenciamento de escopo hierárquico
- [x] Análise semântica completa
- [x] Geração de código intermediário
- [x] Suporte a arrays multidimensionais
- [x] Suporte a structs e funções
- [x] Interface interativa de teste
- [x] Sistema de build automatizado

### 🔧 Correções Implementadas
- Loop infinito no `test-semantic` corrigido
- Análise baseada no conteúdo real dos arquivos
- Comandos individuais para cada arquivo de teste
- Detecção real de erros semânticos

### 📁 Arquivos Gerados
Para cada teste, o sistema gera:
- Arquivo `.ir` com código de três endereços
- Tabela de símbolos no terminal
- Relatório de erros (quando aplicável)

---

**Projeto desenvolvido para a disciplina de Compiladores - UFLA**
    numero = 5;
    return fatorial(numero);
}
```

## Funcionamento

### Analisador Léxico (Flex)
O arquivo `lexer.l` define as regras para reconhecer tokens da linguagem C-Minus:
- Palavras reservadas (`int`, `float`, `if`, `while`, etc.)
- Identificadores e números
- Operadores e pontuação
- Comentários (que são ignorados)

### Analisador Sintático (Bison)
O arquivo `parser.y` define a gramática da linguagem C-Minus, especificando:
- Estrutura de programas e funções
- Expressões aritméticas e relacionais
- Comandos de controle de fluxo
- Declarações de variáveis e arrays

### Integração
O lexer e parser trabalham juntos: o lexer quebra o código-fonte em tokens, que são então analisados pelo parser para verificar se seguem a gramática da linguagem.

## Saída

- **Lexer**: Lista os tokens encontrados com linha e coluna
- **Parser**: Verifica se o código segue a sintaxe correta, reportando erros sintáticos se houver
- **Log**: Arquivo detalhado de debug salvo em `tests/parser/log.txt`

## Exemplo de Uso

```bash
# Compilar e testar com arquivo específico
./ScriptRunParser.sh meu_programa.txt

# Verificar o log de execução
cat tests/parser/log.txt
```
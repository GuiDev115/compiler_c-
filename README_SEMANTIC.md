# Compilador C- - Sistema de Análise Semântica e Geração de Código

## Autores
- **Guilherme Fabricio Brito da Rosa**
- **Harisson de Carvalho Alvarenga**
- **Raul Soares de Carvalho**

## Descrição

Este projeto implementa um compilador para a linguagem C- que inclui:

1. **Tabela de Símbolos** - Implementada com hash table para armazenar identificadores
2. **Análise Semântica** - Verificação de tipos, escopo e declarações
3. **Geração de Código Intermediário** - Código de três endereços

## Características da Linguagem C-

### Tipos de Dados
- `int` - Inteiros
- `float` - Números reais
- `char` - Caracteres
- `struct` - Registros
- Arrays multidimensionais

### Palavras Reservadas
- `int`, `float`, `char`, `void`, `struct`
- `if`, `else`, `while`, `return`

### Funcionalidades
- Funções com recursão
- Parâmetros passados por valor
- Comandos de atribuição, condicionais e iteração
- Comentários `/* */`

## Arquitetura do Sistema

### 1. Tabela de Símbolos (`symbol_table.h/c`)

```c
typedef struct SymbolEntry {
    char* name;              // Nome do símbolo
    SymbolType symbol_type;  // Tipo do símbolo (var, func, struct)
    DataType data_type;      // Tipo de dados (int, float, etc.)
    int scope_level;         // Nível de escopo
    int line_declared;       // Linha de declaração
    int address;             // Endereço relativo
    int is_array;            // Se é array
    ArrayDim* dimensions;    // Dimensões do array
    Parameter* parameters;   // Parâmetros (para funções)
    StructAttr* struct_attrs; // Atributos (para structs)
    struct SymbolEntry* next; // Lista ligada
} SymbolEntry;
```

**Características:**
- Hash table com 211 posições
- Gerenciamento de escopo hierárquico
- Suporte a arrays multidimensionais
- Armazenamento de parâmetros de funções
- Cálculo automático de endereços relativos

### 2. Análise Semântica (`semantic.h/c`)

**Verificações implementadas:**
- Declaração de variáveis antes do uso
- Compatibilidade de tipos em operações
- Redeclaração de símbolos no mesmo escopo
- Verificação de tipos em atribuições
- Verificação de acesso a arrays
- Verificação de chamadas de função

**Exemplo de uso:**
```c
// Verifica operação binária
DataType result = check_binary_op(TYPE_INT, TYPE_FLOAT, "+", line_num);

// Verifica atribuição
DataType assign_result = check_assignment(TYPE_INT, TYPE_FLOAT, line_num);
```

### 3. Geração de Código Intermediário (`code_generator.h/c`)

**Formato de três endereços:**
```
resultado = operando1 operador operando2
```

**Tipos de instruções geradas:**
- Operações aritméticas: `t1 = x + y`
- Atribuições: `x = 42`
- Acesso a arrays: `t1 = arr[i]`
- Atribuição a arrays: `arr[i] = valor`
- Chamadas de função: `t1 = call func`
- Instruções de salto: `goto L1`, `if x goto L1`
- Retorno: `return x`

### 4. Utilitários (`utils.h/c`)

**Funcionalidades:**
- Validação de identificadores
- Conversão de tipos
- Manipulação de strings segura
- Pilha de strings
- Logging de mensagens

## Estrutura do Projeto

```
compiler_c-/
├── c-minus/
│   ├── parser/
│   │   ├── parser.y          # Gramática Bison
│   │   └── parser.tab.c      # Código gerado
│   ├── semantic/
│   │   ├── symbol_table.h/c  # Tabela de símbolos
│   │   ├── semantic.h/c      # Análise semântica
│   │   ├── code_generator.h/c # Gerador de código
│   │   └── utils.h/c         # Utilitários
│   └── lexer/
│       └── lexer.l           # Analisador léxico
├── tests/
│   ├── programa_teste.c-     # Programa de teste
│   └── ...
├── demo.c                    # Demonstração do sistema
├── Makefile                  # Compilação
└── README.md                 # Este arquivo
```

## Compilação e Execução

### Pré-requisitos
```bash
sudo apt-get install flex bison gcc make
```

### Compilação
```bash
make clean      # Limpa arquivos anteriores
make           # Compila o sistema
```

### Demonstração
```bash
make demo      # Compila demonstração
./demo         # Executa demonstração
```

### Teste
```bash
make test      # Testa o compilador
```

## Exemplo de Uso

### Programa C-
```c
int global_var;
float array_test[10];

int main() {
    int local_var;
    float result;
    
    local_var = 42;
    result = 3.14;
    
    array_test[0] = result;
    
    if (local_var > 0) {
        result = local_var + 10;
    }
    
    return 0;
}
```

### Tabela de Símbolos Gerada
```
Nome            Tipo       DataType   Escopo Linha  Endereço 
================================================================
global_var      var        int        0      1      0         
array_test      var        float      0      2      1          [array]
main            func       int        0      4      2         
local_var       var        int        1      5      0         
result          var        float      1      6      1         
```

### Código Intermediário Gerado
```
  1: local_var = 42
  2: result = 3.14
  3: array_test[0] = result
  4: t0 = local_var > 0
  5: if t0 goto L0
  6: goto L1
  7: L0:
  8: t1 = local_var + 10
  9: result = t1
 10: L1:
 11: return 0
```

## Funcionalidades Implementadas

### ✅ Tabela de Símbolos
- [x] Hash table com 211 posições
- [x] Gerenciamento de escopo hierárquico
- [x] Inserção e busca de símbolos
- [x] Armazenamento de tipos e endereços
- [x] Suporte a arrays multidimensionais
- [x] Parâmetros de funções
- [x] Atributos de structs

### ✅ Análise Semântica
- [x] Verificação de declaração antes do uso
- [x] Verificação de tipos em operações
- [x] Verificação de atribuições
- [x] Detecção de redeclaração
- [x] Verificação de acesso a arrays
- [x] Verificação de chamadas de função
- [x] Relatório de erros semânticos

### ✅ Geração de Código Intermediário
- [x] Código de três endereços
- [x] Operações aritméticas
- [x] Atribuições
- [x] Acesso a arrays
- [x] Chamadas de função
- [x] Instruções de salto
- [x] Geração de temporários
- [x] Geração de labels
- [x] Salvamento em arquivo

### ✅ Utilitários
- [x] Validação de identificadores
- [x] Conversão de tipos
- [x] Manipulação segura de strings
- [x] Sistema de logging
- [x] Pilha de strings

## Limitações e Melhorias Futuras

### Limitações Atuais
- Análise semântica de funções não está completa
- Não há otimização de código
- Não há verificação de inicialização de variáveis
- Não há suporte completo a structs

### Melhorias Futuras
- Implementar análise semântica completa de funções
- Adicionar otimizações de código
- Implementar verificação de inicialização
- Adicionar suporte completo a structs
- Implementar geração de código objeto
- Adicionar mais tipos de dados

## Conclusão

Este sistema implementa com sucesso os requisitos especificados:

1. **Tabela de Símbolos com Hash Table**: ✅ Implementada com 211 posições
2. **Análise Semântica**: ✅ Verificação de tipos, escopo e declarações
3. **Geração de Código de Três Endereços**: ✅ Código intermediário completo
4. **Tratamento de Erros**: ✅ Relatórios detalhados de erros semânticos

O sistema pode ser facilmente estendido para incluir mais funcionalidades e otimizações conforme necessário.

# Compilador C-Minus

Este projeto implementa um compilador para a linguagem C-Minus, incluindo analisador léxico (Flex) e analisador sintático (Bison).

## Sobre C-Minus

C-Minus é uma linguagem de programação simplificada baseada em C, comumente utilizada em cursos de compiladores para fins educacionais. A linguagem suporta:
- Tipos básicos: `int` e `float`
- Estruturas de controle: `if`, `else`, `while`
- Funções e recursão
- Arrays
- Operadores aritméticos e relacionais
- Comentários multi-linha

## Estrutura do Projeto

```
compiler_c-/
├── c-minus/
│   ├── lexer/
│   │   └── lexer.l              # Definições do analisador léxico (Flex)
│   └── parser/
│       └── parser.y             # Definições do analisador sintático (Bison)
├── tests/
│   └── parser/
│       └── teste.txt            # Arquivos de teste para o parser
├── c-minus-lexer/               # Analisador léxico standalone
│   ├── c-minus-lexer.l         
│   └── tests/                   # Testes do lexer
├── scriptCompileAndRun.sh       # Script para compilar e executar apenas o lexer
├── ScriptRunParser.sh           # Script para compilar e executar o parser completo
└── README.md
```

## Dependências

Para executar este projeto, você precisa ter instalado:

- **Flex**: Ferramenta para gerar analisadores léxicos
- **Bison**: Ferramenta para gerar analisadores sintáticos
- **GCC**: Compilador C

### Instalação das Dependências (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install flex bison gcc
```

## Como Compilar e Executar

### 1. Analisador Léxico (Lexer apenas)

Para testar apenas o analisador léxico:

```bash
# Dar permissão de execução
chmod +x scriptRunLexer.sh

# Executar o lexer
./scriptRunLexer.sh c-minus-lexer teste.txt
```

Este comando irá:
- Navegar até o diretório `c-minus-lexer`
- Gerar o arquivo `lex.yy.c` usando `flex`
- Compilar para criar o executável
- Executar o analisador léxico com o arquivo de teste

### 2. Compilador Completo (Lexer + Parser)

Para compilar e executar o analisador sintático completo:

```bash
# Dar permissão de execução
chmod +x ScriptRunParser.sh

# Executar o parser completo
./ScriptRunParser.sh teste.txt
```

O script `ScriptRunParser.sh` automatiza o processo completo:

1. **Geração do Parser**: Executa `bison` no arquivo `c-minus/parser/parser.y` para gerar:
   - `parser.tab.c` (código do parser)
   - `parser.tab.h` (definições de tokens)

2. **Geração do Lexer**: Executa `flex` no arquivo `c-minus/lexer/lexer.l` para gerar:
   - `scanner.yy.c` (código do lexer integrado)

3. **Compilação**: Usa `gcc` para compilar ambos os arquivos, criando o executável `c-` em `tests/parser/`

4. **Execução**: Roda o compilador com o arquivo de teste especificado

5. **Debug**: Salva o log detalhado em `tests/parser/log.txt`

### Arquivos de Teste

O script procura arquivos de teste em duas localizações:
1. No diretório raiz do projeto
2. Na pasta `tests/parser/`

Exemplo de arquivo de teste (`teste.txt`):
```c
/* Programa exemplo em C-Minus */
int fatorial(int n) {
    if (n <= 1)
        return 1;
    else
        return n * fatorial(n - 1);
}

int main(void) {
    int numero;
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
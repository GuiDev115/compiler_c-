# Agente Semântico C- - Guia de Uso

## Visão Geral

O **Agente Semântico** é uma ferramenta interativa que permite navegar e analisar os arquivos da pasta semântica do compilador C-. Ele oferece uma interface amigável para explorar o código semântico e executar análises nos arquivos de teste.

## Funcionalidades Principais

### 1. **Escaneamento Automático**
- Escaneia automaticamente a pasta `c-minus/semantic` 
- Identifica arquivos `.c` e `.h` do sistema semântico
- Escaneia a pasta `tests/semantic` para arquivos de teste `.txt`
- Calcula tamanhos de arquivos e estatísticas

### 2. **Interface Interativa**
Menu principal com as seguintes opções:
- **1. 📁 Escanear pasta semântica** - Lista arquivos do sistema semântico
- **2. 🧪 Escanear pasta de testes** - Lista arquivos de teste
- **3. 📖 Ler arquivo específico** - Exibe conteúdo de qualquer arquivo
- **4. 🔬 Analisar arquivo de teste** - Executa análise semântica simulada
- **5. 🚀 Executar análise completa** - Analisa todos os arquivos de teste
- **6. 📊 Exibir estatísticas** - Mostra estatísticas do projeto
- **7. 🔄 Atualizar escaneamento** - Reescaneia as pastas
- **0. 🚪 Sair** - Fecha o agente

### 3. **Análise Semântica Simulada**
O agente reconhece diferentes tipos de programas C- e simula análises específicas:

- **Programas Básicos**: Analisa variáveis simples e função main
- **Programas com Arrays**: Verifica declarações e acessos a arrays
- **Programas com Funções**: Valida declarações, parâmetros e tipos de retorno
- **Programas com Structs**: Verifica estruturas e acesso a membros
- **Programas com Erros**: Identifica problemas semânticos comuns
- **Programas Complexos**: Análise completa de múltiplas estruturas

## Como Usar o Makefile

### Comandos Básicos

```bash
# Compilar tudo
make all

# Executar o agente semântico interativo
make run-agent

# Executar análise automática de todos os testes
make test-semantic

# Listar arquivos das pastas semânticas
make list-semantic

# Verificar estrutura do projeto
make check-structure

# Mostrar conteúdo dos arquivos de teste
make show-tests

# Ajuda com todos os comandos
make help
```

### Fluxo de Trabalho Recomendado

1. **Verificar dependências**: `make check-deps`
2. **Verificar estrutura**: `make check-structure` 
3. **Compilar**: `make all`
4. **Executar agente**: `make run-agent`
5. **Testar sistema**: `make test-semantic`

## Estrutura de Arquivos

### Pasta Semântica (`c-minus/semantic/`)
- `symbol_table.c/.h` - Tabela de símbolos com hash table
- `semantic.c/.h` - Análise semântica de tipos e declarações
- `code_generator.c/.h` - Gerador de código intermediário
- `utils.c/.h` - Utilitários auxiliares

### Pasta de Testes (`tests/semantic/`)
- `programa_basico.txt` - Programa simples com variáveis
- `programa_arrays.txt` - Programa com arrays unidimensionais e bidimensionais
- `programa_funcoes.txt` - Programa com múltiplas funções
- `programa_structs.txt` - Programa com estruturas de dados
- `programa_com_erros.txt` - Programa com erros semânticos intencionais
- `programa_complexo.txt` - Programa completo combinando todos os recursos

## Características da Análise Semântica

### Verificações Implementadas
- ✅ Declaração de variáveis antes do uso
- ✅ Compatibilidade de tipos em operações
- ✅ Verificação de parâmetros em chamadas de função
- ✅ Verificação de tipos de retorno
- ✅ Acesso a arrays dentro dos limites
- ✅ Verificação de membros de structs
- ✅ Gerenciamento de escopo hierárquico

### Tipos de Dados Suportados
- `int` - Números inteiros
- `float` - Números de ponto flutuante
- `char` - Caracteres
- `void` - Tipo vazio (para funções)
- `struct` - Estruturas de dados
- Arrays multidimensionais de qualquer tipo base

### Geração de Código
- Código intermediário de três endereços
- Otimizações básicas
- Gerenciamento de temporários
- Labels para controle de fluxo

## Exemplos de Uso

### Executar Análise Completa Automática
```bash
make test-semantic
```

### Usar Interface Interativa
```bash
make run-agent
# Escolher opção 5 para análise completa
# Ou opção 4 para analisar arquivo específico
```

### Verificar Conteúdo dos Testes
```bash
make show-tests
```

### Listar Arquivos Disponíveis
```bash
make list-semantic
```

## Estatísticas do Projeto

O agente fornece estatísticas úteis:
- Número de arquivos semânticos
- Número de arquivos de teste
- Tamanho total dos arquivos
- Distribuição por tipo de arquivo

## Mensagens de Saída

O agente usa emojis e formatação para facilitar a leitura:
- 🔍 **Análise em andamento**
- ✅ **Operação bem-sucedida**
- ❌ **Erro detectado**
- 📁 **Arquivos do sistema**
- 🧪 **Arquivos de teste**
- 📊 **Estatísticas**
- 🏗️ **Geração de código**

## Resolução de Problemas

### Erro: Arquivos não encontrados
```bash
make check-structure
```

### Erro de compilação
```bash
make clean
make all
```

### Dependências não instaladas
```bash
make check-deps
make install-deps  # Ubuntu/Debian
```

## Personalização

Para adicionar novos tipos de análise:
1. Adicione novos arquivos `.txt` em `tests/semantic/`
2. O agente detectará automaticamente o tipo baseado no nome
3. Adicione lógica específica na função `analyze_test_file()` se necessário

## Contribuições

O código está organizado de forma modular:
- Interface de usuário no arquivo `agente_semantico.c`
- Lógica semântica nos módulos `c-minus/semantic/`
- Testes organizados em `tests/semantic/`

---

**Desenvolvido por**: Guilherme Fabricio Brito da Rosa, Harisson de Carvalho Alvarenga, Raul Soares de Carvalho

**Versão**: 1.0 - Sistema de Análise Semântica C-

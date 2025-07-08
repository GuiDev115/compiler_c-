# Como Executar o Compilador C- em Qualquer Máquina

## 📋 Instruções de Portabilidade

### 1. Estrutura Necessária

Certifique-se de que você tem a seguinte estrutura de diretórios:

```
compiler_c-/                    # Pasta raiz do projeto
├── c-minus/
│   ├── lexer/
│   │   ├── lexer.l
│   │   └── ...
│   ├── parser/
│   │   ├── parser.y
│   │   └── ...
│   └── semantic/               # OBRIGATÓRIO
│       ├── semantic.c
│       ├── semantic.h
│       ├── symbol_table.c
│       ├── symbol_table.h
│       ├── code_generator.c
│       ├── code_generator.h
│       ├── utils.c
│       └── utils.h
├── tests/
│   └── semantic/               # OBRIGATÓRIO
│       ├── programa_basico.txt
│       ├── programa_arrays.txt
│       ├── programa_funcoes.txt
│       └── ...
├── agente_semantico.c
├── Makefile
└── README.md
```

### 2. Compilação e Execução

#### Opção 1: Execução Automática (Recomendada)
```bash
# 1. Navegue até a pasta raiz do projeto
cd caminho/para/compiler_c-

# 2. Compile o agente semântico
gcc -o agente_semantico agente_semantico.c c-minus/semantic/*.c -I.

# 3. Execute (o programa detectará automaticamente o diretório)
./agente_semantico
```

#### Opção 2: Usando Makefile
```bash
# Se houver um Makefile configurado
make agente-semantico
./agente_semantico
```

### 3. Troubleshooting

#### Problema: "Estrutura do projeto não encontrada"
**Solução:**
1. Certifique-se de estar na pasta raiz `compiler_c-`
2. Verifique se as pastas `c-minus/semantic/` e `tests/semantic/` existem
3. Use a opção manual quando solicitado pelo programa

#### Problema: "Diretório semântico não encontrado"
**Solução:**
```bash
# Verifique se os diretórios existem
ls -la c-minus/semantic/
ls -la tests/semantic/

# Se não existirem, crie-os
mkdir -p c-minus/semantic
mkdir -p tests/semantic
```

#### Problema: Erros de compilação
**Solução:**
```bash
# Instale as dependências necessárias (Ubuntu/Debian)
sudo apt update
sudo apt install build-essential flex bison

# Ou no CentOS/RHEL
sudo yum install gcc flex bison

# Ou no macOS
brew install gcc flex bison
```

### 4. Execução em Diferentes Sistemas

#### Linux/Ubuntu:
```bash
cd compiler_c-
gcc -o agente_semantico agente_semantico.c c-minus/semantic/*.c -I.
./agente_semantico
```

#### Windows (WSL/MinGW):
```bash
cd compiler_c-
gcc.exe -o agente_semantico.exe agente_semantico.c c-minus/semantic/*.c -I.
./agente_semantico.exe
```

#### macOS:
```bash
cd compiler_c-
clang -o agente_semantico agente_semantico.c c-minus/semantic/*.c -I.
./agente_semantico
```

### 5. Configuração Personalizada

Se você precisar especificar um caminho diferente:

1. Execute o programa
2. Quando aparecer "Estrutura do projeto não encontrada"
3. Escolha 's' para especificar manualmente
4. Digite o caminho completo para a pasta `compiler_c-`

Exemplo:
```
🔄 Deseja especificar manualmente o caminho? (s/n): s
📝 Digite o caminho completo para a pasta compiler_c-: /home/usuario/projetos/compiler_c-
```

### 6. Verificação de Funcionamento

Após a execução bem-sucedida, você deve ver:
```
🤖 Agente Semântico Inicializado
📁 Pasta base: /caminho/para/compiler_c-
✅ Estrutura do projeto verificada com sucesso!
🔍 Escaneando pasta semântica: /caminho/para/compiler_c-/c-minus/semantic
═══════════════════════════════════════════════════════════════
📄 semantic.c (X.XX KB)
📄 semantic.h (X.XX KB)
...
```

### 7. Recursos do Agente Semântico

Uma vez executando, você terá acesso a:

- **📁 Escaneamento automático** de arquivos
- **🧪 Análise de testes** individuais
- **📖 Visualização** de conteúdo de arquivos
- **🔬 Análise semântica** completa
- **🚀 Execução em lote** de todos os testes
- **📊 Estatísticas** do projeto

### 8. Exemplos de Uso

#### Análise de um arquivo específico:
1. Execute `./agente_semantico`
2. Escolha opção `4` (Analisar arquivo de teste)
3. Selecione o arquivo desejado
4. Veja a análise completa com tabela de símbolos e código intermediário

#### Análise completa do projeto:
1. Execute `./agente_semantico`
2. Escolha opção `5` (Executar análise completa)
3. Aguarde a análise de todos os arquivos de teste

### 9. Arquivos Gerados

O programa gera automaticamente:
- `codigo_3enderecos_*.ir` - Arquivos com código intermediário
- Tabelas de símbolos exibidas no terminal
- Relatórios de erros (quando aplicável)

---

## 🔧 Para Desenvolvedores

### Modificação do Caminho Base

Se você quiser hardcodar um caminho específico, edite o arquivo `agente_semantico.c` na função `main()`:

```c
// Substitua a detecção automática por:
char base_path[] = "/seu/caminho/personalizado/compiler_c-";
```

### Compilação com Debug

```bash
gcc -g -DDEBUG -o agente_semantico agente_semantico.c c-minus/semantic/*.c -I.
```

### Adição de Novos Testes

1. Crie arquivos `.txt` na pasta `tests/semantic/`
2. Execute o agente e use a opção `7` (Atualizar escaneamento)
3. Os novos arquivos aparecerão automaticamente

---

**Nota:** Este sistema foi projetado para ser completamente portável. Contanto que você mantenha a estrutura de diretórios correta, funcionará em qualquer sistema operacional com GCC instalado.

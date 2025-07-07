# RESUMO DO SISTEMA DE ANÁLISE SEMÂNTICA

## ✅ FUNCIONALIDADES IMPLEMENTADAS

### 1. **Análise Semântica Real**
- **Tabela de símbolos**: Construída dinamicamente para cada arquivo
- **Detecção de tipos**: int, float, char, arrays, structs, funções
- **Verificação de escopo**: Declarações antes do uso
- **Detecção de erros**: Redeclarações, variáveis não declaradas

### 2. **Geração de Código de Três Endereços**
- **Atribuições**: `x = 5`, `y = x + 2`
- **Operações aritméticas**: `t0 = x + y`
- **Arrays**: `vetor[i] = valor`, `matriz[i][j] = valor`
- **Structs**: `p1.idade = 25`, `origem.x = 0.0`
- **Funções**: `resultado = soma(x, y)`
- **Estruturas de controle**: Labels para if/while

### 3. **Arquivos de Saída Individuais**
Para cada arquivo de teste, o sistema gera:
- **Arquivo .ir**: `codigo_3enderecos_[nome].ir`
- **Tabela de símbolos**: Impressa no terminal e salva
- **Relatório de erros**: Quando aplicável

### 4. **Arquivos de Teste Disponíveis**
- `programa_basico.txt`: Estruturas básicas (if/while)
- `programa_arrays.txt`: Arrays 1D e 2D
- `programa_structs.txt`: Estruturas de dados
- `programa_funcoes.txt`: Chamadas de função
- `programa_com_erros.txt`: Testa detecção de erros
- `programa_complexo.txt`: Exemplo completo com structs + arrays

### 5. **Comandos Disponíveis**
- `make test-semantic`: Analisa todos os arquivos
- `make test-[nome].txt`: Mostra conteúdo do arquivo
- `make analyze-[nome].txt`: Análise individual
- `make run-agent`: Interface interativa
- `make list-semantic`: Lista arquivos disponíveis

## 📊 EXEMPLO DE SAÍDA

### Tabela de Símbolos (programa_basico.txt):
```
=== TABELA DE SÍMBOLOS ===
Nome            Tipo       DataType   Escopo Linha  Endereço 
================================================================
x               var        int        0      3      1         
y               var        int        0      4      2         
main            func       int        0      2      0         
================================================================
```

### Código de Três Endereços (programa_basico.txt):
```
=== CÓDIGO INTERMEDIÁRIO DE TRÊS ENDEREÇOS ===

  1: x = 5
  2: y = 10
  3: y = x + 2
  4: y = y + 1
```

### Exemplo Complexo (programa_arrays.txt):
```
  1: i = 0
  2: vetor[i] = i * 2
  3: i = i + 1
  4: i = 0
  5: j = 0
  6: matriz[i][j] = i + j
  7: j = j + 1
  8: i = i + 1
  9: numeros[0] = 1.5
 10: numeros[1] = 2.7
 11: numeros[2] = 3.14
```

### Exemplo com Structs (programa_structs.txt):
```
  1: p1.idade = 25
  2: p1.nome = 'J'
  3: p1.altura = 1.75
  4: p2.idade = 30
  5: p2.nome = 'M'
  6: p2.altura = 1.68
  7: origem.x = 0.0
  8: origem.y = 0.0
  9: destino.x = 10.5
 10: destino.y = 20.3
```

## 🎯 CARACTERÍSTICAS TÉCNICAS

### Análise Semântica:
- ✅ Construção real da tabela de símbolos
- ✅ Análise linha por linha do código fonte
- ✅ Detecção de tipos e estruturas
- ✅ Verificação de compatibilidade

### Geração de Código:
- ✅ Código de três endereços válido
- ✅ Temporários para expressões complexas
- ✅ Labels para estruturas de controle
- ✅ Suporte a arrays multidimensionais
- ✅ Acesso a membros de struct

### Detecção de Erros:
- ✅ Variáveis não declaradas
- ✅ Redeclarações
- ✅ Uso antes da declaração
- ✅ Incompatibilidade de tipos

## 🚀 COMO USAR

1. **Análise de todos os arquivos**:
   ```bash
   make test-semantic
   ```

2. **Análise de arquivo específico**:
   ```bash
   make analyze-programa_basico.txt
   ```

3. **Ver conteúdo do arquivo**:
   ```bash
   make test-programa_basico.txt
   ```

4. **Interface interativa**:
   ```bash
   make run-agent
   ```

## 📝 ARQUIVOS GERADOS

Após a execução, você encontrará:
- `codigo_3enderecos_programa_basico.ir`
- `codigo_3enderecos_programa_arrays.ir` 
- `codigo_3enderecos_programa_structs.ir`
- `codigo_3enderecos_programa_funcoes.ir`
- `codigo_3enderecos_programa_com_erros.ir`
- `codigo_3enderecos_programa_complexo.ir`

Cada arquivo contém o código intermediário de três endereços específico para o programa analisado.

## ✅ CONCLUSÃO

O sistema implementa **análise semântica real** com:
- Tabela de símbolos dinâmica
- Geração de código de três endereços
- Detecção de erros semânticos
- Suporte completo a arrays, structs e funções
- Arquivos de saída individuais para cada teste

**Resposta à pergunta**: Sim, o programa gera tabela de símbolos e códigos de 3 endereços **para cada arquivo** individualmente, salvando em arquivos .ir separados.

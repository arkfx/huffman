# 🗜️ Algoritmo de Huffman em C

[![C](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Build](https://img.shields.io/badge/build-Make-green.svg)](https://www.gnu.org/software/make/)

## 📋 Descrição

Este projeto implementa o **algoritmo de codificação de Huffman** em linguagem C, uma técnica de compressão de dados sem perdas amplamente utilizada. O algoritmo atribui códigos de tamanho variável aos caracteres baseado em suas frequências de ocorrência, otimizando o espaço de armazenamento.

---

## ⚙️ Funcionalidades

| Módulo | Descrição |
|--------|-----------|
| 📊 **Análise de Frequência** | Calcula frequência de cada caractere na entrada |
| 🌳 **Construção da Árvore** | Cria árvore binária (min-heap) baseada nas frequências |
| 🔧 **Geração de Códigos** | Gera códigos Huffman através de travessia da árvore |
| 📦 **Codificação** | Converte string em sequência de bits otimizada |
| 🔓 **Decodificação** | Reconstrói string original a partir dos dados comprimidos |
| 💾 **Operações de Arquivo** | Gerencia persistência em formato `.huff` |
| 🧪 **Suite de Testes** | Verificação abrangente das funcionalidades |

---

## 📁 Estrutura do Projeto

```
huffman/
├── 📁 bin/                # Executáveis e arquivos compilados
├── 📁 include/            # Headers (.h)
│   ├── huffman.h
│   ├── huffman_codes.h
│   ├── huffman_common.h
│   ├── huffman_heap.h
│   ├── huffman_io.h
│   └── huffman_tree.h
├── 📁 src/                # Código fonte (.c)
│   ├── decoder.c
│   ├── encoder.c
│   ├── huffman_codes.c
│   ├── huffman_heap.c
│   ├── huffman_io.c
│   └── huffman_tree.c
├── 📁 tests/              # Arquivos de teste
│   └── test_huffman.c
├── 📋 Makefile            # Regras de compilação
└── 📖 README.md           # Documentação
```

### 📂 Descrição dos Diretórios
- **`bin/`** - Contém arquivos objeto (`.o`) e executáveis gerados
- **`include/`** - Headers com interfaces dos módulos
- **`src/`** - Implementação das funcionalidades principais
- **`tests/`** - Suite de testes unitários

---

## 🚀 Início Rápido

### 🧪 Teste Básico
Para verificar rapidamente o funcionamento do projeto:

```powershell
make test
```

Este comando executa automaticamente:
1. 🧹 **Limpeza** dos artefatos anteriores
2. 🔨 **Compilação** do projeto completo  
3. ⚡ **Teste integrado** com exemplo "hello world"

---

## 🛠️ Compilação

### 📋 Pré-requisitos
- Compilador C (GCC recomendado)
- Make (para automação)
- Sistema Windows com PowerShell

### 🔨 Comandos de Compilação

```powershell
# Compilação completa
make

# Limpeza total (build + output)
make clean

# Limpeza apenas do build
make clean_build

# Limpeza apenas dos arquivos .huff
make clean_output
```

---

## 💻 Como Usar

### 📦 Codificador

Comprime uma string e salva em arquivo `.huff`:

```powershell
.\bin\encoder.exe "sua string aqui"
```

**Exemplo prático:**
```powershell
.\bin\encoder.exe "hello world"
```

**Saída esperada:**
- 📊 Códigos Huffman por caractere
- 🔢 String codificada (bits)
- 💾 Arquivo `saida.huff` gerado
- 📈 Estatísticas de compressão

### 🔓 Decodificador

Reconstrói a string original do arquivo `.huff`:

```powershell
.\bin\decoder.exe <arquivo.huff>
```

**Exemplo:**
```powershell
.\bin\decoder.exe saida.huff
```

**Resultado:**
- 🔄 String original decodificada
- ✅ Verificação de integridade

---

## 🧪 Testes Avançados

### 🔬 Testes Unitários Detalhados

Para executar a suite completa de testes:

```powershell
# Compilação dos testes
gcc -Wall -Wextra -g -Iinclude -o tests\run_all_tests.exe tests\test_huffman.c src\huffman_heap.c src\huffman_tree.c src\huffman_codes.c src\huffman_io.c

# Execução
.\tests\run_all_tests.exe
```

**Ou usando objetos pré-compilados:**
```powershell
gcc -Wall -Wextra -g -Iinclude -o tests\run_all_tests.exe tests\test_huffman.c bin\huffman_heap.o bin\huffman_tree.o bin\huffman_codes.o bin\huffman_io.o
```

### 🎯 Casos de Teste Inclusos
- ✅ Strings vazias
- ✅ Caractere único  
- ✅ Múltiplos caracteres
- ✅ Casos extremos
- ✅ Integridade de arquivo

---

## 🛡️ Exemplo de Uso Completo

```powershell
# 1. Compilar o projeto
make

# 2. Codificar uma mensagem
.\bin\encoder.exe "Este é um exemplo de compressão Huffman!"

# 3. Decodificar o arquivo gerado
.\bin\decoder.exe saida.huff

# 4. Verificar resultados
# A saída deve mostrar a mensagem original decodificada
```

---

## 🔧 Tecnologias

| Tecnologia | Versão | Uso |
|------------|--------|-----|
| **C** | C99+ | Linguagem principal |
| **GCC** | Latest | Compilação |
| **Make** | 4.0+ | Automação de build |
| **PowerShell** | 5.1+ | Scripts Windows |

---

<div align="center">

**⭐ Se este projeto foi útil, considere dar uma estrela!**

</div>
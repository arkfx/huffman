# Algoritmo de Huffman em C

## Descrição

Este projeto é uma implementação do algoritmo de codificação de Huffman em linguagem C. A codificação de Huffman é um método de compressão de dados sem perdas que atribui códigos de tamanho variável aos caracteres de entrada com base em suas frequências. Caracteres mais frequentes recebem códigos menores, enquanto caracteres menos frequentes recebem códigos maiores, resultando em uma representação de dados mais compacta.

O projeto consiste em um codificador, que comprime uma string de entrada e a salva em um arquivo `.huff`, e um decodificador, que lê um arquivo `.huff` e reconstrói a string original.

## Funcionalidades

- **Cálculo de Frequência:** Calcula a frequência de cada caractere na string de entrada.
- **Construção da Árvore de Huffman:** Cria uma árvore binária (min-heap) com base nas frequências dos caracteres.
- **Geração de Códigos:** Gera os códigos de Huffman para cada caractere atravessando a árvore.
- **Codificação:** Converte a string de entrada em uma sequência de bits usando os códigos de Huffman gerados.
- **Decodificação:** Reconstrói a string original a partir da sequência de bits codificada e da árvore de Huffman.
- **Operações de Arquivo:**
    - Salva a árvore de Huffman e os dados codificados em um arquivo (`.huff`).
    - Lê a árvore de Huffman e os dados codificados de um arquivo (`.huff`) para decodificação.
- **Testes:** Inclui um conjunto de testes para verificar a corretude das funcionalidades de codificação, decodificação e operações de arquivo.

## Estrutura do projeto
```
huffman/
├── bin/                # Contém os arquivos e executáveis compilados
├── include/            # Contém os headers (.h)
│   ├── huffman.h
│   ├── huffman_codes.h
│   ├── huffman_common.h
│   ├── huffman_heap.h
│   ├── huffman_io.h
│   └── huffman_tree.h
├── src/                # Contém os arquivos de código fonte (.c)
│   ├── decoder.c
│   ├── encoder.c
│   ├── huffman_codes.c
│   ├── huffman_heap.c
│   ├── huffman_io.c
│   └── huffman_tree.c
├── tests/              # Contém os arquivos de teste
│   └── test_huffman.c
├── Makefile            # Define as regras para compilar o projeto
└── README.md           # Esse arquivo
```

- `bin/`: Armazena os arquivos objeto (`.o`) e os executáveis (`encoder`, `decoder`) gerados durante a compilação.
- `include/`: Contém os arquivos de cabeçalho (`.h`) que definem as interfaces dos módulos do projeto.
- `src/`: Contém os arquivos de código fonte (`.c`) com a implementação das funcionalidades.
- `tests/`: Contém os arquivos de teste para garantir a correta execução do algoritmo de Huffman

## Como Testar o Projeto

Para verificar rapidamente a funcionalidade principal do projeto, você pode usar o comando `make test`.
Navegue até o diretório raiz do projeto no terminal e execute:

```bash
make test
```

Este comando executará as seguintes etapas em sequência:

1.  **Limpeza Completa:** Remove todos os artefatos de compilação anteriores (conteúdo do diretório `bin/`) e quaisquer arquivos de saída de testes anteriores (como `saida.huff`).
2.  **Compilação do Projeto:** Compila todos os arquivos fonte necessários e cria os executáveis `encoder` e `decoder`.
3.  **Execução do Teste de Exemplo:**
    *   Executa `./bin/encoder "hello world"`, que codifica a string "hello world", exibe os códigos Huffman, os dados codificados, as estatísticas de compressão e salva a saída em `saida.huff`.
    *   Executa `./bin/decoder saida.huff`, que lê o arquivo `saida.huff`, decodifica os dados e exibe a string original.

Após a execução, você poderá verificar visualmente na saída do terminal se a string decodificada ("hello world") corresponde à original impressa pelo decodificador. Este teste integrado ao `Makefile` serve como uma verificação básica de ponta a ponta.

### Executando os Testes Unitários Detalhados (Opcional)

Para usuários que desejam realizar testes unitarios de maneira mais detalhada, o arquivo `tests/test_huffman.c` contém uma suíte de testes unitários mais abrangente. Para compilar e executar estes testes:

1.  **Navegue até o diretório raiz do projeto.**
2.  **Compile os testes junto com os módulos necessários.** Você pode fazer isso de algumas maneiras:

    *   Compilando todos os fontes necessários diretamente:
        ```bash
        gcc -Wall -Wextra -g -Iinclude -o tests/run_all_tests tests/test_huffman.c src/huffman_heap.c src/huffman_tree.c src/huffman_codes.c src/huffman_io.c
        ```
    *   Alternativamente, se você já compilou o projeto com `make` (o que cria os arquivos objeto `.o` no diretório `bin/`), você pode linkar com esses objetos:
        ```bash
        gcc -Wall -Wextra -g -Iinclude -o tests/run_all_tests tests/test_huffman.c bin/huffman_heap.o bin/huffman_tree.o bin/huffman_codes.o bin/huffman_io.o
        ```
        (No Windows, o executável de saída seria `tests\run_all_tests.exe`)

3.  **Execute o programa de teste:**
    ```bash
    ./tests/run_all_tests
    ```
    (No Windows: `tests\run_all_tests.exe`)

Isso executará todos os casos de teste definidos em `tests/test_huffman.c` (incluindo testes para strings vazias, strings de caractere único, etc.) e reportará "ALL TESTS PASSED" ou "SOME TESTS FAILED" ao final.

## Como Compilar

Este projeto utiliza um `Makefile` para facilitar a compilação. Certifique-se de ter um compilador C (como GCC) instalado e o `make` disponível no seu ambiente.

Para compilar o projeto, navegue até o diretório raiz do projeto no terminal e execute os seguintes comandos:

1.  **Compilar os executáveis (codificador e decodificador):**
    ```bash
    make
    ```
    Este comando primeiro limpará quaisquer artefatos de compilação anteriores (o conteúdo do diretório `bin/`) e depois compilará os fontes, criando os executáveis `encoder` e `decoder` no diretório `bin/`. Os arquivos `.huff` existentes *não* serão apagados por este comando.

2.  **(OPCIONAL) Limpar arquivos compilados e/ou de saída:**
    *   Para remover todos os arquivos objeto, executáveis e arquivos `.huff` gerados:
        ```bash
        make clean
        ```
    *   Para remover apenas os artefatos de compilação (diretório `bin/`):
        ```bash
        make clean_build
        ```
    *   Para remover apenas os arquivos de saída `.huff`:
        ```bash
        make clean_output
        ```


## Como Executar

Após a compilação, os executáveis `encoder` e `decoder` estarão localizados no diretório `bin/`.

### Codificador (`encoder`)

O codificador pega uma string como entrada, a comprime e salva o resultado em um arquivo chamado `saida.huff`.

**Uso:**

```bash
./bin/encoder "sua string para codificar aqui"
```

**Exemplo:**

```bash
./bin/encoder "hello world"
```

Isso irá:
1.  Imprimir os códigos de Huffman gerados para cada caractere.
2.  Imprimir a string codificada (sequência de bits).
3.  Salvar a árvore de Huffman e os dados comprimidos em `saida.huff`.
4.  Imprimir estatísticas de compressão (tamanho original, tamanho comprimido, taxa de compressão).

### Decodificador (`decoder`)

O decodificador pega um arquivo `.huff` como entrada (gerado pelo `encoder`) e imprime a string original decodificada.

**Uso:**

```bash
./bin/decoder <arquivo_de_entrada.huff>
```

**Exemplo:**
Se você executou o exemplo do codificador acima, um arquivo `saida.huff` terá sido criado. Para decodificá-lo:

```bash
./bin/decoder saida.huff
```

Isso irá:
1.  Ler a árvore de Huffman e os dados comprimidos do arquivo `saida.huff`.
2.  Decodificar os dados.
3.  Imprimir a string original decodificada.

## Tecnologias Utilizadas

-   **Linguagem C:** O projeto é inteiramente desenvolvido em C.
-   **GCC:** Utilizado como compilador C (configurado no `Makefile`).
-   **Make:** Utilizado para automatizar o processo de compilação.

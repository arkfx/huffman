CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
SRCDIR = src
OBJDIR = bin
INCLUDEDIR = include

# Códigos fonte
SOURCES = $(SRCDIR)/huffman_heap.c $(SRCDIR)/huffman_tree.c $(SRCDIR)/huffman_codes.c $(SRCDIR)/huffman_io.c
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Executáveis
ENCODER = $(OBJDIR)/encoder
DECODER = $(OBJDIR)/decoder

# Regra padrão: builda os executáveis após limpar os artefatos de compilação
all: clean_build $(ENCODER) $(DECODER)

# Cria o diretório binário se não existir
$(OBJDIR):
	mkdir $(OBJDIR)

# Compila os arquivos objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build encoder
$(ENCODER): $(OBJECTS) $(SRCDIR)/encoder.c | $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ $(SRCDIR)/encoder.c $(OBJECTS)

# Build decoder
$(DECODER): $(OBJECTS) $(SRCDIR)/decoder.c | $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ $(SRCDIR)/decoder.c $(OBJECTS)

# Limpa os arquivos compilados
clean_build:
	-RD /S /Q $(OBJDIR)

# Limpa arquivos de saída (ex: arquivos .huff)
clean_output:
	-DEL /F *.huff

# Limpa tudo (artefatos de compilação e arquivos de saída)
clean: clean_build clean_output

# Cria um teste: limpa tudo, depois compila, então executa comandos de teste
test: clean all
	$(ENCODER) "hello world"
	$(DECODER) saida.huff


.PHONY: all clean clean_build clean_output test 
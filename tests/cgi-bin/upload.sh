#!/bin/bash

UPLOAD_DIR="../uploads"

if [ ! -d "$UPLOAD_DIR" ]; then
    mkdir -p "$UPLOAD_DIR"
fi

# Ler o cabeçalho da requisição
read CONTENT_TYPE
read CONTENT_LENGTH

MAX_SIZE=10000000  # Limite de 10MB

# Verificar se o conteúdo é maior que o tamanho permitido
if [ "$CONTENT_LENGTH" -gt "$MAX_SIZE" ]; then
  echo "Status: 413 Payload Too Large"
  echo "Content-type: text/html"
  echo ""
  echo "<html><body><h2>O arquivo enviado é muito grande.</h2></body></html>"
  exit 1
fi

# Lê a entrada inteira
BODY=$(cat)

# Extrair o boundary do cabeçalho Content-Type
BOUNDARY=$(echo "$CONTENT_TYPE" | sed 's/.*boundary=//')

# Encontrar o nome do arquivo
FILENAME=$(echo "$BODY" | grep -Po 'filename="\K[^"]+')

# Extrair o conteúdo do arquivo entre os boundaries
FILECONTENT=$(echo "$BODY" | sed -n "/$BOUNDARY/!d;/Content-Type/,\$p" | sed '1,/Content-Type:.*/d' | sed '$d')

# Salvar o conteúdo do arquivo no diretório de uploads
echo "$FILECONTENT" > "$UPLOAD_DIR/$FILENAME"

# Responder com uma mensagem HTML de sucesso
echo "Content-type: text/html"
echo ""
echo "<html><body><h2>Upload do arquivo $FILENAME realizado com sucesso!</h2></body></html>"

exit 0

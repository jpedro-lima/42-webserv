#!/usr/bin/env python3import os
import json

# Diretório onde os arquivos estão armazenados
UPLOAD_DIR = os.getenv('SAVE_INTO', '/tmp/uploads')

# Imprime o cabeçalho HTTP
print("Content-Type: application/json\n")

try:
    # Lista os arquivos no diretório
    files = os.listdir(UPLOAD_DIR)
    # Filtra apenas arquivos regulares
    files = [f for f in files if os.path.isfile(os.path.join(UPLOAD_DIR, f))]
    
    # Retorna a lista de arquivos como JSON
    print(json.dumps(files))

except Exception as e:
    print(json.dumps({"error": str(e)}))

#!/usr/bin/env python3

import os
import cgi
import cgitb
from urllib.parse import parse_qs, urlparse

# Habilita o modo de depuração
cgitb.enable()

# Diretório onde os arquivos estão armazenados
UPLOAD_DIR = os.getenv('SAVE_INTO', '/tmp/uploads')

# Pega o método HTTP usado na requisição
method = os.environ['REQUEST_METHOD']

# Processa a requisição DELETE
if method == 'DELETE':
    # Pega o arquivo a partir da query string
    query = os.environ['QUERY_STRING']
    params = parse_qs(query)
    filename = params.get('file', [None])[0]

    if filename:
        filepath = os.path.join(UPLOAD_DIR, filename)
        
        # Verifica se o arquivo existe
        if os.path.exists(filepath) and os.path.isfile(filepath):
            try:
                os.remove(filepath)
                print(f"O arquivo '{filename}' foi deletado com sucesso.")
            except Exception as e:
                print(f"Erro ao deletar o arquivo: {e}")
        else:
            print(f"Arquivo '{filename}' não encontrado.")
    else:
        print("Nenhum arquivo especificado para deletar.")
else:
    print("Método HTTP não suportado. Use DELETE para deletar arquivos.")

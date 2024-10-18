#!/usr/bin/env python3

import cgi
import os
import cgitb

# Habilita o modo de depuração
cgitb.enable()

# Diretório de upload definido pela variável de ambiente, ou um valor padrão
UPLOAD_DIR = os.getenv('SAVE_INTO', '/tmp/uploads')
CURRENT_DIR = os.getcwd()

# Cria o diretório de upload, caso não exista
if not os.path.exists(UPLOAD_DIR):
    os.makedirs(UPLOAD_DIR, exist_ok=True)

# Processa os dados do formulário
form = cgi.FieldStorage()

def render_response(title, message, filename=None):
    """Função para renderizar a resposta HTML"""
    return f"""
    <!DOCTYPE html>
    <html lang="pt-BR">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>{title}</title>
        <style>
            body {{
                font-family: Arial, sans-serif;
                background-color: #f4f4f4;
                display: flex;
                justify-content: center;
                align-items: center;
                height: 100vh;
                margin: 0;
            }}
            .container {{
                background-color: #fff;
                padding: 20px;
                border-radius: 8px;
                box-shadow: 0 0 15px rgba(0, 0, 0, 0.1);
                text-align: center;
                width: 400px;
            }}
            h1 {{
                color: #4CAF50;
                margin-bottom: 20px;
            }}
            p {{
                font-size: 16px;
                color: #333;
            }}
            .success {{
                font-weight: bold;
                color: #4CAF50;
            }}
            .file-info {{
                background-color: #e0f7fa;
                padding: 10px;
                border-radius: 5px;
                margin-top: 20px;
            }}
            .back-link {{
                display: inline-block;
                margin-top: 20px;
                padding: 10px 20px;
                background-color: #4CAF50;
                color: white;
                text-decoration: none;
                border-radius: 4px;
            }}
            .back-link:hover {{
                background-color: #45a049;
            }}
        </style>
    </head>
    <body>
        <div class="container">
            <h1>{title}</h1>
            <p class="success">{message}</p>
            <div class="file-info">
                {f"<p><strong>Nome do arquivo:</strong> {filename}</p>" if filename else ""}
                <p><strong>Local de armazenamento:</strong> {UPLOAD_DIR}</p>
                <p><strong>Diretório de trabalho atual:</strong> {CURRENT_DIR}</p>
            </div>
            <a href="/upload" class="back-link">Voltar para o upload</a>
        </div>
    </body>
    </html>
    """

# Verifica se o campo "file" está presente no formulário
if "file" in form:
    fileitem = form['file']

    # Verifica se o arquivo foi realmente enviado
    if fileitem.filename:
        filename = os.path.basename(fileitem.filename)
        filepath = os.path.join(UPLOAD_DIR, filename)

        try:
            # Escreve o arquivo de forma segura usando o gerenciador de contexto
            with open(filepath, 'wb') as f:
                f.write(fileitem.file.read())

            # Exibe a resposta de sucesso
            print(render_response(
                title="Upload bem-sucedido",
                message=f"O arquivo <strong>{filename}</strong> foi salvo com sucesso.",
                filename=filename
            ))

        except IOError as e:
            # Exibe a mensagem de erro em caso de falha ao salvar o arquivo
            print(render_response(
                title="Erro ao salvar o arquivo",
                message=f"Erro ao salvar o arquivo: {e}"
            ))

    else:
        # Exibe mensagem de erro caso nenhum arquivo tenha sido enviado
        print(render_response(
            title="Erro no upload",
            message="Nenhum arquivo foi enviado. Por favor, tente novamente."
        ))

else:
    # Exibe mensagem de erro caso o campo de upload não esteja presente
    print(render_response(
        title="Erro no upload",
        message="Nenhum campo de arquivo encontrado no formulário."
    ))

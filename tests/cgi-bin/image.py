import sys
import os

def save_file_from_stdin():
    # Obtém o nome do arquivo a partir do argumento da linha de comando

    path = os.getenv('SAVE_INTO', os.getcwd())
    file_name = os.getenv('filename', "normal")
    file_path = os.path.join(path, file_name)
    
    # Abre o arquivo para escrita no diretório de execução
    with open(file_path, 'wb') as f:
        # Lê os dados da entrada padrão e escreve no arquivo
        f.write(sys.stdin.buffer.read())

    print(f"Arquivo '{file_name}' salvo no diretório: {os.getcwd()}")

if __name__ == "__main__":
    save_file_from_stdin()

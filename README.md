# WebServ - Um Servidor HTTP em C++98

Este projeto faz parte do currículo da 42 e tem como objetivo implementar um servidor web compatível com HTTP/1.1, escrito em C++98. Ele é projetado para processar conexões simultâneas de clientes e gerenciar métodos HTTP básicos, como GET, POST, DELETE, PUT e HEAD.

Foi utilizado o [NGINX](https://nginx.org/) como base do arquivo .conf

## Funcionalidades

- **Manipulação de Requisições HTTP:** Suporte aos métodos mencionados acima, incluindo o envio e recebimento de cabeçalhos e corpo de mensagem.
- **Servidor Multicliente:** Capacidade de gerenciar várias conexões usando multiplexação de E/S com select().
- **Serviços CGI:** Suporte para execução de scripts dinâmicos por meio de Common Gateway Interface. Suporta as linguagens `Python` e `PHP`
- **Arquivos de Configuração Personalizáveis**: Ajuste de parâmetros como porta, diretórios raiz, tamanhos máximos de corpo e páginas de erro personalizadas.
- **Serviço de Arquivos Estáticos e Dinâmicos:** Habilidade de servir conteúdo estático de diretórios e processar scripts dinâmicos.

## Exemplo de arquivo .conf
```txt
server {
	listen		127.0.0.42:8000
	server_name	webserv

	location / {
		root ./tests/www
		index index.html
		allow_methods GET
	};

	location /form {
		root ./tests/www
		index form.html
		allow_methods GET POST
		
		location *.py {
			cgi_pass /tests/cgi-bin/form.py
		}
	};
	
	location /redirect {
		return 301 /form
	};
}
```

## Como Executar

Compile o projeto usando o comando:
```bash
$ make
```

Execute o servidor com o arquivo de configuração desejado:
```bash
$ ./webserv [arquivo_de_configuração.conf]
```

## HTTP: Introdução Básica

HTTP (Hypertext Transfer Protocol) é o protocolo fundamental da web. Ele segue o modelo de requisição-resposta, onde o cliente envia uma solicitação para o servidor, e este retorna uma resposta contendo o recurso ou status da operação.

#### Métodos HTTP Suportados:

    GET: Recupera recursos.
    POST: Envia dados ao servidor.
    PUT: Cria ou substitui recursos.
    DELETE: Remove recursos.
    HEAD: Obtém metadados de recursos sem retornar o conteúdo.

#### Recursos Aprimorados
Manuseio de Erros: Páginas de erro personalizadas para status como 404 (não encontrado).
    Suporte a Redirecionamentos: Configurável via arquivo de configuração.
    Autoindex: Lista diretórios quando um arquivo index não está disponível.

#### Referências

- [Documentação HTTP](https://www.rfc-editor.org/rfc/rfc9110.html)
- [RFC9110](https://www.rfc-editor.org/rfc/rfc9110.html) para detalhes sobre métodos HTTP.


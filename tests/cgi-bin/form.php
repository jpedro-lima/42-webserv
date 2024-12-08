<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    parse_str(file_get_contents("php://input"), $post_vars);
    $name = htmlspecialchars($post_vars['name'] ?? 'Nome não fornecido');
    $lastname = htmlspecialchars($post_vars['lastname'] ?? 'Sobrenome não fornecido');
    echo <<<HTML
<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Resultado do Formulário</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
            background: #f4f4f4;
        }
        .result {
            background-color: #fff;
            padding: 30px;
            border-radius: 10px;
            box-shadow: 0 5px 15px rgba(0, 0, 0, 0.2);
            text-align: center;
        }
        h1 {
            color: #333;
        }
        p {
            font-size: 1.2rem;
            color: #555;
        }
    </style>
</head>
<body>
    <div class="result">
        <h1>Olá, $name $lastname!</h1>
        <p>Seu cadastro foi realizado com sucesso.</p>
    </div>
</body>
</html>
HTML;
} else {
    echo "Método de requisição inválido.";
}
?>
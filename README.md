# Sistema de Relato de Catástrofes Naturais

## Objetivo
Aplicação em linguagem C para cadastro e consulta de relatos de catástrofes naturais ocorridas em um raio de até 10 km, com persistência dos dados em arquivo.

## Funcionalidades
- Cadastro de relatos com validação de dados
- Cálculo de distância por coordenadas (fórmula de Haversine)
- Consulta de relatos por raio de até 10 km
- Ordenação alfabética por nome
- Persistência em arquivo `.txt`


## Estrutura do Arquivo `relatos.txt`
Cada linha contém:
Nome;CPF;Telefone;Tipo;Descricao;Latitude;Longitude;Data

#Exemplo:

Maria Silva;12345678901;999999999;Enchente;Rua completamente alagada;-23.5505;-46.6333;01/06/2025

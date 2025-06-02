#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265359
#define RAIO_TERRA 6371 // Raio da Terra em km
#define MAX_RELATOS 1000

// Struct do relato
typedef struct {
    char nome[100];
    char cpf[15];
    char telefone[20];
    char tipo[50];
    char descricao[200];
    float latitude;
    float longitude;
    char data[11]; // formato dd/mm/aaaa
} Relato;

// Função para converter graus em radianos
double grausParaRadiano(double grau) {
    return grau * PI / 180.0;
}

// Função para calcular distância entre dois pontos
double calcularDistancia(double lat1, double lon1, double lat2, double lon2) {
    double dLat = grausParaRadiano(lat2 - lat1);
    double dLon = grausParaRadiano(lon2 - lon1);

    lat1 = grausParaRadiano(lat1);
    lat2 = grausParaRadiano(lat2);

    double a = sin(dLat / 2) * sin(dLat / 2) +
               sin(dLon / 2) * sin(dLon / 2) * cos(lat1) * cos(lat2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return RAIO_TERRA * c;
}

// Função para validar CPF (apenas verifica se tem 11 dígitos)
int validarCPF(char *cpf) {
    return strlen(cpf) == 11;
}

// Função para validar telefone (mínimo 8 dígitos)
int validarTelefone(char *telefone) {
    return strlen(telefone) >= 8;
}

// Função para validar coordenadas
int validarCoordenadas(float latitude, float longitude) {
    return (latitude >= -90 && latitude <= 90) && (longitude >= -180 && longitude <= 180);
}

// Função para cadastrar um relato
void cadastrarRelato(Relato *relatos, int *quantidade) {
    if (*quantidade >= MAX_RELATOS) {
        printf("Limite máximo de relatos atingido.\n");
        return;
    }

    Relato r;

    printf("Nome: ");
    getchar();
    fgets(r.nome, 100, stdin);
    r.nome[strcspn(r.nome, "\n")] = 0;

    do {
        printf("CPF (11 dígitos): ");
        scanf("%s", r.cpf);
        if (!validarCPF(r.cpf)) {
            printf("CPF inválido. Tente novamente.\n");
        }
    } while (!validarCPF(r.cpf));

    do {
        printf("Telefone: ");
        scanf("%s", r.telefone);
        if (!validarTelefone(r.telefone)) {
            printf("Telefone inválido. Tente novamente.\n");
        }
    } while (!validarTelefone(r.telefone));

    printf("Tipo de Catástrofe (ex.: Enchente, Deslizamento): ");
    getchar();
    fgets(r.tipo, 50, stdin);
    r.tipo[strcspn(r.tipo, "\n")] = 0;

    printf("Descrição: ");
    fgets(r.descricao, 200, stdin);
    r.descricao[strcspn(r.descricao, "\n")] = 0;

    do {
        printf("Latitude (-90 a 90): ");
        scanf("%f", &r.latitude);
        printf("Longitude (-180 a 180): ");
        scanf("%f", &r.longitude);
        if (!validarCoordenadas(r.latitude, r.longitude)) {
            printf("Coordenadas inválidas. Tente novamente.\n");
        }
    } while (!validarCoordenadas(r.latitude, r.longitude));

    printf("Data (dd/mm/aaaa): ");
    scanf("%s", r.data);

    relatos[*quantidade] = r;
    (*quantidade)++;

    printf("Relato cadastrado com sucesso!\n");
}

// Função para listar todos os relatos
void listarRelatos(Relato *relatos, int quantidade) {
    if (quantidade == 0) {
        printf("Nenhum relato cadastrado.\n");
        return;
    }

    printf("\n==== LISTA DE RELATOS ====\n");
    for (int i = 0; i < quantidade; i++) {
        printf("\nRelato #%d\n", i + 1);
        printf("Nome: %s\n", relatos[i].nome);
        printf("CPF: %s\n", relatos[i].cpf);
        printf("Telefone: %s\n", relatos[i].telefone);
        printf("Tipo: %s\n", relatos[i].tipo);
        printf("Descrição: %s\n", relatos[i].descricao);
        printf("Latitude: %.6f\n", relatos[i].latitude);
        printf("Longitude: %.6f\n", relatos[i].longitude);
        printf("Data: %s\n", relatos[i].data);
    }
}

// Função para buscar relatos por raio de até 10km
void buscarPorRaio(Relato *relatos, int quantidade, float lat, float lon) {
    printf("\nRelatos dentro de 10 km:\n");
    int encontrados = 0;
    for (int i = 0; i < quantidade; i++) {
        double distancia = calcularDistancia(lat, lon, relatos[i].latitude, relatos[i].longitude);
        if (distancia <= 10) {
            printf("\nNome: %s\n", relatos[i].nome);
            printf("Tipo: %s\n", relatos[i].tipo);
            printf("Descrição: %s\n", relatos[i].descricao);
            printf("Data: %s\n", relatos[i].data);
            printf("Distância: %.2f km\n", distancia);
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("Nenhum relato encontrado nesse raio.\n");
    }
}

// Função para ordenar por nome (bubble sort)
void ordenarPorNome(Relato *relatos, int quantidade) {
    Relato temp;
    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = 0; j < quantidade - i - 1; j++) {
            if (strcmp(relatos[j].nome, relatos[j + 1].nome) > 0) {
                temp = relatos[j];
                relatos[j] = relatos[j + 1];
                relatos[j + 1] = temp;
            }
        }
    }
    printf("Relatos ordenados por nome.\n");
}

// Função para salvar relatos em arquivo
void salvarRelatos(Relato *relatos, int quantidade) {
    FILE *file = fopen("relatos.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        fprintf(file, "%s;%s;%s;%s;%s;%.6f;%.6f;%s\n",
                relatos[i].nome, relatos[i].cpf, relatos[i].telefone,
                relatos[i].tipo, relatos[i].descricao,
                relatos[i].latitude, relatos[i].longitude, relatos[i].data);
    }
    fclose(file);
    printf("Dados salvos com sucesso!\n");
}

// Função para carregar relatos do arquivo
int carregarRelatos(Relato *relatos) {
    FILE *file = fopen("relatos.txt", "r");
    int count = 0;
    if (file != NULL) {
        while (fscanf(file, " %99[^;];%14[^;];%19[^;];%49[^;];%199[^;];%f;%f;%10[^\n]\n",
                      relatos[count].nome, relatos[count].cpf, relatos[count].telefone,
                      relatos[count].tipo, relatos[count].descricao,
                      &relatos[count].latitude, &relatos[count].longitude, relatos[count].data) != EOF) {
            count++;
        }
        fclose(file);
    }
    return count;
}

// Main
int main() {
    Relato relatos[MAX_RELATOS];
    int quantidade = carregarRelatos(relatos);
    int opcao;

    do {
        printf("\n==== Sistema de Relato de Catástrofes ====\n");
        printf("1. Cadastrar Relato\n");
        printf("2. Listar Relatos\n");
        printf("3. Buscar Relatos por Raio (10 km)\n");
        printf("4. Ordenar Relatos por Nome\n");
        printf("5. Salvar e Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarRelato(relatos, &quantidade);
                break;
            case 2:
                listarRelatos(relatos, quantidade);
                break;
            case 3: {
                float lat, lon;
                printf("Informe sua latitude: ");
                scanf("%f", &lat);
                printf("Informe sua longitude: ");
                scanf("%f", &lon);
                buscarPorRaio(relatos, quantidade, lat, lon);
                break;
            }
            case 4:
                ordenarPorNome(relatos, quantidade);
                break;
            case 5:
                salvarRelatos(relatos, quantidade);
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 5);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_ITEMS 50
#define MAX_LEN 50

typedef struct {
    char username[MAX_LEN];
    char password[MAX_LEN];
    char items[MAX_ITEMS][MAX_LEN];
    int itemCount;
} User;

User users[MAX_USERS];
int userCount = 0;

// Função para carregar os usuários do arquivo
void carregarUsuarios() {
    FILE *file = fopen("users.dat", "rb");
    if (file == NULL) {
        printf("Nenhum usuário registrado ainda.\n");
        return;
    }
    fread(&userCount, sizeof(int), 1, file);
    fread(users, sizeof(User), userCount, file);
    fclose(file);
}

// Função para salvar os usuários no arquivo
void salvarUsuarios() {
    FILE *file = fopen("users.dat", "wb");
    fwrite(&userCount, sizeof(int), 1, file);
    fwrite(users, sizeof(User), userCount, file);
    fclose(file);
}

// Função para registrar um novo usuário
void registrarUsuario() {
    if (userCount >= MAX_USERS) {
        printf("Limite de usuários atingido!\n");
        return;
    }

    char username[MAX_LEN], password[MAX_LEN];

    printf("Digite o nome de usuário: ");
    scanf("%s", username);
    printf("Digite a senha: ");
    scanf("%s", password);

    // Verifica se o nome de usuário já existe
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Usuário já existe!\n");
            return;
        }
    }

    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    users[userCount].itemCount = 0;  // Nenhum item no início
    userCount++;

    salvarUsuarios();
    printf("Usuário registrado com sucesso!\n");
}

// Função para fazer login
int fazerLogin() {
    char username[MAX_LEN], password[MAX_LEN];

    printf("Digite o nome de usuário: ");
    scanf("%s", username);
    printf("Digite a senha: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login bem-sucedido!\n");
            return i;  // Retorna o índice do usuário
        }
    }

    printf("Usuário ou senha incorretos!\n");
    return -1;  // Retorna -1 se o login falhar
}

// Função para adicionar um item
void adicionarItem(int userIndex) {
    if (users[userIndex].itemCount >= MAX_ITEMS) {
        printf("Limite de itens atingido!\n");
        return;
    }

    char item[MAX_LEN];
    printf("Digite o nome do item: ");
    scanf("%s", item);

    strcpy(users[userIndex].items[users[userIndex].itemCount], item);
    users[userIndex].itemCount++;

    salvarUsuarios();
    printf("Item adicionado com sucesso!\n");
}

// Função para listar os itens
void listarItens(int userIndex) {
    printf("Itens do usuário %s:\n", users[userIndex].username);
    for (int i = 0; i < users[userIndex].itemCount; i++) {
        printf("%d. %s\n", i + 1, users[userIndex].items[i]);
    }
}

// Função principal
int main() {
    carregarUsuarios();

    int opcao, userIndex;

    while (1) {
        printf("1. Registrar\n2. Login\n3. Sair\nEscolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            registrarUsuario();
        } else if (opcao == 2) {
            userIndex = fazerLogin();
            if (userIndex != -1) {
                int subOpcao;
                while (1) {
                    printf("1. Adicionar item\n2. Listar itens\n3. Logout\nEscolha uma opção: ");
                    scanf("%d", &subOpcao);

                    if (subOpcao == 1) {
                        adicionarItem(userIndex);
                    } else if (subOpcao == 2) {
                        listarItens(userIndex);
                    } else if (subOpcao == 3) {
                        printf("Logout efetuado!\n");
                        break;
                    } else {
                        printf("Opção inválida!\n");
                    }
                }
            }
        } else if (opcao == 3) {
            printf("Encerrando o programa...\n");
            break;
        } else {
            printf("Opção inválida!\n");
        }
    }

    return 0;
}

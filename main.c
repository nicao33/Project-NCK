#include <stdio.h>

// Função para exibir uma descrição sobre mim
void sobreMim() {
    printf("**********************************\n");
    printf("*       SOBRE MIM                *\n");
    printf("**********************************\n");
    printf("* Nome: Nicolas Machado             *\n");
    printf("* Idade: 19 anos                  *\n");
    printf("* Profissão: Desenvolvedor        *\n");
    printf("* Hobbies: Programar, Ler, Viajar *\n");
    printf("* Interesses: Tecnologia, IA      *\n");
    printf("**********************************\n\n");
}

int main() {
    printf("Bem-vindo ao programa 'Sobre Mim'!\n\n");
    
    // Chama a função para exibir as informações
    sobreMim();
    
    printf("Obrigado por usar este programa!\n");

    return 0;
}

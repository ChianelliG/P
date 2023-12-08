#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    ALCOOL,
    DIESEL,
    GASOLINA
} Combustivel;

typedef struct Veiculo {
    char proprietario[50];
    Combustivel combustivel;
    char modelo[50];
    char cor[20];
    char numCha[17];
    int ano;
    char placa[8];
    struct Veiculo *prox;
} Veiculo;

Veiculo *criarVeiculo(char proprietario[], Combustivel combustivel,
                      char modelo[], char cor[], char numCha[17], int ano, char placa[]);

Combustivel validaCombustivel(char combustivel);

bool validarPlaca(char placa[]);

Veiculo *cadastrarVeiculo(Veiculo **lista);

void imprimirLista(Veiculo *lista);

void funcaoA(Veiculo *lista);

void funcaoB(Veiculo *lista);

void funcaoC(Veiculo *lista);

void funcaoD(Veiculo *lista);

int main(void) {
    Veiculo *listaVeiculos = NULL;
    int opcao;

    do {
        printf("\nEscolha uma opcao\n");
        printf("1: Cadastrar veiculo\n");
        printf("2: Imprimir lista\n");
        printf("3: Funcao A\n");
        printf("4: Funcao B\n");
        printf("5: Funcao C\n");
        printf("6: Funcao D\n");
        printf("0: Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarVeiculo(&listaVeiculos);
                break;
            case 2:
                imprimirLista(listaVeiculos);
                break;
            case 3:
                funcaoA(listaVeiculos);
                break;
            case 4:
                funcaoB(listaVeiculos);
                break;
            case 5:
                funcaoC(listaVeiculos);
                break;
            case 6:
                funcaoD(listaVeiculos);
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    while (listaVeiculos != NULL) {
        Veiculo *temp = listaVeiculos;
        listaVeiculos = listaVeiculos->prox;
        free(temp);
    }

    return 0;
}

Veiculo *criarVeiculo(char proprietario[], Combustivel combustivel,
                      char modelo[], char cor[], char numCha[17], int ano, char placa[]) {
    Veiculo *novoVeiculo = (Veiculo *)malloc(sizeof(Veiculo));
    if (novoVeiculo == NULL) {
        perror("Erro ao alocar memoria para o veiculo");
        exit(EXIT_FAILURE);
    }

    strcpy(novoVeiculo->proprietario, proprietario);
    novoVeiculo->combustivel = combustivel;
    strcpy(novoVeiculo->modelo, modelo);
    strcpy(novoVeiculo->cor, cor);
    stpcpy(novoVeiculo->numCha, numCha);
    novoVeiculo->ano = ano;
    strcpy(novoVeiculo->placa, placa);
    novoVeiculo->prox = NULL;

    return novoVeiculo;
}

Combustivel validaCombustivel(char combustivel) {
    switch (combustivel) {
        case 'a':
            return ALCOOL;
        case 'd':
            return DIESEL;
        case 'g':
            return GASOLINA;
        default:
            printf("Combustivel invalido! Tente novamente\n");
            exit(EXIT_FAILURE);
    }
}

bool validarPlaca(char placa[]) {
    if (strlen(placa) != 7) {
        printf("A placa nao possui 7 caracteres.\n");
        return false;
    }

    for (int i = 0; i < 2; ++i) {
        if (!((placa[i] >= 'A' && placa[i] <= 'Z') || (placa[i] >= 'a' && placa[i] <= 'z'))) {
            printf("Os tres primeiros caracteres nao sao alfabeticos.\n");
            return false;
        }
    }

    for (int i = 3; i < 7; ++i) {
        if (!(placa[i] >= '0' && placa[i] <= '9')) {
            printf("Os quatro ultimos caracteres nao sao numericos.\n");
            return false;
        }
    }

    printf("Placa valida!\n");
    return true;
}

Veiculo *cadastrarVeiculo(Veiculo **lista) {
    char proprietario[50];
    Combustivel combustivel;
    char modelo[50];
    char cor[20];
    char numCha[17];
    int ano;
    char placa[8];

    printf("Proprietario: ");
    scanf("%s", proprietario);
    
    printf("Combustivel (a - Alcool, d - Diesel, g - Gasolina): ");
    scanf(" %c", &combustivel);
    combustivel = validaCombustivel(combustivel);
    
    printf("Modelo: ");
    scanf("%s", modelo);
    
    printf("Cor: ");
    scanf("%s", cor);
    
    printf("Numero do Chassi: ");
    scanf("%s", numCha);
    
    printf("Ano: ");
    scanf("%d", &ano);
    
    int placaValida;
    do {
        printf("Placa: (somente 7 caracteres)");
        scanf("%s", placa);
        placaValida = validarPlaca(placa);
    } while (!placaValida);

    Veiculo *novoVeiculo = criarVeiculo(proprietario, combustivel, modelo, cor, numCha, ano, placa);

    novoVeiculo->prox = *lista;
    *lista = novoVeiculo;

    return novoVeiculo;
}

void imprimirLista(Veiculo *lista) {
    Veiculo *atual = lista;
    while (atual != NULL) {
        printf("Proprietario: %s\n", atual->proprietario);
        printf("Combustivel: ");
        switch (atual->combustivel) {
            case ALCOOL:
                printf("Alcool\n");
                break;
            case DIESEL:
                printf("Diesel\n");
                break;
            case GASOLINA:
                printf("Gasolina\n");
                break;
        }
        printf("Modelo: %s\n", atual->modelo);
        printf("Cor: %s\n", atual->cor);
        printf("Numero do Chassi: %.2s\n", atual->numCha);
        printf("Ano: %d\n", atual->ano);
        printf("Placa: %s\n", atual->placa);
        printf("\n");

        atual = atual->prox;
    }
}

void funcaoA(Veiculo *lista) {
    Veiculo *atual = lista;
    printf("Proprietarios cujos carros sao do ano de 2010 ou mais e que sejam movidos a diesel\n");

    while (atual != NULL) {
        if (atual->ano >= 2010 && atual->combustivel == DIESEL) {
            printf("Proprietario: %s\n", atual->proprietario);
            printf("Combustivel: Diesel\n");
            printf("Modelo: %s\n", atual->modelo);
            printf("Cor: %s\n", atual->cor);
            printf("Numero do Chassi: %.2s\n", atual->numCha);
            printf("Ano: %d\n", atual->ano);
            printf("Placa: %s\n", atual->placa);
            printf("\n");
        }

        atual = atual->prox;
    }
}

void funcaoB(Veiculo *lista) {
    Veiculo *atual = lista;
    printf("As placas que comecam com j e terminam com 0, 2, 4 ou 7\n");

    while (atual != NULL) {
        if (atual->placa[0] == 'j' && (atual->placa[6] == '0' ||
                                        atual->placa[6] == '2' || atual->placa[6] == '4' || atual->placa[6] == '7')) {
            printf("Placa: %s\n", atual->placa);
            printf("Proprietario: %s\n", atual->proprietario);
            printf("\n");
        }

        atual = atual->prox;
    }
}

void funcaoC(Veiculo *lista) {
    Veiculo *atual = lista;
    printf("Modelo e cor dos veiculos que as placas possuem vogal no segundo caractere e a soma de valores numericos da placa seja numero par\n");

    while (atual != NULL) {
        int somaN = 0;
        for (int i = 3; i < 7; i++) {
            somaN += atual->placa[i] - '0';
        }

        if ((atual->placa[1] == 'a' || atual->placa[1] == 'e' || atual->placa[1] == 'i' ||
             atual->placa[1] == 'o' || atual->placa[1] == 'u') && somaN % 2 == 0) {
            printf("Modelo: %s\n", atual->modelo);
            printf("Cor: %s\n", atual->cor);
            printf("\n");
        }

        atual = atual->prox;
    }
}

void funcaoD(Veiculo *lista) {
    printf("Digite o numero do Chassi para a troca de proprietario: ");
    char numCha[20];
    scanf("%s", numCha);

    Veiculo *atual = lista;
    int encontrado = 0;

    while (atual != NULL) {
        int temZero = 0;
        for (int i = 0; i < 7; i++) {
            if (atual->placa[i] == '0') {
                temZero = 1;
                break;
            }
        }

        if (temZero == 0 && strcmp(atual->numCha, numCha) == 0) {
            printf("Troca de proprietario com o fornecimento do numero do chassi "
                   "apenas para carros com placas que nao possuam nenhum digito igual a zero\n");
            printf("Numero do Chassi: %.2s\n", atual->numCha);
            printf("Placa: %s\n", atual->placa);
            printf("Digite o novo proprietario: ");
            scanf("%s", atual->proprietario);
            printf("Troca de proprietario realizada com sucesso!\n");

            encontrado = 1;
            break;
        }
        atual = atual->prox;
    }

    if (!encontrado) {
        printf("Veiculo com o numero do chassi fornecido nao encontrado ou placa possui digito igual a zero.\n");
    }
}

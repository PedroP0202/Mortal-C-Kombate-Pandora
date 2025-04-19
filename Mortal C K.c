#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <wchar.h>

#define MAX_HEALTH 1000

typedef struct {
    char letra;
    char nome[50];
    int estamina;
} Ataque;

typedef struct {
    char nome[50];
    int ataque;
    int estamina;
} Combo;


typedef struct {
       char* comando;
       char acao;
} ComboParaHistorico;

typedef struct Node {
    char attack[150];
    int life_points;
    int stamina_points;
    struct Node* next;
} Node;

typedef struct {
    char nome[50];
    int vida;
    int estamina;
    Ataque ataques[12];
     char historico[100];
    Combo combo[5];
    Node* history;

} Jogador;

ComboParaHistorico comboss[] = {
        {"ARROZAO", '<'},
        {"DADBAD", '@'},
       {"STTEACC", '#'},

    };

void limparBuffer() {
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}


Node* criarNode(char* attack, int life_points, int stamina_points) {
    Node* node = (Node*) malloc(sizeof(Node));
    if (attack != NULL && strlen(attack) > 0) {
        strncpy(node->attack, attack, sizeof(node->attack) - 1);
    } else {
        node->attack[0] = '\0';
    }
    node->attack[sizeof(node->attack) - 1] = '\0';
    node->life_points = life_points;
    node->stamina_points = stamina_points;
    node->next = NULL;
    return node;
}

void adicionarNode(Jogador *jogador, char* attack, int life_points, int stamina_points) {
    Node* node = criarNode(attack, life_points, stamina_points);
    if (jogador->history == NULL) {
        jogador->history = node;
    } else {
        Node* current = jogador->history;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
}

void initHistoricoP(Jogador *jogador) {
    char historicoInicial[] = "ZPAETRCBOM";
    int vidaInicial = 837;
    int estaminaInicial = 1091;
    for (int i = 0; i < strlen(historicoInicial); i++) {
        char ataque[1] = {historicoInicial[i]};
        adicionarNode(jogador, ataque, vidaInicial, estaminaInicial);
    }
}
void initHistoricoS(Jogador *jogador) {
    char historicoInicial[] = "";
    int vidaInicial = 837;
    int estaminaInicial = 1091;
    for (int i = 0; i < strlen(historicoInicial); i++) {
        char ataque[2] = {historicoInicial[i], '\0'};
        adicionarNode(jogador, ataque, vidaInicial, estaminaInicial);
    }
}









void printHistorico(Jogador *jogador) {
    Node* current = jogador->history;

    char historico[256];
    int idx = 0;
    historico[0] = '\0';
    while (current!= NULL) {


        if (current->attack[0]!= ' ') {
            if (idx >= 17) {
                memmove(historico, historico + 1, idx);
                historico[idx - 1] = toupper(current->attack[0]);
                historico[idx] = '\0';
            } else {
                historico[idx++] = toupper(current->attack[0]);
                historico[idx] = '\0';
            }
        }

        current = current->next;
    }

    printf("%.17s", historico);
}
//
// void printHistorico(Jogador *jogador, char *historricoParaCombo) {
//     Node* current = jogador->history;
//     char  comboss[] = {"ARROZAO","DADBAD","STTEACC","TATAPAAA"};
//     char historico[256];
//     int idx = 0;
//     historico[0] = '\0';
//    int count =0;
//
//     for (int i = 0; i < strlen(historricoParaCombo) ; i++ ) {
//
//         if (historricoParaCombo[i]== '<') {
//             count = 1;
//
//
//         }else if (historricoParaCombo[i]== '@') {
//             count = 2;
//         }else if (historricoParaCombo[i]== '#') {
//             count = 3;
//         } else if (historricoParaCombo[i]== '$') {
//             count = 4;
//
//
//         }
//     }
//     while (current!= NULL) {
//
//         // for (int i = 0; i < strlen(historricoParaCombo) ; i++ ) {
//
//             if (count == 1 ) {
//
//
//                 for (int i = index; i < i+7; i++) {
//                     historico[ i+1 ] = comboss[0];//ARROZAO
//                 historico[i+2] = '\0';
//                 }
//
//             }else if (count == 2) {
//                 memmove(historico, historico + 1, idx);
//                 historico[idx - 1] = comboss[1];//DADBAD
//                 historico[idx] = '\0';
//             }else if (count == 3) {
//                 memmove(historico, historico + 1, idx);
//                 historico[idx - 1] = comboss[2];//STTEACC
//                 historico[idx] = '\0';
//             } else if (count == 4) {
//                 memmove(historico, historico + 1, idx);
//                 historico[idx - 1] = comboss[3];//TATAPAAA
//                 historico[idx] = '\0';
//
//
//             }else {
//
//                 if (idx >= 17) {
//                 memmove(historico, historico + 1, idx);
//                 historico[idx - 1] = toupper(current->attack[0]);
//                 historico[idx] = '\0';
//             }else {
//                 historico[idx++] = toupper(current->attack[0]);
//                 historico[idx] = '\0';
//             }
//         // }
//
//
//
//         }
//
//         current = current->next;
//     }
//
//     printf("%s", historico);
// }

void printHistorico1(Jogador *jogador, const char *historricoParaCombo) {
    Node* current = jogador->history;

    char historico[256];
    int idx = 0;
    historico[0] = '\0';



    // Adiciona os ataques normais ao histórico
    while (current!= NULL) {
        if (current->attack[0]!= ' ') {
            if (idx >= 17) {
                memmove(historico, historico + 1, idx);
                historico[idx - 1] = toupper(current->attack[0]);
                historico[idx] = '\0';
            } else {
                historico[idx++] = toupper(current->attack[0]);
                historico[idx] = '\0';
            }
        }

        current = current->next;
    }

    // Adiciona os combos ao histórico
    for (int i = 0; historricoParaCombo[i]!= '\0'; i++) {
        switch (historricoParaCombo[i]) {
            case '<': {

                strncpy(historico + idx, "RROZAO", 7);
                idx += 6;
                historico[idx] = '\0';

                break;
            }
            case '@': {

                strncpy(historico + idx, "ADBAD", 6);
                idx += 5;
                historico[idx] = '\0';

                break;
            }
            case '#': {

                strncpy(historico + idx, "TTEACC", 7);
                idx += 7;
                historico[idx] = '\0';

                break;
            }
            case '$': {

                strncpy(historico + idx, "ATAPAAA", 8);
                idx += 7;
                historico[idx] = '\0';

                break;
            }
        }
    }

    printf("%s", historico);
}







int efeitos[13][13] = {
    {0, 4, 8, 12, 16, -20, -16, 12, -8, -4, 0, 20,    0},  // Z
    {-4, 0, 4, 8, 12, 16, -20, -16, -12, 16, 0, 20,   0},  // P
    {-8, -4, 0, 4, 8, 12, 16, -20, -16, 12, 0, 20,    0},  // A
    {-12, -8, -4, 0, 4, -8, 12, 16, 20, -16, 0, 20,   0},  // E
    {-16, -12, -8, -4, 0, 4, -8, 12, 16, 20, 0, 20,   0},  // T
    {20, -16, -12, 8, -4, 0, 4, 8, 12, -16, 0, 20,    0},  // R
    {16, 20, -16, -12, 8, -4, 0, -8, -4, -8, 0, 20,   0},  // C
    {-12, 16, 20, -16, -12, -8, 8, 0, 16, -20, 0, 20, 0},  // B
    {8, 12, 16, -20, -16, -12, 4, -16, 0, 20, 0, 20,  0},  // O
    {4, -16, -12, 16, -20, 16, 8, 20, -20, 0, 0, 20,  0},  // M
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,              0},  // D
    {-20, -20, -20, -20, -20, -20, -20, -20, -20, -20, 0, 0, 0}, // ' '

    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

Combo combos[] = {
       { "ARROZAO", 500, 500},
  { "DADBAD", 400,400},
        { "STTEACC",300, 300},
       { "TATAPAAA",200, 200},
    };

int indiceAtaque(char letra) {
    switch (letra) {
        case 'Z': return 0;
        case 'P': return 1;
        case 'A': return 2;
        case 'E': return 3;
        case 'T': return 4;
        case 'R': return 5;
        case 'C': return 6;
        case 'B': return 7;
        case 'O': return 8;
        case 'M': return 9;
        case 'D': return 10;
        case ' ': return 11;
        default: return -1;
    }
}

int multiplicador(int estamina) {
    int counter = 1;
    if(estamina <= 250) {
        counter = 4;
    } else if(estamina <= 500) {
        counter = 3;
    } else if(estamina <= 750) {
        counter = 2;
    }

    return counter;
}

void printVidaEstamina(Jogador *jogador) {
    Node* current = jogador->history;
    int vida = jogador->vida;
    int estamina = jogador->estamina;

    while (current!= NULL) {
        vida = current->life_points;
        estamina = current->stamina_points;
        current = current->next;
    }

    printf("P#%s [%d|%d] (x%d)\n", jogador->nome, vida, estamina, multiplicador(estamina));
}

void inicializarJogador(Jogador *jogador, const char *nome, Ataque ataques[]) {
    strncpy(jogador->nome, nome, sizeof(jogador->nome) - 1);
    jogador->nome[sizeof(jogador->nome) - 1] = '\0';
    jogador->vida = 837;
    jogador->estamina = 1091;
    jogador->historico[0] = '\0';
    for (int i = 0; i < 12; i++) {
        jogador->ataques[i] = ataques[i];
    }
    jogador->history = NULL;

}

Ataque encontrarAtaque(Jogador *jogador, char letra) {
    Ataque ataqueInvalido = {'X', "Entrada invalida", 0};


    for (int i = 0; i < 12; i++) {
        if (jogador->ataques[i].letra == letra) {
            return jogador->ataques[i];
        }
    }
    return ataqueInvalido;
}






void processarAtaque(Jogador *atacante, Jogador *defensor, char letraAtaque, char letraDefesa, int mult1, int mult2) {
    int indiceAtq = indiceAtaque(letraAtaque);
    int indiceDef = indiceAtaque(letraDefesa);
    int efeito = efeitos[indiceAtq][indiceDef];
    int danoFinal = efeito;
    int len;
    int vidaRecuperada;

    Ataque ataque = encontrarAtaque(atacante, letraAtaque);
    Ataque defesa = encontrarAtaque(defensor, letraDefesa);





    if (letraAtaque == 'D' ) {
        atacante->estamina += 7;

        vidaRecuperada = 13 * mult1;

        atacante->vida += vidaRecuperada;
        if (atacante->vida > 999) atacante->vida = 999;
        if (atacante->estamina < 0) atacante->estamina = 0;
        if (atacante->estamina > 1103 ) atacante->estamina = 1103;
    }

    if (letraDefesa == 'D' ) {

        defensor->estamina += 7;

        vidaRecuperada = 13 * mult2;

        defensor->vida += vidaRecuperada;
        if (defensor->vida > 999) defensor->vida = 999;
        if (defensor->estamina < 0) defensor->estamina = 0;
        if (defensor->estamina > 1103 ) defensor->estamina = 1103;

        if (atacante->estamina <= 0 ) {

            atacante->estamina = 0;

        }else {
            atacante->estamina -= ataque.estamina;

        }
        if (defensor->estamina <= 0 ) {

            defensor->estamina = 0;

        }else {

            defensor->estamina -= defesa.estamina;
        }

        len = strlen(atacante->historico);
        if (len >= 17) {
            memmove(atacante->historico, atacante->historico + 1, len - 1);
            atacante->historico[len - 1] = ataque.letra;
            atacante->historico[len] = '\0';
        } else {
            strncat(atacante->historico, &ataque.letra, 1);
        }

        len = strlen(defensor->historico);
        if (len >= 17) {
            memmove(defensor->historico, defensor->historico + 1, len - 1);
            defensor->historico[len - 1] = defesa.letra;
            defensor->historico[len] = '\0';
        } else {
            strncat(defensor->historico, &defesa.letra, 1);
        }
        return;
    }

    if (danoFinal > 0) {
        defensor->vida -= danoFinal * mult2;
    } else if (danoFinal < 0) {
        atacante->vida += danoFinal * mult1;
    }


    if (atacante->estamina <= 0 ) {

        atacante->estamina = 0;

    }else {
        atacante->estamina -= ataque.estamina;

    }
    if (defensor->estamina <= 0 ) {

        defensor->estamina = 0;

    }else {

        defensor->estamina -= defesa.estamina;
    }


    if (defensor->estamina <= 0 ) {

        defensor->estamina = 0;

    }
    if (defensor->vida > 999) defensor->vida = 999;
    if (defensor->estamina > 1103 ) defensor->estamina = 1103;
    if (atacante->vida > 999) atacante->vida = 999;
    if (atacante->vida < 0) atacante->vida = 0;
    if (atacante->estamina > 1103 ) atacante->estamina = 1103;
    if (atacante->estamina < 0) atacante->estamina = 0;
    if (defensor->vida < 0) defensor->vida = 0;

    len = strlen(atacante->historico);
    if (len >= 17) {
        memmove(atacante->historico, atacante->historico + 1, len - 1);
        atacante->historico[len - 1] = ataque.letra;
        atacante->historico[len] = '\0';
    } else {
        strncat(atacante->historico, &ataque.letra, 1);

    }

    len = strlen(defensor->historico);
    if (len >= 17) {
        memmove(defensor->historico, defensor->historico + 1, len - 1);
        defensor->historico[len - 1] = defesa.letra;
        defensor->historico[len] = '\0';
    } else {
        strncat(defensor->historico, &defesa.letra, 1);
    }
}




void exibirStatus(Jogador *jogador) {
    printf("P#%s [%d|%d] (x%d)\n", jogador->nome, jogador->vida, jogador->estamina, multiplicador(jogador->estamina));
    printf("H: %.20s \n", jogador->historico);
    printf("I: ");
}

int tamanhoHistorico(Node* node) {
    if (node == NULL) {
        return 0;
    } else {

        return 1 + tamanhoHistorico(node->next);
    }
}

int processarCombo(Jogador *jogador, char *input, Jogador *oponente) {

    if (strncmp(input, "TARZANTABORDA", 13) == 0) {
        int x;
        sscanf(input + 13, "%d", &x); // Ler o valor de X

        // Requisito 16.4: Verificar se a estamina está dentro dos limites (500 a 900)
        if (jogador->estamina < 500 || jogador->estamina >= 900) {
            printf("Estamina insuficiente para TARZANTABORDA!\n");
            return 0;
        }

        // Requisito 16.3: Retroceder até o início se X for maior que o histórico
        int tamanhoHistoricoo = tamanhoHistorico(jogador->history); // Usar o histórico do jogador
        if (x > tamanhoHistoricoo) {
            x = tamanhoHistoricoo; // Retrocede até o início
        }

        // Apagar os X últimos elementos da lista ligada (histórico do jogador)
        Node* current = jogador->history;
        while (x > 0 && current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
            x--;
        }

        // Atualiza o histórico do jogador (e possivelmente outros estados)
        jogador->history = current;

        // Exibe mensagem de sucesso
        if (current == NULL) {
            printf("TARZANTABORDA ativado! O jogo voltou para o início.\n");
        } else {
            printf("TARZANTABORDA ativado! Retrocedeu %d jogadas.\n", x);
        }
        return 1; // Combo TARZANTABORDA executado com sucesso
    }

        for (int i = 0; i < 4; i++) {
            if (strstr(input, combos[i].nome) != NULL) {
                if (jogador->estamina >= 750) {
                oponente->vida -= combos[i].ataque;
                jogador->estamina -= combos[i].estamina;
                return 1;
                } else {
                    printf("Estamina Insuficiente\n");
                }
            }
        }

    return 0;
}
// int processarCombo(Jogador *jogador, char *input, Jogador *oponente, Node *history) {
//     // Requisito 16.1: Verificar estamina suficiente para combos normais
//     if (strncmp(input, "TARZANTABORDA", 13) != 0 && jogador->estamina <= 750) {
//         printf("Estamina Insuficiente\n");
//         return 0;
//     }
//
//     // Requisito 16.2: Tratar combo especial TARZANTABORDA
//     if (strncmp(input, "TARZANTABORDA", 13) == 0) {
//         int x = 0;
//         sscanf(input + 13, "%d", &x); // ler o valor de X
//         if (jogador->estamina < 500 || jogador->estamina >= 900) {
//             printf("Estamina Insuficiente para TARZANTABORDA\n");
//             return 0;
//         }
//         // Requisito 16.3: Verificar se X é maior que o número de jogadas ocorridas
//         int tamanhoHistoricoo = tamanhoHistorico(history);
//         if (x > tamanhoHistoricoo) {
//             x = tamanhoHistoricoo;
//         }
//         // Apagar os X últimos elementos da lista ligada
//         for (int i = 0; i < x; i++) {
//             Node *temp = history;
//             history = history->next;
//             free(temp);
//         }
//         printf("TARZANTABORDA ativado! Retrocedendo %d jogadas.\n", x);
//         return 1;
//     }

    //

    // Tratar combos normais
//     for (int i = 0; i < 4; i++) {
//         if (strstr(input, combos[i].nome) != NULL) {
//             oponente->vida -= combos[i].ataque;
//             jogador->estamina -= combos[i].estamina;
//             printf("Combo %s ativado!\n", combos[i].nome);
//             return 1;
//         }
//     }
//     return 0;
// }

void processarJogada(Jogador *jogador1, Jogador *jogador2,  char *comandos1, const char *comandos2, int modoS, char historricoParaCombo) {
    // int len1 = strlen(comandos1);
    int len2 = 5;
    int mult1 = multiplicador(jogador1->estamina);
    int mult2 = multiplicador(jogador2->estamina);


    // int encontrarCombo = processarCombo(jogador1, comandos1, jogador2);
    // if (encontrarCombo) {
    //     char combo_str[50];
    //     strcpy(combo_str, comandos1);
    //     printf("[%s, ]\n", combo_str);
    //
    //
    //     for (int i = 0; i < strlen(comandos1); i++) {
    //         char ataque[1] = {comandos1[i]};
    //         adicionarNode(jogador1, ataque, jogador1 ->vida, jogador1 ->estamina);
    //     }
    //
    //     adicionarNode(jogador2, combo_str, jogador2->vida, jogador2->estamina);
    // } else
    int encontrarCombo = processarCombo(jogador1, comandos1, jogador2);
    if (encontrarCombo) {
        char combo_str[50];
        strcpy(combo_str, comandos1);
        printf("[%s, ]\n", combo_str);

        // Remove os ataques individuais do combo do histórico
        Node* temp = jogador1->history;
        while (temp != NULL && strlen(temp->attack) == 1) { // Remove apenas ataques de 1 caractere
            Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
        jogador1->history = temp; // Atualiza o início do histórico

        // Adiciona o combo completo como um único nó no histórico
        adicionarNode(jogador1, combo_str, jogador1->vida, jogador1->estamina);
        adicionarNode(jogador2, "", jogador2->vida, jogador2->estamina);
    } else  {
        for (int i = 0; i < 5; i++) {

                   if (comandos1[i] == '\0') {
                       comandos1[i+1] = '\0';
                       comandos1[i] = ' ';
                   }
                   char ataque1 = comandos1[i];
                              char ataque2 = (i < len2) ? comandos2[i] : ' ';

            if ((ataque1 != ' ' && (encontrarAtaque(jogador1, ataque1).letra == 'X' || encontrarAtaque(jogador1, ataque1).letra == 'G' ||
                encontrarAtaque(jogador1, ataque1).letra == 'H' || encontrarAtaque(jogador1, ataque1).letra == 'I' ||
                encontrarAtaque(jogador1, ataque1).letra == 'J' || encontrarAtaque(jogador1, ataque1).letra == 'K' ||
                encontrarAtaque(jogador1, ataque1).letra == 'L' || encontrarAtaque(jogador1, ataque1).letra == 'N' ||
                encontrarAtaque(jogador1, ataque1).letra == 'Q' || encontrarAtaque(jogador1, ataque1).letra == 'U' ||
                encontrarAtaque(jogador1, ataque1).letra == 'V' || encontrarAtaque(jogador1, ataque1).letra == 'W'))) {
                printf("Entrada invalida\n");
                return;
            }


                processarAtaque(jogador1, jogador2, ataque1, ataque2, mult1, mult2);


            adicionarNode(jogador1, &ataque1, jogador1->vida, jogador1->estamina);
            adicionarNode(jogador2, &ataque2, jogador2->vida, jogador2->estamina);

            if (modoS!= 1) {
                       if (ataque1 != ' ' && ataque2 != ' ') {
                printf("[%c,%c]", toupper(ataque1), toupper(ataque2));
            } else if (ataque1 != ' ' && ataque2 == ' ') {
                printf("[%c, ]", toupper(ataque1));
            } else if (ataque1 == ' ' && ataque2 != ' ') {
                printf("[ ,%c]", toupper(ataque2));
            }

            }

        }
        printf("\n");
    }



}

int verificarCombo(const char *comandos) {

    const char *combos[] = {"ARROZAO", "DADBAD", "STTEACC", "TATAPAAA"};
    int numCombos = sizeof(combos) / sizeof(combos[0]);

    for (int i = 0; i < numCombos; i++) {
        if (strstr(comandos, combos[i]) != NULL) {
            return 1;
        }
    }

    return 0;
}
// int verificarTARZANTABORDA(const char *comandos) {
//     const char *combos[] = {"TARZANTABORDA"};
//     int numCombos = sizeof(combos) / sizeof(combos[0]);
//
//     for (int i = 0; i < numCombos; i++) {
//         if (strstr(comandos, combos[i]) == comandos) {
//             char *p = comandos + strlen(combos[i]);
//             while (*p != '\0') {
//                 if (!isdigit(*p)) {
//                     return 0; // Não é um combo válido
//                 }
//                 p++;
//             }
//             return 1; // É um combo válido
//         }
//     }
//
//     return 0; // Não é um combo válido
// }

int verificarTARZANTABORDA(const char *comandos) {
    const char *combos[] = {"TARZANTABORDA"};

    for (int i = 0; i < (int)(sizeof(combos) / sizeof(combos[0])); i++) {
        if (strstr(comandos, combos[i]) == comandos) {
            char *p = (char *)(comandos + strlen(combos[i]));

            while (*p != '\0') {
                if (!isdigit(*p)) {
                    return 0;
                }
                p++;
            }
            return 1;
        }
    }
    return 0;
}

char getComboAcao(char* comando) {
        for (int i = 0; i < sizeof(combos) / sizeof(combos[0]); i++) {
                if (strcmp(comando, comboss[i].comando) == 0) {
                        return comboss[i].acao;
                    }
            }
    return '\0';
    }



int main(int argc, char *argv[]) {


    int modoS = 0;
    int seed = 1;




    if (argc != 2) {
        seed = 1;
    }else {
        seed = atoi(argv[1]);
    }


    if (argc == 3) {
        if (strcmp(argv[2], "S") == 0) {
            modoS = 1;
        } else if (strcmp(argv[2], "V") != 0) {
            printf("Entrada invalida\n");
            return 1;
        }
    }





    FILE *file;
    char line[256];
    file = fopen("pedro.txt", "r");


    Ataque ataques[] = {
        {'Z', "Zarabatana", 23},
        {'P', "Pontapé", 23},
        {'A', "Agarrar",23},
        {'E', "Estalada",23},
        {'T', "Tombeta",23},
        {'R', "Rasteira",23},
        {'C', "Cotovelada",23},
        {'B', "Bicada", 23},
        {'O', "Onda de Choque", 23},
        {'M', "Murro",23},
        {'D', "Defender",0},
        {' ', "Descansa", -23}

    };


    Jogador jogador1, jogador2;

    char comandos1[100];
    char comandos2[100];
    char ataque1;
    Ataque ataque;

    inicializarJogador(&jogador1, "1", ataques);
    inicializarJogador(&jogador2, "2", ataques);
    initHistoricoP(&jogador1);
    // initHistoricoS(&jogador2);



    Node* jogador1history = NULL;
        Node* jogador2_history = NULL;

    srand(seed);
    int tamanhoHistoricoo = tamanhoHistorico(jogador1.history);
    int tamanhoHistoricooo = tamanhoHistorico(jogador1.history);

    char historrico[100];
    char historricoParaCombo[100];
    strcpy(historrico, "ZPAETRCBOM");

    int oi =0;

    while (1) {

        if (modoS != 1) {
            // exibirStatus(&jogador1);
        // printf("P#%s [%d|%d] (x%d)\n", jogador1.nome, jogador1.vida, jogador1.estamina, multiplicador(jogador1.estamina));
        printVidaEstamina(&jogador1);
        printf("H: ");
        printHistorico1(&jogador1,historricoParaCombo);
        printf("\nI: ");
        }




        if (file != NULL) {

            while (fgets(line, sizeof(line), file)) {
                fscanf(file, " %s", &comandos1);
            }

            // Fecha o ficheiro
            fclose(file);

        }else {
            scanf(" %s", comandos1);
            limparBuffer();
        }



        // processarCombo(&jogador1, comandos1, &jogador2, jogador1.history);




        int encontrarCombo = verificarCombo(comandos1);
        int encontrarComboT = verificarTARZANTABORDA(comandos1);

        ataque1 = comandos1[0];
        ataque = encontrarAtaque(&jogador1, ataque1);
        if (ataque.letra == 'X' || strlen(comandos1) >= 6 && !encontrarCombo  ) {
            printf("Entrada invalida\n");
           return 0;
        }else {
            for (int i = 0; i < strlen(comandos1); i++) {
                // if (encontrarComboT ) {
                //
                //     return 1;
                // }
                if (!isupper(comandos1[i]  ) ) {
                    printf("Entrada invalida\n");
                    return 0;
                }
            }
        }
        // processarCombo(&jogador1, comandos1, &jogador2  );

        if (modoS != 1) {
            // exibirStatus(&jogador2);
        // printf("P#%s [%d|%d] (x%d)\n", jogador2.nome, jogador2.vida, jogador2.estamina, multiplicador(jogador2.estamina));
        printVidaEstamina(&jogador2);
        printf("H: ");
        printHistorico(&jogador2);
        printf("\nI: ");
        }






        int num_ataques = 5;
        char comandos2[7];
        comandos2[0] = '\0';

        tamanhoHistoricoo = tamanhoHistorico(jogador1.history);

        if (strlen(comandos1) >= 6  ) {
            for (int i = tamanhoHistoricoo ; i < tamanhoHistoricoo +strlen(comandos1) ; i++){
                historrico[i] = comandos1[i - tamanhoHistoricoo];
                oi+=1 ;
            }

        }else {
            for (int i = tamanhoHistoricoo+oi ; i < tamanhoHistoricoo +5 + oi ; i++){
            historrico[i] = comandos1[i - (tamanhoHistoricoo + oi) ];

        }
        }


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        for (int i = 0 ; i < tamanhoHistoricoo +strlen(comandos1) ; i++){
            historricoParaCombo[i] =historrico[i] ;

        }

        if (strlen(comandos1) >= 6 ) {
            char acao = getComboAcao(comandos1);
            if (acao != '\0') {
                historricoParaCombo[tamanhoHistoricooo] = acao;
                historricoParaCombo[tamanhoHistoricooo + 1] = '\0'; // Termine a string com caractere nulo
            }
        } else {
            for (int i = tamanhoHistoricooo + oi; i < tamanhoHistoricooo + 5; i++) {
                historricoParaCombo[i] = comandos1[i - (tamanhoHistoricooo+oi)];
            }
            historricoParaCombo[tamanhoHistoricooo + 5 + oi] = '\0'; // Termine a string com caractere nulo
        }




        // for (int i = 0; i < strlen(historricoParaCombo); i++) {
        //     wprintf(L"%c", historricoParaCombo[i]);
        // }




        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        for (int i = 0; i < num_ataques; i++) {
            int random_attack_index = rand() % tamanhoHistoricoo ;



            char attack_letter = historrico[random_attack_index];
            comandos2[i] = attack_letter;

        }
        comandos2[num_ataques] = '\0';






        if(modoS != 1) {
            for(int i = 0; i < 5; i++) {
            printf("%c", comandos2[i]);
        }
        printf("\n");
        }






        processarJogada(&jogador1, &jogador2, comandos1, comandos2, modoS,historricoParaCombo );

        if (jogador1.vida <= 0 && jogador2.vida <= 0) {
                   printf("Empate! Ambos jogadores perderam.\n");
                   return 0;
               } else if (jogador1.vida <= 0) {
                       printf("Jogador %s venceu o jogo!\n", jogador2.nome);
                       return 0;
               } else if (jogador2.vida <= 0) {
                            printf("Jogador %s venceu o jogo!\n", jogador1.nome);
                           return 0;
               }


    }

    return 0;
}

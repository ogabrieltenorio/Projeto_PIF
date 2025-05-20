#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>

#define LARGURA_TELA 80
#define ALTURA_TELA 24
#define LARGURA_CANOS 6
#define ESPACO_CANO 8
#define POS_X_PASSARO 10
#define GRAVIDADE 1
#define PULO 3
#define TOTAL_CANOS 3
#define ARQUIVO_RANKING "ranking.txt"
#define TAM_NOME 20
#define MAX_JOGADORES 100

typedef struct {
    int y;
} Passaro;

typedef struct {
    int x;
    int gap_y;
    bool passou;
} Cano;

typedef struct {
    char nome[TAM_NOME];
    int pontuacao;
} Jogador;

Passaro passaro;
Cano canos[TOTAL_CANOS];
int pontuacao = 0;
int recorde = 0;
bool fim_de_jogo = false;
bool jogar_novamente = false;

void desenhar_moldura() {
    for (int x = 0; x < LARGURA_TELA; x++) {
        mvprintw(1, x, "-");
        mvprintw(ALTURA_TELA - 2, x, "-");
    }
    for (int y = 2; y < ALTURA_TELA - 2; y++) {
        mvprintw(y, 0, "|");
        mvprintw(y, LARGURA_TELA - 1, "|");
    }
    mvprintw(0, (LARGURA_TELA - 45) / 2, "MUITO MAIS DO QUE UM TRABALHO. UM APRENDIZADO");
}


void mostrar_ranking() {
    clear();
    desenhar_moldura();
    mvprintw(3, (LARGURA_TELA - 7) / 2, "RANKING");
    FILE *arquivo = fopen(ARQUIVO_RANKING, "r");
    if (arquivo) {
        Jogador jogadores[MAX_JOGADORES];
        int count = 0;
        while (fscanf(arquivo, "%s %d", jogadores[count].nome, &jogadores[count].pontuacao) == 2) {
            count++;
        }
        fclose(arquivo);
        for (int i = 0; i < count && i < 5; i++) {
            mvprintw(5 + i, (LARGURA_TELA - 20) / 2, "%d. %s - %d", i + 1, jogadores[i].nome, jogadores[i].pontuacao);
        }
    } else {
        mvprintw(5, (LARGURA_TELA - 20) / 2, "Ranking vazio ainda!");
    }
    mvprintw(ALTURA_TELA - 3, (LARGURA_TELA - 35) / 2, "Pressione qualquer tecla para jogar...");
    getch();
}

void carregar_recorde() {

    FILE *arquivo = fopen("recorde.txt", "r");
    if (arquivo) {
        fscanf(arquivo, "%d", &recorde);
        fclose(arquivo);
    }
}

void salvar_recorde() {
    FILE *arquivo = fopen("recorde.txt", "w");
    if (arquivo) {
        fprintf(arquivo, "%d", recorde);
        fclose(arquivo);
    }
}

void reiniciar_jogo() {
    passaro.y = ALTURA_TELA / 2;
    for (int i = 0; i < TOTAL_CANOS; i++) {
        canos[i].x = LARGURA_TELA + i * (LARGURA_TELA / TOTAL_CANOS);
        canos[i].gap_y = rand() % (ALTURA_TELA - ESPACO_CANO - 4) + 2;
        canos[i].passou = false;
    }
    pontuacao = 0;
    fim_de_jogo = false;
    jogar_novamente = false;
}

void desenhar_jogo() {
    clear();
    desenhar_moldura();
    mvprintw(ALTURA_TELA - 1, 2, "Pontuação: %d   Recorde: %d", pontuacao, recorde);
    attron(COLOR_PAIR(1)); mvprintw(passaro.y, POS_X_PASSARO, ">"); attroff(COLOR_PAIR(1));
    for (int i = 0; i < TOTAL_CANOS; i++) {
        for (int y = 2; y < ALTURA_TELA - 2; y++) {
            if (y < canos[i].gap_y || y > canos[i].gap_y + ESPACO_CANO) {
                for (int w = 0; w < LARGURA_CANOS; w++) {
                    attron(COLOR_PAIR(2)); mvprintw(y, canos[i].x + w, "|"); attroff(COLOR_PAIR(2));
                }
            }
        }
    }
    wnoutrefresh(stdscr);
    doupdate();
}

void atualizar_jogo() {
    passaro.y += GRAVIDADE;

    for (int i = 0; i < TOTAL_CANOS; i++) {
        canos[i].x--;

        if (!canos[i].passou && canos[i].x + LARGURA_CANOS < POS_X_PASSARO) {
            pontuacao++;
            canos[i].passou = true;
        }

        if (canos[i].x + LARGURA_CANOS < 1) {
            canos[i].x = LARGURA_TELA - 2;
            canos[i].gap_y = rand() % (ALTURA_TELA - ESPACO_CANO - 4) + 2;
            canos[i].passou = false;
        }

        if (POS_X_PASSARO >= canos[i].x && POS_X_PASSARO < canos[i].x + LARGURA_CANOS) {
            if (passaro.y < canos[i].gap_y || passaro.y > canos[i].gap_y + ESPACO_CANO) {
                fim_de_jogo = true;
            }
        }
    }

    if (passaro.y < 2 || passaro.y >= ALTURA_TELA - 2) {
        fim_de_jogo = true;
    }
}

int comparar_scores(const void *a, const void *b) {
    return ((Jogador *)b)->pontuacao - ((Jogador *)a)->pontuacao;
}

void salvar_no_ranking(const char *nome, int pontuacao) {
    Jogador jogadores[MAX_JOGADORES];
    int count = 0;

    FILE *arquivo = fopen(ARQUIVO_RANKING, "r");
    if (arquivo) {
        while (fscanf(arquivo, "%s %d", jogadores[count].nome, &jogadores[count].pontuacao) == 2) {
            count++;
        }
        fclose(arquivo);
    }

    strncpy(jogadores[count].nome, nome, TAM_NOME);
    jogadores[count].pontuacao = pontuacao;
    count++;

    qsort(jogadores, count, sizeof(Jogador), comparar_scores);

    arquivo = fopen(ARQUIVO_RANKING, "w");
    for (int i = 0; i < count && i < 5; i++) {
        fprintf(arquivo, "%s %d\n", jogadores[i].nome, jogadores[i].pontuacao);
    }
    fclose(arquivo);
}

void mostrar_game_over() {
    timeout(-1);
    echo();
    curs_set(TRUE);
    clear();
    desenhar_moldura();
    mvprintw(ALTURA_TELA / 2 - 2, (LARGURA_TELA - 20) / 2, "FIM DE JOGO!");
    mvprintw(ALTURA_TELA / 2, (LARGURA_TELA - 25) / 2, "Pontuação final: %d", pontuacao);
    mvprintw(ALTURA_TELA - 12, 2, "Digite seu nome: "); move(ALTURA_TELA - 11, 2);

    // Exibir ranking no Game Over
    FILE *arquivo = fopen(ARQUIVO_RANKING, "r");
    if (arquivo) {
        Jogador jogadores[MAX_JOGADORES];
        int count = 0;
        while (fscanf(arquivo, "%s %d", jogadores[count].nome, &jogadores[count].pontuacao) == 2) {
            count++;
        }
        fclose(arquivo);
        mvprintw(ALTURA_TELA - 9, 2, "RANKING:");
        for (int i = 0; i < count && i < 5; i++) {
            mvprintw(ALTURA_TELA - 8 + i, 2, "%d. %s - %d", i + 1, jogadores[i].nome, jogadores[i].pontuacao);
        }
    } else {
        mvprintw(ALTURA_TELA / 2 + 8, (LARGURA_TELA - 20) / 2, "Ranking vazio ainda!");
    }
    char nome[TAM_NOME];
    getnstr(nome, TAM_NOME - 1);
    noecho();
    curs_set(FALSE);

    salvar_no_ranking(nome, pontuacao);
    if (pontuacao > recorde) {
        recorde = pontuacao;
        salvar_recorde();
    }

    mvprintw(ALTURA_TELA / 2 + 4, (LARGURA_TELA - 40) / 2, "Deseja jogar novamente? (s/n): ");
    int ch = getch();
    if (ch == 's' || ch == 'S') {
        jogar_novamente = true;
    } else {
        mvprintw(ALTURA_TELA / 2 + 6, (LARGURA_TELA - 30) / 2, "Pressione qualquer tecla para sair...");
endwin();
        getch();
    }
}

int main() {
    srand(time(NULL));
    carregar_recorde();

    do {
        initscr();
    curs_set(FALSE);
    timeout(100);
    keypad(stdscr, TRUE);
    noecho();
    cbreak();
    clearok(stdscr, TRUE);
    idlok(stdscr, TRUE);
    leaveok(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);  // Pássaro
    init_pair(2, COLOR_GREEN, COLOR_BLACK);   // Canos
        noecho();
        cbreak();
        timeout(100);
        curs_set(FALSE);

        mostrar_ranking();
        reiniciar_jogo();

        while (!fim_de_jogo) {
            int tecla = getch();
            if (tecla == ' ') {
                passaro.y -= PULO;
            }
            atualizar_jogo();
            desenhar_jogo();
        }

                mostrar_game_over();
    } while (jogar_novamente);

    return 0;
}
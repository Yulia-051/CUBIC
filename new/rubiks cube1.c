
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define SIZE 5 // Размер стороны кубика

// Функция для вывода матрицы
void printMatrix(char matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        printf("        ");
        for (int j = 0; j < SIZE; j++) {

            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

void
R(char right[SIZE][SIZE], char front[SIZE][SIZE], char down[SIZE][SIZE], char up[SIZE][SIZE], char back[SIZE][SIZE]) {
    char temp[SIZE][SIZE];
    char temp1[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            temp[i][j] = right[i][j];
        }
    }
    for (int j = 0, k = 4; j < SIZE; j++, k--) {
        up[j][4] = front[j][4];
        for (int i = 0; i < SIZE; i++) {
            right[i][k] = temp[j][i];
        }
    }

    printMatrix(right);
}

void U(char l[SIZE][SIZE], char f[SIZE][SIZE], char r[SIZE][SIZE], char b[SIZE][SIZE]) {
    char temp[SIZE][SIZE];
    //не доделано (сверху не поворачивает )
    for (int j = 0; j < SIZE; j++) {
        temp[0][j] = l[0][j];
    }

    for (int j = 0; j < SIZE; j++) {
        l[0][j] = f[0][j];
    }
    for (int j = 0; j < SIZE; j++) {
        f[0][j] = r[0][j];
    }
    for (int j = 0; j < SIZE; j++) {
        r[0][j] = b[0][j];
    }
    for (int j = 0; j < SIZE; j++) {
        b[0][j] = temp[0][j];
    }
}

void u_f(char l[SIZE][SIZE], char f[SIZE][SIZE], char r[SIZE][SIZE], char b[SIZE][SIZE]) {
    char temp[SIZE][SIZE];
    for (int j = 0; j < SIZE; j++) {
        temp[1][j] = l[1][j];
    }

    for (int j = 0; j < SIZE; j++) {
        l[1][j] = f[1][j];
    }
    for (int j = 0; j < SIZE; j++) {
        f[1][j] = r[1][j];
    }
    for (int j = 0; j < SIZE; j++) {
        r[1][j] = b[1][j];
    }
    for (int j = 0; j < SIZE; j++) {
        b[1][j] = temp[1][j];
    }
}

void E(char l[SIZE][SIZE], char f[SIZE][SIZE], char r[SIZE][SIZE], char b[SIZE][SIZE]) {
    char temp[SIZE][SIZE];
    for (int j = 0; j < SIZE; j++) {
        temp[2][j] = l[2][j];
    }

    for (int j = 0; j < SIZE; j++) {
        l[2][j] = f[2][j];
    }
    for (int j = 0; j < SIZE; j++) {
        f[2][j] = r[2][j];
    }
    for (int j = 0; j < SIZE; j++) {
        r[2][j] = b[2][j];
    }
    for (int j = 0; j < SIZE; j++) {
        b[2][j] = temp[2][j];
    }
}

void U(char l[SIZE][SIZE], char f[SIZE][SIZE], char r[SIZE][SIZE], char b[SIZE][SIZE]) {
    char temp[SIZE][SIZE];
    //не доделано (сверху не поворачивает )
    for (int j = 0; j < SIZE; j++) {
        temp[0][j] = b[0][j];
    }

    for (int j = 0; j < SIZE; j++) {
        b[0][j] = r[0][j];
    }
    for (int j = 0; j < SIZE; j++) {
        r[0][j] = f[0][j];
    }
    for (int j = 0; j < SIZE; j++) {
        f[0][j] = l[0][j];
    }
    for (int j = 0; j < SIZE; j++) {
        l[0][j] = temp[0][j];
    }
}

void U2(char l[SIZE][SIZE], char f[SIZE][SIZE], char r[SIZE][SIZE], char b[SIZE][SIZE]) {
    char temp[SIZE][SIZE];
    for (int j = 0; j < SIZE; j++) {
        temp[1][j] = b[1][j];
    }

    for (int j = 0; j < SIZE; j++) {
        b[1][j] = r[1][j];
    }
    for (int j = 0; j < SIZE; j++) {
        r[1][j] = f[1][j];
    }
    for (int j = 0; j < SIZE; j++) {
        f[1][j] = l[1][j];
    }
    for (int j = 0; j < SIZE; j++) {
        l[1][j] = temp[1][j];
    }
}

void E(char l[SIZE][SIZE], char f[SIZE][SIZE], char r[SIZE][SIZE], char b[SIZE][SIZE]) {
    char temp[SIZE][SIZE];
    for (int j = 0; j < SIZE; j++) {
        temp[2][j] = b[2][j];
    }

    for (int j = 0; j < SIZE; j++) {
        b[2][j] = r[2][j];
    }
    for (int j = 0; j < SIZE; j++) {
        r[2][j] = f[2][j];
    }
    for (int j = 0; j < SIZE; j++) {
        f[2][j] = l[2][j];
    }
    for (int j = 0; j < SIZE; j++) {
        l[2][j] = temp[2][j];
    }
}

void M(char u[SIZE][SIZE], char f[SIZE][SIZE], char d[SIZE][SIZE], char b[SIZE][SIZE]) {
    char temp[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        temp[i][2] = u[i][2];
    }


    for (int i = 0; i < SIZE; i++) {
        u[i][2] = f[i][2];
    }
    for (int i = 0; i < SIZE; i++) {
        f[i][2] = d[i][2];
    }
    for (int i = 0; i < SIZE; i++) {
        d[i][2] = b[i][2];
    }
    for (int i = 0; i < SIZE; i++) {
        b[i][2] = temp[i][2];
    }
}

void printRubiksCube(char left[SIZE][SIZE], char front[SIZE][SIZE], char right[SIZE][SIZE], char back[SIZE][SIZE],
    char up[SIZE][SIZE], char down[SIZE][SIZE]) {
    // Вывод верхней части
    printMatrix(up);

    // Вывод левой, передней, правой и задней частей
    for (int i = 0; i < SIZE; i++) {
        printf("%c%c%c%c%c   ", left[i][0], left[i][1], left[i][2], left[i][3], left[i][4]);
        printf("%c%c%c%c%c   ", front[i][0], front[i][1], front[i][2], front[i][3], front[i][4]);
        printf("%c%c%c%c%c   ", right[i][0], right[i][1], right[i][2], right[i][3], right[i][4]);
        printf("%c%c%c%c%c\n", back[i][0], back[i][1], back[i][2], back[i][3], back[i][4]);
    }

    // Вывод нижней части
    printMatrix(down);
}

int isEdge(char edge) {
    char edges[] = { 'F', 'R', 'U' };
    for (int i = 0; i < 3; ++i) {
        if (edge == edges[i]) return 1;
    }
    return 0;
}


int main() {
    // Создание матриц для каждой стороны кубика Рубика
    char right[SIZE][SIZE] = { {'R', 'R', 'R', 'R', 'R'},
                              {'R', 'R', 'R', 'R', 'R'},
                              {'R', 'R', 'R', 'R', 'R'},
                              {'R', 'R', 'R', 'R', 'R'},
                              {'R', 'R', 'R', 'R', 'R'} };

    char left[SIZE][SIZE] = { {'O', 'O', 'O', 'O', 'O'},
                             {'O', 'O', 'O', 'O', 'O'},
                             {'O', 'O', 'O', 'O', 'O'},
                             {'O', 'O', 'O', 'O', 'O'},
                             {'O', 'O', 'O', 'O', 'O'} };

    char front[SIZE][SIZE] = { {'G', 'G', 'G', 'G', 'G'},
                              {'G', 'G', 'G', 'G', 'G'},
                              {'G', 'G', 'G', 'G', 'G'},
                              {'G', 'G', 'G', 'G', 'G'},
                              {'G', 'G', 'G', 'G', 'G'} };

    char back[SIZE][SIZE] = { {'B', 'B', 'B', 'B', 'B'},
                             {'B', 'B', 'B', 'B', 'B'},
                             {'B', 'B', 'B', 'B', 'B'},
                             {'B', 'B', 'B', 'B', 'B'},
                             {'B', 'B', 'B', 'B', 'B'} };

    char up[SIZE][SIZE] = { {'W', 'W', 'W', 'W', 'W'},
                           {'W', 'W', 'W', 'W', 'W'},
                           {'W', 'W', 'W', 'W', 'W'},
                           {'W', 'W', 'W', 'W', 'W'},
                           {'W', 'W', 'W', 'W', 'W'} };

    char down[SIZE][SIZE] = { {'Y', 'Y', 'Y', 'Y', 'Y'},
                             {'Y', 'Y', 'Y', 'Y', 'Y'},
                             {'Y', 'Y', 'Y', 'Y', 'Y'},
                             {'Y', 'Y', 'Y', 'Y', 'Y'},
                             {'Y', 'Y', 'Y', 'Y', 'Y'} };

    char test[SIZE][SIZE] = { {'1', '2', '3', '4', '5'},
                             {'6', '7', '8', '9', '1'},
                             {'1', '1', '1', '1', '1'},
                             {'1', '1', '1', '1', '1'},
                             {'1', '1', '1', '1', '1'} };
    // Вывод матриц в виде развертки куба
    // Верхняя часть
    //int flag = 0;
    printRubiksCube(left, front, test, back, up, down);
    R(test, front, down, up, back);
    //printRubiksCube(left, front, right, back, up, down);
    while (1) {
        char cmd[16] = { '\0' };
        printf("\nEnter command: ");
        fgets(cmd, 16, stdin);

        // F1', F2, F3, F4, F5, U1, U2, U3, U4, U5, R1, R2....
        if (cmd[strlen(cmd) - 1] == '\n') {
            cmd[strlen(cmd) - 1] = '\0';
        }
        if (!strcmp(cmd, "exit")) break;
        char edge = 0, direct = ' ';
        int layer = 0;


        int ret = sscanf(cmd, "%c%d%c", &edge, &layer, &direct);
        if (ret < 2 || ret > 3 || !isEdge(edge) || (layer > 5) || (layer < 1) || !((direct == '\'') || (direct == ' '))) {
            puts("[Error] Incorrect cmd");
            fflush(stdout);
            continue;
        }
        printf("%c %d %c", edge, layer, direct);
        switch (edge) {
        case 'U': {
            int layer;
            if (isdigit(input[1])) layer = input[1] - '0';
            else {
                puts("Incorrect cmd");
                break;
            }
            if (strlen(input) == 3 && input[2] == '\'')
                U(left, front, right, back/*, up*/, layer);  // против
            else if (strlen(input) == 2)
                U2(left, front, right, back/*, up*/, layer);  // по
            else {
                puts("Incorrect cmd");
                break;
            }
            break;
        }
        case 'D': {
            int layer;
            if (isdigit(input[1])) layer = input[1] - '0';
            else {
                puts("Incorrect cmd");
                break;
            }
            if (strlen(input) == 3 && input[2] == '\'')
                U(left, front, right, back/*, up*/, layer);  // против
            else if (strlen(input) == 2)
                U2(left, front, right, back/*, up*/, layer);  // по
            else {
                puts("Incorrect cmd");
                break;
            }
            break;
        }
        default: {
            puts("Unknown cmd");
        }

    }


    return 0;
}

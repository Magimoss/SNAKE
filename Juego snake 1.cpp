#include <stdio.h>
#include <conio.h> 
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>

#define ALTURA 28
#define ANCHO 100

int colaSerpienteX[100], colaSerpienteY[100];
int longitudColaSerpiente, juegoTerminado, tecla, puntuacion, x, y, frutaX, frutaY;

void ocultarCursor();
void moverCursor(int x, int y);
void configuracion();
void generarFruta();
void dibujarBorde();
void dibujar();
void entrada();
void verificarColisiones();
void actualizarSerpiente();
void verificarFruta();
void mostrarMensajeFinal();

void ocultarCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = FALSE;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void moverCursor(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x, y};
    SetConsoleCursorPosition(hConsole, pos);
}

void configuracion() {
    juegoTerminado = 0;
    x = ANCHO / 2;
    y = ALTURA / 2;
    generarFruta();
    puntuacion = 0;
    longitudColaSerpiente = 0;
}

void generarFruta() {
    do {
        frutaX = rand() % ANCHO;
    } while (frutaX == 0);
    
    do {
        frutaY = rand() % ALTURA;
    } while (frutaY == 0);
}

void dibujarBorde() {
    for (int i = 0; i < ANCHO + 2; i++)
        printf("-");
    printf("\n");
}

void dibujar() {
    moverCursor(0, 0);
    dibujarBorde();
    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j <= ANCHO; j++) {
            if (j == 0 || j == ANCHO) printf("#");
            else if (i == y && j == x) printf("O");
            else if (i == frutaY && j == frutaX) printf("*");
            else {
                int imprimirCola = 0;
                for (int k = 0; k < longitudColaSerpiente; k++) {
                    if (colaSerpienteX[k] == j && colaSerpienteY[k] == i) {
                        printf("o");
                        imprimirCola = 1;
                    }
                }
                if (!imprimirCola) printf(" ");
            }
        }
        printf("\n");
    }
    dibujarBorde();
    printf("Puntuacion = %d\n", puntuacion);
    printf("Presiona W, A, S, D para moverte.\n");
    printf("Presiona X para salir del juego.\n");
}

void entrada() {
    if (kbhit()) {
        switch (tolower(getch())) {
            case 'a': if (tecla != 2) tecla = 1; break;
            case 'd': if (tecla != 1) tecla = 2; break;
            case 'w': if (tecla != 4) tecla = 3; break;
            case 's': if (tecla != 3) tecla = 4; break;
            case 'x': juegoTerminado = 1; break;
        }
    }
}

void verificarColisiones() {
    if (x < 0 || x >= ANCHO || y < 0 || y >= ALTURA) juegoTerminado = 1;
    for (int i = 0; i < longitudColaSerpiente; i++) {
        if (colaSerpienteX[i] == x && colaSerpienteY[i] == y) juegoTerminado = 1;
    }
}

void actualizarSerpiente() {
    int prevX = colaSerpienteX[0];
    int prevY = colaSerpienteY[0];
    colaSerpienteX[0] = x;
    colaSerpienteY[0] = y;

    for (int i = 1; i < longitudColaSerpiente; i++) {
        int tempX = colaSerpienteX[i];
        int tempY = colaSerpienteY[i];
        colaSerpienteX[i] = prevX;
        colaSerpienteY[i] = prevY;
        prevX = tempX;
        prevY = tempY;
    }
    
    switch (tecla) {
        case 1: x--; break;
        case 2: x++; break;
        case 3: y--; break;
        case 4: y++; break;
    }
}

void verificarFruta() {
    if (x == frutaX && y == frutaY) {
        generarFruta();
        puntuacion += 10;
        longitudColaSerpiente++;
    }
}

void mostrarMensajeFinal() {
    system("cls");
    printf("###########################\n");
    printf("#       JUEGO TERMINADO   #\n");
    printf("#     Puntuacion: %d      #\n", puntuacion);
    printf("###########################\n");
}

int main() {
    configuracion();
    ocultarCursor();

    while (!juegoTerminado) {
        dibujar();
        entrada();
        actualizarSerpiente();
        verificarColisiones();
        verificarFruta();
        Sleep(33);
    }

    mostrarMensajeFinal();
    return 0;
}

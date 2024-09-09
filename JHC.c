#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Para usar la funciC3n sleep()

#define WIDTH 75   // Ancho del tablero
#define HEIGHT 75  // Alto del tablero

void imprimirTablero(int tablero[HEIGHT][WIDTH]) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			printf("%c ", tablero[i][j] ? 'O' : ' ');  // 'O' representa las cC)lulas vivas, '.' las muertas
		}
		printf("\n");
	}
}

int contarVecinosVivos(int tablero[HEIGHT][WIDTH], int x, int y) {
	int vivos = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) continue;  // Saltar la propia celda
			int filaVecino = (x + i + HEIGHT) % HEIGHT;
			int colVecino = (y + j + WIDTH) % WIDTH;
			vivos += tablero[filaVecino][colVecino];
		}
	}
	return vivos;
}

void colocarLWSS(int tablero[HEIGHT][WIDTH], int x, int y) {
    // Asegúrate de que el LWSS no salga del tablero
    if (x >= 0 && x + 5 < WIDTH && y >= 0 && y + 2 < HEIGHT) {
        // Establecer el patrón LWSS
        tablero[y][x] = 1;        // (y, x)
        tablero[y][x + 1] = 1;    // (y, x+1)
        tablero[y][x + 2] = 1;    // (y, x+2)
        tablero[y + 1][x + 2] = 1;  // (y+1, x+2)
        tablero[y + 2][x + 1] = 1;  // (y+2, x+1)
        tablero[y + 2][x + 2] = 1;  // (y+2, x+2)
    } else {
        printf("Posición fuera del tablero.\n");
    }
}

void actualizarTablero(int tablero[HEIGHT][WIDTH]) {
	int nuevoTablero[HEIGHT][WIDTH] = {0};

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			int vecinosVivos = contarVecinosVivos(tablero, i, j);
			if (tablero[i][j] == 1) {  //celda viva
				if (vecinosVivos < 2 || vecinosVivos > 3) {
					nuevoTablero[i][j] = 0;  // Muerte por soledad o sobrepoblaciC3n
				} else {
					nuevoTablero[i][j] = 1;  // Sobrevive
				}
			} else {  // celda muerta
				if (vecinosVivos == 3) {
					nuevoTablero[i][j] = 1;  // Nace una nueva celula
				}
			}
		}
	}

	// Copiar el nuevo tablero al tablero original
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			tablero[i][j] = nuevoTablero[i][j];
		}
	}
}

int main() {
	int tablero[HEIGHT][WIDTH] = {0};


	//PatrC3n ("glider")
	tablero[1][2] = 1;
	tablero[2][3] = 1;
	tablero[3][1] = 1;
	tablero[3][2] = 1;
	tablero[3][3] = 1;
	//PatrC3n ("Blinker")
	tablero[10][8] = 1;
	tablero[10][9] = 1;
	tablero[10][10] = 1;

	//PatrC3n ("glider")
	tablero[21][22] = 1;
	tablero[22][23] = 1;
	tablero[23][21] = 1;
	tablero[23][22] = 1;
	tablero[23][23] = 1;
	//PatrC3n ("glider")
	tablero[31][32] = 1;
	tablero[32][33] = 1;
	tablero[33][31] = 1;
	tablero[33][32] = 1;
	tablero[33][33] = 1;
    colocarLWSS(tablero, 45, 5);
	
	while (1) {
		system("clear");  // Limpiar pantalla para una mejor visualizaciC3n
		imprimirTablero(tablero);
		actualizarTablero(tablero);
		usleep(200000);  // Pausa de 200 milisegundos entre generaciones
	}

	return 0;
}

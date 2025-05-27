#include <stdio.h>

#define NMAX 1000

void seg_lines(long n, long m, long x, long digit, char matrix[NMAX][NMAX])
{
	long i, j;

	if (digit != 0 && digit != 1 && digit != 7) {
		for (i = m - x; i < m; i++) {
			for (j = x; j < m - x; j++)
				matrix[i][j] = '^';
		}
		//Construim Linia din mijloc a cifrelor
	}
	if (digit != 1 && digit != 4) {
		for (i = 0; i < x; i++) {
			for (j = x; j < m - x; j++)
				matrix[i][j] = '^';
		}
		//Construim linia de sus a cifrelor
	}
	if (digit != 1 && digit != 4 && digit != 7) {
		for (i = n - x; i < n; i++) {
			for (j = x; j < m - x; j++)
				matrix[i][j] = '^';
		}
	}
	//Construim linia de jos a cifrelor
}

void seg_columns(long n, long m, long x, long digit, char matrix[NMAX][NMAX])
{
	long i, j;

	if (digit != 1 && digit != 2 && digit != 3 && digit != 7) {
		for (j = 0; j < x; j++) {
			for (i = x; i < m - x; i++)
				matrix[i][j] = '^';
		}
		//Construim coloana din stanga sus a cifrelor
	}
	if (digit != 5 && digit != 6) {
		for (j = m - x; j < m; j++) {
			for (i = x; i < m - x; i++)
				matrix[i][j] = '^';
		}
		//Construim coloana din dreapta sus a cifrelor
	}
	if (digit == 0 || digit == 2 || digit == 6 || digit == 8) {
		for (j = 0; j < x; j++) {
			for (i = m; i < n - x; i++)
				matrix[i][j] = '^';
		}
		//Construim coloana din stanga jos a cifrelor
	}
	if (digit != 2) {
		for (j = m - x; j < m; j++) {
			for (i = m; i < n - x; i++)
				matrix[i][j] = '^';
		}
		//Construim coloana din dreapta jos a cifrelor
	}
}

void P_command(char matrix[NMAX][NMAX], long long n, long long m)
{
	long long i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++)
			printf("%c ", matrix[i][j]);
		printf("\n");
	}
	printf("\n");
	//Afisam matricea
}

void W_command(char matrix[NMAX][NMAX], long n, long m, long digit)
{
	long i, j;
	char matrix_aux[NMAX][NMAX];

	for (i = 0; i < digit % n; i++) {
		for (j = 0; j < m; j++)
			matrix_aux[i][j] = matrix[i][j];
		//Retinem primele digit linii in matricea auxiliara
	}
	for (i = digit % n; i < n; i++) {
		for (j = 0; j < m; j++)
			matrix[i - digit % n][j] = matrix[i][j];
		//Mutam restul liniilor in sus
	}
	for (i = n - (digit % n); i < n; i++) {
		for (j = 0; j < m; j++)
			matrix[i][j] = matrix_aux[i - n + digit % n][j];
		//Adaugam matricea auxiliara
	}
}

void S_command(char matrix[NMAX][NMAX], long n, long m, long digit)
{
	long i, j;
	char matrix_aux[NMAX][NMAX];

	for (i = n - (digit % n); i < n; i++) {
		for (j = 0; j < m; j++)
			matrix_aux[i - n + digit % n][j] = matrix[i][j];
		//Retinem ultimele digit linii in matricea auxiliara
	}
	for (i = n - (digit % n) - 1; i >= 0; i--) {
		for (j = 0; j < m;  j++)
			matrix[i + digit % n][j] = matrix[i][j];
		//Mutam restul liniilor in jos
	}
	for (i = 0; i < digit % n; i++) {
		for (j = 0; j < m; j++)
			matrix[i][j] = matrix_aux[i][j];
		//Adaugam matricea auxiliara
	}
}

void D_command(char matrix[NMAX][NMAX], long n, long m, long digit)
{
	long i, j;
	char matrix_aux[NMAX][NMAX];

	for (j = m - digit % m; j < m; j++) {
		for (i = 0; i < n; i++)
			matrix_aux[i][j - m + digit % m] = matrix[i][j];
		//Retinem ultimele digit coloane in matricea auxiliara
	}
	for (j = m - (digit % m) - 1; j >= 0; j--) {
		for (i = 0; i < n; i++)
			matrix[i][j + digit % m] = matrix[i][j];
		//Mutam restul coloanelor la dreapta
	}
	for (j = 0; j < digit % m; j++) {
		for (i = 0; i < n; i++)
			matrix[i][j] = matrix_aux[i][j];
		//Adaugam matricea auxiliara
	}
}

void A_command(char matrix[NMAX][NMAX],  long n, long m, long digit)
{
	long i, j;
	char matrix_aux[NMAX][NMAX];

	for (j = 0; j < digit % m; j++) {
		for (i = 0; i < n; i++)
			matrix_aux[i][j] = matrix[i][j];
		//Retinem primele digit coloane in matricea auxiliara
	}
	for (j = digit % m; j < m; j++) {
		for (i = 0; i < n;  i++)
			matrix[i][j - digit % m] = matrix[i][j];
		//Mutam restul coloanelor la stanga
	}
	for (j = m - digit % m; j < m; j++) {
		for (i = 0; i < n; i++)
			matrix[i][j] = matrix_aux[i][j - m + digit % m];
		//Adaugam matricea auxiliara
	}
}

int main(void)
{
	long long N, M, L, W;
	long long i, j;
	unsigned long long digit;
	char comanda, matrix[NMAX][NMAX];

	scanf("%lld%lld%lld", &N, &M, &L);
	W = (int)(L / 3);
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++)
			matrix[i][j] = ' ';
		//Initializam matricea cu spatii
	}
	while (1) {
		scanf(" %c", &comanda);
		if (comanda == 'F') {
			scanf("%llu", &digit);
			if (digit > 9)
				printf("The input given is not a digit.\n");
			for (i = 0; i < N; i++) {
				for (j = 0; j < M; j++)
					matrix[i][j] = ' ';
				//Reinitializez matricea cu spatii pt a construi o noua cifra
			}
			seg_lines(N, M, W, digit, matrix);
			seg_columns(N, M, W, digit, matrix);
			//Construiesc cifra
		}
		if (comanda == 'P')
			P_command(matrix, N, M);//Afisez cifra
		if (comanda == 'W') {
			scanf("%llu", &digit);
			W_command(matrix, N, M, digit);
			//Mut matricea cu digit linii in sus 
		}
		if (comanda == 'A') {
			scanf("%llu", &digit);
			A_command(matrix, N, M, digit);
			//Mut matricea cu digit coloane la stanga
		}
		if (comanda == 'S') {
			scanf("%llu", &digit);
			S_command(matrix, N, M, digit);
			//Mut matricea cu digit linii in jos
		}
		if (comanda == 'D') {
			scanf("%llu", &digit);
			D_command(matrix, N, M, digit);
			//Mut matricea cu digit coloane la dreapta
		}
		if (comanda == 'Q')
			break;
		//Ultima comanda citita
		if (comanda >= 'A' && comanda <= 'Z')
			if (comanda != 'F' && comanda != 'P' && comanda != 'W')
				if (comanda != 'S' && comanda != 'A' && comanda != 'D')
					if (comanda != 'Q')
						printf("Invalid command.\n");
	}
	return 0;
}

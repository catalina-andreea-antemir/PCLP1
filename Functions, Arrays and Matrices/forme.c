#include <stdio.h>

#define NMAX 101

void forma_p(int d, int u, int m, int n)
{
	int i, j;

	if (d < -50 || d > 50 || d <= 0) {
		printf("Unsupported size to display shape");
	} else {
		if (u % 45 != 0) {
			printf("Unsupported angle to display shape");
		} else {
			if (u % 90 == 0) {
				for (i = 0; i < d; i++) {
					for (j = 0; j < d; j++)
						printf("*");
					/*Evit trecerea pe o noua linie la finalul formei,
					deoarece se va face aceasta trecere in functia main
					(se va repeta acest proces in fiecare functie)*/
					if (i != d - 1)
						printf("\n");
				}
			} else {
				if (u % 45 == 0) {
					for (i = 0; i < 2 * d - 1; i++) {
						for (j = 0; j < 2 * d; j++) {
							if (i + j < d - 1 || i < j - d + 1 || j < i - d + 1 || i + j > 3 * d - 3)
								printf(" ");
							else
								printf("*");
						}
						if (i != 2 * d - 2)
							printf("\n");
					}
				}
			}
		}
	}
	if (m != n - 1)
		printf("\n");
	//Evit adaugarea unui rand liber, 
	//in cazul in care aceasta e ultima forma afisata
}

void forma_d(int l, int i, int m, int n)
{
	int k, j;

	if (l < -50 || l > 50 || l <= 0 || i < -50 || i > 50 || i <= 0) {
		printf("Unsupported size to display shape");
	} else {
		for (k = 0; k < i; k++) {
			for (j = 0; j < l; j++)
				printf("*");
			if (k != i - 1)
				printf("\n");
		}
	}
	if (m != n - 1)
		printf("\n");
	//Evit adaugarea unui rand liber, 
	//in cazul in care aceasta e ultima forma afisata
}

void forma_t(int lc, int u, int m, int n)
{
	int i, j;

	if (lc < -50 || lc > 50 || lc <= 0) {
		printf("Unsupported size to display shape");
	} else {
		if (u % 90 != 0) {
			printf("Unsupported angle to display shape");
		} else {
			if (u >= 0) {
				if ((int)(u / 360.0 * 100) % 100 == 25) {
		//Verificam daca unghiul are masura de 90, 450, 810 etc. grade
					for (i = 0; i < lc; i++) {
						for (j = 0; j < lc; j++) {
							if (i + j <= lc - 1)
								printf("*");
							else
								printf(" ");
						}
						if (i != lc - 1)
							printf("\n");
					}
				}
				if ((int)(u / 360.0 * 100) % 100 == 50) {
		//Verificam daca unghiul are masura de 180, 540, 900 etc. grade
					for (i = 0; i < lc; i++) {
						for (j = 0; j < lc; j++) {
							if (i > j)
								printf(" ");
							else
								printf("*");
						}
						if (i != lc - 1)
							printf("\n");
					}
				}
				if ((int)(u / 360.0 * 100) % 100 == 75) {
		//Verificam daca unghiul are masura de 270, 630, 990 etc. grade
					for (i = 0; i < lc; i++) {
						for (j = 0; j < lc; j++) {
							if (i + j < lc - 1)
								printf(" ");
							else
								printf("*");
						}
						if (i != lc - 1)
							printf("\n");
					}
				}
				if ((int)(u / 360.0 * 100) % 100 == 0) {
		//Verificam daca unghiul are masura de 0, 360, 720 etc. grade
					for (i = 0; i < lc; i++) {
						for (j = 0; j < lc; j++) {
							if (i >= j)
								printf("*");
							else
								printf(" ");
						}
						if (i != lc - 1)
							printf("\n");
					}
				}
			} else {
		//Lucrurile stau altfel cand valoarea unghiului este negativa
				if ((int)((-u) / 360.0 * 100) % 100 == 25) {
		//Verificam daca unghiul are masura de 270, 630, 990 etc. grade
					for (i = 0; i < lc; i++) {
						for (j = 0; j < lc; j++) {
							if (i + j < lc - 1)
								printf(" ");
							else
								printf("*");
						}
						if (i != lc - 1)
							printf("\n");
					}
				}
				if ((int)(-(u) / 360.0 * 100) % 100 == 75) {
		//Verificam daca unghiul are masura de 90, 450, 810 etc. grade
					for (i = 0; i < lc; i++) {
						for (j = 0; j < lc; j++) {
							if (i + j <= lc - 1)
								printf("*");
							else
								printf(" ");
						}
						if (i != lc - 1)
							printf("\n");
					}
				}
				if ((int)(-(u) / 360.0 * 100) % 100 == 50) {
		//Verificam daca unghiul are masura de 180, 540, 900 etc. grade
					for (i = 0; i < lc; i++) {
						for (j = 0; j < lc; j++) {
							if (i > j)
								printf(" ");
							else
								printf("*");
						}
						if (i != lc - 1)
							printf("\n");
					}
				}
				if ((int)(-(u) / 360.0 * 100) % 100 == 0) {
		//Verificam daca unghiul are masura de 0, 360, 720 etc. grade
					for (i = 0; i < lc; i++) {
						for (j = 0; j < lc; j++) {
							if (i >= j)
								printf("*");
							else
								printf(" ");
						}
						if (i != lc - 1)
							printf("\n");
					}
				}
			}
		}
	}
	if (m != n - 1)
		printf("\n");
	//Evit adaugarea unui rand liber, 
	//in cazul in care aceasta e ultima forma afisata
}

void forma_c(int d, int u, int m, int n)
{
	int i, j;

	if (d < -50 || d > 50 || d % 2 == 0 || d <= 0) {
		printf("Unsupported size to display shape");
	} else {
		if (u % 45 != 0) {
			printf("Unsupported angle to display shape");
		} else {
			if (u % 90 == 0) {
				for (i = 0; i < d; i++) {
					for (j = 0; j < d; j++) {
						if (i == (d - 1) / 2 || j == (d - 1) / 2)
							printf("*");
						else
							printf(" ");
					}
					if (i != d - 1)
						printf("\n");
				}
			} else {
				if (u % 45 == 0) {
					for (i = 0; i < d; i++) {
						for (j = 0; j < d; j++) {
							if (i + j == d - 1 || i == j)
								printf("*");
							else
								printf(" ");
						}
						if (i != d - 1)
							printf("\n");
					}
				}
			}
		}
	}
	if (m != n - 1)
		printf("\n");
	//Evit adaugarea unui rand liber, 
	//in cazul in care aceasta e ultima forma afisata
}

void forma_f(int d, int m, int n)
{
	int i, j;

	if (d < -50 || d > 50 || d % 2 == 0 || d <= 0) {
		printf("Unsupported size to display shape");
	} else {
		for (i = 0; i < d; i++) {
			for (j = 0; j < d; j++) {
				if (j == (d - 1) / 2 || i == (d - 1) / 2 || i == 0 || j == 0 || i == d - 1 || j == d - 1)
					printf("*");
				else
					printf(" ");
			}
			if (i != d - 1)
				printf("\n");
		}
	}
	if (m != n - 1)
		printf("\n");
	//Evit adaugarea unui rand liber, 
	//in cazul in care aceasta e ultima forma afisata
}

int main(void)
{
	int N, i, dimensiune[NMAX], unghi[NMAX], lungime[NMAX];
	int inaltime[NMAX], lungime_cateta[NMAX];
	char forma[NMAX];

	scanf("%d", &N);
	for (i = 0; i < N; i++) {
		scanf(" %c", &forma[i]);
		if (forma[i] == 'p')
			scanf("%d%d", &dimensiune[i], &unghi[i]);
		if (forma[i] == 'd')
			scanf("%d%d", &lungime[i], &inaltime[i]);
		if (forma[i] == 't')
			scanf("%d%d", &lungime_cateta[i], &unghi[i]);
		if (forma[i] == 'c')
			scanf("%d%d", &dimensiune[i], &unghi[i]);
		if (forma[i] == 'f')
			scanf("%d", &dimensiune[i]);
	}
	for (i = 0; i < N; i++) {
		if (forma[i] == 'p')
			forma_p(dimensiune[i], unghi[i], i, N);
		if (forma[i] == 'd')
			forma_d(lungime[i], inaltime[i], i, N);
		if (forma[i] == 't')
			forma_t(lungime_cateta[i], unghi[i], i, N);
		if (forma[i] == 'c')
			forma_c(dimensiune[i], unghi[i], i, N);
		if (forma[i] == 'f')
			forma_f(dimensiune[i], i, N);
		if (i != N - 1)
			printf("\n");
	}
	return 0;
}

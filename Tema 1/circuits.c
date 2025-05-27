#include <stdio.h>
#include <string.h>
#include <math.h>

#define NMAX 1001
#define EROARE 1e-6

void verifica_legea_I(int N, int W)
{
	double curent_in[NMAX] = {0};
	double curent_out[NMAX] = {0};
	int nod_in, nod_out, nod_vizitat[NMAX] = {0};
	double curent;
	int i;

	// Se citesc firele si se calculeaza sumele curentilor
	for (i = 0; i < W; i++) {
		scanf("%d %d %lf", &nod_in, &nod_out, &curent);
		curent_out[nod_in - 1] += curent;
		curent_in[nod_out - 1] += curent;
		nod_vizitat[nod_in - 1]++;
		nod_vizitat[nod_out - 1]++;
	}
	for (i = 0; i < N; i++) {
		if (nod_vizitat[i] <= 1) {
			printf("Circuitul este deschis in nodul %d.\n", i + 1);
			return;
		}
	}
	// Se verifica nodurile
	for (i = 0; i < N; i++) {
		if (fabs(curent_in[i] - curent_out[i]) > EROARE) {
			printf("Legea 1 a lui Kirchhoff nu se respecta pentru egalitatea ");
			printf("%.9fA = %.9fA in nodul %d.\n", curent_in[i], curent_out[i], i + 1);
			//Folosesc return pentru a iesi din functie
			return;
		}
	}
	printf("Legea 1 a lui Kirchhoff se respecta pentru circuitul dat.\n");
}

void verifica_legea_II(int N, int W)
{
	int nod_in, nod_out, nr_componente, i, j;
	double curent, tensiune;
	double tensiune_consumatori, tensiune_surse;
	char tip_componenta;

	tensiune_consumatori = 0;
	tensiune_surse = 0;
	//Se citesc firele si componentele
	for (i = 0; i < W; i++) {
		scanf("%d %d %lf %d", &nod_in, &nod_out, &curent, &nr_componente);
		for (j = 0; j < nr_componente; j++) {
			scanf(" %c %lf", &tip_componenta, &tensiune);
			if (tensiune < 0) {
				printf("Sursa de tensiune nu poate fi negativa.\n");
				return;
			}
			if (tip_componenta == 'R') {
				tensiune_consumatori += curent * tensiune;
			} else if (tip_componenta == 'E') {
				tensiune_surse += tensiune;
			} else {
				//Aici nu mai stiu cum trebuia afisat
				printf("Componenta dorita nu exista.\n");
			}
		}
	}
	//Se verifica egalitatea caderilor de tensiune
	//Am folosit "fabs" pentru siguranta
	if (fabs(tensiune_consumatori - tensiune_surse) > EROARE) {
		printf("Legea a 2-a lui Kirchhoff nu se respecta pentru egalitatea");
		printf(" %.9fV = %.9fV.\n", tensiune_consumatori, tensiune_surse);
	} else {
		printf("Legea a 2-a lui Kirchhoff se respecta pentru circuitul dat.\n");
	}
}

int main(void)
{
	char L[4];
	int N, W;
	scanf(" %s", L);
	scanf("%d %d", &N, &W);
	if (strcmp(L, "I") == 0)
		verifica_legea_I(N, W);
	else if (strcmp(L, "II") == 0)
		verifica_legea_II(N, W);
	else
		printf("Legile existente sunt doar Legea 1 si Legea a 2-a\n");
	return 0;
}

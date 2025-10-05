#include <stdio.h>

#define NMAX 10001

//Am folosit algoritmul clasic BubbleSort pentru sortarea unui vector
void sort_shield(long v[], long n)
{
	int i, m, ok, aux;

	m = n;
	do {
		ok = 1;
		for (i = 0; i < m - 1; i++)
			if (v[i] < v[i + 1]) {//Sortez vectorul descrescator
				aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				ok = 0;
			}
		m--;
	} while (ok == 0);
}

int main(void)
{
	long N, M, shields[NMAX], number_shield = 0, used_shield, damage;
	long damage_received, i, j, k, nr_error = 0, valoare;
	unsigned long long HP;
	char tip;

	scanf("%llu", &HP);
	scanf("%ld", &N);
	for (i = 0; i < N; i++) {
		scanf(" %c %ld", &tip, &valoare);
		if (tip == 'H' && HP > 0)
			HP += valoare;
			//Daca se citeste o valoare de tip Heal (H) aceasta se adauga la HP
		else if (tip == 'S')
			shields[number_shield++] = valoare;
			//Formez un vector cu valorile de tip Shield (S)
		else
			nr_error++;
			//Retin numarul de date introduse care nu sunt de tip (H) sau (S)
	}
	sort_shield(shields, number_shield);//Sortez vectorul descrescator
	scanf("%ld", &M);
	for (i = 1; i <= nr_error; i++)
		printf("Invalid item type.\n");
	printf("Initial health points: %llu\n", HP);
	for (i = 0; i < M; i++) {
		used_shield = 0;//Retine valoarea scutului care verifica conditiile date
		scanf("%ld", &damage);
		for (j = 0; j < number_shield; j++) {
			if (shields[j] <= damage) {
				used_shield = shields[j];
				for (k = j; k < number_shield - 1; k++)
					shields[k] = shields[k + 1];
				number_shield--;
				break;
				//Am sters valoarea scutului folosit din vector
			}
		}
		if (used_shield == 0 && number_shield > 0)
			used_shield = shields[--number_shield];
			/*Daca nu a fost gasita nicio valoarea corespunzatoare cerintelor
			folosesc ultima valoare din vectorul de scuturi sortat descrescator
			care este si cea mai mica, fiind apoi stearsa din vector*/
		damage_received = damage - used_shield;
		if (damage_received > 0) {
			if (damage_received <= HP && HP > 0)
				HP -= damage_received;
			else
				HP = 0;
		}
		if (HP <= 0)
			HP = 0;
		printf("%llu", HP);
		if (used_shield != 0)
			printf(" %ld", used_shield);
		printf("\n");
		if (HP <= 0) {
			printf("You died.");
			return 0;
		}
	}
	printf("Foe Vanquished!");
	return 0;
}

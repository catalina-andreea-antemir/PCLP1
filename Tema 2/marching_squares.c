//Antemir Andreea-Catalina 314CA
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NMAX 1000

//Pixel structure
typedef struct {
	int r;
	int g;
	int b;
} pixel;

pixel **allocate_matrix(int n, int m)
{
	pixel **mat;
	int i;

	mat = malloc(n * sizeof(pixel *));
	if (!mat) {
		return NULL;
	}
	for (i = 0; i < n; i++) {
		mat[i] = calloc(m, sizeof(pixel));
		if (!mat[i]) {
			// Release the memory already allocated
			for (int j = 0; j < i; j++) {
				free(mat[j]);
			}
			free(mat);
			return NULL;
		}
	}
	return mat;
}

void read_img(pixel ***mat, int *height, int *width, int *value)
{
	int i, j;
	char type[3];

	scanf("%s", type);
	if (strcmp(type, "P3") != 0) {
		printf("Eroare: trebuie sa fie P3\n");
		exit(0);
	}
	scanf("%d %d", height, width);
	scanf("%d", value);
	*mat = allocate_matrix(*height, *width);
	if (!*mat) {
		exit(0);
	}
	for (i = 0; i < *height; i++) {
		for (j = 0; j < *width; j++) {
			//To avoid having more than 80 characters on the line
			pixel *p = &(*mat)[i][j];
			if (scanf("%d%d%d", &p->r, &p->g, &p->b) != 3) {
				printf("Eroare: eroare citire pixeli");
				exit(0);
			} else {
				if ((*mat)[i][j].r > *value || (*mat)[i][j].r < 0) {
					printf("Eroare: valoare pixel necorespunzatoare");
					exit(0);
				}
				if ((*mat)[i][j].g > *value || (*mat)[i][j].g < 0) {
					printf("Eroare: valoare pixel necorespunzatoare");
					exit(0);
				}
				if ((*mat)[i][j].b > *value || (*mat)[i][j].b < 0) {
					printf("Eroare: valoare pixel necorespunzatoare");
					exit(0);
				}
			}
		}
	}
	printf("Imagine citita cu succes [%d-%d]\n", *height, *width);
}

void write_img(pixel **mat, int height, int width, int value)
{
	int i, j;

	if (!mat)
		exit(0);

	printf("P3\n");
	printf("%d %d\n", width, height);
	printf("%d\n", value);

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			printf("%d %d %d\n", mat[i][j].r, mat[i][j].g, mat[i][j].b);
		}
	}
}

void resize_img(pixel ***mat, int *height, int *width, int factor)
{
	int new_height = (*height) * factor;
	int new_width = (*width) * factor;

	pixel **new_mat = allocate_matrix(new_height, new_width);
	if (!new_mat)
		return;

	for (int i = 0; i < new_height; i++) {
		for (int j = 0; j < new_width; j++) {
			new_mat[i][j] = (*mat)[i / factor][j / factor];
		}
	}
	//We empty the pixel matrix to make room for the resized one
	for (int i = 0; i < *height; i++)
		free((*mat)[i]);
	free(*mat);
	*mat = new_mat;
	*height = new_height;
	*width = new_width;
	printf("Imagine redimensionata cu succes [%d-%d]\n", *height, *width);
}

void calculate_grid(pixel **mat, int height, int width, int ***grid, int ok)
{
	int grid_height, grid_width, i, j, sum, cnt;

	grid_height = (height / 4) + 1;
	grid_width = (width / 4) + 1;

	*grid = (int **)malloc(grid_height * sizeof(int *));
	for (int i = 0; i < grid_height; i++)
		(*grid)[i] = (int *)malloc(grid_width * sizeof(int));
	for (i = 0; i <= height; i += 4) {
		for (j = 0; j <= width; j += 4) {
			sum = 0; cnt = 0;
			//Checking if the element is inside the matrix
			if (i < height && j < width) {
				//The element
				sum += (mat[i][j].r + mat[i][j].g + mat[i][j].b) / 3;
				cnt++; //Counting the neighbors of the element
			}
			if (i - 1 >= 0 && j - 1 >= 0) {
				//Arithmetic mean of the upper left neighbor
				sum += (mat[i - 1][j - 1].r + mat[i - 1][j - 1].g
				+ mat[i - 1][j - 1].b) / 3;
				cnt++;
			}
			if (i - 1 >= 0 && j + 1 < width) {
				sum += (mat[i - 1][j + 1].r + mat[i - 1][j + 1].g
				+ mat[i - 1][j + 1].b) / 3;
				cnt++;
			}
			if (i + 1 < height && j - 1 >= 0) {
				sum += (mat[i + 1][j - 1].r + mat[i + 1][j - 1].g
				+ mat[i + 1][j - 1].b) / 3;
				cnt++;
			}
			if (i + 1 < height && j + 1 < width) {
				sum += (mat[i + 1][j + 1].r + mat[i + 1][j + 1].g
				+ mat[i + 1][j + 1].b) / 3;
				cnt++;
			}
			//We give binary values to the grid according to the value of gamma
			if (sum / cnt <= 200)
				(*grid)[i / 4][j / 4] = 1;
			else
				(*grid)[i / 4][j / 4] = 0;
		}
	}
	//We use ok to display the grid if calculated_grid function
	//is not called in march
	if (ok == 1) {
		printf("Grid calculat cu succes [%d-%d]\n", (height / 4), (width / 4));
		for (i = 0; i < (height / 4); i++) {
			for (j = 0; j < (width / 4); j++) {
				printf("%d ", (*grid)[i][j]);
			}
			printf("\n");
		}
	}
}

void init_contur(int patterns[16][4][4])
{
	int i, j, k;

	//We display the 16 patterns
	for (k = 0; k < 16; k++) {
		printf("P3\n");
		printf("4 4\n");
		printf("255\n");
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				printf("%d ", patterns[k][i][j]);
				printf("%d ", patterns[k][i][j]);
				printf("%d\n", patterns[k][i][j]);
			}
		}
	}
}

void march(pixel **m, int **grid, int height, int width, int patterns[16][4][4])
{
	int patt = 0;
	int i, j, x, y;

	calculate_grid(m, height, width, &grid, 0);
	for (i = 0; i < (height / 4); i++) {
		for (j = 0; j < (width / 4); j++) {
			patt = 0;
			//Calculate the number of the pattern
			patt += grid[i + 1][j] * 1;
			patt += grid[i + 1][j + 1] * 2;
			patt += grid[i][j + 1] * 4;
			patt += grid[i][j] * 8;
			//Modifying the pixel matrix with the pattern
			for (x = 0; x < 4; x++) {
				for (y = 0; y < 4; y++) {
					m[4 * i + x][4 * j + y].r = patterns[patt][x][y];
					m[4 * i + x][4 * j + y].g = patterns[patt][x][y];
					m[4 * i + x][4 * j + y].b = patterns[patt][x][y];
				}
			}
		}
		patt = 0;
	}
	printf("Marching Squares aplicat cu succes [%d-%d]\n", height, width);
	//Empty the grid after use
	if (grid) {
		for (int i = 0; i < (height / 4) + 1; i++)
			free(grid[i]);
	    free(grid);
	}
}

int main(void)
{
	pixel **mat = NULL;
	int **grid = NULL;
	int height, width, value;
	char command[50];
	int patterns[16][4][4] = {{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
	{0, 0, 0, 0}},
	{{0, 0, 0, 0}, {0, 0, 0, 0}, {255, 0, 0, 0}, {180, 255, 0, 0}},
	{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 255}, {0, 0, 255, 180}},
	{{0, 0, 0, 0}, {0, 0, 0, 0}, {255, 255, 255, 255}, {180, 180, 180, 180}},
	{{0, 0, 255, 180}, {0, 0, 0, 255}, {0, 0, 0, 0}, {0, 0, 0, 0}},
	{{0, 0, 255, 180}, {0, 0, 0, 255}, {255, 0, 0, 0}, {180, 255, 0, 0}},
	{{0, 0, 255, 180}, {0, 0, 255, 180}, {0, 0, 255, 180}, {0, 0, 255, 180}},
	{{0, 255, 180, 180}, {255, 180, 180, 180}, {180, 180, 180, 180},
	{180, 180, 180, 180}},
	{{180, 255, 0, 0}, {255, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
	{{180, 255, 0, 0}, {180, 255, 0, 0}, {180, 255, 0, 0}, {180, 255, 0, 0}},
	{{180, 255, 0, 0}, {255, 0, 0, 0}, {0, 0, 0, 255}, {0, 0, 255, 180}},
	{{180, 180, 255, 0}, {180, 180, 180, 255}, {180, 180, 180, 180},
	{180, 180, 180, 180}},
	{{180, 180, 180, 180}, {255, 255, 255, 255}, {0, 0, 0, 0}, {0, 0, 0, 0}},
	{{180, 180, 180, 180}, {180, 180, 180, 180}, {180, 180, 180, 255},
	{180, 180, 255, 0}},
	{{180, 180, 180, 180}, {180, 180, 180, 180}, {255, 180, 180, 180},
	{0, 255, 180, 180}},
	{{255, 255, 255, 255}, {255, 255, 255, 255}, {255, 255, 255, 255},
	{255, 255, 255, 255}}}; //The 16 patterns

	while (1) {
		scanf("%s", command);//We read the command from stdin
		if (strcmp(command, "READ") == 0) {
			if (mat) {//We emty the pixel matrix
				for (int i = 0; i < height; i++)
					free(mat[i]);
				free(mat);
			}
			if (grid) {//We emty the pixel matrix
				for (int i = 0; i < (height / 4) + 1; i++)
					free(grid[i]);
				free(grid);
			} //Just in case we receiv the command READ multiple times
			read_img(&mat, &height, &width, &value);
		}
		if (strcmp(command, "WRITE") == 0)
			write_img(mat, height, width, value);
		if (strcmp(command, "RESIZE") == 0) {
			if (grid) {
				for (int i = 0; i < (height / 4) + 1; i++)
					free(grid[i]);
				free(grid);
			}
			resize_img(&mat, &height, &width, 4);
		}
		if (strcmp(command, "INIT_CONTUR") == 0)
			init_contur(patterns);
		if (strcmp(command, "GRID") == 0) {
			calculate_grid(mat, height, width, &grid, 1);
			if (!grid) {//Empty the grid after use
				for (int i = 0; i < (height / 4) + 1; i++)
					free(grid[i]);
				free(grid);
			}
		}
		if (strcmp(command, "MARCH") == 0)
			march(mat, grid, height, width, patterns);
		if (strcmp(command, "EXIT") == 0) {//Empty the matrix and the grid
			if (mat) {
				for (int i = 0; i < height; i++)
					free(mat[i]);
				free(mat);
			}
			if (grid) {
				for (int i = 0; i < (height / 4) + 1; i++)
					free(grid[i]);
				free(grid);
			}
			printf("Gigel a terminat\n"); return 0;
		}
	}
	return 0;
}

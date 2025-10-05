#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LMW 3
#define LCOMM 256
#define K 3
#define LP 20
#define LC 256
#define LFN 50
#define LSEL 4

//Define the structure to represent an image
typedef struct {
	char mw[LMW];
	int width, height, color, value;
	int ***pixels;
} I;

//Allocates memory for a matrix of pixels (3D)
int ***allocate(int height, int width, int color)
{
	int ***matrix = (int ***)malloc(height * sizeof(int **));
	if (!matrix) {
		fprintf(stderr, "Memory allocation failed\n");
		return NULL;
	}
	for (int i = 0; i < height; i++) {
		matrix[i] = (int **)malloc(width * sizeof(int *));
		if (!matrix[i]) {
			fprintf(stderr, "Memory allocation failed\n");
			for (int j = 0; j < i; j++) {
				free(matrix[j]);
			}
			free(matrix);
			return NULL;
		}
		for (int j = 0; j < width; j++) {
			matrix[i][j] = (int *)calloc(color, sizeof(int));
			if (!matrix[i][j]) {
				fprintf(stderr, "Memory allocation failed\n");
				//Free allocated memory in case of failure
				for (int k = 0; k < j; k++) {
					free(matrix[i][k]);
				}
				free(matrix[i]);
				for (int k = 0; k < i; k++) {
					for (int l = 0; l < width; l++) {
						free(matrix[k][l]);
					}
					free(matrix[k]);
				}
				free(matrix);
				return NULL;
			}
		}
	}
	return matrix;
}

void free_matrix(int ***matrix, int height, int width)
{
	if (!matrix)
		return;
	for (int i = 0; i < height; i++) {
		if (matrix[i]) {
			for (int j = 0; j < width; j++) {
				free(matrix[i][j]); // Free each channel array
			}
			free(matrix[i]); // Free each column array
		}
	}
	free(matrix); // Free top-level array
}

void free_image(I *img)
{
	if (img && (*img).pixels) {
		free_matrix((*img).pixels, (*img).height, (*img).width);
		(*img).pixels = NULL;
	}
}

void load_image(char *filename, I *img, int *selection)
{
	free_image(img); //Free any existing image memory
	FILE *file = fopen(filename, "rt");
	if (!file) {
		printf("Failed to load %s\n", filename); return;
	}
	if (fscanf(file, "%2s", (*img).mw) != 1 ||
		(strcmp((*img).mw, "P5") != 0 && strcmp((*img).mw, "P6") != 0 &&
		strcmp((*img).mw, "P2") != 0 && strcmp((*img).mw, "P3") != 0)) {
		printf("Failed to load %s\n", filename); return;
	}
	if (strcmp((*img).mw, "P3") == 0 || strcmp((*img).mw, "P6") == 0) {
		(*img).color = 3; // RGB
	} else {
		(*img).color = 1; // Greyscale
	}
	char verify_comment[LCOMM]; //Skip comments if any exists
	while (fgets(verify_comment, sizeof(verify_comment), file)) {
		if (verify_comment[0] != '#')
			break;
	} //If magic word is P2 or P3 the file is open as ASCII
	if (strcmp((*img).mw, "P2") == 0 || strcmp((*img).mw, "P3") == 0) {
		fscanf(file, "%d%d%d", &(*img).width, &(*img).height, &(*img).value);
		if ((*img).value > 255) {
			printf("Failed to load %s\n", filename); return;
		}
		fgetc(file); //Read newline character
		(*img).pixels = allocate((*img).height, (*img).width, (*img).color);
		if (!(*img).pixels) {
			fprintf(stderr, "Failed to allocate memory\n"); return;
		}
		for (int i = 0; i < (*img).height; i++) {
			for (int j = 0; j < (*img).width; j++) {
				for (int k = 0; k < (*img).color; k++) {
					if (fscanf(file, "%d", &(*img).pixels[i][j][k]) != 1) {
						fprintf(stderr, "Failed to read pixel data.\n");
						free_image(img); return;
					}
				}
			}
		}
	} else {
		fclose(file); //If magic word is P5 or P6 the file is open as binary
		file = fopen(filename, "rb");
		if (!file) {
			printf("Failed to load %s\n", filename); return;
		} //We reset the position to be able to read the dimensions
		fseek(file, strlen((*img).mw) + 1, SEEK_SET);
		fscanf(file, "%d%d%d", &(*img).width, &(*img).height, &(*img).value);
		if ((*img).value > 255) {
			printf("Failed to load %s\n", filename); return;
		}
		fgetc(file); //Read the newline character
		(*img).pixels = allocate((*img).height, (*img).width, (*img).color);
		if (!(*img).pixels) {
			fprintf(stderr, "Failed to allocate memory\n"); return;
		}
		for (int i = 0; i < (*img).height; i++) {
			for (int j = 0; j < (*img).width; j++) {
				for (int k = 0; k < (*img).color; k++) {
					if (fread(&(*img).pixels[i][j][k], 1, 1, file) != 1) {
						fprintf(stderr, "Failed to read pixel data.\n");
						free_image(img); return;
					}
				}
			}
		}
	}
	selection[0] = 0; selection[1] = 0; selection[2] = (*img).width;
	selection[3] = (*img).height; fclose(file);
	printf("Loaded %s\n", filename);
}

void select_region(I *img, int x1, int y1, int x2, int y2, int *selection)
{
	if (!(*img).pixels) {
		printf("No image loaded\n");
		return;
	}
	//We swap x1 and x2 if necessary
	if (x1 > x2) {
		int swap = x1;
		x1 = x2;
		x2 = swap;
	}
	//We swap y1 and y2 if necessary
	if (y1 > y2) {
		int swap = y1;
		y1 = y2;
		y2 = swap;
	}
	if (x1 < 0 || y1 < 0 || x2 > (*img).width || y2 > (*img).height) {
		printf("Invalid set of coordinates\n");
		return;
	}
	if (x1 == x2 || y1 == y2) {
		printf("Invalid set of coordinates\n");
		return;
	}
	//Set the selection
	selection[0] = x1;
	selection[1] = y1;
	selection[2] = x2;
	selection[3] = y2;
	printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
}

void select_all(I *img, int *selection)
{
	if (!(*img).pixels) {
		printf("No image loaded\n");
		return;
	}
	//Set the selection with the dimensions of the image
	selection[0] = 0;
	selection[1] = 0;
	selection[2] = (*img).width;
	selection[3] = (*img).height;
	printf("Selected ALL\n");
}

void histogram(I *img, int x, int y)
{
	if (!(*img).pixels) {
		printf("No image loaded\n");
		return;
	}
	//Ensure the image is in blask and white
	if ((*img).color != 1) {
		printf("Black and white image needed\n");
		return;
	}
	//Check if y respects the conditions given
	if (y < 2 || (y & (y - 1)) != 0 || y > 256) {
		printf("Invalid set of parameters\n");
		return;
	}
	int *histogram = calloc(y, sizeof(int));
	//Populate the histogram bins based on pixel intensity values
	for (int i = 0; i < (*img).height; i++) {
		for (int j = 0; j < (*img).width; j++) {
			int pixel = (*img).pixels[i][j][0];
			int bin = pixel / (256 / y);
			if (bin >= y)
				bin = y - 1;
			histogram[bin]++;
		}
	}
	//Find the maximum frexuency for scaling the histogram display
	int max_frequency = 0;
	for (int i = 0; i < y; i++) {
		if (histogram[i] > max_frequency) {
			max_frequency = histogram[i];
		}
	}
	//Display the histogram as a bar chart using *
	for (int i = 0; i < y; i++) {
		int stars = ((histogram[i] * 1.0) / (max_frequency * 1.0)) * x;
		printf("%d\t|\t", stars);
		for (int j = 0; j < stars; j++) {
			printf("*");
		}
		printf("\n");
	}
	free(histogram);
}

void equalize_image(I *img)
{
	if (!(*img).pixels) {
		printf("No image loaded\n");
		return;
	}
	//Ensure the image is in black and white
	if ((*img).color != 1) {
		printf("Black and white image needed\n");
		return;
	}
	//Compute the histogram
	int *histogram = calloc((*img).value + 1, sizeof(int));
	for (int i = 0; i < (*img).height; i++) {
		for (int j = 0; j < (*img).width; j++) {
			histogram[(*img).pixels[i][j][0]]++;
		}
	}
	//Calculate the total number of pixels in the image
	int total_pixels = (*img).width * (*img).height;
	//Compute the cumulative histogram
	int *acc_hist = calloc((*img).value + 1, sizeof(int));
	acc_hist[0] = histogram[0];
	for (int i = 1; i <= (*img).value; i++) {
		acc_hist[i] = acc_hist[i - 1] + histogram[i];
	}
	//Apply the histogram equalization transformation
	for (int i = 0; i < (*img).height; i++) {
		for (int j = 0; j < (*img).width; j++) {
			int pixel = (*img).pixels[i][j][0];
			int new_value = (int)round(((double)acc_hist[pixel] /
			total_pixels) * (*img).value);
			//Clamp function to ensure it remins within limits
			if (new_value < 0) {
				new_value = 0;
			} else if (new_value > (*img).value) {
				new_value = (*img).value;
			}
			//Update the pixel value
			(*img).pixels[i][j][0] = new_value;
		}
	}
	free(histogram);
	free(acc_hist);
	printf("Equalize done\n");
}

void rotate_image(I *img, int angle, int *select)
{
	int ***rotated;

	if (!(*img).pixels) {
		printf("No image loaded\n");
		return;
	}
	if (angle % 90 != 0) {
		printf("Unsupported rotation angle\n");
		return;
	}
	//Normalize the number of 90 degree rotation (0 - 3 rotations)
	int rotations = (angle / 90) % 4;
	if (rotations < 0)
		rotations += 4;
	int x1 = select[0], y1 = select[1];
	int x2 = select[2], y2 = select[3];
	//Rotate the entire image
	if (x1 == 0 && y1 == 0 && x2 == (*img).width && y2 == (*img).height) {
		for (int r = 0; r < rotations; r++) {
			rotated = allocate((*img).width, (*img).height, (*img).color);
			if (!rotated) {
				fprintf(stderr, "Memory allocation failed\n");
				return;
			}
			//Rotate by rearranging pixel positions
			for (int i = 0; i < (*img).height; i++) {
				for (int j = 0; j < (*img).width; j++) {
					for (int k = 0; k < (*img).color; k++) {
						int pixel = (*img).pixels[i][j][k];
						rotated[j][(*img).height - 1 - i][k] = pixel;
					}
				}
			}
			free_matrix((*img).pixels, (*img).height, (*img).width);
			(*img).pixels = rotated;
			//Swap image dimensions and update the selection
			int temp = (*img).width;
			(*img).width = (*img).height;
			(*img).height = temp;
			temp = select[0]; select[0] = select[1]; select[1] = temp;
			temp = select[2]; select[2] = select[3]; select[3] = temp;
		}
		printf("Rotated %d\n", angle);
		return;
	}
	//Rotate only a selected square region
	if ((x2 - x1) != (y2 - y1)) {
		printf("The selection must be square\n");
		return;
	}
	int size = x2 - x1; //Square selection
	for (int r = 0; r < rotations; r++) {
		int ***rotated = allocate(size, size, (*img).color);
		if (!rotated) {
			fprintf(stderr, "Memory allocation failed\n");
			return;
		}
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				for (int k = 0; k < (*img).color; k++) {
					int pixel = (*img).pixels[y1 + i][x1 + j][k];
					rotated[j][size - 1 - i][k] = pixel;
				}
			}
		}
		//Copy the rotated selection back into the original image
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				for (int k = 0; k < (*img).color; k++) {
					(*img).pixels[y1 + i][x1 + j][k] = rotated[i][j][k];
				}
			}
		}
		free_matrix(rotated, size, size);
	}
	printf("Rotated %d\n", angle);
}

void crop_image(I *img, int *selection)
{
	if (!(*img).pixels) {
		printf("No image loaded\n");
		return;
	}
	//Extract the coordinates of the selected region
	int x1 = selection[0];
	int y1 = selection[1];
	int x2 = selection[2];
	int y2 = selection[3];
	//Calculate the dimensions of the cropped area
	int new_width = x2 - x1;
	int new_height = y2 - y1;
	int ***cropped = allocate(new_height, new_width, (*img).color);
	if (!cropped) {
		fprintf(stderr, "Memory allocation failed\n");
		return;
	}
	//Copy the selected region's pixels into the new cropped image
	for (int i = 0; i < new_height; i++) {
		for (int j = 0; j < new_width; j++) {
			for (int k = 0; k < (*img).color; k++) {
				cropped[i][j][k] = (*img).pixels[y1 + i][x1 + j][k];
			}
		}
	}
	//Free memory of the original image
	if ((*img).pixels) {
		free_matrix((*img).pixels, (*img).height, (*img).width);
	}
	//Update the image structure with the cropped image details
	(*img).pixels = cropped;
	(*img).width = new_width;
	(*img).height = new_height;
	//Update the selection
	selection[0] = 0;
	selection[1] = 0;
	selection[2] = new_width;
	selection[3] = new_height;
	printf("Image cropped\n");
}

void apply_kernel(I *img, char *par, const int ker[K][K], int *selection)
{
	int i, j, k, idx, ki, kj, x1, x2, y1, y2, channels, width, height;

	if (!(*img).pixels) {
		printf("No image loaded\n");
		return;
	}
	//Ensure the image is color
	if ((*img).color != 3) {
		printf("Easy, Charlie Chaplin\n");
		return;
	}
	//Using shorter variables to respect coding style
	x1 = selection[0]; y1 = selection[1];
	x2 = selection[2]; y2 = selection[3];
	channels = (*img).color;
	width = (*img).width;
	height = (*img).height;
	int ***new_pixels = allocate((*img).height, (*img).width, channels);
	//Initialize the new_pixels with the original ones
	for (i = 0; i < (*img).height; i++) {
		for (j = 0; j < (*img).width; j++) {
			for (k = 0; k < channels; k++) {
				new_pixels[i][j][k] = (*img).pixels[i][j][k];
			}
		}
	}
	//Apply the kernel to the selected region of the image
	for (i = y1; i < y2; i++) {
		for (j = x1; j < x2; j++) {
			for (k = 0; k < channels; k++) {
				int new_value = 0;
				//Ensure the pixel is not at the edge of the image
				if (i > 0 && i < height - 1 && j > 0 && j < width - 1) {
					for (idx = 0; idx < 9; idx++) {
						ki = idx / 3 - 1;//Kernel row offset
						kj = idx % 3 - 1;//Kernel column offset
						int pixel = (*img).pixels[i + ki][j + kj][k];
						new_value += pixel * ker[ki + 1][kj + 1];
					}
					//Normalize the kernel effect  based on the parameter
					if (strcmp(par, "BLUR") == 0) {
						new_value /= 9.0;
					} else if (strcmp(par, "GAUSSIAN_BLUR") == 0) {
						new_value /= 16.0;
					}
					//Clamp function to ensure it remins within limits
					if (new_value > 255) {
						new_pixels[i][j][k] = 255;
					} else if (new_value < 0) {
						new_pixels[i][j][k] = 0;
					} else {
						new_pixels[i][j][k] = new_value;
					}
				}
			}
		}
	}
	free_matrix((*img).pixels, (*img).height, (*img).width);
	//Update the image
	(*img).pixels = new_pixels;
	printf("APPLY %s done\n", par);
}

void save_image(char *filename, const I *img, int ascii)
{
	if (!img || !(*img).pixels) {
		printf("No image loaded\n");
		return;
	}
	FILE *file = fopen(filename, "wt");
	//Determine the appropriate format based on "ascii"
	if (ascii == 1) {
		//Comvert binary into ASCII
		if (strcmp((*img).mw, "P5") == 0) {
			fprintf(file, "P2\n");
		} else if (strcmp((*img).mw, "P6") == 0) {
			fprintf(file, "P3\n");
		} else {
			fprintf(file, "%s\n", (*img).mw);
		}
	} else {
		//Convert ASCII into binary
		if (strcmp((*img).mw, "P2") == 0) {
			fprintf(file, "P5\n");
		} else if (strcmp((*img).mw, "P3") == 0) {
			fprintf(file, "P6\n");
		} else {
			fprintf(file, "%s\n", (*img).mw);
		}
	}
	//WWrite the data into file
	fprintf(file, "%d %d\n%d\n", (*img).width, (*img).height, (*img).value);
	//Write the pixels into file based on file's format
	if (ascii == 1) { //ASCII formal
		for (int i = 0; i < (*img).height; i++) {
			for (int j = 0; j < (*img).width; j++) {
				for (int k = 0; k < (*img).color; k++) {
					fprintf(file, "%d ", (*img).pixels[i][j][k]);
				}
			}
			//Newline after each row
			fprintf(file, "\n");
		}
	} else { //Binary format
		for (int i = 0; i < (*img).height; i++) {
			for (int j = 0; j < (*img).width; j++) {
				for (int k = 0; k < (*img).color; k++) {
					//Write pixel values as raw bytes
					fputc((*img).pixels[i][j][k], file);
				}
			}
		}
	}
	fclose(file);
	printf("Saved %s\n", filename);
}

void exit_function(I *img)
{
	if (!(*img).pixels) {
		printf("No image loaded\n");
		return;
	}
	free_image(img);
}

/*The function for precessing the command so
that the main function remains shorter and clear*/
void process_commands(I *img, int *selection)
{
	char filename[LFN], command[LC], param[LP] = "no parameter";
	int a, x1, y1, x2, y2, x, y, z, angle, ascii, ok = 1;

	while (ok) {
		fgets(command, sizeof(command), stdin);
		if (strncmp(command, "LOAD", 4) == 0) {
			a = sscanf(command + 5, "%s", filename);
			if (a == 1) { //If sscanf returns only one right value
				load_image(filename, img, selection);
			} else {
				printf("Invalid command\n");
			}
		} else if (strncmp(command, "SELECT ALL", 10) == 0) {
			select_all(img, selection);
		} else if (strncmp(command, "SELECT", 6) == 0) {
			a = sscanf(command + 7, "%d%d%d%d%d", &x1, &y1, &x2, &y2, &z);
			if (a == 4) {
				select_region(img, x1, y1, x2, y2, selection);
			} else {
				printf("Invalid command\n");
			}
		} else if (strncmp(command, "HISTOGRAM", 9) == 0) {
			a = sscanf(command + 10, "%d %d %d", &x, &y, &z);
			if (!(*img).pixels) {
				printf("No image loaded\n");
			} else if (a == 2) {
				histogram(img, x, y);
			} else {
				printf("Invalid command\n");
			}
		} else if (strncmp(command, "EQUALIZE", 8) == 0) {
			equalize_image(img);
		} else if (strncmp(command, "ROTATE", 6) == 0) {
			a = sscanf(command + 7, "%d", &angle);
			if (a == 1) {
				rotate_image(img, angle, selection);
			} else {
				printf("Invalid command\n");
			}
		} else if (strncmp(command, "CROP", 4) == 0) {
			crop_image(img, selection);
		} else if (strncmp(command, "APPLY", 5) == 0) {
			char *token  = strtok(command + 6, "\n");
			if (token)
				strncpy(param, token, sizeof(param) - 1);
			if (strcmp(param, "EDGE") == 0) {
				const int ek[K][K] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
				apply_kernel(img, param, ek, selection);
			} else if (strcmp(param, "SHARPEN") == 0) {
				const int sk[K][K] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
				apply_kernel(img, param, sk, selection);
			} else if (strcmp(param, "BLUR") == 0) {
				const int bk[K][K] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
				apply_kernel(img, param, bk, selection);
			} else if (strcmp(param, "GAUSSIAN_BLUR") == 0) {
				const int gk[K][K] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};
				apply_kernel(img, param, gk, selection);
			} else if (!(*img).pixels) {
				printf("No image loaded\n");
			} else if (strcmp(param, "no parameter") == 0) {
				printf("Invalid command\n");
			} else {
				printf("APPLY parameter invalid\n");
			}
		} else if (strncmp(command, "SAVE", 4) == 0) {
			ascii = strstr(command, "ascii") ? 1 : 0;
			if (ascii == 0)//Delete the possible newline added
				filename[sizeof(filename)] = '\0';
			if (sscanf(command + 5, "%s", filename) != 1) {
				printf("Invalid command\n");
				return;
			}
			save_image(filename, img, ascii);
		} else if (strncmp(command, "EXIT", 4) == 0) {
			exit_function(img); ok = 0;
		} else {
			printf("Invalid command\n");
		}
	}
}

int main(void)
{
	I img = {0};
	int selection[LSEL] = {0, 0, 0, 0};
	process_commands(&img, selection);
	return 0;
}

//Antemir Andreea-Catalina 314CA

The algorithm begins by declaring a structure in which 
we retain the rgb values of a pixel.

ALLOCATE_MATRIX function aims to dynamically allocate 
memory to a matrix.

The READ_IMG function aims to read from stdin an image 
of you PPM (pixel matrix), 
its type (P3), dimensions (height and width), and, and 
the maximum pixel value.
If the requirements of the statement are not met, then 
an error message is displayed and the program stops.

The WRITE_IMG function aims to display the pixel array 
in stdout with all its type, dimensions and maximum pixel value.

RESIZE_IMG function aims to resize the pixel array with 
a known factor = 4. For this we considered a new pixel array
that we subsequently allocated to the initial matrix (which 
we gave free previously because we no longer use it along the
way) to doesn't take up too much memory.

CALCULATE_GRID function has the role of calculating the grid of 
the matrix. To do this, we first check whether the current element 
is in the matrix, as for each of its neighbors. If this condition 
is met, the arithmetic mean is made which is then compared with a 
gamma value ( = 200). If the average is greater than 200, the element 
in the grid will take the value 1, and otherwise, 0. 
In this function I used a variable ok. This is to check where the 
calculated_grid function is called, because if it is called in the
march function, the grid should not be displayed in stdout.

The INIT_CONTUR function displays the 16 4x4 size templates.

The MARCH function has the role of modifying each 4x4 portion of the pixel 
matrix with a 16 template determined based on the binary values in the grid.
After we finish doing this, we release the memory of the grid.

In the main function we initialized the 16 templates displayed in init_contur 
and read from sdtin the command.

If the READ command is read several times, then before calling the
command-specific READ_IMG function, we release the memory of the grid and the
pixel matrix.

If the RESIZE command is read several times, then before calling the resize_img 
function, we release the grid memory because the matrix will be different, as
well as the grid. We do not release the matrix memory in the main function 
in case of resize command, because this is already done inside the resize_img
function.

When the exit command is read from the stdin, we release the memory used for 
the matrix and grid, display the requested message and stop the program.

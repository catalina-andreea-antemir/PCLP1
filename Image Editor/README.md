    To implement this code I decided to use a structure
in which to remember the data of an image, such as dimensions,
magic_word, pixel values and maximum pixel value. 
    Regarding memory, I have implemented 3 functions in order to
help me, named "allocate" which deals with memory allocation, 
"free_matrix", which deals with the release of memory given to the matrix
pixels and "free_image" dealing with the release of the granted memory of
the whole image, meaning the magic_word, the dimensions, the maximum value
and the pixel matrix.
    Follows the implementation of all functions required in the statement.
    The first function is "load_image" which deals with uploading an image
data, its absolute path is retained in "filename". In this
function I also check the possible comments by ignoring them in case they
are found. Here I check whether the given file is binary or ASCII type. I
figure out this thing based on the magic_word. So I open first
the ASCII file to read the magic_word, and then I will reopen
the file according to its type and read the data of the uploaded image.
Also here it is checked whether the image is black and white or color
based on the magic_word. This aspect is retained in the "color" variable.
If the image is color then the variable takes the value 3 because a
pixel retains the values RGB, and if the image is black and white then the
variable retains 1. At the end of the function, we set the selection on the
entire image so that we can achieve the other operations, since most are done
based on a selection.
    The second function is "select_region", and as the name says, it
deals with selecting a portion of the given image.
    The next function is "select_all" which deals with the selection of the
whole images.
    Then comes the "histogram". In this function is allocated memory for
a vector that will store the histogram, then go through all the pixels of
the image, determining the interval corresponding to each pixel based on
its intensity. Each interval is saved in the allocated histogram. After
the histograms calculation, I determine the maximum frequency (the maximum
number of pixels in a interval). The histogram is displayed in the form of
a bar graph, in which each the bar is represented by stars (*), and the
size of the bars is proportional with the frequency of each interval reported
at the maximum frequency. Finally, the memory allocated for the calculated
histogram is released to prevent leakage of memory.
    In the "equalize_image" function, a vector is created for the images
histogram, which contains the frequency of each intensity value.
The pixels of the image are also traversed and the frequency corresponding
to each intensity values are added. Then, the total number is calculated
based on its width and height, to normalize cumulative values in the following
steps. After that, it is created a vector for the cumulative histogram, which
is the cumulative sum of frequencies in the original histogram. Equalization
is done by calculating the new value of each pixel based on the cumulative
histogram, ensuring that it remains within the valid limits by the "clamp"
function. After the update of pixel value, the memory for the original and
cumulative histograms is released to prevent memory leakage.
    The next function is "rotate_image", in which it is performed
rotation based on a given angle (multiple of 90) of a square section or
of the whole picture. For a square selection, a temporary matrix is allocated
to store the pixels of the rotated selection. Pixels in the selected region are
moved to the appropriate locations in the temporary matrix, based on rotation
desired. Rotated pixels are copied back to the selected region of the original
image. Temporarily used memory is released. For rotation of the entire image,
the function allocates a temporary array to store the pixels of the rotated
image. The function scrolls through the pixels of the original image and
positions them in the corresponding locations in the rotated matrix, depending
on the required rotation. Image sizes are updated to reflect
changing orientation (width becomes height and vice versa). After each
rotation, the previously allocated memory is released.
    The "crop_image" function extracts the selection coordinates and calculates
dimensions of the cut-out area. It then allocates the memory needed for the
image cut and copy the selection pixels into the new matrix. Then release
the memory used by the original image and updates the image structure
to reflect the changes.
    The "apply_kernel" function applies the kernel only to the selected region.
For each pixel in the selected area, a new value is calculated using
the kernel. This process involves going through the neighbors of the central
pixel, according to the kernel, multiplication of neighboring pixel values by
coefficients corresponding to the kernel, the weighted amount of these products
that determines new value. If the parameter is "BLUR" or "GAUSSIAN_BLUR", the
value calculated is normalized by dividing by 9 or 16, respectively
adjust the kernel effect. The resulting values are limited to the valid range
[0, 255] using the "clamp" function. To prevent access to memory from
outside the image, the function excludes pixels on the edges (where the kernel
would exceed image limits).
    The "save_image" function deals with saving the image to another file. If
this command ends with "ascii" then it will save binary files as text.
Otherwise, if the file is text, it will be saved as binary type.
    The "exit_function" function deals with closing the program at the moment
inserting it from the keyboard.
    The "process_commands" function deals with checking the command and making
operations required for each command. This function has been implemented
to leave the main function more airy. Thus, if the "LOAD" command is inserted I
check if it is followed by a file. If not then it shows "Invalid command". In
case of meeting the "SELECT" command followed by 4 valid parameters it will
call the specific function, and otherwise will show "Invalid command". If the
"SELECT ALL" , "EQUALIZE", "CROP" or "EXIT" commands are inserted, then it will
call the specific function of each commands, and for "EXIT" it comes out
of the loop for reading. In the case of the  "HISTOGRAM" command is checked
if it is followed by 2 valid parameters. If so, it will call the function if
"Invalid command" is not displayed. The same is done in the case of the
"ROTATE" command, where it is checked first if followed by a parameter
representing the angle of rotation. In case of "APPLY" command, I check
the type of apply desired to be applied. Each type of apply function will be
given as a parameter one type of kernel with the values specific to the
parameter. For the "SAVE" command I check if it is followed by the name of a
file and if the word "ascii" exists at the end or not to convert from
ASCII to binary. If the file does not precede the command will display
"Invalid command" and in otherwise the function is called. If the command
is followed by the word "ascii" then remove the possible newline character
at the end of the file name. Here I used "sscanf" to check the case in which
is given from stdin more parameters then the command should have.
    In the "main" function, image data and selection are initialized, and then
the process_comands function is called.


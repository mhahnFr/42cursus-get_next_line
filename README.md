# Welcome to 42cursus-get_next_line!
This project is part of the 42cursus at the [42 school](https://www.github.com/42-Heilbronn). The idea behind the project is to read any file specified by its corresponding file descriptor line by line. As a bonus, one can also handle multiple file descriptors, so that the function can be called with one file descriptor, then with another one, and always be capable to get the next line of the specified file.

## Purpose of this repository
This repository showcases my own solutions, although I fixed a little detail in the bonus part, as it was a mistake which made me fail the bonus part at the [42 school](https://www.github.com/42-Heilbronn).

### Approach
The approach is object-orientied: A string-builder is taking care of the parts read from the file. When reading is finished, unnecessary parts are removed, the string-builder is also capable to determine its current size and to create a string representation. In the bonus part, another linked list holds the string-builders that are already in use. That way only that amount of memory that is strictly necessary is used.

## Usage
To use this function, simply use its makefile and include the ``get_next_line.h`` header in your project. You can change the size of the buffer in the makefile.

### Final notes
This repository shows my own solutions of the project at the 42 school, although they are a little bit edited to meet a better coding style.

© 2021 [mhahnFr](https://www.github.com/mhahnFr)
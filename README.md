# Welcome to 42cursus-get-next-line!
This project is part of the 42cursus at the 42 school. The idea behind the
project is to read any file specified by its corresponding file descriptor line
by line. As a bonus, one can also handle multiple file descriptors, so that the
function can be called with one file descriptor, then with another one, and
always be capable to get the next line of the specified file.

## Usage
To use this function, simply use its makefile and include the
``get_next_line.h`` header in your project. As of now, you also need to compile
your project with ``-D BUFFER_SIZE=XX``, as the header is using the buffer size
value.

### Final notes
This repository shows my own solutions of the project at the 42 school,
although they are a little bit edited to meet a better coding style.

© 2021 [mhahnFr](https://www.github.com/mhahnFr)
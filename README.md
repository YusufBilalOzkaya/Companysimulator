# Companysimulator
a simulator application project written with pure c language

📚 Libraries Used and Their Roles
The project is built using standard C libraries to ensure cross-platform compatibility and efficient resource management:

stdio.h (Standard Input/Output): Handles all console interactions, formatted printing, and file operations (File I/O) for saving reports.

stdlib.h (Standard Library): Facilitates Dynamic Memory Allocation via malloc() and free(), and manages process termination with exit() status codes.

math.h (Mathematical Functions): Used for complex financial modeling, specifically calculating exponential growth in taxes and branch costs using the pow() function.

string.h (String Handling): Performs safe memory copying (strcpy), length calculations (strlen), and buffer manipulation for dynamic string storage.


--------------(For users who do not wish to compile the source code, a pre-compiled .exe file is included within the project files)----------------

⚙️ Compilation and Installation
You can compile and run this project on any system with a C compiler (GCC, Clang, or MSVC).

🐧 Linux & 🍎 macOS
Open your terminal and use the following commands. Note that the -lm flag is required to link the math library.

Bash

# Compile the source code
gcc main.c -o CompanySimulator -lm

# Run the executable
./CompanySimulator
🪟 Windows
Option 1: Command Line (GCC/MinGW)

DOS

gcc main.c -o CompanySimulator.exe
CompanySimulator.exe
Option 2: IDE

Open main.c in Dev-C++, Code::Blocks, or Visual Studio.

Click Build & Run. (Make sure to link the math library in project settings if required).

MADE BY [Y.B.O]

# DollTor

DollTor is a simple command-line text editor written in C++. It allows users to edit and run code snippets in both C++ and Python directly from the terminal.

## Features

- Edit text files directly from the command line interface.
- Save and load files.
- Run code snippets as C++ or Python programs.
- Basic text editing commands (:q, :w, :b, :r, :h).

## Getting Started

### Prerequisites

- g++ compiler (for compiling C++ code)
- Python interpreter (for running Python code)
- C++17 or later support

### Installation

Clone the repository:

```bash
git clone https://github.com/dollengo/DollTor.git
cd DollTor
```

Compile and run the program:

```bash
./build_and_run.sh
```

### Usage

To open an existing text file or create a new one:

```bash
dolltor filename.txt
```

Once inside DollTor, you can edit the file:

```plaintext
Welcome to DollTor, your favorite text editor!
filename.txt
1 > Line 1
2 > Line 2
3 > :w  # Save the file
4 >
```

### Commands

- **`:q`**: Quit the editor.
- **`:w`**: Save and delete this part of the code that has `:w`.
- **`:b <num>`**: Go back `<num>` lines.
- **`:p`**: Print all entered lines.
- **`:r cpp`**: Run the code as C++.
- **`:r python`**: Run the code as Python.
- **`:h`**: Show all commands.

### Example Workflow

1. Edit the file:
   ```plaintext
   1 > #include <iostream>
   2 > using namespace std;
   3 > int main() {
   4 >     cout << "Hello, DollTor!" << endl;
   5 >     return 0;
   6 > }
   7 >
   ```

2. Save the file (`:w`) and run as C++ (`:r cpp`).

### Cleaning Up

DollTor cleans up temporary files automatically when quitting.

## Contributing

Feel free to fork this repository, make improvements, and submit pull requests. Contributions are welcome!

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Cross-Plataform
I'm not sure if it will be possible to run on Windows and MacOS on version 1.0.0 of DollTor.
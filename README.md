# MyFtp

## Overview
**myFTP** is an FTP server implemented in C, focusing on handling network communication via TCP sockets. The project requires implementing a basic FTP protocol while adhering to specific rules and constraints outlined below.

Bonuses include implementing an FTP client and enhancing the server for full RFC959 compliance.

Find out more information about the project at [Project PDF](./B-NWP-400_myFTP.pdf)

---

## Compilation
The project uses a Makefile for building and managing the binary. The following rules are available:
- **`make`**: Compiles the project.
- **`make re`**: Cleans and recompiles the project.
- **`make clean`**: Removes object files.
- **`make fclean`**: Removes binary and object files.

---

## Usage
``./myftp port path ``

 - port: Port number on which the server socket listens.
 - path: Path to the home directory for the Anonymous user.

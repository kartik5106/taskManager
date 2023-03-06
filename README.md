# taskManager
Network-Based Task Manager

The Network-Based Task Manager is a program that allows users to manage their tasks and projects over the network. Users can create and assign tasks to themselves or other users, set deadlines, and track progress. The program uses a client-server architecture built on C sockets to enable multiple users to access the task manager simultaneously, improving collaboration and productivity.

To run the program, you will need the following software installed on your computer:
 1.A C compiler (such as GCC)
 2.A Unix-like operating system (such as Linux or macOS)

Usage :
To use the program ,first compile the server and client in different terminals.
then run the server executable and subsequently run the client executable.

Terminal

Server:
    
    $ gcc server.c -o ser
    $ ./ser

Client:
    
    $ gcc client.c -o cli
    $ ./cli

Use the task manager using the onscreen instructions on the client side.

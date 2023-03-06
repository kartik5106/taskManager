#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8008

// Struct to represent a task
typedef struct Task
{
  int id;
  char *name;
  char *description;
  int priority;
  char *due_date;
} Task;

int main(int argc, char *argv[])
{
  int listenfd, connfd;
  struct sockaddr_in serv_addr, cli_addr;
  socklen_t clilen;
  char buffer[1024];
  int n;
  Task task;
  Task tasklist[10];
  int task_id = 0;

  // Create socket
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenfd < 0)
  {
    perror("Error opening socket");
    exit(1);
  }

  // Set server address
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(PORT);

  // Bind socket to address
  if (bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    perror("Error binding socket");
    exit(1);
  }

  // Listen for incoming connections
  listen(listenfd, 5);
  printf("Listening for connections on port %d...\n", PORT);

  while (1)
  {
    // Accept incoming connection
    clilen = sizeof(cli_addr);
    int option=1;
    connfd = accept(listenfd, (struct sockaddr *)&cli_addr, &clilen);
    setsockopt(connfd,SOL_SOCKET,SO_REUSEADDR,&option,sizeof(option));
    if (connfd < 0)
    {
      perror("Error accepting connection");
      continue;
    }
    printf("Connected to client at %s:%d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

    // Handle requests from client
    while (n = recv(connfd, buffer, 1024, 0)>0)
    {
    //  buffer[n] = '\0';
    // if(n = recv(connfd, buffer, 1024, 0)<0){
    //     printf("error in recievieng");  
    // }
      if (strcmp(buffer, "create") == 0)
      {
        // recv(connfd, &tasklist[task_id], sizeof(Task), 0);
        // tasklist[task_id].id = ++task_id;
        printf("user is creating a task\n");
        //   recv(connfd,buffer,sizeof(buffer),0);
        // send(connfd, "success", 7, 0);
      }
      else if (strcmp(buffer, "view") == 0)
      {
        // Send list of tasks to client
        // ...
        // send(connfd, "success", 7, 0);
        printf("user is viewing the task list\n");
        // Send each task to client
        // ...
      }
      else if (strcmp(buffer, "edit") == 0)
      {
        // Receive task data from client
        // recv(connfd, &task, sizeof(Task), 0);
        printf("user is editing a task\n");

        // Update task in task list
        // ...
        // send(connfd, "success", 7, 0);
      }
      else if (strcmp(buffer, "delete") == 0)
      {
        // Receive task ID from client
        // recv(connfd, &task.id, sizeof(int), 0);
        // Delete task from task list
        // ...
        // send(connfd, "success", 7, 0);
      }
    }

    // Close connection
    close(connfd);
    printf("Disconnected from client at %s:%d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
  }

  return 0;
}

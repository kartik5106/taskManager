#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8008

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
// Function to perform Selection Sort
void selectionSort(int arr[], int n)
{
    int i, j, min_idx;
 
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++) {
 
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
 
        // Swap the found minimum element
        // with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}

typedef struct Task
{
    int id;
    char name[50];
    char description[100];
    int priority;
    char due_date[30];
} Task;

int main()
{

    int sockfd;
    struct sockaddr_in serv_addr;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error opening socket");
        exit(1);
    }

    // Set server address
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    // serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error connecting to server");
        exit(1);
    }

    printf("Connected to server\n");

    int choice;
    Task task;
    int task_id = 0;
    int i = 0;
    Task tasklist[10];
    while (1)

    {
        printf("\nTask Manager\n");
        printf("1. Create Task\n");
        printf("2. View Tasks\n");
        printf("3. Edit Task\n");
        // printf("4. View priority wise\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        int n;
            if(n=send(sockfd, "create", 7 , 0)<0)
            {
                printf("data not sent");
            }
            else{
            // recv task data from user
            printf("Enter task name: ");
            scanf("%s", task.name);
            // task.name = strdup(buffer);
            printf("Enter task description: ");
            scanf("%s", task.description);
            // task.description = strdup(buffer);
            printf("Enter task priority (1-5): ");
            scanf("%d", &task.priority);
            printf("Enter task due date (mm/dd/yyyy): ");
            scanf("%s", task.due_date);
            // task.due_date = strdup(buffer);
            // printf("Enter task ID : ");
            // scanf("%d", &task.id);
            task.id=task_id;

            tasklist[task_id]=task;

            task_id++;
            printf("Task created successfully\n");
            }
            break;
        case 2:

            // 	  int i = 0;
            if(n=send(sockfd, "view", 5, 0)<0)
            {
                printf("data not sent");
            }
            printf("ID  Name        Description               Priority  Due Date\n");
            printf("--------------------------------------------------------------\n");
            int c=0;
            while(c<task_id)
            {

            printf("%-3d %-10s %-25s %-9d %s\n", tasklist[c].id+1,
                   tasklist[c].name, tasklist[c].description,
                   tasklist[c].priority, tasklist[c].due_date);

            c++;

            }
            break;

        case 3:
            //edit task

            int ed;
            printf("Enter the Task id to be edited");
            scanf("%d",&ed);
            
            Task task1;
            printf("Enter task name: ");
            scanf("%s", task1.name);
            // task.name = strdup(buffer);
            printf("Enter task description: ");
            scanf("%s", task1.description);
            // task.description = strdup(buffer);
            printf("Enter task priority (1-5): ");
            scanf("%d", &task1.priority);

            printf("Enter task due date (mm/dd/yyyy): ");
            scanf("%s", task1.due_date);

            tasklist[ed]=task1;
            break;
        // case 4:
        //     int temp[10];
        //     for (int k = 0; k < task_id; k++)
        //     {
        //         temp[k]=tasklist[k].priority;
        //     }
        //     int size=sizeof(temp)/sizeof(temp[0]);

        //     selectionSort(temp,size);

        //     int arr_Id[15],k=0,j=0;

        //     while(k<size){
        //     while(j<=task_id){
        //         if(temp[k]==tasklist[j].priority)
        //         {
        //             arr_Id[k]=j;
        //             k++;
        //         }
        //         j++;
        //     }
        //     }

        //     for (int o = 0; o < size; o++)
        //     {
        //         printf(" %d ",arr_Id[o]);
        //     }
            
        //     break;
        case 4:
            close (sockfd);
            printf("Disconnected from server\n");
            exit (0);
            break;

        default:
            printf("Invalid choice\n");
            break;
        }
    }
}

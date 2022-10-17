#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define TRUE 1
#define SERVER_IP_ADDRESS "0.0.0.0"
#define SERVER_PORT 1234  //while using wireshart, set the filter to tcp port with this server number
#define RECEIVE_BUFFER_SIZE 1024

int main(int argc, char const *argv[]) 
{
  struct sockaddr_in server;//server socket endpoint
  struct sockaddr_in client;//client socket endpoint
  char receive_buffer[RECEIVE_BUFFER_SIZE];

  int serverFd = socket(AF_INET, SOCK_STREAM, 0);

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS);
  server.sin_port = htons(SERVER_PORT);

  //bind the server file descriptor to the server socket endpoint
  bind(serverFd, (struct sockaddr *)&server, sizeof(struct sockaddr_in));
  //listen to 10 clients simutaneously
  listen(serverFd, 10);
 
  while (TRUE) 
  {
    printf("Waiting for client connection...\n");
    
    socklen_t sock_len = sizeof(struct sockaddr_in);

    //file descriptor of client socket returned from the client socket endpoint - used to communicate with the client
    int clientFd = accept(serverFd, (struct sockaddr *)&client, &sock_len);

    //getting the client ip
    char *client_ip = inet_ntoa(client.sin_addr);

    //client.sin_port - temp port just for the current communication channel
    printf("Accepted connection: %s:%d\n", client_ip, ntohs(client.sin_port));

    memset(receive_buffer, 0, sizeof(receive_buffer));

    //read message sent from the client
    int size = read(clientFd, receive_buffer, sizeof(receive_buffer));

    printf("Client message received: %s \n", receive_buffer);

    //send the message we just read back to the client
    write(clientFd, receive_buffer, size);

    close(clientFd);
  }

  close(serverFd);

  return 0;
}

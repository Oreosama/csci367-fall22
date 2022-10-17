#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP_ADDRESS "127.0.0.1"
#define SERVER_PORT 1234
#define RECEIVE_BUFFER_SIZE 1024

const char message[] = "Hello!\n";

int main(int argc, char const *argv[]) 
{
  struct sockaddr_in server;

  int file_desc = socket(AF_INET, SOCK_STREAM, 0);

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS);
  server.sin_port = htons(SERVER_PORT);

  char *server_ip = inet_ntoa(server.sin_addr);

  printf("Connecting to: %s:%d\n", server_ip, ntohs(server.sin_port));

  int result = connect(file_desc, (struct sockaddr *)&server, sizeof(struct sockaddr_in));

  char *client_ip = inet_ntoa(server.sin_addr);

  printf("Client IP and Port: %s:%d\n", client_ip, ntohs(server.sin_port));
  
  /*write/send message to the server*/
  int byte_count = write(file_desc, message, strlen(message));

  char receive_buffer[RECEIVE_BUFFER_SIZE];

  memset(receive_buffer, 0, sizeof(receive_buffer));

  /*read response from the server*/
  byte_count = read(file_desc, receive_buffer, sizeof(receive_buffer));
  
  /*close socket after receiving the message*/
  close(file_desc);

  printf("Server response: %s \n", receive_buffer);


  return 0;
}

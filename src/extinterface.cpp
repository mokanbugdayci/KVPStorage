// /**
//  * @file extinterface.cpp
//  * @author your name (you@domain.com)
//  * @brief 
//  * @version 0.1
//  * @date 2022-03-27
//  * 
//  * @copyright Copyright (c) 2022
//  * 
//  */

// #include <sys/socket.h>
// #include <arpa/inet.h>
// #include <unistd.h>
// #include <netinet/in.h>
// #include <stdlib.h>
// #include <iostream>
// #include <string>
// #include <string.h>
// #include <stdio.h>
// #include "../inc/extinterface.h"

// #include <thread>

// #define PORT 1024

// struct arg_struct
// {
//    int arg1;
//    int arg2;
// } *args;


// void* func(void* arg)
// {
//       int new_socket, valread;
//       struct sockaddr_in address;
//       int addrlen = sizeof(address);
//       char buffer[1024] = {0};
//       char *hello = "Hello from server";

//       // detach the current thread
//       // from the calling thread
//       pthread_detach(pthread_self());

//       printf("Inside the thread\n");

//       printf("socket is listening...\n");

//       new_socket = ((struct arg_struct*)args)->arg1;

//       while(read( new_socket, buffer, 1024) != -1)
//       {
//             printf("wait for read...\n");
//             // valread = ;
//             // if(valread == -1)
//             // {
//             //       printf("close socket\n");
//             //       //pthread_exit(NULL);
//             // }
//             printf("%s\n",buffer );
//             send(new_socket , hello , strlen(hello) , 0 );
            
//             printf("Hello message sent\n");
//             // close(sock->server_fd);
//       }
  
// //     // exit the current thread
// //     pthread_exit(NULL);
// }

// /**
//  * @brief Construct a new Extinterface:: Extinterface object
//  * 
//  */
// Extinterface::Extinterface()
// {
      // int new_socket, valread;
      // pthread_t tid;
      // struct sockaddr_in address;
      // int opt = 1;
      // int addrlen = sizeof(address);
      // char buffer[1024] = {0};
      // args = (struct arg_struct*)malloc(sizeof(struct arg_struct) * 1);

      // // Creating socket file descriptor
      //  printf("socket is creating...\n");
      // if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
      // {
      //       printf("socket failed\n");
      // }
      // else
      //       printf("socket is created\n");
      
      // // Forcefully attaching socket to the port 8080#include <string>
      // if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
      // {
      //       printf("setsockopt\n");
      // }

      // address.sin_family = AF_INET;
      // address.sin_addr.s_addr = INADDR_ANY;
      // address.sin_port = htons( PORT );
      
      // printf("socket is binding...\n");
      // // Forcefully attaching socket to the port 8080
      // if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
      // {
      //       printf("bind failed\n");
      // }
      // else 
      //       printf("socket is binded\n");

      // if (listen(server_fd, 10) < 0)
      // {
      //       printf("listen\n");
      // }

      // while(1)
      // {
      //       printf("connection is accepting...\n");

      //       if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
      //                         (socklen_t*)&addrlen)) > -1)
      //       {
      //             args->arg1 = new_socket;
      //             printf("accept\n");
      //             pthread_create(&tid, NULL, &func, args);
      //             //pthread_join(tid, NULL);
      //       }
      // }
      // printf("exit\n");

// }
/**
 * @file application.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <algorithm>
// #include <pthread.h>
#include <thread>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <mutex>

#include "../inc/storage.h"
#include "../inc/parser.h"
#include "../inc/extinterface.h"
#include "../inc/application.h"



#define PORT 1024

struct arg_struct
{
   int arg1;
   int arg2;
} *args;

std::mutex parserMutex;

/**
 * @brief 
 * 
 * @param args 
 */
void kvpApp(std::string &inputOutputBuff)
{
      Parser *parser = new Parser;
      // ParserObj *parserObj = new ParserObj;
      Storage *kvpStorage = new Storage;

      
      if(parser->inputParser(inputOutputBuff))//, parserObj))
      {
            parserMutex.lock();
            switch(parser->getCommand())
            {
                  case Parser::CMD_SET_KV:
                        if(kvpStorage->setRecord(parser->getKey(), parser->getValue()))
                              inputOutputBuff = "OK";
                        else
                              inputOutputBuff = "";                              
                        break;

                  case Parser::CMD_GET_KV:
                        inputOutputBuff = kvpStorage->getRecord(parser->getKey());
                        break;

                  case Parser::CMD_DELETE_KV:
                        if(kvpStorage->deleteRecord(parser->getKey()))
                              inputOutputBuff = "OK";
                        else
                              inputOutputBuff = "";
                        break;

                  default:
                        break;
                  // case ParserObj::CMD_SET_KV:
                  //       if(kvpStorage->setRecord(parserObj->getKey(), parserObj->getValue()))
                  //             std::cout << "OK" << std::endl;
                  //       else
                  //             std::cout << " " << std::endl;                               
                  //       break;

                  // case ParserObj::CMD_GET_KV:
                  //       std::cout << kvpStorage->getRecord(parserObj->getKey()) << std::endl;
                  //       break;

                  // case ParserObj::CMD_DELETE_KV:
                  //       if(kvpStorage->deleteRecord(parserObj->getKey()))
                  //             std::cout << "OK" << std::endl;
                  //       else
                  //             std::cout << " " << std::endl; 
                  //       break;

                  // default:
                  //       break;
            }
            parserMutex.unlock();

            inputOutputBuff += "\n";
      }
      else
      {
            //inputOutputBuff.clear();
      }

      delete parser;
      delete kvpStorage;
}

/**
 * @brief 
 * 
 * @param args 
 */
void cliInterfaceApp(void *args)
{
      std::string input;

      // Parser *parser = new Parser;
      // // ParserObj *parserObj = new ParserObj;
      // Storage *kvpStorage = new Storage;

      while(input != "q")
      {
            std::cout << "> ";
            std::getline(std::cin, input);

            std::thread cliThread(kvpApp, std::ref(input));
            cliThread.join();

            std::cout << input;
      }
}

// void* func(void* arg)
// {
//       int new_socket, valread;
//       struct sockaddr_in address;
//       int addrlen = sizeof(address);
//       char buffer[1024] = {0};
//       char *hello = "Hello from server";

//       // detach the current thread
//       // from the calling thread
//       //pthread_detach(pthread_self());

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


/**
 * @brief 
 * 
 * @param args 
 */
void extInterfaceApp(void *args_from_main_thr)
{
      // Extinterface *sock = new Extinterface();

      int new_socket, valread, server_fd;
      struct sockaddr_in address;
      int opt = 1;
      int addrlen = sizeof(address);
      char buffer[1024] = {0};
      args = (struct arg_struct*)malloc(sizeof(struct arg_struct) * 1);

      // Creating socket file descriptor
      //  printf("socket is creating...\n");
       server_fd = socket(AF_INET, SOCK_STREAM, 0);
      if(server_fd == -1)
      {
            // printf("socket failed\n");
      }
      else
            // printf("socket is created\n");
      
      // Forcefully attaching socket to the port 
      if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
      {
            // printf("setsockopt\n");
      }

      address.sin_family = AF_INET;
      address.sin_addr.s_addr = INADDR_ANY;
      address.sin_port = htons( PORT );
      
      // Forcefully attaching socket to the port 8080
      if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
      {
            // printf("bind failed\n");
      }
      else 
            // printf("socket is binded\n");

      if (listen(server_fd, 5) < 0)
      {
            // printf("listen\n");
      }

      while(1)
      {
            if((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) >= 0)
            {
            //      new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
                  // args->arg1 = new_socket;
                  // printf("accept\n");
                  // std::thread socketThread();
                  // pthread_create(&tid, NULL, &func, args);
                  //pthread_join(tid, NULL);
            }

            while(read( new_socket, buffer, 1024) > 0)
            {
                  std::string input(buffer);
                  std::thread socketThread(kvpApp, std::ref(input));
                  socketThread.join();
                  send(new_socket, input.c_str(), input.size(), 0);
                  memset(buffer, 0, sizeof(buffer));
            }            
      }
      printf("exit\n");     
}
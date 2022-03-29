/**
 * @file application.cpp
 * @author M. Okan Bugdayci
 * @brief 
 * @version 0.1
 * @date 2022-03-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
/* Std libraries */
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <mutex>

/* User headers */
#include "../inc/storage.h"
#include "../inc/parser.h"
#include "../inc/application.h"

/* socket port */
#define PORT 1024 

std::mutex parserMutex;

/**
 * @brief 
 * 
 * @param args 
 */
void kvpApp(std::string &inputOutputBuff)
{
      Parser *parser = new Parser;
      Storage *kvpStorage = new Storage;

      if(parser->inputParser(inputOutputBuff))
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
            }
            parserMutex.unlock();

            inputOutputBuff += "\n";
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

      while(input != "q")
      {
            std::cout << "> ";
            std::getline(std::cin, input);

            std::thread cliThread(kvpApp, std::ref(input));
            cliThread.join();

            std::cout << input;
      }
}


/**
 * @brief 
 * 
 * @param args 
 */
void extInterfaceApp(void *args_from_main_thr)
{
      int socketFd, opt = 1;

      //Creating socket file descriptor
      socketFd = socket(AF_INET, SOCK_STREAM, 0);
      if(socketFd == -1)
      {
            exit(-1);
      }
      
      // Forcefully attaching socket to the port 
      if(setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
      {
            exit(-1);
      }

      struct sockaddr_in socketAddress;
      int addresLen = sizeof(socketAddress);
      socketAddress.sin_family = AF_INET;
      socketAddress.sin_addr.s_addr = INADDR_ANY;
      socketAddress.sin_port = htons(PORT);
      
      // attaching socket to the port
      bind(socketFd, (struct sockaddr *)&socketAddress, addresLen);
      listen(socketFd, 5);

      int newSocket;
      char buffer[1024] = {0};

      while(1)
      {
            newSocket = accept(socketFd, (struct sockaddr *)&socketAddress, (socklen_t*)&addresLen);

            while(read(socketFd, buffer, 1024) > 0)
            {
                  std::string input(buffer);
                  std::thread socketThread(kvpApp, std::ref(input));
                  socketThread.join();
                  send(newSocket, input.c_str(), input.size(), 0);
                  memset(buffer, 0, sizeof(buffer));
            }            
      }     
}
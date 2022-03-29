/**
 * @file main.cpp
 * @author M. Okan Bugdayci
 * @brief 
 * @version 0.1
 * @date 2022-03-26
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
#include <thread>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

#include "../inc/storage.h"
#include "../inc/parser.h"
#include "../inc/application.h"

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char **argv)
{
      int test = 0;
      std::thread kvpCliThread(cliInterfaceApp, &test);
      std::thread kvpExtThread(extInterfaceApp, &test);

      kvpCliThread.join();
      kvpExtThread.join();

      // Extinterface *sock = new Extinterface();

      return 0;
}


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


#include <thread>

#include "../inc/main.h"
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
      std::thread kvpCliThread(cliInterface, &argc); //, &test);
      std::thread kvpExtThread(extInterface, &argc);

      kvpCliThread.join();
      kvpExtThread.join();

      return 0;
}


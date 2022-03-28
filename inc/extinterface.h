/**
 * @file extinterface.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _EXTINTERFACE_H_
#define _EXTINTERFACE_H_

#include <string>


#include "../inc/parser.h"

class Extinterface : public Parser
{

      public:
            int server_fd;
            Extinterface();
            ~Extinterface();

};


#endif  //_EXTINTERFACE_H_
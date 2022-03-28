/**
 * @file parser.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>

class ParserObj
{
      public:
            typedef enum
            {
                  CMD_NULL,
                  CMD_GET_KV,
                  CMD_SET_KV,
                  CMD_DELETE_KV
            }Commands_t;

            std::string getKey() {return params[0];}
            std::string getValue() {return params[1];}
            Commands_t getCommand() { return cmd;}
            void setKey(std::string& k) {params[0] = k;}
            void setValue(std::string& v) {params[1] = v;}
            void setCommand(Commands_t c) {cmd = c;}
            void setParam(int i, std::string v) {params[i] = v;}

      private:
            std::string params[2];
            Commands_t cmd;
};

class Parser : public ParserObj
{
      public:
            
            typedef enum
            {
                  ERR_INVALID_CMD,
                  ERR_WRONG_NUM_OF_ARG,
                  ERR_INVALID_KEY
            }Error_t;
            
            Parser();
            ~Parser();
            bool inputParser(std::string& input);
            // bool inputParser(std::string& input, ParserObj *output);       

      private:
            std::string errorMessage(Error_t err_code);
};


#endif  //_PARSER_H_
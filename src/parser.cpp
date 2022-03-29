/**
 * @file parser.cpp
 * @author M. Okan Bugdayci
 * @brief 
 * @version 0.1
 * @date 2022-03-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "../inc/parser.h"

/* Command - Argument table. number of argument for eac comment and numerical value of command mapped */
const std::map<std::string, std::map<int, ParserObj::Commands_t>> commandTable =
{     
/*    {"Cmd String",    {{Number of cmd's argument,   cmd's numeric value}}} */
      {"GET",           {{1,                          ParserObj::CMD_GET_KV}}},
      {"SET",           {{2,                          ParserObj::CMD_SET_KV}}},
      {"DELETE",        {{1,                          ParserObj::CMD_DELETE_KV}}}
};

/**
 * @brief Construct a new Parser:: Parser object
 * 
 */
Parser::Parser()
{
}

/**
 * @brief Destroy the Parser:: Parser object
 * 
 */
Parser::~Parser()
{
}

/**
 * @brief 
 * 
 * @param input 
 * @return true 
 * @return false 
 */
bool Parser::inputParser(std::string& input)
{
      int argument_counter = 0;
      std::string cmd_str, temp;
      std::vector<std::string> arguments;

      /* Parse line to words */
      std::stringstream words(input);

      //first check the command. accept commands non-case sensitive.
      words >> cmd_str;
      std::transform(cmd_str.begin(), cmd_str.end(), cmd_str.begin(), ::toupper);

      while(words >> temp)
      {
            arguments.push_back(temp);
            argument_counter++;
      }

      /* Iterate on command items table to obtain command and its arguments */
      for (auto const& cmdItemOnTable : commandTable)
      {
            /* Compare input cmd with table. if cmd is not available return false and print error message */
            if(cmd_str == cmdItemOnTable.first) 
            {
                  /* Iterate command parameters (number of argument for cmd and numeric value of cmd) */
                  for(auto const& cmdParamsOnTable : cmdItemOnTable.second)
                  {
                        /* Argument counter must be equal to number of argument for cmd */
                        if(cmdParamsOnTable.first == argument_counter)
                        {
                              /* Set numeric value of cmd in parserObj */
                              setCommand(cmdParamsOnTable.second);

                              /* Set key-value pairs in parserObj */
                              for(int i = 0; i < argument_counter; i++)
                              {
                                    setParam(i, arguments[i]);

                                    /* pucntuation check. do not allow the punctuations as a key by theirselves */
                                    if(i == 0)
                                    {
                                          arguments[0].erase (std::remove_if (arguments[0].begin(), arguments[0].end(), ispunct), arguments[0].end());
                                          if(arguments[0].empty())
                                          {
                                                errorMessage(ERR_INVALID_KEY);
                                                return false;
                                          }
                                    }
                              }

                              return true;   
                        }
                        else
                        {
                              input = errorMessage(ERR_WRONG_NUM_OF_ARG);
                              return false;
                        }
                  }
            }
      }

      input = errorMessage(ERR_INVALID_CMD);
      return false; 
}


/**
 * @brief 
 * 
 * @param err_code 
 * @return std::string 
 */
std::string Parser::errorMessage(Error_t err_code)
{
      std::string error_str;
      switch(err_code)
      {
            case ERR_INVALID_CMD:
                  error_str = "(Error) Invalid command";
                  break;
            case ERR_WRONG_NUM_OF_ARG:
                  error_str = "(Error) Wrong number of arguments for command";
                  break;
            case ERR_INVALID_KEY:
                  error_str = "(Error) Invalid key";
                  break;
            default:
                  break;
      }

      return error_str += "\n";

}
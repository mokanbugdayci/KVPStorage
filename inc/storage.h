/**
 * @file storage.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _STORAGE_H_
#define _STORAGE_H_

#include <string>


class Storage 
{
      public:
            typedef enum
            {
                  ERR_KEY_NOT_FOUND,
                  ERR_DB_NOT_ACCESSABLE,
            }Error_t;
            
            Storage();
            ~Storage();

            std::string getRecord(std::string const &key);
            bool setRecord(std::string const &key, std::string const &value);
            bool deleteRecord(std::string const &key);

      private:
            void errorMessage(Error_t err_code);
};


#endif  //_STORAGE_H_
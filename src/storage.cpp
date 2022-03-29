/**
 * @file storage.cpp
 * @author your name (you@domain.com)
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
#include <string>

#include "../inc/storage.h"

const std::string storageFileName = "./kvpDataBase";
const std::string tempResultFileName = "./kvpTempResult";
const std::string delimiter = " ";

/**
 * @brief Construct a new Storage:: Storage object
 * 
 */
Storage::Storage()
{

}

Storage::~Storage()
{
}

/**
 * @brief 
 * 
 * @param err_code 
 */
void Storage::errorMessage(Error_t err_code)
{
      switch(err_code)
      {
            case ERR_KEY_NOT_FOUND:
                  std::cout << "(Null) Not found" << std::endl;
                  break;
            case ERR_DB_NOT_ACCESSABLE:
                  std::cout << "(Error) Storage is not accesable" << std::endl;
                  break;
            default:
                  break;
      }
}


/**
 * @brief 
 * 
 * @param key 
 * @return std::vector<std::string> 
 */
std::string Storage::getRecord(std::string const &key)
{
      std::string record;
      std::string bashCmd = "grep -n \"" + key + delimiter + "\" " + storageFileName + " | awk -F  \""+ delimiter + "\" '{print $2}' >> " + tempResultFileName;

      std::ifstream tempResultFile;

      system((char*)bashCmd.c_str());

      tempResultFile.open(tempResultFileName);

      if(tempResultFile.is_open())
      {
            std::getline(tempResultFile, record);
      }
      else
            errorMessage(ERR_DB_NOT_ACCESSABLE);

      tempResultFile.close();
      
      bashCmd = "rm -f " + tempResultFileName; 
      system((char*)bashCmd.c_str());

      return record;
}

/**
 * @brief 
 * 
 * @param key 
 * @param value 
 * @return true 
 * @return false 
 */
bool Storage::setRecord(std::string const &key, std::string const &value)
{
      deleteRecord(key);
      std::string bashCmd = "echo \"" + key + delimiter + value + "\" >> " + storageFileName; 

      system((char*)bashCmd.c_str());

      return true;
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */

bool Storage::deleteRecord(std::string const &key)
{
      std::string tempRecord = getRecord(key);
      
      if(tempRecord.empty())
      {
            return false;
      }

      std::string bashCmd = "sed -i '/" + key + delimiter + "/d' " + storageFileName;
      system((char*)bashCmd.c_str());

      return true;
}
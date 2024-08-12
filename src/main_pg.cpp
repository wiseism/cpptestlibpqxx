//
// Created by edidada on 2020/5/28.
//
#include <iostream>
#include <pqxx/pqxx>

using namespace pqxx;

int main(int argc, char* argv[])
{
    try{
        connection C("dbname=test user=postgres password=5Edidada \
      hostaddr=127.0.0.1 port=5432");
        if (C.is_open()) {
            std::cout << "Opened database successfully: " << C.dbname() << std::endl;
        } else {
            std::cout << "Can't open database" << std::endl;
            return 1;
        }
        C.close();
    }catch (const std::exception &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

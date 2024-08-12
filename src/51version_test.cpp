//
// Created by edidada on 2020/5/28.
//
#include <iostream>
#include <pqxx/pqxx>

int main()
{
    try
    {
        pqxx::connection C("dbname=test user=postgres password=5Edidada \
      hostaddr=127.0.0.1 port=5432");
        std::cout << "Connected to " << C.dbname() << std::endl;
        pqxx::work W(C);

        pqxx::result R = W.exec("SELECT name FROM user_tbl");

        std::cout << "Found " << R.size() << " in table user_tbl:" << std::endl;
        for (auto row: R)
            std::cout << row[0].c_str() << std::endl;

        std::cout << "Doubling all employees' salaries..." << std::endl;
        W.exec("UPDATE user_tbl SET salary=salary*2");

        std::cout << "Making changes definite: ";
        W.commit();
        std::cout << "ok." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

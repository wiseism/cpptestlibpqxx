//
// Created by edidada on 2020/5/28.
//
#include <iostream>
#include <pqxx/pqxx>

int main(int, char *argv[])
{
    pqxx::connection c("dbname=test user=postgres password=5Edidada \
      hostaddr=127.0.0.1 port=5432");
    pqxx::work txn(c);

    // Query the DB using txn.exec().
    // Here, we expect exactly one result row, so we use
    // exec1() instead.  It checks that we get exactly one
    // row (throwing an exception otherwise), and returns that
    // row, instead of a full result set.
    // As of libpqxx 7.x, you'd just use query_value<int>() for
    // this simple case.
    pqxx::row r = txn.exec(
            "SELECT id "
            "FROM user_tbl "
            "WHERE name =" + txn.quote(argv[1]));

    // We can address the first field in the row as r[0].
    // The column's name would also work, but be less
    // efficient: r["id"].
    // The field's as<type>() method converts the field's
    // string value to a type of our choice.
    int employee_id = r[0].as<int>();

    std::cout << "Updating employee #" << employee_id << std::endl;

    // Update the employee's salary.
    // Here we use exec0() to say that we expect an empty
    // result.  If the result does contain data, it will
    // throw an exception.
    txn.exec(
            "UPDATE EMPLOYEE "
            "SET salary = salary + 1 "
            "WHERE id = " + txn.quote(employee_id));

    // Make our change definite.
    txn.commit();
}

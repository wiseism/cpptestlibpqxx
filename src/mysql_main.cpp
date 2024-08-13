#include <mysql.h>
#include <iostream>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // 初始化MySQL连接
    conn = mysql_init(NULL);

    // 连接到MySQL服务器
    if (!mysql_real_connect(conn, "localhost", "your_username", "your_password", "your_database", 0, NULL, 0)) {
        std::cerr << "Error connecting to MySQL: " << mysql_error(conn) << std::endl;
        return 1;
    }

    // 准备SQL语句
    const char* query = "INSERT INTO articles (id, title, content) VALUES (%d, '%s', '%s') "
                        "ON DUPLICATE KEY UPDATE title=VALUES(title), content=VALUES(content)";

    // 替换下面的占位符为实际的值
    int id = 1;
    const char* title = "Example Title";
    const char* content = "Example Content";

    // 执行SQL语句
    if (mysql_query(conn, query, id, title, content)) {
        std::cerr << "Error executing query: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }

    // 通常情况下，INSERT ... ON DUPLICATE KEY UPDATE 不需要处理结果集
    // 但如果你需要确认受影响的行数，可以使用 mysql_affected_rows()
    std::cout << "Rows affected: " << mysql_affected_rows(conn) << std::endl;

    // 关闭连接
    mysql_close(conn);

    return 0;
}
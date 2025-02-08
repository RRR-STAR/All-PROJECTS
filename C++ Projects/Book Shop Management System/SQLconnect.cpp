#include <iostream>
#include <mysql.h>
/**
 * The Reaon why V.S.Code MinGW compiler can't recognised the mysql files because,
 * MySQL downloaded in system as 64 bit and the MinGW compiler is still 32-bit.
 */

int main() {
    std::cout <<"\n\nFirst Line of Main()";
    
    MYSQL *conn;
    conn = mysql_init(NULL);
    
    if (conn == NULL) {
        std::cout << "mysql_init() failed\n";
        return EXIT_FAILURE;
    }
    
    if (mysql_real_connect(conn, "localhost", "root", "$this->@SMR_2005", "", 3306, NULL, 0) == NULL) {
        std::cout <<"\nmysql_real_connect() failed\n";
        mysql_close(conn);
        return EXIT_FAILURE;
    }
    
    std::cout <<"\nConnected to MySQL successfully!" << std::endl;
    
    mysql_close(conn);
    return EXIT_SUCCESS;
}
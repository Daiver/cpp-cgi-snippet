#include "mysqlworker.h"

MySQLWorker::MySQLWorker()
{
    this->isConnectedToDb = false;
    this->connection = NULL;
}

MySQLWorker::ConnectionResult MySQLWorker::connect(const std::string &server, const std::string &login,
                            const std::string &password, const std::string &dbName)
{
    MYSQL *con = mysql_init(NULL);
    char err[256];

    if (con == NULL) 
    {
        sprintf(err, "MySQL is NULL; error: %s\n", mysql_error(con));
        mysql_close(con);        
        return ConnectionResult::Left(err);
    }  

    if (mysql_real_connect(con, server.c_str(), login.c_str(), password.c_str(), 
                                                    dbName.c_str(), 0, NULL, 0) == NULL) 
    {
        sprintf(err, "MySQL cannot connect to DB error: %s\n", mysql_error(con));
        mysql_close(con);        
        return ConnectionResult::Left(err);
    }   
    this->connection = con;
    return ConnectionResult::Right(con);
}

#include "mysqlworker.h"

MySQLWorker::MySQLWorker()
{
    this->isConnectedToDb = false;
    this->connection = NULL;
}

MySQLWorker::~MySQLWorker()
{
    if(this->connection != NULL)
        mysql_close(this->connection);
}

MySQLWorker::ConnectionResult MySQLWorker::connect(const std::string &server, const std::string &login,
                            const std::string &password, const std::string &dbName)
{
    if(this->connection != NULL){
        mysql_close(this->connection);
        this->connection = NULL;
    }

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
    this->isConnectedToDb = true;
    return ConnectionResult::Right(con);
}

SQLWorker::SQLQueryResult MySQLWorker::query(const std::string &qu) const
{
    //printf("Start\n");
    if (mysql_query(connection, qu.c_str())) {
        char err[256];
        sprintf(err, "MySQL cannot execute query error: %s\n", mysql_error(connection));
        //printf("here %s\n", err);
        //printf(">'%s'<\n", qu.c_str());
        return SQLQueryResult::Left(err);
    }

    MYSQL_RES *result = mysql_store_result(connection);
    VectorOfVectorOfString res;

    if (result == NULL) 
    {
        //printf("here2\n");
        char err[256];
        const char *errMsg = mysql_error(connection);
        if(strlen(errMsg) == 0)
            return SQLQueryResult::Right(res);
        sprintf(err, "MySQL cannot store result error: %s\n", errMsg);
        return SQLQueryResult::Left(err);
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;


    while ((row = mysql_fetch_row(result))) 
    { 
        res.push_back(std::vector<std::string>(num_fields));
        for(int i = 0; i < num_fields; i++) 
        { 
            res[res.size() - 1][i] = row[i] ? row[i] : "NULL"; 
        } 
    }

    mysql_free_result(result);
    //printf("finish\n");
    return SQLQueryResult::Right(res);
}

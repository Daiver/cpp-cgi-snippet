#include "database.hpp"

using namespace orm;

Database::Database(SQLWorker *worker): sqlWorker(worker)
{
}

void Database::createScheme()
{
    for(int i = 0; i < models.size(); ++i){
        std::string q = models[i].getCreationTableQuery();
        //std::cout << i << " " << q << "\n";
        this->sqlWorker->query(q);
    }
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <mysql/mysql.h>

#define DATABASE_NAME  "SM"
#define DATABASE_USERNAME "root"
#define DATABASE_PASSWORD "kopkaffe"
MYSQL *mysql1;

void mysql_connect (void)
{
     //initialize MYSQL object for connections
 mysql1 = mysql_init(NULL);

     if(mysql1 == NULL)
     {
         fprintf(stderr, "ABB : %s\n", mysql_error(mysql1));
         return;
     }

     //Connect to the database
     if(mysql_real_connect(mysql1, "localhost", DATABASE_USERNAME, DATABASE_PASSWORD, DATABASE_NAME, 0, NULL, 0) == NULL)
     {
      fprintf(stderr, "%s\n", mysql_error(mysql1));
     }
     else
     {
         printf("Database connection successful.\r\n");
     }
}


int main(int argc, char **argv)
{
mysql_connect();

mysql_query(mysql1, "INSERT INTO SM (id, kW, kWh, PQ) VALUES (4, 10, 10, 10)");
        return 0;
}

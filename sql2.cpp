#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <mysql/mysql.h>

#define DATABASE_NAME  "SM"
#define DATABASE_USERNAME "root"
#define DATABASE_PASSWORD "kopkaffe"
#include <string>
#include <vector>
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
    int id=3;
    int kW=400;
    int kWh=300;
    int PQ=100;
char q[1024];
for (int i=0;i<3;i++)
{
    sprintf(q,"INSERT INTO SM(id,kW) VALUES(%d,%d)",id,kW);

    mysql_query(mysql1, q);
}
return 0;
}

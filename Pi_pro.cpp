#include "RF24Mesh/RF24Mesh.h"
#include <RF24/RF24.h>
#include <time.h>
#include <RF24Network/RF24Network.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <mysql/mysql.h>
#include <string>
#include <vector>
#define DATABASE_NAME  "SM"
#define DATABASE_USERNAME "root"
#define DATABASE_PASSWORD "kopkaffe"

MYSQL *mysql1;

using namespace std;

RF24 radio(RPI_V2_GPIO_P1_15, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_8MHZ);
RF24Network network(radio);
RF24Mesh mesh(radio,network);

struct dat {
  //Effect in watt
 uint16_t Effect;
  //Effect in watt hours
 uint16_t Effect_Hour;
  //Voltage in milli volt
 uint16_t Voltage;
  //Amp in amp
 uint16_t Ampere;
  //Time in ms
 uint16_t Time_Stamp;
uint8_t id2;
uint8_t check;
}dat;

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

int main(int argc, char** argv) {
mysql_connect();

//



//
char q[1024];
  // Set the nodeID to 0 for the master node
  mesh.setNodeID(0);
  // Connect to the mesh
  printf("start\n");
  mesh.begin();
  radio.printDetails();

while(true)
{
  // Call network.update as usual to keep the network updated
  mesh.update();

  // In addition, keep the 'DHCP service' running on the master node so addresses will
  // be assigned to the sensor nodes
  mesh.DHCP();
  // Check for incoming data from the sensors
  while(network.available()){

//printf("rcv\n");
    RF24NetworkHeader header;
    network.peek(header);
//
int totSize = sizeof(network.peek(header))+sizeof(dat);
   // uint32_t dat = 0;
    switch(header.type){
      // Display the incoming millis() values from the sensor nodes
      case 'M': network.read(header,&dat,sizeof(dat));

    for(int i=0; i<mesh.addrListTop && dat.check==29; i++){

cout << " RF24Network Address: ";
cout << oct << (mesh.addrList[i].address) << endl;
}
if (dat.id2 <= 3){
sprintf(q,"INSERT INTO SM1(id,effect,effectHour,voltage,ampere,timeStamp,totalStr) VALUES(%d,%d,%d,%d,%d,%d,%d)",dat.id2,dat.Effect,dat.Effect_Hour,dat.Voltage,dat.Ampere,dat.Time_Stamp,totSize);
    mysql_query(mysql1, q);
cout << "Package Received and added to Radial 1" << endl;
cout << "Package received from ID: " << dat.id2 << " / Effect: " << dat.Effect << " / Effect Hour: "  << dat.Effect_Hour << " / Voltage: "  << dat.Voltage << " / Ampere: " << dat.Ampere << " / Time Stamp: " << dat.Time_Stamp << " / Package Size: " << totSize << " bits." << endl;
}
if(dat.id2 == 4 || dat.id2 == 5 || dat.id2 == 6){
sprintf(q,"INSERT INTO SM2(id,effect,effectHour,voltage,ampere,timeStamp,totalStr) VALUES(%d,%d,%d,%d,%d,%d,%d)",dat.id2,dat.Effect,dat.Effect_Hour,dat.Voltage,dat.Ampere,dat.Time_Stamp,totSize);
    mysql_query(mysql1, q);
cout << "Package Received and added to Radial 2" << endl;
cout << "Package received from ID: " << dat.id2 << " / Effect: " << dat.Effect << " / Effect Hour: "  << dat.Effect_Hour << " / Voltage: "  << dat.Voltage << " / Ampere: " << dat.Ampere << " / Time Stamp: " << dat.Time_Stamp << " / Package Size: " << totSize << " bits." << endl;
}
if (dat.id2 >= 7){
sprintf(q,"INSERT INTO SM3(id,effect,effectHour,voltage,ampere,timeStamp,totalStr) VALUES(%d,%d,%d,%d,%d,%d,%d)",dat.id2,dat.Effect,dat.Effect_Hour,dat.Voltage,dat.Ampere,dat.Time_Stamp,totSize);
    mysql_query(mysql1, q);
cout << "Package Received and added to Radial 3" << endl;
cout << "Package received from ID: " << dat.id2 << " / Effect: " << dat.Effect << " / Effect Hour: "  << dat.Effect_Hour << " / Voltage: "  << dat.Voltage << " / Ampere: " << dat.Ampere << " / Time Stamp: " << dat.Time_Stamp << " / Package Size: " << totSize << " bits." << endl;
}


 break;
      default:  network.read(header,0,0);
                printf("Rcv bad type %d from 0%o\n",header.type,header.from_node);
                break;
    }
  }
delay(2);
  }
return 0;
}

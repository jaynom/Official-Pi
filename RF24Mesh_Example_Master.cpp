#include "RF24Mesh/RF24Mesh.h"
#include <RF24/RF24.h>
#include <time.h>
#include <RF24Network/RF24Network.h>
#include <iostream>
using namespace std;

RF24 radio(RPI_V2_GPIO_P1_15, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_8MHZ);
RF24Network network(radio);
RF24Mesh mesh(radio,network);

struct dat {
  //Effect in watt
  unsigned long Effect;
  //Effect in watt hours
  unsigned long Effect_Hour;
  //Voltage in milli volt
  unsigned long Voltage;
  //Amp in amp
  unsigned long Ampere;
  //Time in ms
  unsigned long Time_Stamp;
}dat;


int main(int argc, char** argv) {

  // Set the nodeID to 0 for the master node
  mesh.setNodeID(0);
  // Connect to the mesh
  printf("start\n");
  mesh.begin();
  radio.printDetails();

while(1)
{
  // Call network.update as usual to keep the network updated
  mesh.update();

  // In addition, keep the 'DHCP service' running on the master node so addresses will
  // be assigned to the sensor nodes
  mesh.DHCP();
  // Check for incoming data from the sensors
  while(network.available()){
//    printf("rcv\n");
    RF24NetworkHeader header;
    network.peek(header);

   // uint32_t dat = 0;
    switch(header.type){
      // Display the incoming millis() values from the sensor nodes
      case 'M': network.read(header,&dat,sizeof(dat));
                cout << "Rcv " << dat.Effect << "from" << header.from_node << endl;
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

#include "airport.h"

vector<taxiway*> mainPath;
taxiway *rwCommon;
vector<taxiway*> toGate;
vector<taxiway*> fromGate;
//


simQueue sq;

void configure_taxiways_and_runways(){

  int mainPathID = 0;

                                 // landing runway and right taxiway
  mainPath.push_back(new taxiway(RW1X1,RW1Y1,RW1X2,RW1Y2,30,mainPathID++));
  mainPath.push_back(new taxiway(RW1X2,RW1Y2,TWX1,TWY1,10,mainPathID++));

  float twXdisp = ((float)TWX2-TWX1)/(nGates+1);
  float twYdisp = ((float)TWY2-TWY1)/(nGates+1);

  for(int i=0; i<=nGates; ++i){ // main taxiway. need 1 + nGates segments.
    mainPath.push_back(new taxiway( (TWX1+i*twXdisp),  (TWY1+i*twYdisp),
			      (TWX1+(i+1)*twXdisp), 
			      (TWY1+(i+1)*twYdisp),
			     5,mainPathID++));
  }
                               // left taxiway and takeoff runway
  mainPath.push_back(new taxiway(TWX2,TWY2,RW2X1,RW2Y1,6,mainPathID++));
  mainPath.push_back(new taxiway(RW2X1,RW2Y1,RW2X2,RW2Y2,30,mainPathID++));
  
  for(int i=0; i<nGates; ++i){ // taxiways to and from gates
    toGate.push_back(new taxiway( TWX1+(i+1)*twXdisp, TWY1+(i+1)*twYdisp,
				  TWX1+(i+1)*twXdisp, TWYT,
				  5,i));
    fromGate.push_back(new taxiway( TWX1+(i+1)*twXdisp, TWYT,
				    TWX1+(i+1)*twXdisp, TWY1+(i+1)*twYdisp,
				    5,i));
  }
      
  rwCommon = new taxiway(0,0,0,0,0,0);  // common part of runways.
}

void initialize_sq_with_arrival_events(){
  ifstream arFile("arrivals.txt");

  int arrivalT, serviceT;

  int id = 1;
  while(arFile >> arrivalT){
    arFile >> serviceT;

    plane *inPlane = new plane(id++,arrivalT,serviceT);

    inPlane->move(300,300);
  for(int i=0; i<360; i++){
    inPlane->forward(3);
    inPlane->right(1);
  }
    sq.insert(arrivalT,inPlane);
  }



}

int main(){
  initCanvas("Airport Simulator",800,0,1000,1000);
  
  configure_taxiways_and_runways();

  initialize_sq_with_arrival_events();

  sq.process_till_empty();

  usleep(10000000); // wait for 10 seconds.  
                    // Time to admire canvas before it is closed.
  closeCanvas();
}

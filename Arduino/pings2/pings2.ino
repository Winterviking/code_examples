//
//
// Ping the server > > > >
// Actual >> >> 
//
//
//
//

#include <EtherCard.h>
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <compat/deprecated.h>

// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x66,0x66,0x66,0x66,0x66,0x66 };

byte Ethernet::buffer[700];

uint32_t t;
uint32_t delta_t;

word len = 0;
word pos = 0;

bool zw_abcd1 = false;
bool zw_abcd2 = false;

typedef struct {
  uint8_t bad_state_counter;
  bool bad_line : 1;
  bool connection_missing : 1;
  bool bad_dhcp : 1;
  bool bad_dns : 1;
  bool hw_failure : 1;
  bool yummy3 : 1;
  
} SYSTEM_STATE;

SYSTEM_STATE sys_state;


// called when a ping comes in (replies to it are automatic)
static void gotPinged (byte* ptr) {
  ether.printIp(">>> ping from: ", ptr);
}

//
// states
//
typedef enum {
  EES_STARTUP,
  EES_SETUP,
  EES_IDLE,
  EES_PING_REQUEST,
  EES_POST_REQUEST
} E_ETHERCARD_STATE;

typedef enum {
  ESD_HW = 0,
  ESD_LINE = 1,
  ESD_DNS = 2,
  ESD_NETWORK = 3,
  ESD_MAX = 4
} E_STARTUP_DEGRADATOR;

E_ETHERCARD_STATE ees_state;
E_ETHERCARD_STATE bkp_ees_state;
E_STARTUP_DEGRADATOR degradator;

//
//
//
// PING ROLL
//

uint32_t loop_time = 0;

void initPingTask(){
  bkp_ees_state = ees_state;
  ees_state = EES_PING_REQUEST;
  
  ether.printIp("Pinging: ", ether.hisip);
  loop_time = t;
  ether.clientIcmpRequest(ether.hisip);
}

uint8_t pingtaskres = 0;
void loopFunctionPingTask(){
  pingtaskres = 0;
  
  if (len > 0 && ether.packetLoopIcmpCheckReply(ether.hisip)) {
    Serial.print("  ");
    Serial.print((uint32_t)(millis() - loop_time));
    Serial.println(" ms");
    ees_state = bkp_ees_state;
    len = 0;

    pingtaskres = 1;
  }

  if ( millis() - loop_time > 10000 ){
    zw_abcd1 = false;
    ees_state = bkp_ees_state;

    pingtaskres = 2;
    Serial.println("ping timeout");
  }

//  return pingtaskres;
}




//
//
//
// POST REQUEST 
//

void initPostTask(){

}

void loopFunctionPostTask(){

}







//
// MAIN >> >> >>
//
int main(void){
  //init();

  sei();

        // on the ATmega168, timer 0 is also used for fast hardware pwm
        // (using phase-correct PWM would mean that timer 0 overflowed half as often
        // resulting in different millis() behavior on the ATmega8 and ATmega168)
        sbi(TCCR0A, WGM01);
        sbi(TCCR0A, WGM00);

        // set timer 0 prescale factor to 64
        // this combination is for the standard 168/328/1280/2560
        sbi(TCCR0B, CS01);
        sbi(TCCR0B, CS00);

        // enable timer 0 overflow interrupt
        sbi(TIMSK0, TOIE0);

  sys_state = {0,false,false,false,false,false};
  
  
  Serial.begin(57600);
  Serial.println("Initiated... ooo :\n");

  DDRC &= ~(0b00000011);
  PORTC |= 0b00000011;


  uint8_t pinc = 0;

  t = millis();




  ees_state = EES_STARTUP; // let go
  degradator = ESD_HW;

  Serial.println("end add init");

//ESD_HW

 
  
  uint32_t zz_zz_t = 0;
  while (1){
    //
    // timing routines
    delta_t = millis() - t;
    t = t + delta_t;

    if (zz_zz_t >= 1000){ Serial.print("+"); zz_zz_t = 0;}
    else zz_zz_t+= delta_t;
   
    
    //
    // loopy task
    if (degradator >= ESD_LINE){
      len = 0; pos = 0;
      len = ether.packetReceive(); // go receive new packets
      pos = ether.packetLoop(len); // respond to incoming pings
    }


  //
  // Startup sequence
  // 


  

  

  


  
  

  


    
    //
    // ping a remote server once every few seconds
    switch (ees_state){
      case EES_STARTUP:
        ees_state = EES_SETUP;
      break;
      case EES_SETUP:
        switch(degradator){
          case ESD_HW:
            do {
              if (ether.begin(sizeof Ethernet::buffer, mymac, SS) == 0) { // Change 'SS' to your Slave Select pin, if you arn't using the default pin
                Serial.println(F("Failed to access Ethernet controller"));
                sys_state.hw_failure = true;
                sys_state.bad_state_counter++;
                delay(10000);
              } else {
                Serial.println(F("Ethernet controller accessible"));
                sys_state.hw_failure = false;
                sys_state.bad_state_counter = 0;
                degradator = degradator + 1;
                
              }
            } while (sys_state.hw_failure);
          break;
          case ESD_LINE:
            do {
              if (!ether.dhcpSetup()){
                Serial.println(F("DHCP failed"));
                
                sys_state.bad_dhcp = true;
                sys_state.bad_state_counter++;
                
                if (sys_state.bad_state_counter == 3) {
                  degradator = degradator - 1;
                  sys_state.bad_state_counter = 0;
                  break;
                }
                //delay(1000); // autodelay
              } else {
                Serial.println(F("DHCP connected"));
                sys_state.bad_dhcp = false;
                degradator = degradator + 1;
                sys_state.bad_state_counter = 0;

              }
            } while(sys_state.bad_dhcp);

            if (!sys_state.bad_dhcp){
              ether.registerPingCallback(gotPinged);
              
              ether.printIp("IP:  ", ether.myip);
              ether.printIp("GW:  ", ether.gwip);
            }
          break;
          case ESD_DNS:
            do{
              // use DNS to locate the IP address we want to ping
              if (!ether.dnsLookup(PSTR("www.google.com"))) {
                Serial.println("DNS failed");
                sys_state.bad_state_counter++;
                sys_state.bad_dns = true;
                
                if (sys_state.bad_state_counter == 3) {
                  degradator = degradator - 1;
                  sys_state.bad_state_counter = 0;
                  break;
                }
                  
                  //              ether.parseIp(ether.hisip, "74.125.77.99");
              } else {
                Serial.println(F("DNS lookup successful"));
                sys_state.bad_dns = false;
                sys_state.bad_state_counter = 0;
                degradator = degradator + 1;
              }
            } while(sys_state.bad_dns);

            if (!sys_state.bad_dns){
              ether.printIp("SRV: ", ether.hisip);
            }
            
                     
            
          break;
          case ESD_NETWORK:
            switch(pingtaskres){
              case 0:
                initPingTask();
                Serial.println("check connectivity"); 
              break;
              case 1:
                sys_state.connection_missing = false;
                sys_state.bad_state_counter = 0;
                degradator = degradator + 1;
                pingtaskres = 0;
              break;
              case 2:
                Serial.println("Unsuccessful");
                sys_state.bad_state_counter++;
                sys_state.connection_missing = true;
                pingtaskres = 0;
                
                if (sys_state.bad_state_counter == 3) {
                  degradator = degradator - 1;
                  sys_state.bad_state_counter = 0;

                }
              break;
            };
          break;
          case ESD_MAX:
            ees_state = EES_IDLE; // go to "waitstate"
            Serial.println(F("OK"));
          break;
        };
      break;      
      case EES_PING_REQUEST:
        loopFunctionPingTask();
      break;
      case EES_POST_REQUEST:
        loopFunctionPostTask();
      break;
      case EES_IDLE:
        //
        // State dispatcher :: by input ::
        //
        
        //check btn
        pinc = ~PINC;

 //       Serial.println(pinc);

        if ((pinc & 0b00000001) && (!zw_abcd1)){
          //ees_state = EES_PING_REQUEST;
          //initPingTask();
          degradator = degradator - 1;
          ees_state = EES_SETUP;
          
          
          
          zw_abcd1 = true;
        }

        if ((pinc & 0b00000010) && (!zw_abcd2)){
          ees_state = EES_PING_REQUEST;
          initPostTask();
          zw_abcd2 = true;
        }
        

        if ((pinc&0b00000001) == 0){
          zw_abcd1 = false;
        }
        if ((pinc&0b00000010) == 0){
          zw_abcd2 = false;
        }
      break;
    };
  }

  return 1;
}












void setup () {

}

void loop () {

}

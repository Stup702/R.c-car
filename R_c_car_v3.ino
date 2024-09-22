#include <IRremote.h>

#define recv_pin 7

IRrecv irrecv(recv_pin);
decode_results results;
int past;

/*things to set:
  left motor is motor a;
  right motor is motor b;
*/



// wired connections
#define a_ia 8
#define a_ib 9
#define b_ia 10 // D10 --> Motor B Input A --> MOTOR B +
#define b_ib 11 // D11 --> Motor B Input B --> MOTOR B -


// functional connections
#define apwm a_ia
#define adir a_ib
#define bpwm b_ia // Motor B PWM Speed
#define bdir b_ib // Motor B Direction



#define PWM_SLOW 50  // arbitrary slow speed PWM duty cycle
#define DIR_DELAY 1000 // brief delay for abrupt motor changes
 
void a_motor_forward(){
  // set the motor speed and direction
      digitalWrite( adir, HIGH ); // direction = forward
      analogWrite( apwm, 255-PWM_SLOW ); // PWM speed = slow
  
}

void a_motor_reverse(){
  // set the motor speed and direction
      digitalWrite( adir, LOW ); // direction = reverse
      analogWrite( apwm, PWM_SLOW ); // PWM speed = slow

}

void b_motor_forward(){
  // set the motor speed and direction
      digitalWrite( bdir, HIGH ); // direction = forward
      analogWrite( bpwm, 255-PWM_SLOW ); // PWM speed = slow
  
}

void b_motor_reverse(){
  // set the motor speed and direction
      digitalWrite( bdir, LOW ); // direction = reverse
      analogWrite( bpwm, PWM_SLOW ); // PWM speed = slow

}

void brake(){
  //motor a
        digitalWrite( adir, LOW );
        digitalWrite( apwm, LOW );
  //motor b
        digitalWrite( bdir, LOW );
        digitalWrite( bpwm, LOW );
  

}



void setup()
{
  Serial.begin( 9600 );

  irrecv.enableIRIn();
  irrecv.blink13(true);

  
  pinMode( adir, OUTPUT );
  pinMode( apwm, OUTPUT );
  pinMode( bdir, OUTPUT );
  pinMode( bpwm, OUTPUT );

  digitalWrite( adir, LOW );
  digitalWrite( apwm, LOW );
  digitalWrite( bdir, LOW );
  digitalWrite( bpwm, LOW );
}
 
void loop()
{
  
    
    if(irrecv.decode(&results)){
        Serial.println(results.value, HEX);
        switch(results.value){

         
         
      case 0xFF18E7:
        past = 1; // 1) Forward      

        ///////////////////////////////////////////
        
        //braking before staring to reduce damage from abrupt changes
        
        
        brake();
        

        //////////////////////////////////////////

        Serial.println( "Forward..." );
      
        delay( DIR_DELAY );


        a_motor_forward();
        b_motor_forward();

        

        break;      
         



         
 
      case 0xFF4AB5: // 2) Reverse
        Serial.println( "Reverse" );

        past =2;


        ///////////////////////////////////////////

        //braking before starting to reduce damage from abrupt changes

        brake();

        //////////////////////////////////////////

        //motor b
       
        delay( DIR_DELAY );


        a_motor_reverse();

        b_motor_reverse();
        break;      
         
      
      case 0xFF10EF:
        past = 3; // 3) LEFT      
        //when going left, right motor should spin forward, left motor should spin backward


        ///////////////////////////////////////////
        //braking before staring to reduce damage from abrupt changes

        brake();
        //////////////////////////////////////////

        Serial.println( "LEFT" );
      
        delay( DIR_DELAY );


        a_motor_reverse();
        b_motor_forward();

        break; 

      case 0xFF5AA5:
        past = 4; // 4) RIGHT      

        //when going right, left motor should spin forward, right motor should spin in reverse


        ///////////////////////////////////////////

        //braking before starting to reduce damage from abrupt changes

        brake();

        //////////////////////////////////////////

        Serial.println( "RIGHT" );
      
        delay( DIR_DELAY );

        a_motor_forward();
        b_motor_reverse();
        
        break; 

           
         
        
      case 0xFFFFFFFF: //////////////////////////////////////for repeating
        switch(past){

          case 1:
            // 1) Forward      

            ///////////////////////////////////////////
            
            //braking before staring to reduce damage from abrupt changes
            
            
            brake();
            

            //////////////////////////////////////////

            Serial.println( "Forward..." );
          
            delay( DIR_DELAY );


            a_motor_forward();
            b_motor_forward();

            

            break;      
            



            
    
          case 2: // 2) Reverse
            Serial.println( "Reverse" );

            


            ///////////////////////////////////////////

            //braking before starting to reduce damage from abrupt changes

            brake();

            //////////////////////////////////////////

            //motor b
          
            delay( DIR_DELAY );


            a_motor_reverse();

            b_motor_reverse();
            break;      
            
          
          case 3:
            // 3) LEFT      
            //when going left, right motor should spin forward, left motor should spin backward


            ///////////////////////////////////////////
            //braking before staring to reduce damage from abrupt changes

            brake();
            //////////////////////////////////////////

            Serial.println( "LEFT" );
          
            delay( DIR_DELAY );


            a_motor_reverse();
            b_motor_forward();

            break; 

          case 4:
            // 4) RIGHT      

            //when going right, left motor should spin forward, right motor should spin in reverse


            ///////////////////////////////////////////

            //braking before starting to reduce damage from abrupt changes

            brake();

            //////////////////////////////////////////

            Serial.println( "RIGHT" );
          
            delay( DIR_DELAY );

            a_motor_forward();
            b_motor_reverse();
            
            break;



        }
      default:
        // wrong character! display the menu again!
        break;
    }
  } 
 
  // repeat the main loop and redraw the menu...
}
/*EOF*/
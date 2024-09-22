#include <IRremote.h>

#define recv_pin 7

IRrecv irrecv(recv_pin);
decode_results results;
int past_cmd;

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
  boolean isValidInput;
  {
    
    if(irrecv.decode(&results)){
        Serial.println(reslts.value, HEX);
        switch(results.value){

         
         
      case 0xFF10EF:
        past = 1; // 1) Forward      

        ///////////////////////////////////////////
        
        //braking before staring to reduce damage from abrupt changes
        
        //motor b
        digitalWrite( bdir, LOW );
        digitalWrite( bpwm, LOW );

        //motor a
        digitalWrite( adir, LOW );
        digitalWrite( apwm, LOW );

        //////////////////////////////////////////

        Serial.println( "Forward..." );
      
        delay( DIR_DELAY );
        // set the motor speed and direction
        digitalWrite( bdir, HIGH ); // direction = forward
        analogWrite( bpwm, 255-PWM_SLOW ); // PWM speed = slow
        

        // set the motor speed and direction
        digitalWrite( adir, HIGH ); // direction = forward
        analogWrite( apwm, 255-PWM_SLOW ); // PWM speed = slow
        isValidInput = true;
        break;      
         



         
 
      case 0xFF4AB5: // 2) Reverse
        Serial.println( "Reverse" );

        past =2;


        ///////////////////////////////////////////

        //braking before starting to reduce damage from abrupt changes

        //motor b
        digitalWrite( bdir, LOW );
        digitalWrite( bpwm, LOW );

        //motor a
        digitalWrite( adir, LOW );
        digitalWrite( apwm, LOW );

        //////////////////////////////////////////

        //motor b
       
        delay( DIR_DELAY );
        // set the motor speed and direction
        digitalWrite( bdir, LOW ); // direction = reverse
        analogWrite( bpwm, PWM_SLOW ); // PWM speed = slow

        //motor a

        // set the motor speed and direction
        digitalWrite( adir, LOW ); // direction = reverse
        analogWrite( apwm, PWM_SLOW ); // PWM speed = slow
        isValidInput = true;
        break;      
         
      
      case 0xFF10EF:
        past = 3; // 3) LEFT      
        //when going left, right motor should spin forward, left motor should spin backward


        ///////////////////////////////////////////
        //braking before staring to reduce damage from abrupt changes

        //motor b
        digitalWrite( bdir, LOW );
        digitalWrite( bpwm, LOW );

        //motor a
        digitalWrite( adir, LOW );
        digitalWrite( apwm, LOW );

        //////////////////////////////////////////

        Serial.println( "LEFT" );
      
        delay( DIR_DELAY );
        // b forward
        digitalWrite( bdir, HIGH ); // direction = forward
        analogWrite( bpwm, 255-PWM_SLOW ); // PWM speed = slow

        // a reverse
        digitalWrite( adir, LOW ); // direction = reverse
        analogWrite( apwm, PWM_SLOW ); // PWM speed = slow
        isValidInput = true;
        break; 

      case FF5AA5:
        past = 4; // 4) RIGHT      

        //when going right, left motor should spin forward, right motor should spin in reverse


        ///////////////////////////////////////////

        //braking before starting to reduce damage from abrupt changes

        //motor b
        digitalWrite( bdir, LOW );
        digitalWrite( bpwm, LOW );

        //motor a
        digitalWrite( adir, LOW );
        digitalWrite( apwm, LOW );

        //////////////////////////////////////////

        Serial.println( "RIGHT" );
      
        delay( DIR_DELAY );
        // a forward
        digitalWrite( adir, HIGH ); // direction = forward
        analogWrite( apwm, 255-PWM_SLOW ); // PWM speed = slow

        // b reverse
        digitalWrite( bdir, LOW ); // direction = reverse
        analogWrite( bpwm, PWM_SLOW ); // PWM speed = slow
        isValidInput = true;
        break; 

           
         
        
      case 0xFFFFFFFF: //////////////////////////////////////for repeating
        switch(past){
          case 1:
            // 2) Forward      

            ///////////////////////////////////////////
            //breaking before starting 
  
            //motor b
            digitalWrite( bdir, LOW );
            digitalWrite( bpwm, LOW );

            //motor a
            digitalWrite( adir, LOW );
            digitalWrite( apwm, LOW );

            //////////////////////////////////////////

            Serial.println( "Forward..." );
            
            //  set the motor speed and direction
            digitalWrite( bdir, HIGH ); // direction = forward
            analogWrite( bpwm, 255-PWM_SLOW ); // PWM speed = slow
           
            // set the motor speed and direction
            digitalWrite( adir, HIGH ); // direction = forward
            analogWrite( apwm, 255-PWM_SLOW ); // PWM speed = slow
            isValidInput = true;
            break;      
         



         
 
          case 2: // 4) Reverse
            Serial.println( "Reverse" );

            ///////////////////////////////////////////
            //breaking before starting 

            //motor b
            digitalWrite( bdir, LOW );
            digitalWrite( bpwm, LOW );

            //motor a
            digitalWrite( adir, LOW );
            digitalWrite( apwm, LOW );

            //////////////////////////////////////////

            //motor b

           
            // set the motor speed and direction
            digitalWrite( bdir, LOW ); // direction = reverse
            analogWrite( bpwm, PWM_SLOW ); // PWM speed = slow

            //motor a


            // set the motor speed and direction
            digitalWrite( adir, LOW ); // direction = reverse
            analogWrite( apwm, PWM_SLOW ); // PWM speed = slow
            isValidInput = true;
            break;

          case 3:
            3) LEFT      
            //when going left, right motor should spin forward, left motor should spin backward


            ///////////////////////////////////////////
            //braking before staring to reduce damage from abrupt changes

            //motor b
            digitalWrite( bdir, LOW );
            digitalWrite( bpwm, LOW );

            //motor a
            digitalWrite( adir, LOW );
            digitalWrite( apwm, LOW );

            //////////////////////////////////////////

            Serial.println( "LEFT" );
          
            // b forward
            digitalWrite( bdir, HIGH ); // direction = forward
            analogWrite( bpwm, 255-PWM_SLOW ); // PWM speed = slow

            // a reverse
            digitalWrite( adir, LOW ); // direction = reverse
            analogWrite( apwm, PWM_SLOW ); // PWM speed = slow
            isValidInput = true;
            break; 


          case 4:
            // 4) RIGHT      

            //when going right, left motor should spin forward, right motor should spin in reverse


            ///////////////////////////////////////////

            //braking before starting to reduce damage from abrupt changes

            //motor b
            digitalWrite( bdir, LOW );
            digitalWrite( bpwm, LOW );

            //motor a
            digitalWrite( adir, LOW );
            digitalWrite( apwm, LOW );

            //////////////////////////////////////////

            Serial.println( "RIGHT" );
          
            delay( DIR_DELAY );
            // a forward
            digitalWrite( adir, HIGH ); // direction = forward
            analogWrite( apwm, 255-PWM_SLOW ); // PWM speed = slow

            // b reverse
            digitalWrite( bdir, LOW ); // direction = reverse
            analogWrite( bpwm, PWM_SLOW ); // PWM speed = slow
            isValidInput = true;
            break; 



        }
      default:
        // wrong character! display the menu again!
        isValidInput = false;
        break;
    }
  } while( isValidInput == true );
 
  // repeat the main loop and redraw the menu...
}
/*EOF*/

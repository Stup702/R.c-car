#include <IRremote.h>

#define recv_pin 7

IRrecv irrecv(recv_pin);
decode_results results;
int past_cmd;

 
// wired connections
#define b_ia 10 // D10 --> Motor B Input A --> MOTOR B +
#define b_ib 11 // D11 --> Motor B Input B --> MOTOR B -
#define a_ia 9
#define a_ib 8

// functional connections
#define bpwm b_ia // Motor B PWM Speed
#define bdir b_ib // Motor B Direction
#define apwm a_ia
#define adir a_ib


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
  // draw a menu on the serial port
  Serial.println( "-----------------------------" );
  Serial.println( "MENU:" );
  Serial.println( "1) Fast forward" );
  Serial.println( "2) Forward" );
  Serial.println( "3) Soft stop (coast)" );
  Serial.println( "4) Reverse" );
  Serial.println( "5) Fast reverse" );
  Serial.println( "6) Hard stop (brake)" );
  Serial.println( "-----------------------------" );
  do
  {
    byte c;
    // get the next character from the serial port
    Serial.print( "?" );
    while( !Serial.available() )
      ; // LOOP...
    c = Serial.read();
    // execute the menu option based on the character recieved
    switch( c )
    {
         
         
      case '1': // 2) Forward      
        Serial.println( "Forward..." );
        // always stop motors briefly before abrupt changes
        digitalWrite( bdir, LOW );
        digitalWrite( bpwm, LOW );
        delay( DIR_DELAY );
        // set the motor speed and direction
        digitalWrite( bdir, HIGH ); // direction = forward
        analogWrite( bpwm, 255-PWM_SLOW ); // PWM speed = slow
        // always stop motors briefly before abrupt changes
        digitalWrite( adir, LOW );
        digitalWrite( apwm, LOW );
        delay( DIR_DELAY );
        // set the motor speed and direction
        digitalWrite( adir, HIGH ); // direction = forward
        analogWrite( apwm, 255-PWM_SLOW ); // PWM speed = slow
        isValidInput = true;
        break;      
         
      case '2': // 3) Soft stop (preferred)
        Serial.println( "Soft stop (coast)..." );
        digitalWrite( bdir, LOW );
        digitalWrite( bpwm, LOW );
        digitalWrite( adir, LOW );
        digitalWrite( apwm, LOW );
        isValidInput = true;
        break;      
 
      case '3': // 4) Reverse
        Serial.println( "Reverse" );

        //motor b

        // always stop motors briefly before abrupt changes
        digitalWrite( bdir, LOW );
        digitalWrite( bpwm, LOW );
        delay( DIR_DELAY );
        // set the motor speed and direction
        digitalWrite( bdir, LOW ); // direction = reverse
        analogWrite( bpwm, PWM_SLOW ); // PWM speed = slow

        //motor a

        // always stop motors briefly before abrupt changes
        digitalWrite( adir, LOW );
        digitalWrite( apwm, LOW );
        delay( DIR_DELAY );
        // set the motor speed and direction
        digitalWrite( adir, LOW ); // direction = reverse
        analogWrite( apwm, PWM_SLOW ); // PWM speed = slow
        isValidInput = true;
        break;      
         
         
        
         
      default:
        // wrong character! display the menu again!
        isValidInput = false;
        break;
    }
  } while( isValidInput == true );
 
  // repeat the main loop and redraw the menu...
}
/*EOF*/

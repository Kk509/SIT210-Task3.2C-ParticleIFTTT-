int light_sensor = A3;
// light sensor reading = value
int value = 0;
// led turns on when the room is bright, vice versa.
int led = D2;
// value >3000 = bright room, value <3000 = dark room
int threshold = 3000;

// current brightness level
bool current;
// previous brightness level
bool previous;

void setup()
{
    pinMode(led, OUTPUT);
    Particle.variable("light", &value, INT);
}

void loop()
{
    value = analogRead(light_sensor);
    String result = String(value);
    current = value > threshold;
    
    // if value > threshold
    if (current)
    {
        analogWrite(led, 255); // Turn on led
    } 
    else
    {
        analogWrite(led, 0); // Turn off led
    }
    
    // e.g. true != false
    if (previous != current)
    {
        previous = current;
        
        if (current)
        {
            // Trigger the event "bright"
            Particle.publish("bright", result, PRIVATE);
        } 
        else
        {
            // Trigger the event "dark"
            Particle.publish("dark", result, PRIVATE);
        }
    }
       
    // delay 1 second
    delay(1000);
}
/* 
 * Modified version of the rosserial IR Ranger example
 * 
 * This example is calibrated for the Sharp GP2Y0A21YK.
 */

#include <ros.h>
#include <ros/time.h>
#include <kobuki_arduino_msgs/Rangers.h>
#include <std_msgs/Int16MultiArray.h>

ros::NodeHandle  nh;
kobuki_arduino_msgs::Rangers rangers_msg;
ros::Publisher pub_range( "rangers_data", &rangers_msg);

const int nr_of_irs = 11;
const int ir_pins[nr_of_irs] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int range_storage[nr_of_irs];
unsigned long last_rangers_time, rangers_timing, last_blink_time, blink_timing, now;
boolean led_on;
int val;

void setup()
{
  nh.initNode();
  nh.advertise(pub_range);
  
  rangers_msg.header.frame_id = "kobuki_rangers";
  rangers_msg.ranges_length = nr_of_irs;
  rangers_msg.ranges = range_storage;
  rangers_timing = 50; // publish the range value every 50 milliseconds, since it takes that long for the sensor to stabilize
  last_rangers_time = 0;
  blink_timing = 500; // blinking frequency in ms
  last_blink_time = 0;
  pinMode(13, OUTPUT);
  led_on = false;
}

void loop()
{
  now = millis();
  if ((now - last_rangers_time) > rangers_timing)
  {
    last_rangers_time = now;
    rangers_msg.header.stamp = nh.now();
    for (unsigned int ir = 0; ir < nr_of_irs; ++ir)
    {
      rangers_msg.ranges[ir] = analogRead(ir_pins[ir]);
    }   
    pub_range.publish(&rangers_msg);
    nh.spinOnce();
  }
   
  // Alive signal
  if ((now - last_blink_time) > blink_timing)
  {
    last_blink_time =  now;
    if (led_on)
    {
      digitalWrite(13, LOW);   // turn LED off
      led_on = false;
    }
    else
    {
      digitalWrite(13, HIGH);   // turn LED on
      led_on = true;
    }
  }
}
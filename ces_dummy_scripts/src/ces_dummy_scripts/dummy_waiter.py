#!/usr/bin/env python
#
# License: BSD
#   https://raw.github.com/robotics-in-concert/rocon_demos/license/LICENSE
#

import rospy
import std_msgs.msg

class DummyWaiter(object):

    def __init__(self):
        self._sub_drink_order = rospy.Subscriber("drink_order", std_msgs.msg.UInt16MultiArray,self._process_drink_order)
        self._pub_drink_ar    = rospy.Publisher("drink_ar",std_msgs.msg.UInt16)
        self._pub_drink_dispensed = rospy.Publisher("drink_dispensed", std_msgs.msg.Empty)
        self._pub_status_message = rospy.Publisher("waiterbot_debug", std_msgs.msg.String)

    def _process_drink_order(self, msg):
        self.log("Received drink order : " + str(msg.data))
        
        self.log("Move to VM")
        rospy.sleep(2)
        self.log("Arrival VM")

        rospy.sleep(1)
        self.log("Sending drink ar 1")        
        self._pub_drink_ar.publish(1)
        rospy.sleep(2)
        self.log("drink 1 dispensed")
        
        rospy.sleep(1)
        self.log("Sending drink ar 1")        
        self._pub_drink_ar.publish(1)
        rospy.sleep(2)
        self.log("drink 1 dispensed")
        
        rospy.sleep(1)
        self.log("Sending drink ar 2")        
        self._pub_drink_ar.publish(2)
        rospy.sleep(2)
        self.log("drink 2 dispensed")
        
        self.log("Sending drink dispensed")
        
        self._pub_drink_dispensed.publish()

        self.log("Navigating to Origin...now")
        rospy.sleep(3)
        self.log("Arrival Oringin")
        

    def _send_feedback(self, feedback, message):
        self._pub_drink_order_feedback(feedback, message)
        

    def log(self, msg):
        rospy.loginfo("Dummy Waiter : " +str(msg))
        self._pub_status_message.publish(str(msg))

    def spin(self):
        rospy.spin()
# Overview

This project is intended to be a very simple wemos switch. This is simple to set up and hook up to home assistant, and will allow you to control devices from your home assistant controller.  It operates similar to how a light switch works.  The total cost of the project (usb power source not included) is $10.

Note: I based the design of this off of the below garage door controller:
http://automatedhome.party/2017/01/06/wifi-garage-door-controller-using-a-wemos-d1-mini/

## Limitations and maintenance

This is intended to be a simple project.  The goals are broad application with low maintenance and low complexity enabling easy implementation by beginners.

As with any project or device you create yourself, you do so at your own risk.  Please ensure you know how to work with electricity and that you wire and use this in a safe way.

# Instructions
Already familiar with this sort of project?  Then the instructions in this readme should get you going.  

Brand new to this sort of thing? then check out the detailed instructions here:
https://github.com/cmgerdes/Easy-MQTT-Switch/blob/master/DetailedInstructions.md

## Prerequisites
You will need the following:
1. An MQTT server
2. A home assistant instance

note: other automation controllers can be used, however all instructions and source code in this project assume home assistant.  If you use a different controller you will need to make any changes needed for the switch to operate with the controller.

# Build instructions
The build is, in general fairly simple.  You will do the following:
1. Purchase parts you do not already have in the BOM: https://github.com/cmgerdes/Easy-Wemos-Switch/blob/master/BOM.txt
2. Edit your HA Config.YAML to add the entry here: https://github.com/cmgerdes/Easy-Wemos-Switch/blob/master/Configuration.yaml
3. Open and compile the .ino here: https://github.com/cmgerdes/Easy-Wemos-Switch/blob/master/MqttSwitch.ino
4. Edit the code to substitute your values in for the variables at the top of the file.  Refer to the comments or the detailed instructions for what each does.
5. Upload the code to the wemos and restart it.  You should see an AP come with the value you gave for host.  Connect this and provide your wireless network info and save.  The AP should disappear (because it is now connected to your network) and setup for the wemos is complete.
6. Wire the control and relay according to this schematic: https://github.com/cmgerdes/Easy-MQTT-Switch/blob/master/WemosSchematic.png.  Note that your device should go across the "NO" (normally open) pins of the relay
7. Glue the wemos board to the top of the relay plastic enclosure with the usb connector facing the same direction as the relay output pins.
8. Print and mount the relay in the enclosure.

Note that your device wires in the same way as if you were controlling it with a lightswitch.  Just use the relay to break or close the circuit.

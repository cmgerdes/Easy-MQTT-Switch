# Overview

This project is intended to be a very simple wemos switch. This is simple to set up and hook up to home assistant, and will allow you to control devices from your home assistant controller.

If the components listed in the BOM are used, this is capable of controller both signal wires (example: turn a gas fireplace on/off) or a 120v or 220v light. The total cost including a usb power adapter (which you probably have already) is $15.  It's $10 without he power adapter.

If different current ratings etc. are required then different parts from the BOM could be substituted in fairly easily.

## Limitations and maintenance

This is intended to be a simple project.  The goals are broad application with low maintenance and low complexity enabling easy implementation by beginnings.

To accomplish this project you will need the following skills:
1. simple soldering
2. 3d printer (for the enclosure).
3. very basic coding skills.

## Prerequisites
You will need the following:
1. An MQTT server
2. A home assistant instance

note: other automation controllers can be used, however all instructions and source code in this project assume home assistant.  If you use a different controller you will need to make any changes needed for the switch to operate with the controller.

# Build instructions
The build is, in general fairly simple.  You will do the following:
1. order the parts.
2. Edit the source code to have your network and mqtt server information, upload the code to the wemos via usb.
3. Wire the control board to the relay and add output wires.
4. Test (ensure that you can connect and control the relay pins using home assistant or whatever home automation controller you're using)
5. Print the enclosure and place the wemos and relay in it.

## Parts order
Order the parts from the BOM located here: https://github.com/cmgerdes/Easy-Wemos-Switch/blob/master/BOM.txt

Note: if you want different specifications for current handling etc. then feel free to order a different relay.  When ordering the relay make sure it can be controlled by a 5v signal and requires low current to turn on.  For high current applications, consider using an SSR.

## Software setup
There are two steps to the software setup:
1. Editing the YAML files for home assistant so it can utilize the MQTT switch.
2. Editing and uploading the software to the wemos

### Editing the YAML files for home assistant
Updating home assistant to use the Wemos switch should be fairly simple.  Simply do the following:
1. edit your configuration.yaml to add the code located in the file here: https://github.com/cmgerdes/Easy-Wemos-Switch/blob/master/Configuration.yaml
2. edit the state_topic and command_topic to your preferred values.
3. validate your config and restart home assistant

Note: if you already have a switch section in your configuration.yaml in home assistant, then simply drop that line (don't add the section twice).

### Editing the wemos software and uploading
first, open the WemosSwitch.ino in the arduino IDE.  You can download the arduino IDE here: https://www.arduino.cc/en/Main/Software

Download the .ino located below and open in the arduino IDE:
https://github.com/cmgerdes/Easy-Wemos-Switch/blob/master/MqttSwitch.ino

Compile the code, you will most likely need to retrieve several libraries.  Below is a list of locations for libraries you will most likely need:
1. WiFiManager.h - https://randomnerdtutorials.com/wifimanager-with-esp8266-autoconnect-custom-parameter-and-manage-your-ssid-and-password/
2. PubSubClient.h - https://pubsubclient.knolleary.net/

Once you have the code compiling, edit the following values:
1. host - The name of the access point you want created for editing parameters and connecting to wifi
2. update_username - The site that allows you to edit the settings will require a user/password.  Specificy the user here.
3. update_password - The site that allows you to edit the settings will require a user/password.  Specificy the password here.
4. mqtt_server - The IP address of the mqtt server you want to connect to
5. switch_topic - the topic to use when connecting to the mqtt server. This should match your command_topic in the yaml above.
6. mqtt_sub - The topic to sub to when connecting to the mqtt server (typically you will just replace the value after the / above with #)
7. mqtt_user - the user you have set up on your mqtt server for connecting
8. mqtt_pass - the password for the mqtt user you have set up on your mqtt server


## Electronics build
The primary focus of this project was making the electronics build simple.  Below are the steps:
1. Remove the input pins from the relay either using a desoldering iron, desoldering braid, or other technique
2. Place the wemos on top of the relay switch and judge how much wire is necessary to reach from the ground pin of the wemos to the "-" pin of the relay
3. Cut 3 wires to this length.  The wires should go into the wemos from the bottom (opposite side as the metal processor)
4. wire the ground pin of the wemos to the "-" pin of the relay, the 5v pin of the wemos to the "+" pin of the relay, and the d1 pin of the Wemos to the "s" pin of the relay.
5. attach 2 wires to the "NO" (Normally Open) pins of the relay.  This means the wires will be disconnected when the relay is turned off.
6. Stop here and test your wemos by firing it up and turn it off and on from home assistant.  Use a multimeter to make sure you see the switch open and close.
7. Apply a small amount of hot glue to the top of the plastic housing for the relay, then place the wemos bottom side down on the glue (so the metal processor that says "wemos" is UP, NOT glued)

The above assemply is now ready to go into the enclosure.

You can find a wiring diagram showing the above here: 
https://github.com/cmgerdes/Easy-MQTT-Switch/blob/master/WemosSchematic.png

## Enclosure
Simply do the following:
1. print the enclosure using the files int he "STL" folder
2. attach the relay board to the bottom board of the enclosure using 3mm screws
3. attach the usb cable to the wemos
4. enclose the wemos with the enclosure lid and attach to the base using 5mm screws.

# Attaching to your device
This switch is simply intended to connect or disconnect two wires (the same way a light switch does).  Simply wire your device across the NO terminals in the same way you would use a light switch to turn the device on or off.

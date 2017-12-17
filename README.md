# CS207_Project
## An Arduino Mini Game Console

This Github repository was created for Computer Science 207. In this class we have to recreate an existing Arduino project and maintain a Github repository with all related files.

For our project we decided to combine two projects into one. The projects are: 

- https://www.hackster.io/Homer/arduino-web-based-car-race-brick-game-cb1b30
- https://www.hackster.io/khanhhs/arduino-web-based-two-player-game-584daa

The folders Default PHP Code and Default Arduino Code contains code from the above projects. All credit goes to the respective authors from those projects.


## Build Instructions

In order to replicate this build, you will need to setup your Arduino and breadboards in a configuration similar to the image below. (Note: You will need to plug your PHPoC Shield into the top of your Arduino UNO before connecting the wires to the respective digital/analog pins)

You will also need to make sure that the PHP files are uploaded to the PHPoC Shield. The PHP files required are: the Default Two-Player game file located in Default PHP Code folder and the modified racing PHP Code located in the Modified PHP Code folder. To upload the files follow this instruction: https://www.phpoc.com/support/manual/phpoc_debugger_manual/contents.php?id=major_upload. In addition the Wi-Fi shield will need to be connecting to the network following the instructions  at: https://www.phpoc.com/support/manual/p4s-347_user_manual/contents.php?id=network_first_setup 

The next step will be uploading the Arduino sketch from the Mode Selection folder. The sketch requires the PHPoC library which can be found at: https://github.com/phpoc/arduino

After the sketch is uploaded, open the serial monitor to see the IP address of the web server. To run the game you will need to type in the URL in a format similar to http://IP_Address/racing_game.php. (Note: the name of PHP file entered in the URL needs to be the same name as the PHP file uploaded to the Shield).

In order to switch between games, turn the potentiometer until the mode you want shows up on the Serial Monitor. Then enter the URL corresponding to the game you want to play. Mode 1 is for the two-player game whereas Mode 2 is for the racing game. 

![alt text](https://github.com/MMeer/CS207_Project/blob/master/img/Final%20Project%20Sketch_bb.jpg)

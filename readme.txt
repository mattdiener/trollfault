===Troll Fault===
This kernel module detects segmentation faults and runs the mpg123 executable to play an mp3 file every time a program causes a segmentation fault.
Note: it is a pretty simple module so you should not have any trouble figuring out how to run any executable

==Pre-Set Up==
-Make sure your kernel was compiled with CONFIG_KPROBE_EVENT=y

==Set Up==
-Install mpg123 (sudo apt-get install mpg123)
-Copy airhorn.mp3 to /etc/troll/ (you will probably need to create this directory)
-Compile the module in the ./module/ directory with make then run "sudo insmod trollfault.ko"
-Cause a segmentation fault in any application and the airhorn mp3 file will be played

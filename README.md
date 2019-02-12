# cryptopass
A CLI utility for generating passwords, based on the Chrome extension and the Android app.

Pre-requisites
--------------

Literally any distro that supports the following:
 * a C++ compiler (not meme compilers that break stuff) 
 * a recent version of CMake (because I'm lazy)
 * a recent version of OpenSSL, LibreSSL (or something else that actually works)
 * git
 * make


Compile
-------

 1. Make sure that you have the above installed.
 2. Open a terminal, tty thingy
 3. Clone this repo
 4. ``cd cryptopass``
 5. ``mkdir build; cd build``
 6. ``cmake ..``
 7. ``make``

And you should have a cryptopass executable that you can play with, yay.


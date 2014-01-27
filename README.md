hormodular
==========

Hormone-based controller for locomotion gait learning and distributed sensing on modular robots.

Inspired on the [Morphomotion project](https://code.google.com/p/morphomotion/) by Avinash Ranganath 

Installing ECF (on GNU/Linux)
--------------------------------------------------------------
Complete instructions can be found [here](http://gp.zemris.fer.hr/ecf/install.html)

 * Download latest ECF (min. 1.3.2) and unzip

 * Install boost:

        sudo apt-get install libboost-dev
    
 * Compile and install ECF:
        
        $ ./configure [ --prefix=DIR ]
        $ make
        $ make install
        
Note: for me, this whole procedure didn't work, but fortunately there is a handy script called 'ecf_install.sh' in the ECF help folder that did work.

 * If you get some error related to the shared library not being found, run this:
        
        export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

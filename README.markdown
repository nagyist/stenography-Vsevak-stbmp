Simple LSB Steganography example
======================
This is a simple C++ programm that hide message in least bits of bmp24 image.
[Read more](http://en.wikipedia.org/wiki/Steganography)

*Disclaimer: it is not cryptosystem, just the most easy example of LSB algorythm. Don't use it if you really want to save your info. Autor makes no guarantee of your informathion security and safety. Using program you agree to accept full responsibility for any damage.*

Use bmp lib [Bmp-manager](https://github.com/Shifter/Bmp-manager)

How to get
---------------------

    cd <workspace>
    git clone https://Vsevak@github.com/Vsevak/stbmp.git
    git cd stbmp
    git submodule update --init

Compilation
---------------------

* using gcc

        cd stbmp
        make

* using Visual Studio project files
* any other

Usage
---------------------

You can encrypt or decrypt some message using command line arguments or just running programm.
Optionally you can choise a char, that mark the end of your string.
Using arguments:

    stbmp [-d [PATH [ stopchar= ] ]
           -e [PATH MESSAGE [ stopchar= ] ]
           -h | --help | -help ]


Running programm just read the prompt

###Usage example:

Encrypt `some_string_to_encypt` in `picture.bmp` using arguments:

	$./stbmp -e /path/to/your/picture.bmp some_string_to_encypt
		OK

Decrypt encrypted string form `picture.bmp` using arguments:

	$./stbmp -d /path/to/your/picture.bmp
	some_string_to_encypt




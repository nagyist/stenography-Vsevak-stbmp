Simple LSB Steganography example
======================
This is a simple C++ programm that hide message in least bits of bmp24 image.
[Read more](http://en.wikipedia.org/wiki/Steganography)

Use bmp lib [Bmp-manager](https://github.com/Shifter/Bmp-manager)

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
Using arguments:

	stbmp [PATH]
	      [PATH MESSAGE]

Running programm just read the prompt

###Usage example:

Encrypt `some_string_to_encypt` in `picture.bmp` using arguments:

	$./stbmp /path/to/your/picture.bmp some_string_to_encypt
		OK

Decrypt encrypted string form `picture.bmp` using arguments:

	$./stbmp /path/to/your/picture.bmp
	some_string_to_encypt




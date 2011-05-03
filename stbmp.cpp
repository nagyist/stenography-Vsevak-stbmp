/**
 * This file is part of stbmp
 *
 *  Copyright (C) 2011, Vsevak <thevsevak@gmail.com>
 *  All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with stbmp.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stdafx.h"

using namespace std;

bool encrypt(const char* path, string message) {
	// Initialization
	bmp<RGB24> image;
	try {
		image.loadImage(path);
	} catch (exception* ex) {
		cout << "File " << path << " not exists, broken or not BMP24" << endl;
		return false;
	}

	int width = image.width();
	bitset<8> m;
	uint32_t x = 0, y = 0;
	rgb24 pixel;

	// Seting lesser bits of img to meaning bits of message
	for (string::iterator i = message.begin(); i != message.end(); i++) {
		image.getPixel(x, y, pixel);

		m = bitset<8> ((unsigned char) (*i));

		bitset<8> r = bitset<8> (pixel.red);
		bitset<8> g = bitset<8> (pixel.green);
		bitset<8> b = bitset<8> (pixel.blue);

		r[7 - 6] = m[0];
		r[7 - 7] = m[1];

		g[7 - 5] = m[2];
		g[7 - 6] = m[3];
		g[7 - 7] = m[4];

		b[7 - 5] = m[5];
		b[7 - 6] = m[6];
		b[7 - 7] = m[7];

		pixel.red = r.to_ulong();
		pixel.green = g.to_ulong();
		pixel.blue = b.to_ulong();

		image.setPixel(x, y, pixel);

		x += 1;
		if (x == width) {
			x = 0;
			y += 1;
		}
	}

	try {
		image.saveImage(path);
	} catch (...) {
		cout << "Error saving Image." << endl;
		return false;
	}
	return true;
}

string decrypt(const char* path, const unsigned char stop_symbol) {
	// Initialization
	string message = "";
	bmp<RGB24> image;
	image.loadImage(path);

	int width = image.width();
	int x = 0, y = 0;
	bitset<8> m = bitset<8> (); // Symbol of message

	// Geting chars from img to message
	for (int i = 0; i <= image.width() * image.height(); i++) {

		rgb24 pixel;
		image.getPixel(x, y, pixel);

		bitset<8> r = bitset<8> (pixel.red);
		bitset<8> g = bitset<8> (pixel.green);
		bitset<8> b = bitset<8> (pixel.blue);

		m[0] = r[7 - 6];
		m[1] = r[7 - 7];

		m[2] = g[7 - 5];
		m[3] = g[7 - 6];
		m[4] = g[7 - 7];

		m[5] = b[7 - 5];
		m[6] = b[7 - 6];
		m[7] = b[7 - 7];

		if ((unsigned char) (m.to_ulong()) == stop_symbol)
			break;

		message += (unsigned char) (m.to_ulong());

		x += 1;
		if (x == width) {
			x = 0;
			y += 1;
		}
	}
	return message + '\n';
}

int main(int argc, char* argv[]) {

	string path, message, ini;
	unsigned char stop_char = '@';

	if (argc > 1) { // Не включать в (argc > 2),
					// используется в построчном вводе
		ini = argv[1];
	}
	if (ini == "--help" || ini == "-help" || ini == "-h") {
		cout << "You can encrypt or decrypt some message" << endl;
		cout << "Hint: you can use command line with args:" << endl;
		cout << "stbmp -d [PATH [ stopsymbol= ] ]\n"
				"      -e [PATH MESSAGE [ stopsymbol= ] ]" << endl;
		return 0;
	}
	if (argc > 2) {
		if (ini == "-d") {
			switch (argc) {
			case 3:
				cout << decrypt(argv[2], stop_char);
				return 0;
			case 4:
				stop_char = argv[3][9];
				cout << decrypt(argv[2], stop_char);
				return 0;
			default:
				cout << "Bag argument number " << argc << endl;
				return 5;
			}
		} else if (ini == "-e") {
			switch (argc) {
			case 4:
				path = argv[2];
				message = argv[3];
				break;
			case 5:
				path = argv[2];
				message = argv[3];
				stop_char = argv[4][9];
				break;
			default:
				cout << "Bag argument number " << argc << endl;
				return 5;
			}
			message += stop_char;
			if (encrypt(path.c_str(), message.c_str())) {
				cout << "\tOK" << endl;
			} else {
				cout << "Error" << endl;
				return 2;
			}
			return 0;
		} else {
			cout << "Bag argument " << ini << endl;
			return 5;
		}
	}

	cout << "You can encrypt or decrypt some message" << endl;
	cout << "Hint: you can use command line with args:" << endl;
	cout << "stbmp -d [PATH [ stopsymbol= ] ]\n"
			"      -e [PATH MESSAGE [ stopchar= ] ]\n"
			"     [-h | --help | -help ]" << endl;

	if (argc < 2) {
		cout << ">>> To decrypt or to encrypt? input: 'd' or 'e'" << endl;
		cin >> ini;
	}

	cout << ">>> Path to your picture?" << endl;
	cin.ignore();
	getline(cin, path, '\n');

	cout << ">>> Any stop char? (default '@')" << endl;
	cin >> stop_char;
	cin.ignore();

	if (ini == "d" || ini == "-d") {
		cout << decrypt(path.c_str(), stop_char);
		return 0;
	}

	if (ini != "-e" && ini != "e") {
		cout << "Bad input" << endl;
		return 3;
	}

	cout << ">>> Input message" << endl;
	getline(cin, message, '\n');
	message += stop_char;

	if (encrypt(path.c_str(), message)) {
		cout << "\nOK\n" << endl;
		return 0;
	} else {
		cout << "Error" << endl;
		return 2;
	}

	return 0;
}

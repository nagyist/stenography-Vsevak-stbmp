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
	unsigned char r0, g0, b0;
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

string decrypt(const char* path) {
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

		if ((unsigned char)(m.to_ulong()) == '@')
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

	string path;
	string message;

	if (argc == 2) {
		cout << decrypt(argv[1]);
		return 0;
	} else if (argc == 3) {
		path = argv[1];
		message = argv[2];
		message += "@";
		encrypt(path.c_str(), message.c_str());
		return 0;
	}

	cout << "You can encrypt or decrypt some message\n" << endl;
	cout << "Hint: you can use command line with args:\n" << endl;
	cout << "stbmp [PATH]\n"
			"      [PATH MESSAGE]" << endl;
	cout << "\tWhere is your picture?" << endl;

	getline(cin, path);

	cout << "\tInput '@' to decrypt or message to encrypt" << endl;

	getline(cin, message);

	const char* p = path.c_str();
	if (message == "@") {
		cout << decrypt(p);
		return 0;
	}

	message += "@";

	if (encrypt(p, message)) {
		cout << "\nOK\n" << endl;
		return 2;
	}

	return 0;
}

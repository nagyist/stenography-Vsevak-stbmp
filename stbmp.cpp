#include "stdafx.h"
#include "/home/vsevak/workspace/Bmp-manager/bmp.cpp"

using namespace std;

void encrypt(const char* path, string message) {
	// Initialization
	bmp<RGB24> image;
	try {
		image.loadImage(path);
	} catch (exception ex) {
		cout << "File " << path << " not exists " << endl;
		return;
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

	image.saveImage(path);
}

string decrypt(const char* path) {
	// Initialization
	string message = "";
	bmp<RGB24> image;
	try {
		image.loadImage(path);
	} catch (exception ex) {
		cout << "File " << path << " not exists " << endl;
		return "Error. Aborted. Retry";
	}

	int width = image.width();
	int x = 0, y = 0;
	unsigned char r0, g0, b0;
	bitset<8> m = bitset<8> (); // Symbol of message

	// Geting chars from img to message
	for (int i = 0; i <= image.width()*image.height(); i++) {

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

		if (char(m.to_ulong()) == '@')
			break;

		message += (unsigned char) (m.to_ulong());

		x += 1;
		if (x == width) {
			x = 0;
			y += 1;
		}
	}
	return message;
}

int main(int argc, char* argv[]) {
	bool flag = 1;
	cout << "You can encrypt or decrypt some message\n" << endl;
	while (flag) {
		cout << "Encrypt or decrypt? (input 1 or 0)" << endl;
		cin >> flag;
		if (flag) {
			cin.ignore();

			cout << "   Where is your picture?" << endl << "Use english path"
					<< endl;
			string path;
			getline(cin, path);

			cout << "   Input message to encrypt" << endl;
			string message;
			getline(cin, message);
			message += '@';

			encrypt(path.c_str(), message);
			cout << "\nOK\n" << endl;
		} else {
			cout << "   Where is your picture?" << endl << "Use english path"
					<< endl;
			string path;
			cin.ignore();
			getline(cin, path);
			cout << decrypt(path.c_str());
		}
	}
	return 0;
}

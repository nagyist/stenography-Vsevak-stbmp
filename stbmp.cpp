#include "stdafx.h"

using namespace std;

void encrypt(string path, string message){
	// Initialization
	bitmap_image bmp = bitmap_image();
	try{
		bmp = bitmap_image(path);
	} catch(exception ex){
		cout<<"File "<< path << " not exists "<<endl;
		return;
	}
	int width = bmp.width();
	bitset<8> m;
	unsigned char r0,g0,b0;
	int x = 0 ,y = 0;
	// Seting lesser bits of img to meaning bits of message
	for(string::iterator i=message.begin(); i!=message.end(); i++){
		bmp.get_pixel(x,y,r0,g0,b0);

		m = bitset<8>((unsigned char)(*i));

		bitset<8> r = bitset<8>(r0); 
		bitset<8> g = bitset<8>(g0);
		bitset<8> b = bitset<8>(b0);

		r[7-6] = m[0];
		r[7-7] = m[1];

		g[7-5] = m[2];
		g[7-6] = m[3];
		g[7-7] = m[4];

		b[7-5] = m[5];
		b[7-6] = m[6];
		b[7-7] = m[7];

		r0 = r.to_ulong();
		g0 = g.to_ulong();
		b0 = b.to_ulong();

		bmp.set_pixel(x,y,r0,g0,b0);

		x +=1;
		if (x==width){
			x=0;
			y+=1;
		}
	}

	bmp.save_image(path);
}



string decrypt(string path){
	// Initialization
	string message = "";
	bitmap_image bmp;
	try{
		bmp = bitmap_image(path);
	} catch(exception ex){
		cout<<"File "<< path << " not exists "<<endl;
		return "Error. Aborted. Retry";
	}
	int width = bmp.width();
	int x=0, y=0;
	unsigned char r0,g0,b0;
	bitset<8> m = bitset<8>();	// Symbol of message
	// Geting chars from img to message
	for(int i=0; i<=bmp.pixel_count(); i++){

		bmp.get_pixel(x,y,r0,g0,b0);

		bitset<8> r = bitset<8>(r0);
		bitset<8> g = bitset<8>(g0);
		bitset<8> b = bitset<8>(b0);

		m[0] = r[7-6];
		m[1] = r[7-7];

		m[2] = g[7-5];
		m[3] = g[7-6];
		m[4] = g[7-7];

		m[5] = b[7-5];
		m[6] = b[7-6];
		m[7] = b[7-7];

		if (char(m.to_ulong()) == '@') break;

		message += (unsigned char)(m.to_ulong());

		x +=1;
		if (x==width){
			x=0;
			y+=1;
		}
	}
	return message;
}



int main(int argc, char* argv[])
{
	bool flag=1;
	cout << "You can encrypt or decrypt some message\n" << endl;
	while (flag) {
		cout << "Encrypt or decrypt? (input 1 or 0)" << endl;
		cin>>flag;
		if (flag) {
			cin.ignore();

			cout << "   Where is yo picture?" << endl << "Use english path"<< endl;
			string path;
			getline(cin,path);

			cout << "   Input message to encrypt" << endl;
			string message;
			getline(cin, message);
			message +='@';

			encrypt(path, message);
			cout << "\nOK\n" << endl;
		}
		else{
			cout << "   Where is yo picture?" << endl << "Use \"/\" kind'a 'C:/a/b/c.bmp'"<< endl;
			string path;
			cin.ignore();
			getline(cin,path);
			cout << decrypt(path);
		}
	}
}

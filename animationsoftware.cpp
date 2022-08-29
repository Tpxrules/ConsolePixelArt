#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
using namespace std;
int x, y, frame= 0, sizer, repeats;
int storage[45][22][10];
int sizex = 45, sizey = 22;
// made by tpxrules
void save() {
	ofstream out;
	out.open("drawing.txt"); //savefile
	for (int k = 0; k < 10 ; k++) {
		for (int i = 0; i < sizey; i++)
		{
			for (int j = 0; j < sizex; j++)
				out << storage[j][i][k] << " ";
			out << endl;
		}
	}
	out.close();
	cout << "saving............... \n";
}
void incode() {
	ofstream out;
	for (int page = 0; page < 10; page++)
	{
		string var = "frame" + to_string(page + 1) + ".ppm";
		out.open(var);	
		//initializing PPM file
		out << "P3" << " " << sizex*10 << " " << sizey*10 << " " << 255 << endl;
		for (int i = 0; i < sizey; i++)
		{
			for (size_t o = 0; o < 10; o++)
			{
				for (int j = 0; j < sizex; j++) {

					for (size_t p = 0; p < 10; p++)
					{
						// translating CMD colors to RGB values
						switch (storage[j][i][page])
						{
						case 0:
							out << "0 0 0 " << endl;
							break;
						case 1:
							out << "0 55 149 " << endl;
							break;
						case 2:
							out << "16 139 14 " << endl;
							break;
						case 3:
							out << "58 150 221 " << endl;
							break;
						case 4:
							out << "255 0 0 " << endl;
							break;
						case 5:
							out << "33 18 129 " << endl;
							break;
						case 6:
							out << "255 216 79 " << endl;
							break;
						case 7:
							out << "205 205 205 " << endl;
							break;
						case 8:
							out << "118 118 118 " << endl;
							break;
						case 9:
							out << "59 120 225 " << endl;
							break;
						case 10:
							out << "22 198 12 " << endl;
							break;
						case 11:
							out << "97 214 214 " << endl;
							break;
						case 12:
							out << "231 72 86 " << endl;
							break;
						case 13:
							out << "180 0 158 " << endl;
							break;
						case 14:
							out << "249 241 165 " << endl;
							break;
						case 15:
							out << "255 255 255 " << endl;
							//white
							break;
						default:
							out << "0 0 0 " << endl;
							break;
						}
					}
				}
			}
		}
		out.close();
	}
}
void toptext() {
	// astheticness *sparkles*
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//---------------
	cout << " ________________________________________________________________________________________\n"
		<< "|Paint.exe_________________________________________________________________________";
	SetConsoleTextAttribute(hConsole, 10);
	cout << "[-]";
	SetConsoleTextAttribute(hConsole, 4);
	cout << "[X]";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|\n";

	//------------------------------------
	SetConsoleTextAttribute(hConsole, 15);
	cout << "( wasd ) move, ( e ) pixel, ( f ) fill , (r) drawing, ( n and m ) frame change\n";
	SetConsoleTextAttribute(hConsole, 14);
	cout << " (k) reload, ( i ) export, ( q ) save, ( x ) save and exit.";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "\t frame:( ";
	SetConsoleTextAttribute(hConsole, 10);
	cout << frame+1;
	SetConsoleTextAttribute(hConsole, 15);
	cout << " / 10 )\n";
	for (int i = 0; i < 16; i++)
	{
		SetConsoleTextAttribute(hConsole, i);
		cout << i << "  ";
	}
	cout << "\n\n";
}
void fill(int ins) {
	//to fill up the entire page with one color
	for (int i = 0; i < sizey; i++)
	{
		for (int j = 0; j < sizex; j++)
			storage[j][i][frame] = ins;
		cout << "\n";
	}
}
void render() {
	// render the scene every update
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < sizey; i++)
	{
		for (int j = 0; j < sizex; j++)
		{
			SetConsoleTextAttribute(hConsole, storage[j][i][frame]);
			if (y == i and x == j)
				cout << "X ";
			else
				cout << "0\ ";
		}
		cout << "\n";
	}
	//setting to white to make commands always white after
	SetConsoleTextAttribute(hConsole, 15);
}
void play() {
	//playing the animation.
	for (int i = 0; i < repeats; i++)
	{
		frame = 0;
		for (int j = 0; j < sizer; j++) {
			Sleep(10);
			system("cls");
			render();
			frame++;
		}
	}
	frame = 0;
}
void load() {
	//input previous saves 
	ifstream in;
	in.open("drawing.txt"); //save file
	for (int k = 0; k < sizey; k++){
		for (int i = 0; i < sizey; i++)
		{
			for (int j = 0; j < sizex; j++)
				in >> storage[j][i][k];
		}
}
	in.close();

}
void brain() {
	//input system
	bool drawing = false;
	char input;
	short int ins;
	bool open = true;

	//brains
	while (1)
	{
		system("cls");
		toptext();
		render();
		// draws when drawing is true
		if (drawing == true)
			storage[x][y][frame] = ins;

		cin >> input;
		//movement
		if (input == 'a' and x > 0) {
			x--;
		}
		else	if (input == 'd' and x < sizex - 1) {
			x++;
		}
		else	if (input == 'w' and y > 0) {
			y--;
		}
		else	if (input == 's' and y < sizey - 1) {
			y++;
		}
		//changing between frames
		else if (input == 'n' and frame > 0) {
			frame--;
		}
		else if (input == 'm' and frame < 9) {
			frame++;
		}else{
		switch (input)
		{
		case 'k':
			load();
			break;
		case 'e':
			cout << "color code:\t";
			cin >> ins;
			storage[x][y][frame] = ins;
			break;
		case 'r':
			if (drawing == true)
				drawing = false;
			else {
				cout << "color code:\t";
				drawing = true;
				cin >> ins;
			}
			break;
		case 'q':
			save();
			break;
		case 'i':
			incode();
			break;
		case 'p':
			cout << "how many frames are you going to display: \t";
			cin >> sizer;
			cout << "repeat amount: \t";
			cin >> repeats;
			play();
			break;
		case 'f':
			cout << "color code:\t";
			cin >> ins;
			fill(ins);
			break;
		case 'x':
			save();
			return;
			break;
		default:
			break;
		}
	}
	}
}
int main()
{
	//main menu
	int input = 0;
	while (1)
	{		
			HANDLE  hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		{
			cout << " ________________________________________________________________________\n"
				<< "|Paint.exe_________________________________________________________";
			SetConsoleTextAttribute(hConsole, 10);
			cout << "[-]";
			SetConsoleTextAttribute(hConsole, 4);
			cout << "[X]";
			SetConsoleTextAttribute(hConsole, 15);
			cout << "|\n";
			cout << "|\t\t\t\t\t\t\t\t\t |\n|\t\t\t\t\t\t\t\t\t |\n|\t\t\t\t\t\t\t\t\t |\n"
				<< "| 1\tto open old drawing                                              |\n"
				<< "| 2\tto make new file                                                 |"
				<< "\n| 3\tto exit                                                          |\n|\t\t\t\t\t\t\t\t\t |\n|\t\t\t\t\t\t\t\t\t |\n|\t\t\t\t\t\t\t\t\t |\n"
				<< "|________________________________________________________________________|\n console :\n >>>";
		}
		cin >> input;
		if (input == 1) {
			//load save
			load();
			brain();
		}
		else if (input == 2) {
			//fill with white
			fill(15);
			brain();
		}
		else if (input == 3) {
			//exit
			return (0);
		}
		system("cls");
	}
	return 0;
}

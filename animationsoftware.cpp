#include <iostream>
#include <windows.h> //for handles
#include <fstream> // for file stuff
#include <string>// in incoding
#include <conio.h> // for button presses
using namespace std;
int x, y, frame = 0, sizer, repeats;
int storage[45][22][10];
int sizex = 45, sizey = 22;
HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
bool drawing = false, thiccdrawing = false;
short int ins;
// made by tpxrules
void save() {
	ofstream out;
	out.open("drawing.txt"); //savefile
	for (int k = 0; k < 10; k++) {
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
		out << "P3" << " " << sizex * 10 << " " << sizey * 10 << " " << 255 << endl;
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
		}out.close();
	}
}
void toptext() {
	// astheticness *sparkles*
	//---------------
	cout << " _________________________________________________________________________________________\n"
		<< "|Paint.exe_________________________________________________________________________";
	SetConsoleTextAttribute(hConsole, 10);
	cout << "[-]";
	SetConsoleTextAttribute(hConsole, 4);
	cout << "[X]";
	SetConsoleTextAttribute(hConsole, 15);
	cout << " |\n";
	//------------------------------------
	SetConsoleTextAttribute(hConsole, 15);
	cout << "( wasd ) move, ( e ) pixel, ( f ) fill , (r) drawing, ( n and m ) frame change \n\t\t\t(t) thick drawing (o)color picker  (";
	SetConsoleTextAttribute(hConsole, ins * 16 + ins);
	cout << "0000";
	SetConsoleTextAttribute(hConsole, 15);
	cout << ")\n";
	SetConsoleTextAttribute(hConsole, 14);
	cout << " (k) reload, ( i ) export, ( q ) save, ( x ) save and exit.";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "\t frame:( ";
	SetConsoleTextAttribute(hConsole, 10);
	cout << frame + 1;
	SetConsoleTextAttribute(hConsole, 15);
	cout << " / 10 )\n";
	SetConsoleTextAttribute(hConsole, 7);
	cout << "               0  ";
	for (int i = 1; i < 16; i++)
	{
		SetConsoleTextAttribute(hConsole, i * 16);
		cout << i << "  ";
	}
	SetConsoleTextAttribute(hConsole, 7);
	cout << "| \n\n";
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
	for (int i = 0; i < sizey; i++)
	{
		for (int j = 0; j < sizex; j++)
		{
			if (y == i and x == j) {
				if (storage[j][i][frame] == 0)
					SetConsoleTextAttribute(hConsole, 7);// here.
				else
					SetConsoleTextAttribute(hConsole, storage[j][i][frame] * 16);
				cout << "X ";
			}
			else {
				SetConsoleTextAttribute(hConsole, storage[j][i][frame] * 16 + storage[j][i][frame]);
				//hue(storage[j][i][frame]);
				cout << "0 ";
			}
		}
		SetConsoleTextAttribute(hConsole, 7);
		cout << "|\n";
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
	for (int k = 0; k < sizey; k++) {
		for (int i = 0; i < sizey; i++)
		{
			for (int j = 0; j < sizex; j++)
				in >> storage[j][i][k];
		}
	}
	in.close();
}
void rerender() {
	system("cls");
	toptext();
	render();
}
void draw() {
	if (drawing == true)
		storage[x][y][frame] = ins;
	if (thiccdrawing == true) {
		storage[x][y][frame] = ins;
		if (y < 22) {
			storage[x - 1][y + 1][frame] = ins;
			storage[x + 1][y + 1][frame] = ins;
			storage[x][y + 1][frame] = ins;
		}
		if (y > 0) {
			storage[x + 1][y - 1][frame] = ins;
			storage[x - 1][y - 1][frame] = ins;
			storage[x][y - 1][frame] = ins;
		}
		storage[x + 1][y][frame] = ins;
		storage[x - 1][y][frame] = ins;
	}
}
void brain() {
	//input system
	char input;
	bool open = true;
	rerender();
	//brains
	while (1)
	{
		// draws when drawing is trues
		if (_kbhit()) {
			switch (_getch())
			{
			case 'a':
				if (x > 0)
					x--;
				draw();
				rerender();
				break;
			case 'd':
				if (x < sizex - 1)
					x++;
				draw();
				rerender();
				break;
			case 'w':
				if (y > 0) {
					y--;
					draw();
					rerender();
					break;
			case 's':
				if (y < sizey - 1)
					y++;
				draw();
				rerender();
				break;
			case 'n':
				if (frame > 0)
					frame--;
				rerender();
				break;
			case 'm':
				if (frame < 9)
					frame++;
				rerender();
				break;
			case 'k':
				load();
				rerender();
				break;
			case 'e':
				storage[x][y][frame] = ins;
				rerender();
				break;
			case 'r':
				if (drawing == true)
					drawing = false;
				else {

					drawing = true;
					draw();
				}
				rerender();
				break;
			case 't':
				if (thiccdrawing == true)
					thiccdrawing = false;
				else {

					thiccdrawing = true;
					draw();
				}
				rerender();
				break;
			case 'o':
				cout << "color code:\t";
				cin >> ins;
				rerender();
				break;
			case 'q':
				save();
				rerender();
				break;
			case 'i':
				incode();
				rerender();
				break;
			case 'p':
				cout << "how many frames are you going to display: \t";
				cin >> sizer;
				cout << "repeat amount: \t";
				cin >> repeats;
				play();
				rerender();
				break;
			case 'f':
				cout << "color code:\t";
				cin >> ins;
				fill(ins);
				rerender();
				break;
			case 'x':
				save();
				return;
				rerender();
				break;
			default:

				break;
				}
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

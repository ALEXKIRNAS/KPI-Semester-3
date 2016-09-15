#include "Interface.h"

// Введення файлу
void input_name(char* title, string& name) {
	cout << "Enter name for " << title << " file:\t";
	cin >> name;
}

// Копіювання файлу
void cpyFile(string& from, string& to) {
	ifstream in(from.data(), ios::binary | ios::in);
	ofstream out(to.data(), ios::binary | ios::out | ios::trunc);

	if (!in) {
		cout << "No such file as: " << from << "!\nNothing to do.";
		system("pause");
		exit(-1);
	}

	cout << "Begin copy from: " << from << " to " << to << "\n";
	cout << "Progress: [";
	for (int i = 0; i < DONE; i++) cout << " ";
	cout << "]";

	for (int i = 0; i < DONE + 1; i++) cout << "\b";

	char buf[BLOCK];
	int curr = 0;
	in.seekg(0, ios::_Seekend);
	size_t size = in.tellg() / DONE;
	in.seekg(0, ios::_Seekbeg);

	while (!in.eof()) {
		in.read(buf, sizeof(buf));
		int inputed = in.gcount();

		out.write(buf, sizeof(char) * inputed);

		while (in.tellg() > curr * size) {
			curr++;
			cout << '.';
			if (inputed != BLOCK) break;
		}
	}

	if (curr != DONE) cout << '.';
	cout << "]";

	cout << "\nDone.\n";
	cout.flush();
}
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <string.h>
#include <conio.h>
//Подключение библиотеки Winscok2, в которой содержаться функции для работы с сокетами
#include <winsock2.h>
#include <thread>
#include "snakelogic.h"
#include "serverrelated.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;
void drawfield(SOCKET sock) {
	generate();
	int n = 1;
	while (n != -1) {
		char buf[2000];
		memset(buf, 0, 2000);
		n = recv(sock, buf, 2000, 0);
		string data = buf;
		
		int c = 0;
		while (c < data.size()) {
			for (int i = 0; i < field.size(); ++i) {
				for (int j = 0; j < field[i].size(); ++j) {
					string tmp = "";
					while (data[c] != ' ') {
						tmp += data[c];
						++c;
					}
					field[i][j] = STI(tmp);
					++c;
				}
			}
		}
		draw();
	}
}
int main() {
	SOCKET sockk = createclient();
	thread mainthr(drawfield, sockk);
	mainthr.detach();
	while (1) {
		char buf[2000];
		char data = _getch();
		string msg = "";
		if (data == 'w')
			msg += data;
		else if (data == 'a')
			msg += "left";
		else if (data == 's')
			msg += "down";
		else if (data == 'd')
			msg += "right";
		else
			msg += "stay";
		send(sockk, msg.c_str(), msg.size(), 0);
	}
	closesocket(sockk);
	return 0;
}

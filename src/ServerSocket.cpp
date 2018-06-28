#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fstream>
#include <string.h>
#include <iostream>

#define PORT 8080

struct sockaddr_in serv;

int main() {
	int skt = socket(AF_INET, SOCK_STREAM, 0);
	
	if (skt < 0){
		std::cout << "Error openning socket" << std::endl;
		exit(1);
	}		
	
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = INADDR_ANY;
	serv.sin_port = htons(PORT);
	memset(&(serv.sin_zero), 0x00, sizeof(serv.sin_zero));
	
	if((bind(skt, (struct sockaddr*)&serv, sizeof(serv))) < 0) {
		std::cout << "Unnable to bind" << std::endl;
		exit(1);
	}
	
	listen(skt, 1);
	std::cout << "Server listening on port " << PORT;
	
	return std::cin.get();
}
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <unistd.h>

struct sockaddr_in serv, client_addr;

int main() 
{	
	std::cout << "Enter the server port: " << std::endl;
	int PORT;
	std::cin >> PORT;

	std::cout << "Enter the message maximum size: " << std::endl;
	int MAXSIZE;
	std::cin >> MAXSIZE;
	
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
	
	std::cout << "Server listening on port " << PORT;
	listen(skt, 5);
	
	int newskt = accept(skt, (struct sockaddr*)&client_addr, (socklen_t*)sizeof(client_addr));
	
	if (newskt < 0) {
		perror("Erron on accpet client");
		exit(1);
	} 
	
	char* buffer[MAXSIZE];
	bzero(buffer, MAXSIZE);
	
	int sktread = read(newskt, buffer, MAXSIZE-1);
	
	if (sktread < 0) {
		std::cout << "Error reading message";
		exit(1);
	}
	
	std::fstream stream("message.dat", std::ios::out | std::ios::binary | std::ios::trunc);
	
	if (stream.good()) {
		stream << buffer;

		if ((write(newskt, "Message recieved and saved properly", 36)) < 0) {
			std::cout << "Error writing message" << std::endl;
			exit(1);
		}		
	}
	else {
		write(newskt, "Erro openning file, connection closed.", 40);
		exit(1);
	}
	
	return std::cin.get();
}
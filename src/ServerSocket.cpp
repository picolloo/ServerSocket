#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <unistd.h>

#define PORT 8080

struct sockaddr_in serv, client_addr;

int main() {
	char* buffer[256];
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
	
	int newskt = accept(skt, (struct sockaddr*)&client_addr, (socklen_t*)sizeof(client_addr));
	
	if (newskt < 0) {
		perror("Erron on accpet client");
		exit(1);
	} 
	
	bzero(buffer, 256);
	
	int sktread = read(newskt, buffer, 255);
	
	if (sktread < 0) {
		std::cout << "Error reading message";
		exit(1);
	}
	
	std::cout << "The message recieved is: " << buffer << std::endl;

	if ((write(newskt, "I recieve your message properly", 31)) < 0) {
		std::cout << "Error writing message" << std::endl;
		exit(1);
	}
	
	
	return std::cin.get();
}
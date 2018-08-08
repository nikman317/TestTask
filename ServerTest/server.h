#include <thread>
#include <string>
#include <iostream>
#include <chrono>


#include "saveQueue.h"


class Server
{
public:
	Server(FILE * f);
	~Server();

	void addClient(std::string message, int delay, int number);
	void ejectMessage();

private:
	FILE * file;
	std::ofstream * os;
	SaveQueue<std::string> q;
	void clientIteration(std::string message, int delay, int number, SaveQueue<std::string>* q);
};



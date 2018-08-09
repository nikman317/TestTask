#include "server.h"
#include <time.h>

Server::Server(FILE * f)
{
	file = f;
}

Server::~Server()
{
	fclose(file);
}

void Server::addClient(std::string message, int delay, int number)
{
	std::thread t(&Server::clientIteration, this, message, delay, number, &q);
	t.detach();
};

void Server::clientIteration(std::string message, int delay, int number, SaveQueue<std::string>* q)
{
	char timeChar[16];
	time_t t;
	t = time(NULL);
	strftime(timeChar, 16, "%X", localtime(&t));
	std::string m(timeChar);
	m += "; " + std::to_string(number) + ": " + message + "\n";
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(delay));
		q->push(m);
	}

};

void Server::ejectMessage()
{
	std::string s = q.pop();
	
	fprintf(file, "%s", s.c_str());

}


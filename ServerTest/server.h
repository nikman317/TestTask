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

	void addClient(std::string message, int delay, int number);										//создает нового клиента и запускает его работу
	void ejectMessage();																			//достает сообщение из очереди и записывает его в чат(файл)

private:
	FILE * file;
	std::ofstream * os;
	SaveQueue<std::string> q;																		//потокобезопасная очередь(сделанна с учетом цели её использования)
	void clientIteration(std::string message, int delay, int number, SaveQueue<std::string>* q);	//повидение клиента - бесконченый цикл с переодичческой отправкой сообщений
};



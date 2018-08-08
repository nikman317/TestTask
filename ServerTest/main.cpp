
#include "server.h"
#include <sstream>
#include <vector>



int main()
{
	std::string temp, temp2;
	FILE * f;
	int n;

	getline(std::cin, temp);
	f = fopen(temp.c_str(), "w");
	if (f == NULL)
		perror("Error opening file");

	Server s(f);
	getline(std::cin, temp);
	n = atoi(temp.c_str());
	if (n < 1)
		perror("Uncorrect number of client");

	int* delays = new int[n];
	std::vector<std::string> allMessage;

	for (int i = 0; i < n; i++)
	{
		getline(std::cin, temp);
		std::istringstream ss(temp);
		ss >> temp2;
		delays[i] = (atoi(temp2.c_str()));
		ss >> temp2;
		allMessage.push_back(temp2);
	}

	for (int i = 0; i < n; i++)
	{
		s.addClient(allMessage.back(), delays[n-i-1], n-i);
		allMessage.pop_back();
	}

	delete[] delays;
		
	while (true)
	{
		s.ejectMessage();
	}
	return 0;
}


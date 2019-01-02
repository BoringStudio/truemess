#include <iostream>

#include "Core/Core.h"
#include "Managers/DatabaseManager.h"
#include "Managers/NetworkManager.h"
#include "Managers/UserManager.h"
#include "Managers/RoomManager.h"

class ServerCore : public Core
{
public:
	ServerCore()
	{
		m_databaseManager = provide<DatabaseManager>("truemess.db");
		m_networkManager = provide<NetworkManager>();
		m_userManager = provide<UserManager>();
		m_roomManager = provide<RoomManager>();
	}

	void run() override
	{
		m_databaseManager->init();
		m_networkManager->init();
		m_userManager->init();
		m_roomManager->init();
	}

private:
	DatabaseManager::ptr m_databaseManager;
	NetworkManager::ptr m_networkManager;
	UserManager::ptr m_userManager;
	RoomManager::ptr m_roomManager;
};

int main(int argc, char** argv)
{
	try {
		ServerCore core;
		core.run();
	}
	catch(const std::runtime_error& e) {
		std::cout << e.what();
		std::cin.get();
	}

	return 0;
}
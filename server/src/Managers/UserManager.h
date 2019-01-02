#pragma once

#include <memory>

#include "../Stuff/Manager.h"

class DatabaseManager;

class UserManager : public Manager<UserManager>
{
public:
	explicit UserManager(const Core& core);

	void init();

private:
	std::shared_ptr<DatabaseManager> m_databaseManager;
};
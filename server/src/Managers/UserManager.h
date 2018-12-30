#pragma once

#include <memory>

#include "../Stuff/BaseManager.h"

class DatabaseManager;

class UserManager : public BaseManager, public PointerDefs<UserManager>
{
public:
	explicit UserManager(const Core& core);

	void init();

private:
	std::shared_ptr<DatabaseManager> m_databaseManager;
};
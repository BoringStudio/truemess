#pragma once

#include <memory>

#include "../Stuff/Manager.h"

class DatabaseManager;

struct Room
{
	uint32_t m_id;
	
};

class RoomManager : public Manager<RoomManager>
{
public:
	explicit RoomManager(const Core& core);

	void init();

private:
	std::shared_ptr<DatabaseManager> m_databaseManager;
};
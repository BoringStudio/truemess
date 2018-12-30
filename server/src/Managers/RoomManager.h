#pragma once

#include <memory>

#include "../Stuff/BaseManager.h"

class DatabaseManager;

struct Room
{
	uint32_t m_id;
	
};

class RoomManager : public BaseManager, public PointerDefs<RoomManager>
{
public:
	explicit RoomManager(const Core& core);

	void init();

private:
	std::shared_ptr<DatabaseManager> m_databaseManager;
};
#include "RoomManager.h"

#include "../Core/Core.h"
#include "DatabaseManager.h"

RoomManager::RoomManager(const Core & core) :
	BaseManager(core)
{
	m_databaseManager = core.get<DatabaseManager>();
}

void RoomManager::init()
{
	m_databaseManager->execute(
		"CREATE TABLE IF NOT EXISTS `rooms` ("
		"	`id`		INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
		"	`name`		TEXT NOT NULL,"
		"	`type`		INTEGER NOT NULL DEFAULT 0"
		");"
	);
}

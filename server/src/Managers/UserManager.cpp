#include "UserManager.h"

#include "../Core/Core.h"
#include "DatabaseManager.h"

UserManager::UserManager(const Core& core) :
	BaseManager(core)
{
	m_databaseManager = core.get<DatabaseManager>();
}

void UserManager::init()
{
	m_databaseManager->execute(
		"CREATE TABLE IF NOT EXISTS `users` ("
		"	`id`		INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
		"	`username`	TEXT NOT NULL,"
		"	`password`	TEXT NOT NULL"
		");"
	);
}

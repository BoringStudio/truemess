#pragma once

#include <string>
#include <sqlite3pp.h>

#include "../Stuff/BaseManager.h"

class DatabaseManager : public BaseManager, public PointerDefs<DatabaseManager>
{
public:
	DatabaseManager(const Core& core, const std::string& db);
	~DatabaseManager();

	void init();

	void execute(const std::string& sql);

	sqlite3pp::database& getDatabase() const;

private:
	std::string m_name;
	std::unique_ptr<sqlite3pp::database> m_database;
};

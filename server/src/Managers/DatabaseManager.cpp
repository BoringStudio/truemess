#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(const Core& core, const std::string& db) :
	Manager(core), m_name(db)
{
	m_database = std::make_unique<sqlite3pp::database>(db.c_str());
}

DatabaseManager::~DatabaseManager()
{
	m_database.reset();
}

void DatabaseManager::init()
{
	m_database = std::make_unique<sqlite3pp::database>(m_name.c_str());

	log("initialized");
}

void DatabaseManager::execute(const std::string& sql)
{
	const auto ret = m_database->execute(sql.c_str());

	if (ret != SQLITE_OK) {
		throw std::runtime_error(m_database->error_msg());
	}
}

sqlite3pp::database& DatabaseManager::getDatabase() const
{
	return *m_database;
}

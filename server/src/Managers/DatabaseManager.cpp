#include "DatabaseManager.h"

DatabaseManager::ConnectionHandle::ConnectionHandle(DatabaseManager& manager, size_t id, sqlite3pp::database* database) :
	m_id(id), m_isValid(true), m_manager(manager), m_database(database)
{
}

DatabaseManager::ConnectionHandle::~ConnectionHandle()
{
	m_manager.release(m_id);
	invalidate();
}

bool DatabaseManager::ConnectionHandle::isValid() const
{
	return m_isValid;
}

sqlite3pp::database* DatabaseManager::ConnectionHandle::operator->() const
{
	return m_database;
}

sqlite3pp::database& DatabaseManager::ConnectionHandle::operator*() const
{
	return *m_database;
}

sqlite3pp::database& DatabaseManager::ConnectionHandle::operator*()
{
	return *m_database;
}

void DatabaseManager::ConnectionHandle::invalidate()
{
	m_isValid = false;
}

DatabaseManager::DatabaseManager(const Core& core, const std::string& db) :
	Manager(core), m_name(db)
{
}

void DatabaseManager::init()
{
	m_connections.resize(4);
	for (size_t i = 0; i < CONNECTION_COUNT; ++i) {
		m_connections[i].database = std::make_unique<sqlite3pp::database>(m_name.c_str());
	}

	log("initialized");
}

DatabaseManager::ConnectionHandle DatabaseManager::getDatabase()
{
	while(true) {
		{
			std::unique_lock<std::mutex> lock(m_connectionsMutex);
			for (size_t i = 0; i < m_connections.size(); ++i) {
				if (m_connections[i].busy) {
					continue;
				}

				m_connections[i].busy = true;
				return ConnectionHandle(*this, i, m_connections[i].database.get());
			}
		}

		{
			std::unique_lock<std::mutex> lock(m_availabilityMutex);
			m_availableConnection.wait(lock);
		}
	}
}

void DatabaseManager::release(size_t id)
{
	{
		std::unique_lock<std::mutex> lock(m_connectionsMutex);
		m_connections[id].busy = false;
	}

	m_availableConnection.notify_all();
}

#pragma once

#include <string>
#include <sqlite3pp.h>

#include "../Stuff/Manager.h"

class DatabaseManager : public Manager<DatabaseManager>
{
	struct Connection
	{
		bool busy = false;
		std::unique_ptr<sqlite3pp::database> database;
	};

public:
	class ConnectionHandle
	{
	public:
		~ConnectionHandle();

		bool isValid() const;

		sqlite3pp::database* operator->() const;
		sqlite3pp::database& operator*() const;
		sqlite3pp::database& operator*();

	private:
		friend class DatabaseManager;

		ConnectionHandle(DatabaseManager& manager, size_t id, sqlite3pp::database* database);

		void invalidate();

		size_t m_id;
		bool m_isValid;
		DatabaseManager& m_manager;
		sqlite3pp::database* m_database;
	};

	DatabaseManager(const Core& core, const std::string& db);

	void init();

	ConnectionHandle getDatabase();

private:
	friend class ConnectionHandle;

	static const size_t CONNECTION_COUNT = 4;

	void release(size_t id);

	std::string m_name;

	std::mutex m_connectionsMutex;
	std::vector<Connection> m_connections;

	std::mutex m_availabilityMutex;
	std::condition_variable m_availableConnection;
};

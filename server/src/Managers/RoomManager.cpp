#include "RoomManager.h"

#include "DatabaseManager.h"

Room::Room(uint32_t id, const std::string& name, Type type) :
	m_id(id), m_name(name), m_type(type)
{
}

uint32_t Room::getId() const
{
	return m_id;
}

std::string Room::getName() const
{
	return m_name;
}

Room::Type Room::getType() const
{
	return m_type;
}

RoomManager::RoomManager(const Core & core) :
	Manager(core)
{
	m_databaseManager = core.get<DatabaseManager>();
}

void RoomManager::init()
{
	auto database = m_databaseManager->getDatabase();
	
	database->execute(
		"CREATE TABLE IF NOT EXISTS `rooms` ("
		"	`id`		INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
		"	`name`		TEXT NOT NULL,"
		"	`type`		INTEGER NOT NULL DEFAULT 0"
		");"
	);

	sqlite3pp::query query(*database, 
		"SELECT * FROM `rooms`;"
	);

	for (auto row : query) {
		auto[id, name, type] = row.get_columns<int32_t, const char*, int32_t>(0, 1, 2);
		m_rooms.emplace(id, std::make_shared<Room>(id, name, static_cast<Room::Type>(type)));
	}
}

Room::ptr RoomManager::createRoom(const std::string& name, Room::Type type)
{
	auto database = m_databaseManager->getDatabase();

	sqlite3pp::transaction transaction(*database);

	sqlite3pp::command command(*database, 
		"INSERT INTO `rooms` (`name`, `type`) VALUES (:name, :type);"
	);
	command.bind(":name", name.data(), static_cast<int>(name.size()), sqlite3pp::nocopy);
	command.bind(":type", static_cast<int>(type));
	
	if (command.execute() != SQLITE_OK) {
		return nullptr;
	}

	const auto id = static_cast<uint32_t>(database->last_insert_rowid());

	transaction.commit();

	auto [iterator, inserted] = m_rooms.emplace(id, std::make_shared<Room>(id, name, type));

	return iterator->second;
}

bool RoomManager::renameRoom(uint32_t id, const std::string& name)
{
	auto database = m_databaseManager->getDatabase();

	sqlite3pp::command command(*database,
		"UPDATE `rooms` SET `name` = :name WHERE `id` = :id"
	);
	command.bind(":id", static_cast<int>(id));
	command.bind(":name", name.data(), static_cast<int>(name.size()), sqlite3pp::nocopy);

	if (command.execute() != SQLITE_OK) {
		return false;
	}

	const auto it = m_rooms.find(id);
	if (it == m_rooms.end()) {
		return false;
	}

	it->second->m_name = name;
	return true;
}

bool RoomManager::removeRoom(uint32_t id)
{
	auto database = m_databaseManager->getDatabase();

	sqlite3pp::command command(*database,
		"DELETE FROM `rooms` WHERE `id` = :id"
	);
	command.bind(":id", static_cast<int>(id));

	if (command.execute() != SQLITE_OK) {
		return false;
	}

	const auto it = m_rooms.find(id);
	if (it == m_rooms.end()) {
		return false;
	}

	m_rooms.erase(it);
	return true;
}

const std::unordered_map<uint32_t, Room::ptr>& RoomManager::getRooms() const
{
	return m_rooms;
}

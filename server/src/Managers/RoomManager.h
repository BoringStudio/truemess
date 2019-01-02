#pragma once

#include <memory>

#include "../Stuff/Manager.h"

class DatabaseManager;

class Room : public detail::PointerDefs<Room>
{
public:
	enum Type : uint8_t
	{
		Text	= 0,
		Voice	= 1
	};

	Room(uint32_t id, const std::string& name, Type type);

	uint32_t getId() const;
	std::string getName() const;
	Type getType() const;

private:
	friend class RoomManager;

	uint32_t m_id;
	std::string m_name;
	Type m_type;
};

class RoomManager : public Manager<RoomManager>
{
public:
	explicit RoomManager(const Core& core);

	void init();

	Room::ptr createRoom(const std::string& name, Room::Type type);
	bool renameRoom(uint32_t id, const std::string& name);
	bool removeRoom(uint32_t id);

	const std::unordered_map<uint32_t, Room::ptr>& getRooms() const;

private:
	std::shared_ptr<DatabaseManager> m_databaseManager;

	std::unordered_map<uint32_t, Room::ptr> m_rooms;
};
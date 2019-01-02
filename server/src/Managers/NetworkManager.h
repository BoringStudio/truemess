#pragma once

#include <mutex>

#include <asio/ip/tcp.hpp>
#include <asio/io_service.hpp>
#include <asio/detail/thread_group.hpp>

#include "../Stuff/Manager.h"

class NetworkManager : public Manager<NetworkManager>
{
	using SocketPtr = std::shared_ptr<asio::ip::tcp::socket>;
	using SocketList = std::list<SocketPtr>;

public:
	NetworkManager(const Core& core, uint16_t port);
	~NetworkManager();

	void init();
	void close();

	void runAcceptor();

	bool isInitialized() const;

private:
	void workerFunction(unsigned id);

	void handleConnection(SocketPtr socket);
	void handleDisconnection(SocketList::iterator iterator);
	void emitReading(SocketList::iterator iterator);

	uint16_t m_port;
	std::shared_ptr<asio::io_service> m_ioService;
	std::shared_ptr<asio::io_service::work> m_work;
	std::shared_ptr<asio::detail::thread_group> m_threadGroup;

	std::mutex m_socketsListMutex;
	SocketList m_sockets;

	std::vector<char> m_buffer;
};

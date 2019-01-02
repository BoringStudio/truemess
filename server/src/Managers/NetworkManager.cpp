#include "NetworkManager.h"

#include <asio.hpp>
#include "RoomManager.h"

NetworkManager::NetworkManager(const Core & core, uint16_t port) :
	Manager(core), m_port(port)
{
}

NetworkManager::~NetworkManager()
{
	close();
}

void NetworkManager::init()
{
	if (m_ioService != nullptr) {
		return;
	}

	m_ioService = std::make_shared<asio::io_service>();
	m_work = std::make_shared<asio::io_service::work>(*m_ioService);

	m_threadGroup = std::make_shared<asio::detail::thread_group>();
	for (unsigned i = 0; i < std::thread::hardware_concurrency(); ++i) {
		m_threadGroup->create_thread(std::bind(&NetworkManager::workerFunction, this, i));
	}
}

void NetworkManager::close()
{
	for (auto& socket : m_sockets) {
		socket->shutdown(asio::ip::tcp::socket::shutdown_both);
	}

	if (m_ioService) {
		m_ioService->stop();
	}
	
	if (m_threadGroup) {
		m_threadGroup->join();
	}

	m_ioService.reset();
	m_work.reset();
	m_threadGroup.reset();
	m_buffer.clear();
}

void NetworkManager::runAcceptor()
{
	if (m_ioService == nullptr) {
		return;
	}

	const asio::ip::tcp::endpoint endpoint{ asio::ip::tcp::v4(), m_port };
	asio::ip::tcp::acceptor acceptor{ *m_ioService, endpoint };

	m_buffer.resize(1024);
	acceptor.listen();
	log("Listening on port ", m_port);

	while (true) {
		auto socket = std::make_shared<asio::ip::tcp::socket>(*m_ioService);
		acceptor.accept(*socket);

		handleConnection(std::move(socket));
	}
}

bool NetworkManager::isInitialized() const
{
	return m_ioService != nullptr;
}

void NetworkManager::workerFunction(unsigned id)
{
	if (m_ioService == nullptr) {
		return;
	}

	log("Started worker thread #", id);

	while(true) {
		try {
			asio::error_code error;
			m_ioService->run(error);

			if (error) {
				log("ASIO exception in worker thread: ", error);
			}
			break;
		}
		catch(const std::runtime_error& e) {
			log("Exception in worker thread: ", e.what());
		}
	}

	log("Stopped worker thread #", id);
}

void NetworkManager::handleConnection(SocketPtr socket)
{
	log("Client connected: ", socket->remote_endpoint());

	SocketList::iterator iterator;

	{
		std::unique_lock<std::mutex> lock(m_socketsListMutex);
		m_sockets.emplace_back(std::move(socket));
		iterator = std::prev(m_sockets.end());
	}

	emitReading(iterator);
}

void NetworkManager::handleDisconnection(SocketList::iterator iterator)
{
	const auto& socket = *iterator;

	log("Client disconnected ", socket->remote_endpoint());

	{
		std::unique_lock<std::mutex> lock(m_socketsListMutex);
		m_sockets.erase(iterator);
	}
}

void NetworkManager::emitReading(SocketList::iterator iterator)
{
	(*iterator)->async_read_some(asio::buffer(m_buffer), [this, iterator](asio::error_code ec, size_t len) {
		if (ec) {
			log("Error: ", ec.message());
			handleDisconnection(iterator);
			return;
		}

		log("Got ", len, " bytes from ", (*iterator)->remote_endpoint());

		std::string str;
		str.resize(len);
		std::memcpy(str.data(), m_buffer.data(), len);

		if (len > 6) {
			std::string command = str.substr(0, 6);

			if (command == "crte: ") {
				const auto name = str.substr(6, len - 6);
				getCore().get<RoomManager>()->createRoom(name, Room::Text);
			}
			else if (command == "dlte: ") {
				try {
					const auto id = std::stoi(str.substr(6, len - 6));
					getCore().get<RoomManager>()->removeRoom(id);
				}
				catch(const std::invalid_argument& e) {
					log("Command error: ", e.what());
				}
			}
		}

		emitReading(iterator);
	});
}

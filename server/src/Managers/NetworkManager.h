#pragma once

#include <mutex>

#include <asio/io_service.hpp>
#include <asio/detail/thread_group.hpp>

#include "../Stuff/Manager.h"

class NetworkManager : public Manager<NetworkManager>
{
public:
	NetworkManager(const Core& core);
	~NetworkManager();

	void init();
	void close();

	bool isInitialized() const;

private:
	void workerFunction(unsigned id);

	bool m_isInitialized;

	std::shared_ptr<asio::io_service> m_ioService;
	std::shared_ptr<asio::io_service::work> m_work;
	std::shared_ptr<asio::detail::thread_group> m_threadGroup;
};
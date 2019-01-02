#include "NetworkManager.h"

#include <asio.hpp>
#include <iostream>

NetworkManager::NetworkManager(const Core & core) :
	Manager(core), m_isInitialized(false)
{
}

NetworkManager::~NetworkManager()
{
	if (!m_isInitialized || m_ioService == nullptr) {
		return;
	}

	m_ioService->stop();
	m_threadGroup->join();
}

void NetworkManager::init()
{
	if (m_isInitialized) {
		return;
	}

	m_ioService = std::make_shared<asio::io_service>();
	m_work = std::make_shared<asio::io_service::work>(*m_ioService);

	m_isInitialized = true;

	m_threadGroup = std::make_shared<asio::detail::thread_group>();
	for (unsigned i = 0; i < std::thread::hardware_concurrency(); ++i) {
		m_threadGroup->create_thread(std::bind(&NetworkManager::workerFunction, this, i));
	}

	log("initialized");

	std::cin.get();
}

void NetworkManager::close()
{
	if (!m_isInitialized) {
		return;
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
}

bool NetworkManager::isInitialized() const
{
	return m_isInitialized;
}

void NetworkManager::workerFunction(unsigned id)
{
	if (!m_isInitialized || m_ioService == nullptr) {
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
}

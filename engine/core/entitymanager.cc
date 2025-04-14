#include "config.h"
#include "entitymanager.h"

namespace Core
{
	/*
	* Adds entity as static.
	*/
	void EntityManager::AddEntity(const std::unique_ptr<Entity>& entity)
	{
		m_StaticEntities.push_back(entity);
	}

	/*
	* Adds entity as defined EntityType.
	*/
	void EntityManager::AddEntity(const std::unique_ptr<Entity>& entity, EntityType eType)
	{
		if (eType == EntityType::Dynamic)
		{
			m_DynamicEntities.push_back(entity);
			return;
		}

		m_StaticEntities.push_back(entity);
	}

	void EntityManager::UpdateEntities(float deltatime)
	{
		// To be implemented.
		// 
		// Might want to replace with a "GetDynamicEntities" function to be handled elsewhere?
	}

	void EntityManager::RemoveEntity(const std::unique_ptr<Entity>& entity)
	{
		auto removeFrom = [](auto& vec, const std::unique_ptr<Entity>& e)
			{
				vec.erase(std::remove(vec.begin(), vec.end(), e), vec.end());
			};

		removeFrom(m_StaticEntities, entity);
		removeFrom(m_DynamicEntities, entity);
	}
}
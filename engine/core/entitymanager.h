#pragma once

#include <vector>
#include <memory>

struct Entity
{
	//TempClass
};

namespace Core
{
	enum EntityType
	{
		Static,
		Dynamic
	};


	class EntityManager
	{
	public:
		void AddEntity(const std::unique_ptr<Entity>& entity);
		void AddEntity(const std::unique_ptr<Entity>& entity, EntityType eType);

		void UpdateEntities(float deltatime);

		void RemoveEntity(const std::unique_ptr<Entity>& entity);

	private:
		std::vector<std::unique_ptr<Entity>> m_StaticEntities;
		std::vector<std::unique_ptr<Entity>> m_DynamicEntities;

	};
}
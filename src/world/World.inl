#include "World.h"

template<typename T, typename... Ts, typename = typename std::enable_if_t<std::is_base_of_v<Entity, T>>>
std::shared_ptr<T> World::spawnCameraSpaceEntity(const glm::vec3& pos, Ts&&... args) {
	std::shared_ptr<T> TEntity = spawnEntity<T>(pos, std::forward<Ts>(args)...);
	std::shared_ptr<Entity> entity = std::dynamic_pointer_cast<Entity>(TEntity);
	entity->isInCameraSpace = true;

	return TEntity;
}

template<typename T, typename... Ts, typename = typename std::enable_if_t<std::is_base_of_v<Entity, T>>>
std::shared_ptr<T> World::spawnEntity(const glm::vec3& pos, Ts&&... args) {
	std::shared_ptr<T> TEntity = std::make_shared<T>(std::forward<Ts>(args)...);
	std::shared_ptr<Entity> entity = std::dynamic_pointer_cast<Entity>(TEntity);
	entity->transform.position = pos;
	entity->hookWorld(this);

	entities.push_back(entity);

	return TEntity;
}

template<typename T>
std::vector<std::shared_ptr<T>> World::getEntitiesNearTo(const glm::vec3& position, float radius) {
	std::vector<std::shared_ptr<T>> result;

	for (auto& entity : entities) {
		if (entity == nullptr)
			continue;

		std::shared_ptr<T> TEntity = std::dynamic_pointer_cast<T>(entity);

		if (TEntity != nullptr && glm::distance(entity->transform.position, position) <= radius) {
			result.push_back(TEntity);
		}
	}

	return result;
}
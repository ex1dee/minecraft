#ifndef INTERSECTLIST_H
#define INTERSECTLIST_H

#include <glm/glm.hpp>
#include <vector>

class IntersectList {
public:
	std::vector<glm::vec3> list;

	void add(const IntersectList& other) {
		list.insert(list.end(), other.list.begin(), other.list.end());
	}

	glm::vec3& getNearestTo(const glm::vec3& position) {
		float minDistance = FLT_MAX;
		glm::vec3 minPoint;

		for (glm::vec3& point : list) {
			float distance = glm::distance(point, position);

			if (distance < minDistance) {
				minDistance = distance;
				minPoint = point;
			}
		}

		return minPoint;
	}

	bool isComplete(int requiredCount) {
		return list.size() == requiredCount;
	}
};

#endif
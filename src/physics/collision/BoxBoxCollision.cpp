#include "BoxBoxCollision.h"

#include <algorithm>

constexpr int
PROJECTION_MIN_INDEX = 0,
PROJECTION_MAX_INDEX = 1;

void BoxBoxCollision::detect(GameObject& obj1, GameObject& obj2) {
	if (obj1.rigidBody.getPhysicsType() == PhysicsType::STATIC && obj2.rigidBody.getPhysicsType() == PhysicsType::STATIC)
		return;

	BoxCollider& box1 = *(BoxCollider*)obj1.collider.get();
	BoxCollider& box2 = *(BoxCollider*)obj2.collider.get();

	Collision collision = detect(box1, box2);
	CollisionHandler::handle(collision, obj1, obj2);
}

void BoxBoxCollision::detect(GameObject& obj, const Block& block) {
	if (obj.rigidBody.getPhysicsType()  == PhysicsType::STATIC)
		return;

	BoxCollider& box = *(BoxCollider*) obj.collider.get();
	Transform transform(block.getPosition());

	for (auto& blockBox : block.getType().colliders) {
		blockBox->updateTransform(transform);

		Collision collision = detect(box, *blockBox);
		CollisionHandler::handle(collision, obj, block);
	}
}

Collision BoxBoxCollision::detect(const BoxCollider& box1, const BoxCollider& box2) {
	Collision collision;
	glm::vec3 minDepthAxis(0);
	float minDepth = FLT_MAX;
	
	std::vector<glm::vec3> sepAxes = calcBoxSepAxes(box1, box2);

	for (glm::vec3& sepAxis : sepAxes) {
		glm::vec2 section1 = projAxis(box1.globalVertices, sepAxis);
		glm::vec2 section2 = projAxis(box2.globalVertices, sepAxis);

		float points[4] = {
			section1[PROJECTION_MIN_INDEX],
			section1[PROJECTION_MAX_INDEX],
			section2[PROJECTION_MIN_INDEX],
			section2[PROJECTION_MAX_INDEX]
		};

		std::sort(std::begin(points), std::end(points));

		float sum = section1[PROJECTION_MAX_INDEX] - section1[PROJECTION_MIN_INDEX]
			   	  + section2[PROJECTION_MAX_INDEX] - section2[PROJECTION_MIN_INDEX];
		float len = std::abs(points[3] - points[0]);

		if (sum < len) {
			collision.collided = false;

			return collision;
		}
		else {
			float depth = sum - len;

			if (depth < minDepth) {
				minDepth = depth;
				minDepthAxis = sepAxis;
			}
		}
	}

	collision.collided = true;
	collision.depth = minDepth;

	glm::vec3 diff = box2.globalVertices[0] - box1.globalVertices[0];
	float normSign = -glm::sign(glm::dot(diff, minDepthAxis));
	collision.normal = glm::normalize(normSign * minDepthAxis);

	return collision;
}

std::vector<glm::vec3> BoxBoxCollision::calcBoxSepAxes(const BoxCollider& box1, const BoxCollider& box2) {
	std::vector<glm::vec3> axes;

	for (int i = 1; i < 4; ++i) {
		glm::vec3 a = box1.globalVertices[i] - box1.globalVertices[0];
		glm::vec3 b = box1.globalVertices[(i + 1) % 3 + 1] - box1.globalVertices[0];

		axes.push_back(glm::normalize(glm::cross(b, a)));
	}

	for (int i = 1; i < 4; ++i) {
		glm::vec3 a = box2.globalVertices[i] - box2.globalVertices[0];
		glm::vec3 b = box2.globalVertices[(i + 1) % 3 + 1] - box2.globalVertices[0];

		axes.push_back(glm::normalize(glm::cross(b, a)));
	}

	for (int i = 1; i < 4; ++i) {
		glm::vec3 a = box1.globalVertices[i] - box1.globalVertices[0];

		for (int j = 1; j < 4; ++j) {
			glm::vec3 b = box2.globalVertices[i] - box2.globalVertices[0];
			glm::vec3 cross = glm::cross(b, a);

			if (glm::length(cross) != 0)
				axes.push_back(glm::normalize(cross));
		}
	}

	return axes;
}

glm::vec2 BoxBoxCollision::projAxis(const std::vector<glm::vec3>& vertices, const glm::vec3& axis) {
	glm::vec2 projSection(proj(vertices[0], axis), proj(vertices[0], axis));

	for (int i = 1; i < vertices.size(); ++i) {
		float p = proj(vertices[i], axis);

		if (p > projSection[PROJECTION_MAX_INDEX])
			projSection[PROJECTION_MAX_INDEX] = p;

		if (p < projSection[PROJECTION_MIN_INDEX])
			projSection[PROJECTION_MIN_INDEX] = p;
	}

	return projSection;
}

float BoxBoxCollision::proj(const glm::vec3& a, const glm::vec3& b) {
	return glm::dot(a, b) / glm::length(b);
}
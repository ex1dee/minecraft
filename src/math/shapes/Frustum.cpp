#include "Frustum.h"

#include "Planes.h"

bool Frustum::isAABBInFrustum(const AABB& aabb) const {
    int pointsInFrustum = 0;

    for (const Plane& plane : planes) {
        if (plane.distanceToPoint(aabb.getVertexInDirection(plane.normal)) >= 0) {
            pointsInFrustum++;
        }
    }

    return pointsInFrustum > 0;
}

void Frustum::update(const glm::mat4& pv) {
    planes[Planes::LEFT].normal.x = pv[0][3] + pv[0][0];
    planes[Planes::LEFT].normal.y = pv[1][3] + pv[1][0];
    planes[Planes::LEFT].normal.z = pv[2][3] + pv[2][0];
    planes[Planes::LEFT].distance = pv[3][3] + pv[3][0];

    planes[Planes::RIGHT].normal.x = pv[0][3] - pv[0][0];
    planes[Planes::RIGHT].normal.y = pv[1][3] - pv[1][0];
    planes[Planes::RIGHT].normal.z = pv[2][3] - pv[2][0];
    planes[Planes::RIGHT].distance = pv[3][3] - pv[3][0];

    planes[Planes::BOTTOM].normal.x = pv[0][3] + pv[0][1];
    planes[Planes::BOTTOM].normal.y = pv[1][3] + pv[1][1];
    planes[Planes::BOTTOM].normal.z = pv[2][3] + pv[2][1];
    planes[Planes::BOTTOM].distance = pv[3][3] + pv[3][1];

    planes[Planes::TOP].normal.x = pv[0][3] - pv[0][1];
    planes[Planes::TOP].normal.y = pv[1][3] - pv[1][1];
    planes[Planes::TOP].normal.z = pv[2][3] - pv[2][1];
    planes[Planes::TOP].distance = pv[3][3] - pv[3][1];

    planes[Planes::NEAR].normal.x = pv[0][3] + pv[0][2];
    planes[Planes::NEAR].normal.y = pv[1][3] + pv[1][2];
    planes[Planes::NEAR].normal.z = pv[2][3] + pv[2][2];
    planes[Planes::NEAR].distance = pv[3][3] + pv[3][2];

    planes[Planes::FAR].normal.x = pv[0][3] - pv[0][2];
    planes[Planes::FAR].normal.y = pv[1][3] - pv[1][2];
    planes[Planes::FAR].normal.z = pv[2][3] - pv[2][2];
    planes[Planes::FAR].distance = pv[3][3] - pv[3][2];
}
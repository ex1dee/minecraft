#include "Frustum.h"

Frustum::Frustum() {
    for (int i = 0; i < 6; ++i) {
        planes[i] = new Plane;
    }
}

Frustum::~Frustum() {
    for (Plane* plane : planes) {
        delete plane;
    }
}

bool Frustum::isAABBInFrustum(const AABB& aabb) {
    if (aabb.min == glm::vec3(0) && aabb.extents == glm::vec3(0))
        return true;

    for (Plane* plane : planes) {
        if (plane->distanceToPoint(aabb.getVP(plane->normal)) < 0) {
            return false;
        }
    }

    return true;
}

void Frustum::update(const glm::mat4& pv) {
    // left
    planes[Planes::Left]->normal.x = pv[0][3] + pv[0][0];
    planes[Planes::Left]->normal.y = pv[1][3] + pv[1][0];
    planes[Planes::Left]->normal.z = pv[2][3] + pv[2][0];
    planes[Planes::Left]->distance = pv[3][3] + pv[3][0];

    // right
    planes[Planes::Right]->normal.x = pv[0][3] - pv[0][0];
    planes[Planes::Right]->normal.y = pv[1][3] - pv[1][0];
    planes[Planes::Right]->normal.z = pv[2][3] - pv[2][0];
    planes[Planes::Right]->distance = pv[3][3] - pv[3][0];

    // bottom
    planes[Planes::Bottom]->normal.x = pv[0][3] + pv[0][1];
    planes[Planes::Bottom]->normal.y = pv[1][3] + pv[1][1];
    planes[Planes::Bottom]->normal.z = pv[2][3] + pv[2][1];
    planes[Planes::Bottom]->distance = pv[3][3] + pv[3][1];

    // top
    planes[Planes::Top]->normal.x = pv[0][3] - pv[0][1];
    planes[Planes::Top]->normal.y = pv[1][3] - pv[1][1];
    planes[Planes::Top]->normal.z = pv[2][3] - pv[2][1];
    planes[Planes::Top]->distance = pv[3][3] - pv[3][1];

    // near
    planes[Planes::Near]->normal.x = pv[0][3] + pv[0][2];
    planes[Planes::Near]->normal.y = pv[1][3] + pv[1][2];
    planes[Planes::Near]->normal.z = pv[2][3] + pv[2][2];
    planes[Planes::Near]->distance = pv[3][3] + pv[3][2];

    // far
    planes[Planes::Far]->normal.x = pv[0][3] - pv[0][2];
    planes[Planes::Far]->normal.y = pv[1][3] - pv[1][2];
    planes[Planes::Far]->normal.z = pv[2][3] - pv[2][2];
    planes[Planes::Far]->distance = pv[3][3] - pv[3][2];

    normalizePlanes();
}

void Frustum::normalizePlanes() {
    for (Plane* plane : planes) {
        float length = glm::length(plane->normal);

        plane->normal /= length;
        plane->distance /= length;
    }
}
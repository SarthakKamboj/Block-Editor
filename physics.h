#pragma once

#include "vec3.h"

class BoxCollider {
public:
    BoxCollider();
    BoxCollider(vec3 dim, vec3 scale, vec3 trans);
    
    vec3 dimensions;
    vec3 scale;
    vec3 transform;

    bool point_collide(vec3& point);

};

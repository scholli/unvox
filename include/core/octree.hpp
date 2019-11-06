//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#pragma once

#include <array>
#include <memory>

#include <glm/glm.hpp>

struct ocnode 
{
    bool has_children;
    std::array<std::shared_ptr<ocnode>, 8> children;
};

struct octree 
{
    glm::vec3 size;
    glm::vec3 pmax;
    glm::vec3 pmin;
};
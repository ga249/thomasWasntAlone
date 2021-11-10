#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "gfc_types.h"
#include "entity.h"

/**
 * @brief provide a pointer to a new platform
 * @param position a vector3d to describe the "top left" corner of the platform
 * @param lwh a vector3d describing the legth, width, and height of the platform respectively (xyz)
 * @return pointer to platform entity
 */
Entity *platform_new(Vector3D position, Vector3D lwh);

#endif
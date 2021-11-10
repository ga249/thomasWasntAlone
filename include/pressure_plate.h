#ifndef __PRESSURE_PLATE_H__
#define __PRESSURE_PLATE_H__

#include "gfc_types.h"
#include "entity.h"

/**
 * @brief provide a pointer to a new door
 * @param position a vector3d to bottom left of the door
 * @return pointer to door entity
 */
Entity *pPlate_new(Vector3D position);

#endif
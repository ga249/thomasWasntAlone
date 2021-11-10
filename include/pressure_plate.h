#ifndef __PRESSURE_PLATE_H__
#define __PRESSURE_PLATE_H__

#include "gfc_types.h"
#include "entity.h"

/**
 * @brief provide a pointer to a new pressure plate
 * @param position a vector3d for center of pressure plate
 * @return pointer to pressure plate entity
 */
Entity *pPlate_new(Vector3D position);

#endif
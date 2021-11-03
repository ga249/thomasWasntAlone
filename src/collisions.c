#include "simple_logger.h"
#include "collisions.h"


int collision_sphere_sphere(Vector3D s1pos,float s1Radius,Vector3D s2pos,float s2Radius)
{
    if (s1pos.x < (s2pos.x - s2Radius) ||
        s1pos.x > (s2pos.x + s2Radius) ||
        s1pos.y < (s2pos.y - s2Radius) ||
        s1pos.y > (s2pos.y + s2Radius) ||
        s1pos.z < (s2pos.z - s2Radius) ||
        s1pos.z > (s2pos.z + s2Radius) )
    {
        return 0;
    }else{
        return 1;
    }
}

int collision_ent_ent(Entity *ent1, Entity *ent2)
{
    switch (ent1->hbType)
    {
    case HB_SPHERE:
        switch (ent2->hbType)
        {
        case HB_SPHERE:
            if (collision_sphere_sphere(ent1->position,ent1->hbRadius,ent2->position,ent2->hbRadius))
            {
                slog("TOUCHINGGGGG");
                return 1;
            }
            return 0;
            break;
        
        case HB_RECT:
            //TODO: sphere vs rect collision test
            break;
        }
        break;
    
    case HB_RECT:
        switch (ent2->hbType)
        {
        case HB_SPHERE:
            //TODO: sphere vs rect collision test
            break;
        
        case HB_RECT:
            //TODO: rect vs rect collision test
            break;
        }
        break;
    }
    
    if (collision_sphere_sphere(ent1->position,ent1->hbRadius,ent2->position,ent2->hbRadius))
    {
        slog("TOUCHINGGGGG");
        return 1;
    }
    return 0;
}
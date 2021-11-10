#include "simple_logger.h"
#include "collisions.h"


int collision_sphere_sphere(Vector3D s1pos,float s1Radius,Vector3D s2pos,float s2Radius)
{
    if ((s1pos.x + s1Radius) < (s2pos.x - s2Radius) ||
        (s1pos.x) > (s2pos.x + s2Radius) ||
        (s1pos.y) < (s2pos.y - s2Radius) ||
        (s1pos.y) > (s2pos.y + s2Radius) ||
        (s1pos.z) < (s2pos.z - s2Radius) ||
        (s1pos.z) > (s2pos.z + s2Radius) )
    {
        return 0;
    }else{
        return 1;
    }
}

int collision_rect_rect(Vector3D r1min,Vector3D r1max,Vector3D r2min,Vector3D r2max)
{
    if (r1max.x > r2min.x ||
        r1min.x < r2max.x ||
        r1max.z < r2min.z ||
        r1min.z > r2max.z ||
        r1max.y > r2min.y ||
        r1min.y < r2max.y)
    {
        return 0;
    }else{
        return 1;
    }
}

int collision_sphere_rect(Vector3D spos, float sradius, Vector3D rmin, Vector3D rmax)
{
    if ((spos.x + sradius) < rmax.x ||
        (spos.x - sradius) > rmin.x ||
        (spos.z + sradius) > rmax.z ||
        (spos.z - sradius) < rmin.z ||
        (spos.y + sradius) < rmax.y ||
        (spos.y - sradius) > rmin.y )
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
            if (collision_sphere_rect(ent1->position, ent1->hbRadius, ent2->hbMin,ent2->hbMax))
            {
                return 1;
            }
            break;
        }
        break;
    
    case HB_RECT:
        switch (ent2->hbType)
        {
        case HB_SPHERE:
            //sphere vs rect collision test
            if (collision_sphere_rect(ent2->position, ent2->hbRadius, ent1->hbMin,ent1->hbMax))
            {
                return 1;
            }
            break;
        
        case HB_RECT:
            //rect vs rect collision test
            if (collision_rect_rect(ent1->hbMin, ent1->hbMax, ent2->hbMin, ent2->hbMax))
            {
                return 1;
            }
            break;
        }
        break;
    default:
        slog("ent doesn't have hitbox type");
        return 0;
        break;

    }
    return 0;
    
}
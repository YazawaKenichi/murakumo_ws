#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

typedef struct
{
    /* data */
    /**
     * @brief This expresses acceleration in free space broken into its linear and angular parts.
     * 
    */
    Vector3 linear;
    Vector3 angular;
} Accel;

typedef struct
{
    /* data */
    /**
     * @brief Mass [kg]
     * 
    */
    float m;
    /**
     * @brief Center of mass [m]
     * 
    */
    Vector3 com;
    /**
     * @brief Inertia Tensor [kg-m^2]
     * 
    */
    float ixx;
    float ixy;
    float ixz;
    float iyy;
    float iyz;
    float izz;
} Inertia;

typedef struct
{
    /* data */
    /**
     * @brief This contains the position of a point in free space.
     * 
    */
    float x;
    float y;
    float z;
} Point;

typedef struct
{
    /* data */
    /**
     * @brief A representation of pose in free space, composed of position and orientation.
     * 
    */
    Point position;
    Rpy rpy;
} Pose;

typedef struct
{
    /* data */
    /**
     * @brief This represents an Roll Pitch Yaw in free space in Roll Pitch Yaw form.
     * 
    */
    float roll;
    float pitch;
    float yaw;
} Rpy;

typedef struct
{
    /* data */
    /**
     * @brief This represents the transform between two coordinate frames in free space.
     * 
    */
    Vector3 translation;
    Rpy rotation;
} Transform;

typedef struct
{
    /* data */
    /**
     * @brief This expresses velocity in free space broken into its linear and angular parts.
     * 
    */
    Vector3 linear;
    Vector3 angular;
} Twist;

typedef struct
{
    /* data */
    /**
     * @brief 
     * 
     * This represents a vector in free space.
     * It is only meant to represent a direction.
     * Therefore, it does not make sense to apply a translation to it.
     * If you want your data to be translatable too, use the Point type instead.
     * 
    */
    float x;
    float y;
    float z;
} Vector3;

#endif

#ifndef IKUtils_h
#define IKUtils_h

/*
Common Inverse Kinematics routines (from the NUKE project)

Need to be coupled with gait generation, and definition of legs/body position
to get a full system
*/

// Body position
typedef struct{
    float rotX;
    float rotY;
    float rotZ;
    float posX;
    float posY;
    float cosB;
    float sinB;
    float cosG;
    float sinG;
} IK_BODY_POS;

// Leg dimensions - can be reused if legs are symmetrical
typedef struct {
    int coxa;  // mm between coxa and femur joints
    int femur; // mm between femur and tibia joints
    int tibia; // mm between tbia joint and foot
} IK_LEG_DIMS;

/* A leg position request (output of body calcs, input to simple 3dof solver). */
typedef struct{
    int x;
    int y;
    int z;
} IK_LEG_REQ;

/* Joint rotations in radians (output of 3dof leg solver). */
typedef struct{
    float coxa;
    float femur;
    float tibia;
} IK_LEG_SOL;

// Call whenever body position changes to pre-calc trig
void prepBodyIK(IK_BODY_POS *bodyPos);

// find the translation of the coxa point, given our rotations
IK_LEG_REQ bodyIK(int X, int Y, int Z, int Xdisp, int Ydisp, float Zrot, IK_BODY_POS *bodyPos);

// calc joint rotations, given our foot offset (x,y,z) from the coxa point
IK_LEG_SOL legIK(int X, int Y, int Z, IK_LEG_DIMS *legDims);

#endif

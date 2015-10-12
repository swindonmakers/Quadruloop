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
} IK_BODY_POS;

// Leg dimensions
typedef struct {
    int x;  // mm between coxa joint and centre of body (forwards is +)
    int y;  // mm between coxa joint and centre of body (right is +)
    int coxa;  // mm between coxa and femur joints
    int femur; // mm between femur and tibia joints
    int tibia; // mm between tbia joint and foot
} IK_LEG_DIMS;


/* A leg position request (output of body calcs, input to simple 3dof solver). */
typedef struct{
    int x;
    int y;
    int z;
    float r;
} IK_LEG_REQ;

/* Servo ouptut values in radians (output of 3dof leg solver). */
typedef struct{
    float coxa;
    float femur;
    float tibia;
} IK_LEG_SOL;

/* find the translation of the coxa point (x,y) in 3-space, given our rotations */
IK_LEG_REQ bodyIK(int X, int Y, int Z, int Xdisp, int Ydisp, float Zrot, IK_BODY_POS *bodyPos);

/* given our leg offset (x,y,z) from the coxa point, calculate servo values */
IK_LEG_SOL legIK(int X, int Y, int Z, IK_LEG_DIMS *legDims);

#endif

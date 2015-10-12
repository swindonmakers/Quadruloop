#include "IKUtils.h"
#include <SpeedTrig.h>

/* Body IK solver: compute where legs should be. */
IK_LEG_REQ bodyIK(int X, int Y, int Z, int Xdisp, int Ydisp, float Zrot, IK_BODY_POS *bodyPos){
    IK_LEG_REQ ans;

    float cosB = SpeedTrig.cos(bodyPos->rotX);
    float sinB = SpeedTrig.sin(bodyPos->rotX);
    float cosG = SpeedTrig.cos(bodyPos->rotY);
    float sinG = SpeedTrig.sin(bodyPos->rotY);
    float cosA = SpeedTrig.cos(bodyPos->rotZ + Zrot);
    float sinA = SpeedTrig.sin(bodyPos->rotZ + Zrot);

    int totalX = X + Xdisp + bodyPos->posX;
    int totalY = Y + Ydisp + bodyPos->posY;

    ans.x = totalX - int(totalX*cosG*cosA + totalY*sinB*sinG*cosA + Z*cosB*sinG*cosA - totalY*cosB*sinA + Z*sinB*sinA) + bodyPos->posX;
    ans.y = totalY - int(totalX*cosG*sinA + totalY*sinB*sinG*sinA + Z*cosB*sinG*sinA + totalY*cosB*cosA - Z*sinB*cosA) + bodyPos->posY;
    ans.z = Z - int(-totalX*sinG + totalY*sinB*cosG + Z*cosB*cosG);

    return ans;
}


/* Simple 3dof leg solver. X,Y,Z are the length from the Coxa rotate to the endpoint. */
IK_LEG_SOL legIK(int X, int Y, int Z, IK_LEG_DIMS *legDims){
    IK_LEG_SOL ans;

    // first, make this a 2DOF problem... by solving coxa
    ans.coxa = SpeedTrig.atan2(X,Y);
    long trueX = sqrt(sq((long)X)+sq((long)Y)) - legDims->coxa;
    long im = sqrt(sq((long)trueX)+sq((long)Z));    // length of imaginary leg

    // get femur angle above horizon...
    float q1 = -SpeedTrig.atan2(Z,trueX);
    long d1 = sq(legDims->femur)-sq(legDims->tibia)+sq(im);
    long d2 = 2*legDims->femur*im;
    float q2 = SpeedTrig.acos((float)d1/(float)d2);
    ans.femur = q1+q2;

    // and tibia angle from femur...
    d1 = sq(legDims->femur)-sq(im)+sq(legDims->tibia);
    d2 = 2*legDims->tibia*legDims->femur;
    ans.tibia = SpeedTrig.acos((float)d1/(float)d2) - PI/2;

    return ans;

}

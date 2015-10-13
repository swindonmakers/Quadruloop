#include "IKUtils.h"
#include <SpeedTrig.h>

void prepBodyIK(IK_BODY_POS *bodyPos) {
    bodyPos->cosB = SpeedTrig.cos(bodyPos->rotX);
    bodyPos->sinB = SpeedTrig.sin(bodyPos->rotX);
    bodyPos->cosG = SpeedTrig.cos(bodyPos->rotY);
    bodyPos->sinG = SpeedTrig.sin(bodyPos->rotY);
}

// find the translation of the coxa point, given our rotations
IK_LEG_REQ bodyIK(int X, int Y, int Z, int Xdisp, int Ydisp, float Zrot, IK_BODY_POS *bodyPos){
    IK_LEG_REQ ans;

    float cosA = SpeedTrig.cos(bodyPos->rotZ + Zrot);
    float sinA = SpeedTrig.sin(bodyPos->rotZ + Zrot);

    int totalX = X + Xdisp + bodyPos->posX;
    int totalY = Y + Ydisp + bodyPos->posY;

    ans.x = totalX -
            int(
                totalX * bodyPos->cosG * cosA +
                totalY * bodyPos->sinB * bodyPos->sinG * cosA +
                Z * bodyPos->cosB * bodyPos->sinG * cosA -
                totalY * bodyPos->cosB * sinA +
                Z * bodyPos->sinB * sinA
            ) +
            bodyPos->posX;
    ans.y = totalY -
            int(
                totalX * bodyPos->cosG * sinA +
                totalY * bodyPos->sinB * bodyPos->sinG * sinA +
                Z * bodyPos->cosB * bodyPos->sinG * sinA +
                totalY * bodyPos->cosB * cosA -
                Z * bodyPos->sinB * cosA
            ) +
            bodyPos->posY;
    ans.z = Z -
            int(
                -totalX * bodyPos->sinG +
                totalY * bodyPos->sinB * bodyPos->cosG +
                Z * bodyPos->cosB * bodyPos->cosG
            );

    return ans;
}


// calc joint rotations, given our foot offset (x,y,z) from the coxa point
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

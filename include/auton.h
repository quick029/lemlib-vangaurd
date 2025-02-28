#ifndef AUTON_H
#define AUTON_H

extern void runAuton();

enum auton_type {
    RED_POSITIVE,
    RED_NEGATIVE,
    BLUE_POSITIVE,
    BLUE_NEGATIVE,
    SKILLS
};

extern auton_type autonType;

extern bool scoreAllianceStake;

extern bool autonConfirmed;

#endif
#ifndef MECANUM_H
#define MECANUM_H

struct MecanumOutput {
    float fl;
    float fr;
    float bl;
    float br;
};

MecanumOutput mecanum_from_vector(float x, float y, float z);

#endif

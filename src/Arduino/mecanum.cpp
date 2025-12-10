#include "mecanum.h"
#include <math.h>

MecanumOutput mecanum_from_vector(float x, float y, float z) {
    float fl = y + x + z;
    float fr = y - x - z;
    float bl = y - x + z;
    float br = y + x - z;

    float max_val = fabs(fl);
    max_val = fmax(max_val, fabs(fr));
    max_val = fmax(max_val, fabs(bl));
    max_val = fmax(max_val, fabs(br));

    if (max_val > 1.0f) {
        fl /= max_val;
        fr /= max_val;
        bl /= max_val;
        br /= max_val;
    }

    return { fl, fr, bl, br };
}

#ifndef __MATRIX_H_
#define __MATRIX_H_

typedef union Mat {
    Vec4 vec[4];
    f32 columns[4][4];
    f32 e[16];
} Mat;

Mat
mat_scalar(f32 s) {
    Mat m;
    m.vec[0] = v4_scalar(s);
    m.vec[1] = v4_scalar(s);
    m.vec[2] = v4_scalar(s);
    m.vec[3] = v4_scalar(s);
    return m;
}

// Functions sourced from: https://github.com/HandmadeMath/HandmadeMath/blob/master/HandmadeMath.h
Vec4
mat_combine_v4(const Vec4 left, const Mat right) {
    Vec4 v;
    v.x = left.e[0] * right.vec[0].x;
    v.y = left.e[0] * right.vec[0].y;
    v.z = left.e[0] * right.vec[0].z;
    v.w = left.e[0] * right.vec[0].w;

    v.x += left.e[1] * right.vec[1].x;
    v.y += left.e[1] * right.vec[1].y;
    v.z += left.e[1] * right.vec[1].z;
    v.w += left.e[1] * right.vec[1].w;

    v.x += left.e[2] * right.vec[2].x;
    v.y += left.e[2] * right.vec[2].y;
    v.z += left.e[2] * right.vec[2].z;
    v.w += left.e[2] * right.vec[2].w;

    v.x += left.e[3] * right.vec[3].x;
    v.y += left.e[3] * right.vec[3].y;
    v.z += left.e[3] * right.vec[3].z;
    v.w += left.e[3] * right.vec[3].w;
    return v;
}

Mat
mat_mul(const Mat a, const Mat b) {
    Mat m;
    m.vec[0] = mat_combine_v4(a.vec[0], b);
    m.vec[1] = mat_combine_v4(a.vec[1], b);
    m.vec[2] = mat_combine_v4(a.vec[2], b);
    m.vec[3] = mat_combine_v4(a.vec[3], b);
    return m;
}

Mat
mat_ortho2d(f32 left, f32 right, f32 bottom, f32 top, f32 znear, f32 zfar) {
    Mat m = {0};
    m.columns[0][0] = 2.0 / (right - left);
    m.columns[1][1] = 2.0 / (top - bottom);
    m.columns[2][2] = 2.0 / (znear - zfar);
    m.columns[3][3] = 1;
    m.columns[3][0] = (left + right) / (left - right);
    m.columns[3][1] = (bottom + top) / (bottom - top);
    m.columns[3][2] = (znear + zfar) / (znear - zfar);
    return m;
}

Mat
mat_make_translation(const Vec3 t) {
    Mat m = mat_scalar(1.0);
    m.columns[3][0] = t.x;
    m.columns[3][1] = t.y;
    m.columns[3][2] = t.z;
    return m;
}

inline Mat
mat_translate(Mat m, const Vec3 t) {
    return mat_mul(m, mat_make_translation(t));
}

Mat
mat_scale(Mat m, Vec3 scale) {
    m.columns[0][0] = scale.x;
    m.columns[1][1] = scale.y;
    m.columns[2][2] = scale.z;
    m.columns[3][3] = 1;
    return m;
}

#endif // __MATRIX_H_
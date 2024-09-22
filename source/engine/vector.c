#ifndef __VECTOR_H_
#define __VECTOR_H_

// Types
#define TEMPLATE_Vec2t(t) \
    typedef union Vec2##t {\
        struct {t x, y;};\
        t e[2];\
   } Vec2##t;

#define TEMPLATE_Vec3t(t) \
    typedef union Vec3##t {\
        struct {t x, y, z;};\
        t e[3];\
   } Vec3##t;

#define TEMPLATE_Vec4t(t) \
    typedef union Vec4##t {\
        struct {t x, y, z, w;};\
        t e[4];\
   } Vec4##t;

#define Vec2 Vec2f32
#define Vec3 Vec3f32
#define Vec4 Vec4f32

// Constructors
#define TEMPLATE_v2t(t) inline intern Vec2##t v2##t(t x, t y) {return (Vec2##t){x, y};}
#define TEMPLATE_v3t(t) inline intern Vec3##t v3##t(t x, t y, t z) {return (Vec3##t){x, y, z};}
#define TEMPLATE_v4t(t) inline intern Vec4##t v4##t(t x, t y, t z, t w) {return (Vec4##t){x, y, z, w};}

#define TEMPLATE_v2t_scalar(t) inline intern Vec2##t v2##t##_scalar(t s) {return (Vec2##t){s, s};}
#define TEMPLATE_v3t_scalar(t) inline intern Vec3##t v3##t##_scalar(t s) {return (Vec3##t){s, s, s};}
#define TEMPLATE_v4t_scalar(t) inline intern Vec4##t v4##t##_scalar(t s) {return (Vec4##t){s, s, s, s};}

#define v2 v2f32
#define v3 v3f32
#define v4 v4f32

#define v2_scalar v2f32_scalar
#define v3_scalar v3f32_scalar
#define v4_scalar v4f32_scalar

// Math
#define TEMPLATE_v2tOPERATOR(t, o, n) inline intern Vec2##t v2##t##_##n(Vec2##t a, Vec2##t b) {return v2##t(a.x o b.x, a.y o b.y);}
#define TEMPLATE_v3tOPERATOR(t, o, n) inline intern Vec3##t v3##t##_##n(Vec3##t a, Vec3##t b) {return v3##t(a.x o b.x, a.y o b.y, a.z o a.z);}
#define TEMPLATE_v4tOPERATOR(t, o, n) inline intern Vec4##t v4##t##_##n(Vec4##t a, Vec4##t b) {return v4##t(a.x o b.x, a.y o b.y, a.z o b.z, a.w o b.w);}

#define TEMPLATE_VecMath(N, t)\
    TEMPLATE_v##N##tOPERATOR(t, +, add)\
    TEMPLATE_v##N##tOPERATOR(t, -, sub)\
    TEMPLATE_v##N##tOPERATOR(t, /, div)\
    TEMPLATE_v##N##tOPERATOR(t, *, mul)

#define v2_add v2f32_add
#define v2_sub v2f32_sub
#define v2_mul v2f32_mul
#define v2_div v2f32_div

#define v3_add v3f32_add
#define v3_sub v3f32_sub
#define v3_mul v3f32_mul
#define v3_div v3f32_div

#define v4_add v4f32_add
#define v4_sub v4f32_sub
#define v4_mul v4f32_mul
#define v4_div v4f32_div

#define v2i_add v2i32_add
#define v2i_sub v2i32_sub
#define v2i_mul v2i32_mul
#define v2i_div v2i32_div

#define v3i_add v3i32_add
#define v3i_sub v3i32_sub
#define v3i_mul v3i32_mul
#define v3i_div v3i32_div

#define v4i_add v4i32_add
#define v4i_sub v4i32_sub
#define v4i_mul v4i32_mul
#define v4i_div v4i32_div

// General Generator
#define GENERATE_VecNt(N)\
    TEMPLATE_Vec##N##t(f32)\
    TEMPLATE_Vec##N##t(f64)\
    TEMPLATE_Vec##N##t(i32)\
    TEMPLATE_Vec##N##t(i64)\
    TEMPLATE_v##N##t(f32)\
    TEMPLATE_v##N##t(f64)\
    TEMPLATE_v##N##t(i32)\
    TEMPLATE_v##N##t(i64)\
    TEMPLATE_v##N##t_scalar(f32)\
    TEMPLATE_v##N##t_scalar(f64)\
    TEMPLATE_v##N##t_scalar(i32)\
    TEMPLATE_v##N##t_scalar(i64)\
    TEMPLATE_VecMath(N, f32)\
    TEMPLATE_VecMath(N, f64)\
    TEMPLATE_VecMath(N, i32)\
    TEMPLATE_VecMath(N, i64)

// Generating
GENERATE_VecNt(2)
GENERATE_VecNt(3)
GENERATE_VecNt(4)

#endif // __VECTOR_H_
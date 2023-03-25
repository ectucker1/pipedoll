#ifndef FLOAT32_SERIALIZE_H
#define FLOAT32_SERIALIZE_H

#include <godot_cpp/variant/packed_float32_array.hpp>

class Float32Serialize
{
public:
    virtual size_t float_size() const = 0;
    virtual void append_to(godot::PackedFloat32Array& data) const = 0;
};

class Float32Deserialize
{
public:
    virtual void read_from(const godot::PackedFloat32Array& data, size_t offset) = 0;
};

#endif // FLOAT32_SERIALIZE_H

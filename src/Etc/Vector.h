#pragma once

namespace rgl {

    struct Vector2i {
        Vector2i() : x(0), y(0) {}
        Vector2i(const int& x, const int& y) : x(x), y(y) {}

        template<typename t>
        Vector2i operator+(const t& s) {
            return Vector2i(x + s, y + s);
        }

        template<typename t>
        Vector2i operator-(const t& s) {
            return Vector2i(x - s, y - s);
        }

        template<typename t>
        Vector2i operator*(const t& s) {
            return Vector2i(x * s, y * s);
        }

        template<typename t>
        Vector2i operator/(const t& s) {
            return Vector2i(x / s, y / s);
        }

        template<typename t>
        void operator+=(const t& s) {
            x += s;
            y += s;
        }

        template<typename t>
        void operator-=(const t& s) {
            x -= s;
            y -= s;
        }

        template<typename t>
        void operator*=(const t& s) {
            x *= s;
            y *= s;
        }

        template<typename t>
        void operator/=(const t& s) {
            x /= s;
            y /= s;
        }

        Vector2i operator+(const Vector2i& v) {
            return Vector2i(x + v.x, y + v.y);
        }

        Vector2i operator-(const Vector2i& v) {
            return Vector2i(x - v.x, y - v.y);
        }

        Vector2i operator*(const Vector2i& v) {
            return Vector2i(x * v.x, y * v.y);
        }

        Vector2i operator/(const Vector2i& v) {
            return Vector2i(x / v.x, y / v.y);
        }

        void operator+=(const Vector2i& v) {
            x += v.x;
            y += v.y;
        }

        void operator-=(const Vector2i& v) {
            x -= v.x;
            y -= v.y;
        }

        void operator*=(const Vector2i& v) {
            x *= v.x;
            y *= v.y;
        }

        void operator/=(const Vector2i& v) {
            x /= v.x;
            y /= v.y;
        }

        int x, y;
    };

    struct Vector3 {
        Vector3() : x(0), y(0), z(0) {}
        Vector3(const float& x, const float& y, const float& z) : x(x), y(y), z(z) {}

        template<typename t>
        Vector3 operator+(const t& s) {
            return Vector3(x + s, y + s, z + s);
        }

        template<typename t>
        Vector3 operator-(const t& s) {
            return Vector3(x - s, y - s, z - s);
        }

        template<typename t>
        auto operator*(const t& s) {
            return Vector3(x * s, y * s, z * s);
        }

        template<typename t>
        Vector3 operator/(const t& s) {
            return Vector3(x / s, y / s, z / s);
        }

        template<typename t>
        void operator+=(const t& s) {
            x += s;
            y += s;
            z += s;
        }

        template<typename t>
        void operator-=(const t& s) {
            x -= s;
            y -= s;
            z -= s;
        }

        template<typename t>
        void operator*=(const t& s) {
            x *= s;
            y *= s;
            z *= s;
        }

        template<typename t>
        void operator/=(const t& s) {
            x /= s;
            y /= s;
            z /= s;
        }

        Vector3 operator+(const Vector3& v) {
            return Vector3(x + v.x, y + v.y, z + v.z);
        }

        Vector3 operator-(const Vector3& v) {
            return Vector3(x - v.x, y - v.y, z - v.z);
        }

        Vector3 operator*(const Vector3& v) {
            return Vector3(x * v.x, y * v.y, z * v.z);
        }

        Vector3 operator/(const Vector3& v) {
            return Vector3(x / v.x, y / v.y, z / v.z);
        }

        void operator+=(const Vector3& v) {
            x += v.x;
            y += v.y;
            z += v.z;
        }

        void operator-=(const Vector3& v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
        }

        void operator*=(const Vector3& v) {
            x *= v.x;
            y *= v.y;
            z *= v.z;
        }

        void operator/=(const Vector3& v) {
            x /= v.x;
            y /= v.y;
            z /= v.z;
        }

        float x, y, z;
    };
    
}
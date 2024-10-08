#pragma once

#include "variant.hpp"
#include "basis.hpp"

struct Transform3D {
	constexpr Transform3D() {}
	Transform3D(const Transform3D &transform) = default;
	Transform3D(Transform3D &&transform) = default;

	/// @brief Create a new identity transform.
	/// @return The identity transform.
	static Transform3D identity();
	/// @brief Create a new transform from a basis and origin.
	/// @param origin The origin of the transform.
	/// @param basis The basis of the transform.
	Transform3D(const Vector3 &origin, const Basis &basis);

	Transform3D &operator =(const Transform3D &transform);

	// Transform3D operations
	void invert();
	void affine_invert();
	void translate(const Vector3 &offset);

	Transform3D inverse() const;
	Transform3D orthonormalized() const;
	Transform3D rotated(const Vector3 &axis, double angle) const;
	Transform3D scaled(const Vector3 &scale) const;
	Transform3D translated(const Vector3 &offset) const;
	Transform3D looking_at(const Vector3 &target, const Vector3 &up) const;
	Transform3D interpolate_with(const Transform3D &to, double weight) const;

	// Transform3D access
	Vector3 get_origin() const;
	void set_origin(const Vector3 &origin);
	Basis get_basis() const;
	void set_basis(const Basis &basis);

	static Transform3D from_variant_index(unsigned idx) { Transform3D a {}; a.m_idx = idx; return a; }
	unsigned get_variant_index() const noexcept { return m_idx; }
private:
	unsigned m_idx = INT32_MIN;
};

inline Variant::Variant(const Transform3D &t) {
	m_type = Variant::TRANSFORM3D;
	v.i = t.get_variant_index();
}

inline Variant::operator Transform3D() const {
	if (m_type != Variant::TRANSFORM3D) {
		api_throw("std::bad_cast", "Failed to cast Variant to Transform3D", this);
	}
	return Transform3D::from_variant_index(v.i);
}

inline Transform3D Variant::as_transform3d() const {
	return static_cast<Transform3D>(*this);
}

inline Transform3D &Transform3D::operator =(const Transform3D &transform) {
	if (this->m_idx != INT32_MIN) {
		// Oh, we have a Transform3D, but we are assigning from another one.
		// Let's just copy the data.
		set_origin(transform.get_origin());
		set_basis(transform.get_basis());
	} else {
		// We are assigning to a Transform3D, but we don't have one.
		// Let's just copy the index/handle.
		this->m_idx = transform.m_idx;
	}
	return *this;
}

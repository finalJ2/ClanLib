/*
**  ClanLib SDK
**  Copyright (c) 1997-2012 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Magnus Norddahl
*/

/// \addtogroup clanPhysics3D_World clanPhysics3D World
/// \{

#pragma once

#include "api_physics3d.h"
#include <memory>

namespace clan
{

class Physics3DWorld;
class Physics3DShape;
class Physics3DObject_Impl;

class CL_API_PHYSICS3D Physics3DObject
{
public:
	Physics3DObject();
	Physics3DObject(Physics3DWorld &world, const Physics3DShape &shape, const Vec3f &position = Vec3f(0.0f), const Quaternionf &orientation = Quaternionf(), const Vec3f &scale = Vec3f(1.0f));
	bool is_null() const { return !impl; }

	Vec3f get_position() const;
	Quaternionf get_orientation() const;
	Vec3f get_scale() const;
	void set_position(const Vec3f &position);
	void set_orientation(const Quaternionf &orientation);
	void set_scale(const Vec3f &scale);

private:
	std::shared_ptr<Physics3DObject_Impl> impl;
};

}

/// \}
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
**    Arkadiusz Kalinowski
*/

/// \addtogroup clanPhysics_Collision clanPhysics Collision
/// \{


#pragma once

#include "../../api_physics.h"
#include "../../../Core/Math/vec2.h" // Should this be included here instead of beeing in polygon_shape.cpp ? 
#include "../../Collision/Shapes/shape.h"

namespace clan
{

class PolygonShape_Impl;
class Angle;
/// \brief Polygon Shape class.
///
/// \xmlonly !group=Physic/Collision/Shapes! !header=polygon_shape.h! \endxmlonly
class CL_API_PHYSICS PolygonShape : public Shape
{
/// \name Construction
/// \{
public:

	/// \brief Constructs a null instance.
	PolygonShape();

	~PolygonShape();

/// \}
/// \name Attributes
/// \{
public:

/// \}
/// \name Operations
/// \{
public:
	//Add us
	//b2Shape * 	Clone (b2BlockAllocator *allocator) const
	//int32 	GetChildCount () const
	//void 	Set (const b2Vec2 *vertices, int32 vertexCount)

	void 	SetAsBox (float width, float height);
	void 	SetAsBox (float width, float height, const Vec2f &center, Angle &angle);
	//bool 	TestPoint (const b2Transform &transform, const b2Vec2 &p) const
	//bool 	RayCast (b2RayCastOutput *output, const b2RayCastInput &input, const b2Transform &transform, int32 childIndex) const
	//void 	ComputeAABB (b2AABB *aabb, const b2Transform &transform, int32 childIndex) const
	//void 	ComputeMass (b2MassData *massData, float32 density) const
	//int32 	GetVertexCount () const
	//const b2Vec2 & 	GetVertex (int32 index) const
	//Add us

/// \}
/// \name Implementation
/// \{
private:

	std::shared_ptr<PolygonShape_Impl> impl;

/// \}
	friend class FixtureDescription;
};

}

/// \}
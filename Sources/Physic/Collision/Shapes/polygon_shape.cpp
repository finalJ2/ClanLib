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

#include "Physic/precomp.h"
#include "shape_impl.h"
#include "polygon_shape_impl.h"
#include "API/Physic/Collision/Shapes/polygon_shape.h"
#include "API/Core/Math/angle.h"

namespace clan
{

PolygonShape_Impl::PolygonShape_Impl()
{
}

PolygonShape_Impl::~PolygonShape_Impl()
{
}


PolygonShape::PolygonShape()
: impl(new PolygonShape_Impl)
{
	shape_impl->shape_type = shape_polygon;
	shape_impl->shape = dynamic_cast<b2Shape*> (&impl->shape);
}

PolygonShape::~PolygonShape()
{

}

void 	PolygonShape::SetAsBox (float width, float height)
{
	impl->shape.SetAsBox(width,height);
}
void 	PolygonShape::SetAsBox (float width, float height, const Vec2f &center, Angle &angle)
{
	impl->shape.SetAsBox(width,
						height,
						b2Vec2(center.x, center.y),
						angle.to_radians());
}


}
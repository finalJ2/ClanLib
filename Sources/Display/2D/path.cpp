/*
**  ClanLib SDK
**  Copyright (c) 1997-2013 The ClanLib Team
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
**    Mark Page
*/

#include "Display/precomp.h"
#include "API/Display/2D/path.h"
#include "path_impl.h"
#include "Display/Font/font_impl.h"

namespace clan
{
	Path::Path() : impl(new PathImpl)
	{
		impl->subpaths.resize(1);
	}

	void Path::set_fill_mode(PathFillMode fill_mode)
	{
		impl->fill_mode = fill_mode;
	}

	void Path::move_to(const Pointf &point)
	{
		if (!impl->subpaths.back().commands.empty())
			impl->subpaths.push_back(CanvasSubpath());

		impl->subpaths.back().points.front() = point;
	}

	void Path::line_to(const Pointf &point)
	{
		impl->subpaths.back().points.push_back(point);
		impl->subpaths.back().commands.push_back(PathCommand::line);
	}

	void Path::bezier_to(const Pointf &control, const Pointf &point)
	{
		impl->subpaths.back().points.push_back(control);
		impl->subpaths.back().points.push_back(point);
		impl->subpaths.back().commands.push_back(PathCommand::quadradic);
	}

	void Path::bezier_to(const Pointf &control1, const Pointf &control2, const Pointf &point)
	{
		impl->subpaths.back().points.push_back(control1);
		impl->subpaths.back().points.push_back(control2);
		impl->subpaths.back().points.push_back(point);
		impl->subpaths.back().commands.push_back(PathCommand::cubic);
	}

	void Path::close()
	{
		if (!impl->subpaths.back().commands.empty())
		{
			impl->subpaths.back().closed = true;
			impl->subpaths.push_back(CanvasSubpath());
		}
	}

	Path Path::glyph(Font &font, unsigned int glyph)
	{
		if (!font.impl)
			return Path();
		return font.impl->glyph_cache.get_glyph_path(font.impl->font_engine, glyph);
	}

	Path Path::rect(const Rectf &box)
	{
		Path path;
		path.move_to(box.get_top_left());
		path.line_to(Pointf(box.get_top_right()));
		path.line_to(Pointf(box.get_bottom_right()));
		path.line_to(Pointf(box.get_bottom_left()));
		path.close();
		return path;
	}

	Path Path::line(const Pointf &start, const Pointf &end)
	{
		Path path;
		path.move_to(start);
		path.line_to(end);
		return path;
	}

	Path Path::ellipse(const Pointf &center, const Sizef &radius)
	{
		Path path;

		clan::Sizef diameter = radius * 2.0f;

		float x = center.x - radius.width;
		float y = center.y - radius.height;

		float kappa = 0.5522848f;		// Kappa is 4*((SqrRoot2) - 1) / 3
		float control_horiz = (diameter.width / 2) * kappa;
		float control_vert = (diameter.height / 2) * kappa;
		float x_end = x + diameter.width;
		float y_end = y + diameter.height;
		float x_middle = x + diameter.width / 2;
		float y_middle = y + diameter.height / 2;

		path.move_to(x, y_middle);
		path.bezier_to(Pointf(x, y_middle - control_vert), Pointf(x_middle - control_horiz, y), Pointf(x_middle, y));
		path.bezier_to(Pointf(x_middle + control_horiz, y), Pointf(x_end, y_middle - control_vert), Pointf(x_end, y_middle));
		path.bezier_to(Pointf(x_end, y_middle + control_vert), Pointf(x_middle + control_horiz, y_end), Pointf(x_middle, y_end));
		path.bezier_to(Pointf(x_middle - control_horiz, y_end), Pointf(x, y_middle + control_vert), Pointf(x, y_middle));

		return path;
	}

	Path Path::rect(const Rectf &box, const clan::Sizef &corner)
	{
		Path path;

		float x = box.left;
		float y = box.top;

		float kappa = 0.5522848f;		// Kappa is 4*((SqrRoot2) - 1) / 3
		float control_horiz = (corner.width) * kappa;
		float control_vert = (corner.height) * kappa;

		float x_middle_a = box.left + corner.width;
		float y_middle_a = box.top + corner.height;

		float x_middle_b = box.right - corner.width;
		float y_middle_b = box.bottom - corner.height;

		path.move_to( x, y_middle_a);

		path.bezier_to(Pointf(x, y_middle_a - control_vert), Pointf(x_middle_a - control_horiz, y), Pointf(x_middle_a, y));
		path.line_to(Pointf(x_middle_b, y));
		path.bezier_to(Pointf(x_middle_b + control_horiz, y), Pointf(box.right, y_middle_a - control_vert), Pointf(box.right, y_middle_a));
		path.line_to(Pointf(box.right, y_middle_b));
		path.bezier_to(Pointf(box.right, y_middle_b + control_vert), Pointf(x_middle_b + control_horiz, box.bottom), Pointf(x_middle_b, box.bottom));
		path.line_to(Pointf(x_middle_a, box.bottom));
		path.bezier_to(Pointf(x_middle_a - control_horiz, box.bottom), Pointf(x, y_middle_b + control_vert), Pointf(x, y_middle_b));
		path.close();

		return path;
	}

	void Path::transform(const Mat3f &transform)
	{
		for (unsigned int subpaths_cnt = 0; subpaths_cnt < impl->subpaths.size(); subpaths_cnt++)
		{
			std::vector<Pointf> &points = impl->subpaths[subpaths_cnt].points;
			for (unsigned int points_cnt = 0; points_cnt < points.size(); points_cnt++)
			{
				points[points_cnt] = transform * points[points_cnt];
			}
		}
	}
}

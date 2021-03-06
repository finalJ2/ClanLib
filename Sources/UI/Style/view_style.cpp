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
*/

#include "UI/precomp.h"
#include "API/UI/Style/style.h"
#include "API/Core/Text/string_help.h"
#include "view_style_impl.h"

namespace clan
{
	ViewStyle::ViewStyle() : impl(new ViewStyleImpl())
	{
	}

	ViewStyle::ViewStyle(ViewStyle &&move) : impl(std::move(move.impl))
	{
	}

	ViewStyle::ViewStyle(const ViewStyle &copy) : impl(new ViewStyleImpl())
	{
		*impl.get() = *copy.impl.get();
	}

	ViewStyle::~ViewStyle()
	{
	}

	ViewStyle &ViewStyle::operator =(const ViewStyle &that)
	{
		*impl.get() = *that.impl.get();
		return *this;
	}

	void ViewStyle::set_layout_none()
	{
		impl->layout = ViewLayout::none;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_layout_block()
	{
		impl->layout = ViewLayout::block;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_layout_line()
	{
		impl->layout = ViewLayout::line;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_layout_vbox()
	{
		impl->layout = ViewLayout::vbox;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_layout_hbox()
	{
		impl->layout = ViewLayout::hbox;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_flex_grow(float grow)
	{
		impl->flex.grow = grow;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_flex_shrink(float shrink)
	{
		impl->flex.shrink = shrink;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_flex_basis_auto()
	{
		impl->flex.basis = ViewFlexBasis();
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_flex_basis(float basis)
	{
		impl->flex.basis.type = ViewFlexBasis::type_length;
		impl->flex.basis.value = basis;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_flex(float grow, float shrink)
	{
		impl->flex.grow = grow;
		impl->flex.shrink = shrink;
		impl->flex.basis = ViewFlexBasis();
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_flex(float grow, float shrink, float basis)
	{
		impl->flex.grow = grow;
		impl->flex.shrink = shrink;
		impl->flex.basis.type = ViewFlexBasis::type_length;
		impl->flex.basis.value = basis;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_flex_none()
	{
		impl->flex.grow = 0.0f;
		impl->flex.shrink = 0.0f;
		impl->flex.basis = ViewFlexBasis();
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_background_none()
	{
		impl->background = ViewBackground();
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_background(const Colorf &color)
	{
		impl->background.color = color;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_background_gradient_to_bottom(const Colorf &top, const Colorf &bottom)
	{
		impl->background.stops.clear();
		impl->background.stops.push_back(ViewGradientStop(top, 0.0f));
		impl->background.stops.push_back(ViewGradientStop(bottom, 1.0f));
		impl->background.angle = 180.0f;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_background_gradient_to_bottom(const Colorf &stop1, float t1, const Colorf &stop2, float t2, const Colorf &stop3, float t3, const Colorf &stop4, float t4)
	{
		impl->background.stops.clear();
		impl->background.stops.push_back(ViewGradientStop(stop1, t1));
		impl->background.stops.push_back(ViewGradientStop(stop2, t2));
		impl->background.stops.push_back(ViewGradientStop(stop3, t3));
		impl->background.stops.push_back(ViewGradientStop(stop4, t4));
		impl->background.angle = 180.0f;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_background_image(const std::string &url)
	{
		impl->background.image = PixelBuffer(url);
			if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_background_size_contain()
	{

	}

	void ViewStyle::set_margin(float left, float top, float right, float bottom)
	{
		impl->margin.left.type = ViewMarginValue::type_length;
		impl->margin.left.value = left;
		impl->margin.right.type = ViewMarginValue::type_length;
		impl->margin.right.value = right;
		impl->margin.top.type = ViewMarginValue::type_length;
		impl->margin.top.value = top;
		impl->margin.bottom.type = ViewMarginValue::type_length;
		impl->margin.bottom.value = bottom;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_margin(float width, float height)
	{
		set_margin(width, height, width, height);
	}

	void ViewStyle::set_margin(float size)
	{
		set_margin(size, size, size, size);
	}

	void ViewStyle::set_border_none()
	{

	}

	void ViewStyle::set_border(const Colorf &color, float left, float top, float right, float bottom)
	{
		impl->border.left.type = ViewBorderValue::type_solid;
		impl->border.left.color = color;
		impl->border.left.width = left;
		impl->border.right.type = ViewBorderValue::type_solid;
		impl->border.right.color = color;
		impl->border.right.width = right;
		impl->border.top.type = ViewBorderValue::type_solid;
		impl->border.top.color = color;
		impl->border.top.width = top;
		impl->border.bottom.type = ViewBorderValue::type_solid;
		impl->border.bottom.color = color;
		impl->border.bottom.width = bottom;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_border(const Colorf &color, float width, float height)
	{
		set_border(color, width, height, width, height);
	}

	void ViewStyle::set_border(const Colorf &color, float size)
	{
		set_border(color, size, size, size, size);
	}

	void ViewStyle::set_border_radius(float size)
	{
		set_border_radius(size, size, size, size);
	}

	void ViewStyle::set_border_radius(float tl, float tr, float bl, float br)
	{
		impl->border.top_left_radius.x = tl;
		impl->border.top_left_radius.y = tl;
		impl->border.top_right_radius.x = tr;
		impl->border.top_right_radius.y = tr;
		impl->border.bottom_left_radius.x = bl;
		impl->border.bottom_left_radius.y = bl;
		impl->border.bottom_right_radius.x = br;
		impl->border.bottom_right_radius.y = br;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_box_shadow(const Colorf &color, float x, float y, float size)
	{
		impl->background.shadow_inset = false;
		impl->background.shadow_color = color;
		impl->background.shadow_offset.x = x;
		impl->background.shadow_offset.y = y;
		impl->background.shadow_blur_radius = size;
		impl->background.shadow_spread_distance = 0.0f;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_padding(float left, float top, float right, float bottom)
	{
		impl->padding.left = left;
		impl->padding.right = right;
		impl->padding.top = top;
		impl->padding.bottom = bottom;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_padding(float width, float height)
	{
		set_padding(width, height, width, height);
	}

	void ViewStyle::set_padding(float size)
	{
		set_padding(size, size, size, size);
	}

	void ViewStyle::set_width(float width)
	{
		impl->content.width.type = ViewWidthValue::type_length;
		impl->content.width.value = width;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_height(float height)
	{
		impl->content.height.type = ViewWidthValue::type_length;
		impl->content.height.value = height;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_static()
	{
		impl->position.mode = ViewPositionMode::static_mode;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_absolute()
	{
		impl->position.mode = ViewPositionMode::absolute;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_fixed()
	{
		impl->position.mode = ViewPositionMode::fixed;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_left(float value)
	{
		impl->position.left.type = ViewPositionValue::type_length;
		impl->position.left.value = value;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_top(float value)
	{
		impl->position.top.type = ViewPositionValue::type_length;
		impl->position.top.value = value;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_right(float value)
	{
		impl->position.right.type = ViewPositionValue::type_length;
		impl->position.right.value = value;
		if (impl->style_changed) impl->style_changed();
	}

	void ViewStyle::set_bottom(float value)
	{
		impl->position.bottom.type = ViewPositionValue::type_length;
		impl->position.bottom.value = value;
		if (impl->style_changed) impl->style_changed();
	}

	bool ViewStyle::is_width_auto() const
	{
		return impl->content.width.type == ViewWidthValue::type_auto;
	}

	bool ViewStyle::is_height_auto() const
	{
		return impl->content.height.type == ViewWidthValue::type_auto;
	}

	float ViewStyle::width() const
	{
		return !is_width_auto() ? impl->content.width.value : 0.0f;
	}

	float ViewStyle::height() const
	{
		return !is_height_auto() ? impl->content.height.value : 0.0f;
	}

	bool ViewStyle::is_static() const
	{
		return impl->position.mode == ViewPositionMode::static_mode;
	}

	bool ViewStyle::is_absolute() const
	{
		return impl->position.mode == ViewPositionMode::absolute;
	}

	bool ViewStyle::is_fixed() const
	{
		return impl->position.mode == ViewPositionMode::fixed;
	}

	bool ViewStyle::is_left_auto() const
	{
		return impl->position.left.type == ViewPositionValue::type_auto;
	}

	bool ViewStyle::is_top_auto() const
	{
		return impl->position.top.type == ViewPositionValue::type_auto;
	}

	bool ViewStyle::is_right_auto() const
	{
		return impl->position.right.type == ViewPositionValue::type_auto;
	}

	bool ViewStyle::is_bottom_auto() const
	{
		return impl->position.bottom.type == ViewPositionValue::type_auto;
	}

	float ViewStyle::left() const
	{
		return !is_left_auto() ? impl->position.left.value : 0.0f;
	}

	float ViewStyle::top() const
	{
		return !is_top_auto() ? impl->position.top.value : 0.0f;
	}

	float ViewStyle::right() const
	{
		return !is_right_auto() ? impl->position.right.value : 0.0f;
	}

	float ViewStyle::bottom() const
	{
		return !is_bottom_auto() ? impl->position.bottom.value : 0.0f;
	}

	bool ViewStyle::is_margin_left_auto() const
	{
		return impl->margin.left.type == ViewMarginValue::type_auto;
	}

	bool ViewStyle::is_margin_top_auto() const
	{
		return impl->margin.top.type == ViewMarginValue::type_auto;
	}

	bool ViewStyle::is_margin_right_auto() const
	{
		return impl->margin.right.type == ViewMarginValue::type_auto;
	}

	bool ViewStyle::is_margin_bottom_auto() const
	{
		return impl->margin.bottom.type == ViewMarginValue::type_auto;
	}

	float ViewStyle::margin_left() const
	{
		return !is_margin_left_auto() ? impl->margin.left.value : 0.0f;
	}

	float ViewStyle::margin_top() const
	{
		return !is_margin_top_auto() ? impl->margin.top.value : 0.0f;
	}

	float ViewStyle::margin_right() const
	{
		return !is_margin_right_auto() ? impl->margin.right.value : 0.0f;
	}

	float ViewStyle::margin_bottom() const
	{
		return !is_margin_bottom_auto() ? impl->margin.bottom.value : 0.0f;
	}

	bool ViewStyle::is_border_left_solid() const
	{
		return impl->border.left.type == ViewBorderValue::type_solid;
	}

	bool ViewStyle::is_border_top_solid() const
	{
		return impl->border.top.type == ViewBorderValue::type_solid;
	}

	bool ViewStyle::is_border_right_solid() const
	{
		return impl->border.right.type == ViewBorderValue::type_solid;
	}

	bool ViewStyle::is_border_bottom_solid() const
	{
		return impl->border.bottom.type == ViewBorderValue::type_solid;
	}

	float ViewStyle::border_left() const
	{
		return impl->border.left.width;
	}

	float ViewStyle::border_top() const
	{
		return impl->border.top.width;
	}

	float ViewStyle::border_right() const
	{
		return impl->border.right.width;
	}

	float ViewStyle::border_bottom() const
	{
		return impl->border.bottom.width;
	}

	float ViewStyle::padding_left() const
	{
		return impl->padding.left;
	}

	float ViewStyle::padding_top() const
	{
		return impl->padding.top;
	}

	float ViewStyle::padding_right() const
	{
		return impl->padding.right;
	}

	float ViewStyle::padding_bottom() const
	{
		return impl->padding.bottom;
	}

	bool ViewStyle::is_layout_none() const
	{
		return impl->layout == ViewLayout::none;
	}

	bool ViewStyle::is_layout_block() const
	{
		return impl->layout == ViewLayout::block;
	}

	bool ViewStyle::is_layout_line() const
	{
		return impl->layout == ViewLayout::line;
	}

	bool ViewStyle::is_layout_vbox() const
	{
		return impl->layout == ViewLayout::vbox;
	}

	bool ViewStyle::is_layout_hbox() const
	{
		return impl->layout == ViewLayout::hbox;
	}

	float ViewStyle::flex_grow() const
	{
		return impl->flex.grow;
	}

	float ViewStyle::flex_shrink() const
	{
		return impl->flex.shrink;
	}

	bool ViewStyle::is_flex_basis_auto() const
	{
		return impl->flex.basis.type == ViewFlexBasis::type_auto;
	}

	float ViewStyle::flex_basis() const
	{
		return !is_flex_basis_auto() ? impl->flex.basis.value : 0.0f;
	}

	void ViewStyle::render(Canvas &canvas, const ViewGeometry &geometry) const
	{
		impl->render(canvas, geometry);
	}

	void ViewStyle::set_style_changed(const std::function<void()> &callback)
	{
		impl->style_changed = callback;
	}
}

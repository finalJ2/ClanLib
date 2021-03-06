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
#include "API/UI/StandardViews/span_layout_view.h"
#include "span_layout_view_impl.h"

namespace clan
{
	SpanLayoutView::SpanLayoutView() : impl(new SpanLayoutViewImpl())
	{
		style.set_layout_none();
	}

	void SpanLayoutView::set_text_alignment(TextAlignment alignment)
	{
		impl->set_text_alignment(alignment);
		set_needs_layout();
		set_needs_render();
	}

	void SpanLayoutView::clear()
	{
		impl->clear();

		std::vector<std::shared_ptr<View>> subviews_copy = subviews();
		for (auto &view : subviews_copy)
			view->remove_from_super();
	}

	void SpanLayoutView::add_text(const std::string &text, const Font &font, const Colorf &color)
	{
		impl->add_text(text, font, color);
		set_needs_layout();
		set_needs_render();
	}

	void SpanLayoutView::add_subview(const std::shared_ptr<View> &view, float baseline_offset)
	{
		View::add_subview(view);
		impl->set_last_baseline_offset(baseline_offset);
	}

	void SpanLayoutView::subview_added(const std::shared_ptr<View> &view)
	{
		impl->add_subview(view);
	}

	void SpanLayoutView::subview_removed(const std::shared_ptr<View> &view)
	{
		impl->remove_subview(view);
	}

	void SpanLayoutView::render_content(Canvas &canvas)
	{
		return impl->render_content(canvas, geometry().content.get_width());
	}

	float SpanLayoutView::get_preferred_width()
	{
		if (style.is_width_auto())
			return impl->get_preferred_width();
		else
			return style.width();
	}

	float SpanLayoutView::get_preferred_height(float width)
	{
		if (style.is_height_auto())
			return impl->get_preferred_height(width);
		else
			return style.height();
	}

	float SpanLayoutView::get_first_baseline_offset(float width)
	{
		return impl->get_first_baseline_offset(width);
	}

	float SpanLayoutView::get_last_baseline_offset(float width)
	{
		return impl->get_last_baseline_offset(width);
	}

	void SpanLayoutView::layout_subviews()
	{
		View::layout_subviews();
		impl->layout_views(geometry().content.get_width());
	}
}

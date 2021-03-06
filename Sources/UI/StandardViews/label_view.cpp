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
#include "API/UI/StandardViews/label_view.h"
#include "API/Display/2D/canvas.h"
#include "API/Display/Render/shared_gc_data.h"
#include "API/Display/2D/path.h"
#include "API/Display/2D/pen.h"
#include "API/Display/2D/brush.h"
#include "API/Display/Font/font.h"
#include "API/Display/Font/font_metrics.h"
#include "API/Display/Font/glyph_metrics.h"
#include "line_metrics.h"
#include <cmath>

namespace clan
{
	std::string LabelView::text() const
	{
		return _text;
	}

	void LabelView::set_text(const std::string &value)
	{
		_text = value;
		set_needs_layout();
	}

	FontDescription LabelView::font() const
	{
		return _font_desc;
	}

	void LabelView::set_font(const FontDescription &value)
	{
		_font_desc = value.clone();
		Canvas canvas = SharedGCData::get_resource_canvas();
		_font = Font(canvas, value);
		set_needs_layout();
	}

	Colorf LabelView::text_color() const
	{
		return _text_color;
	}

	void LabelView::set_text_color(const Colorf &value)
	{
		_text_color = value;
		set_needs_layout();
	}

	TextAlignment LabelView::text_alignment() const
	{
		return _text_alignment;
	}

	void LabelView::set_text_alignment(TextAlignment value)
	{
		_text_alignment = value;
		set_needs_layout();
	}

	LineBreakMode LabelView::line_break_mode() const
	{
		return _line_break_mode;
	}

	void LabelView::set_line_break_mode(LineBreakMode value)
	{
		_line_break_mode = value;
		set_needs_layout();
	}

	bool LabelView::enabled() const
	{
		return _enabled;
	}

	void LabelView::set_enabled(bool value)
	{
		_enabled = value;
		set_needs_layout();
	}

	int LabelView::number_of_lines() const
	{
		return _number_of_lines;
	}

	void LabelView::set_number_of_lines(int value)
	{
		_number_of_lines = value;
		set_needs_layout();
	}

	Colorf LabelView::highlighted_color() const
	{
		return _highlighted_color;
	}

	void LabelView::set_highlighted_color(const Colorf &value)
	{
		_highlighted_color = value;
		set_needs_layout();
	}

	bool LabelView::highlighted() const
	{
		return _highlighted;
	}

	void LabelView::set_highlighted(bool value)
	{
		_highlighted = value;
		set_needs_layout();
	}

	Colorf LabelView::shadow_color() const
	{
		return _shadow_color;
	}

	void LabelView::set_shadow_color(const Colorf &value)
	{
		_shadow_color = value;
		set_needs_layout();
	}

	void LabelView::render_content(Canvas &canvas)
	{
		std::string clipped_text = _text;
		LineMetrics line_metrics(_font);
		GlyphMetrics advance = _font.get_glyph_metrics(canvas, clipped_text);

		if (advance.advance.width > geometry().content.get_width())
		{
			std::string ellipsis = StringHelp::unicode_to_utf8(0x2026);
			GlyphMetrics ellipsis_advance = _font.get_glyph_metrics(canvas, ellipsis);

			switch (_line_break_mode)
			{
			case LineBreakMode::clipping:
				clipped_text = clipped_text.substr(0, _font.clip_from_left(canvas, clipped_text, geometry().content.get_width()));
				break;
			case LineBreakMode::truncating_head:
				clipped_text = ellipsis + clipped_text.substr(_font.clip_from_right(canvas, clipped_text, geometry().content.get_width() - ellipsis_advance.advance.width));
				break;
			case LineBreakMode::truncating_middle:
				{
				std::string text_left = clipped_text.substr(0, _font.clip_from_left(canvas, clipped_text, geometry().content.get_width() * 0.5f - ellipsis_advance.advance.width));
				std::string text_right = clipped_text.substr(_font.clip_from_right(canvas, clipped_text, geometry().content.get_width() * 0.5f - ellipsis_advance.advance.width));
				clipped_text = text_left + ellipsis + text_right;
				}
				break;
			case LineBreakMode::truncating_tail:
				clipped_text = clipped_text.substr(0, _font.clip_from_left(canvas, clipped_text, geometry().content.get_width() - ellipsis_advance.advance.width)) + ellipsis;
				break;
			default:
				break;
			}

			advance = _font.get_glyph_metrics(canvas, clipped_text);
			
			if (advance.advance.width > geometry().content.get_width())
				return; // Still no room.  Draw nothing!
		}

		switch (_text_alignment)
		{
		default:
		case TextAlignment::left:
			canvas.text(_font, 0.0f, line_metrics.ascent, clipped_text, Brush(_text_color));
			break;

		case TextAlignment::right:
			canvas.text(_font, geometry().content.get_width() - advance.advance.width, line_metrics.ascent, clipped_text, Brush(_text_color));
			break;

		case TextAlignment::center:
			canvas.text(_font, std::round((geometry().content.get_width() - advance.advance.width) * 0.5f), line_metrics.ascent, clipped_text, Brush(_text_color));
			break;
		}
	}

	float LabelView::get_preferred_width()
	{
		if (style.is_width_auto())
		{
			Canvas canvas = SharedGCData::get_resource_canvas();
			return _font.get_glyph_metrics(canvas, _text).advance.width;
		}
		else
			return style.width();
	}

	float LabelView::get_preferred_height(float width)
	{
		if (style.is_height_auto())
		{
			LineMetrics line_metrics(_font);
			return line_metrics.line_height;
		}
		else
			return style.height();
	}

	float LabelView::get_first_baseline_offset(float width)
	{
		LineMetrics line_metrics(_font);
		return line_metrics.ascent;
	}

	float LabelView::get_last_baseline_offset(float width)
	{
		return get_first_baseline_offset(width);
	}
}


#include "precomp.h"
#include "text_explosion_ascii.h"
#include "age_ascii.h"

TextExplosionAscii::TextExplosionAscii()
: initial_x(), initial_y()
{
}

void TextExplosionAscii::explode(AgeAscii *console, const std::string &new_text, int new_x, int new_y, clan::Colorf new_color)
{
	letter_positions.clear();
	letter_deltas.clear();
	text = new_text;
	color = new_color;
	initial_x = new_x;
	initial_y = new_y;

	int total_length = text.length();
	int x = initial_x - total_length/2;
	letter_positions.resize(text.length());
	letter_deltas.resize(text.length());
	letter_symbols.resize(text.length());
	for (size_t i = 0; i < text.length(); i++)
	{
		letter_positions[i] = clan::Vec3f((float)x, (float)initial_y, 1.0f);
		letter_deltas[i] = clan::Vec3f((rand()%2000-1000)/(float) 20, -(rand()%2000)/(float) 20, (rand()%2000-1000)/(float) 2000);
		letter_symbols[i] = clan::StringHelp::utf8_to_ucs2(text.substr(i, 1))[0];
		x++;
	}
	timer.reset();
}

void TextExplosionAscii::render(AgeAscii *console)
{
	if (!letter_positions.empty())
	{
		bool still_visible = false;
		timer.update();
		float time_elapsed = timer.get_time_elapsed();
		for (size_t i = 0; i < letter_positions.size(); i++)
		{
			console->set_character((int)letter_positions[i].x, (int)letter_positions[i].y, letter_symbols[i], color);

			letter_positions[i] += letter_deltas[i] * time_elapsed * 5.0f;
			letter_deltas[i].y += time_elapsed * 20.0f;
			//if (letter_deltas[i].y < console->get_console_height())
			//	still_visible = true;
		}
		if (!still_visible)
		{
			letter_positions.clear();
			letter_deltas.clear();
		}
	}
}

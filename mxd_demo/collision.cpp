
#include "collision.h"


void hit(global* g)
{
	static int count1 = 30;
	static int count2 = 30;
	++count1;
	++count2;
	if (count1 > 30)
	{
		auto player_hit_area = &g->pi->hit_area;
		auto enemy_hit_area = &g->ene->hit_area;

		bool is_hit = rectIntersect(player_hit_area, enemy_hit_area);

		if (is_hit)
		{
			count1 = 0;
			g->pi->hit(true);
		}
		else
		{
			g->pi->hit(false);
		}
	}
	if (count2 > 30)
	{
		auto player_atk_area = &g->pi->atk_area;
		auto enemy_hit_area = &g->ene->hit_area;

		bool is_hit = rectIntersect(player_atk_area, enemy_hit_area);

		if (is_hit)
		{
			if (g->pi->is_attacking)
			{
				count2 = 0;
				g->ene->hit(true);
			}
		}
		else
		{
			g->ene->hit(false);
		}
	}
}

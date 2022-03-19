
#include "rigidbody.h"

rigidbody::rigidbody(carama_info* carama)
{
	static world_area left_wall, right_wall, ground,
		block1, block2;

	left_wall.init(-200, 0, 210, 1000);
	right_wall.init(1990, 0, 210, 1000);
	ground.init(-200, 900, 2000, 200);
	block1.init(500, 900, 300, 20);
	block2.init(500, 500, 300, 20);

	left_wall.set_carama(carama);
	right_wall.set_carama(carama);
	ground.set_carama(carama);
	block1.set_carama(carama);
	block2.set_carama(carama);

	//static_objs.push_back(&left_wall);
	//static_objs.push_back(&right_wall);
	//static_objs.push_back(&ground);
	//static_objs.push_back(&block1);
	static_objs.push_back(&block2);
}

rigidbody::~rigidbody()
{
}

void rigidbody::render_static_objs()
{
	for (int i = 0; i < this->static_objs.size(); ++i)
	{
		drawBloodBar(this->static_objs[i], 3, BLACK, LIGHTGRAY, RED, 1.0);
	}
}

void rigidbody::rigidbody_move()
{
	int i, j;
	for (i = 0; i < this->static_objs.size(); ++i)
	{
		for (j = 0; j < this->dynamic_objs.size(); ++j)
		{
			if (rectIntersect(this->static_objs[i], this->dynamic_objs[j]))
			{
				char direct = this->_check_move_direction(this->static_objs[i], this->dynamic_objs[j]);
				printf("%d\n", direct);
				switch (direct)
				{
				case TOP:
					this->dynamic_objs[j]->changeY(
						this->static_objs[i]->get_coord2_in_world()->y);
					break;
				case BOTTOM:
					this->dynamic_objs[j]->changeY(
						this->static_objs[i]->get_coord1_in_world()->y -
						this->dynamic_objs[j]->get_height());
					break;
				case LEFT:
					this->dynamic_objs[j]->changeX(
						this->static_objs[i]->get_coord1_in_world()->x - this->dynamic_objs[j]->get_width());
					break;
				case RIGHT:
					this->dynamic_objs[j]->changeX(
						this->static_objs[i]->get_coord2_in_world()->x);
					break;
				default:
					break;
				}
			}
		}
	}
}

void rigidbody::push_static_objs(world_area* a)
{
	this->static_objs.push_back(a);
}

void rigidbody::push_dynamic_objs(world_area* a)
{
	this->dynamic_objs.push_back(a);
}

/*
 * 检测明确的碰撞方向
 *
 * 每次发生碰撞的时候会有来自8个方向的碰撞，再根据碰撞的参数返回正确的方向
 * 
 * 1.通过两个矩形的中心比较方向，将方向范围缩小成3个
 * 2.对矩形进入的范围进行判断，如果全部进入则结果为正方向之一并进行返回
 * 3.将碰撞矩形的坐标进行差值计算并取绝对值，取较长的一侧为正方向
 * 
 */
char rigidbody::_check_move_direction(world_area* static_obj, world_area* dynamic_obj)
{
	char tmp_result{};
	// 1.通过两个矩形的中心比较方向，将方向范围缩小成3个

	coord tmp_coo =
		*dynamic_obj->get_coord_center_in_world() - *static_obj->get_coord_center_in_world();

	if (tmp_coo.x < 0) tmp_result |= LEFT;
	if (tmp_coo.x > 0) tmp_result |= RIGHT;
	if (tmp_coo.y < 0) tmp_result |= TOP;
	if (tmp_coo.y > 0) tmp_result |= BOTTOM;

	char result{};
	// x
	// 相交的矩形width >= height
	// 动态物体在静态物体的左侧
	if (
		static_obj->get_coord_center_in_world()->x >
		dynamic_obj->get_coord_center_in_world()->x)
	{
		// 动态物体右侧在静态物体的左侧
		if (dynamic_obj->get_coord2_in_world()->x >
			static_obj->get_coord1_in_world()->x)
		{
			tmp_result |= LEFT;
			// 动态物体的上下边完全在静态物体里面
			if (dynamic_obj->get_coord1_in_world()->y >
				static_obj->get_coord1_in_world()->y &&
				dynamic_obj->get_coord2_in_world()->y <
				static_obj->get_coord2_in_world()->y)
			{
				result = LEFT;
			}
		}
	}
	// 动态物体在静态物体的右侧
	else if (
		static_obj->get_coord_center_in_world()->x <
		dynamic_obj->get_coord_center_in_world()->x)
	{
		// 动态物体左侧在静态物体的右侧
		if (static_obj->get_coord2_in_world()->x >
			dynamic_obj->get_coord1_in_world()->x)
		{
			tmp_result |= RIGHT;
			// 动态物体的上下边完全在静态物体里面
			if (dynamic_obj->get_coord1_in_world()->y >
				static_obj->get_coord1_in_world()->y &&
				dynamic_obj->get_coord2_in_world()->y <
				static_obj->get_coord2_in_world()->y)
			{
				result = RIGHT;
			}
		}
	}
	// y
	// 动态物体在静态物体的下方
	if (
		static_obj->get_coord_center_in_world()->y >
		dynamic_obj->get_coord_center_in_world()->y)
	{
		// 动态物体下方在静态物体的上方
		if (dynamic_obj->get_coord2_in_world()->y >
			static_obj->get_coord1_in_world()->y)
		{
			tmp_result |= DOWN;
			// 动态物体的左右边完全在静态物体里面
			if (dynamic_obj->get_coord1_in_world()->x >
				static_obj->get_coord1_in_world()->x &&
				dynamic_obj->get_coord2_in_world()->x <
				static_obj->get_coord2_in_world()->x)
			{
				return DOWN;
			}
		}
	}
	// 动态物体在静态物体的上方
	else if (
		static_obj->get_coord_center_in_world()->y <
		dynamic_obj->get_coord_center_in_world()->y)
	{
		// 动态物体上方在静态物体的下方
		if (static_obj->get_coord2_in_world()->y >
			dynamic_obj->get_coord1_in_world()->y)
		{
			tmp_result |= TOP;
			// 动态物体的左右边完全在静态物体里面
			if (dynamic_obj->get_coord1_in_world()->x >
				static_obj->get_coord1_in_world()->x &&
				dynamic_obj->get_coord2_in_world()->x <
				static_obj->get_coord2_in_world()->x)
			{
				return TOP;
			}
		}
	}

	return result;
	//if (result)
	//{
	//	return result;
	//}
	//else
	//{
	//	return TOP;
	//}
}

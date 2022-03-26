
#include "collision.h"

collision::collision()
{
}

collision::~collision()
{
}

void collision::rigidbody_check()
{
	int i, j;
	world_area* static_area, * dynamic_area;
	for (i = 0; i < this->_static_collsion_objects.size(); ++i)
	{
		static_area = this->_static_collsion_objects[i]->get_collsion_area();
		for (j = 0; j < this->_dynamic_collsion_objects.size(); ++j)
		{
			dynamic_area = this->_dynamic_collsion_objects[j]->get_collsion_area();

			if (rectIntersect(static_area, dynamic_area))
			{
				switch (this->_check_move_direction(static_area, dynamic_area))
				{
				case TOP:
					this->_dynamic_collsion_objects[j]->changeY(
						static_area->get_coord1_in_world()->y -
						this->_dynamic_collsion_objects[j]->get_height());
					break;
				case BOTTOM:
					this->_dynamic_collsion_objects[j]->changeY(
						static_area->get_coord2_in_world()->y);
					break;
				case LEFT:
					this->_dynamic_collsion_objects[j]->changeX(
						static_area->get_coord1_in_world()->x -
						this->_dynamic_collsion_objects[j]->get_width());
					break;
				case RIGHT:
					this->_dynamic_collsion_objects[j]->changeX(
						static_area->get_coord2_in_world()->x);
					break;
				default:
					break;
				}
			}
			else
			{
				two_obs_pos[(long)dynamic_area + (long)static_area] =
					this->_check_move_direction(static_area, dynamic_area);
			}
		}
	}
}

void collision::graviry_check()
{
	int i, j;
	for (i = 0; i < this->_dynamic_collsion_objects.size(); ++i)
	{
		for (j = 0; j < this->_static_collsion_objects.size(); ++j)
		{
			if (rectIntersect(
				this->_dynamic_collsion_objects[i]->get_ground_check_area(),
				this->_static_collsion_objects[j]->get_collsion_area()
			))
			{
				this->_dynamic_collsion_objects[i]->is_on_ground = true;
				break;
			}
		}
		if (j >= this->_static_collsion_objects.size())
		{
			this->_dynamic_collsion_objects[i]->is_on_ground = false;
		}
	}
}

void collision::graviry_force()
{
	vector<dynamic_collsion_object*>::iterator d_it;

	for (d_it = this->_dynamic_collsion_objects.begin(); d_it != this->_dynamic_collsion_objects.end(); ++d_it)
	{
		(*d_it)->v_y += 0.1 * GRAVITY;
		if ((*d_it)->is_on_ground)
		{
			if ((*d_it)->v_y > 0)
			{
				(*d_it)->v_y = 0;
			}
		}
		(*d_it)->changeOffY((*d_it)->v_y);
	}
	//for (int i = 0; i < dynamic_objs->size(); ++i)
	//{
	//	(*dynamic_objs)[i]->v_y += 0.1 * GRAVITY;
	//	if ((*dynamic_objs)[i]->is_on_ground)
	//	{
	//		if ((*dynamic_objs)[i]->v_y > 0)
	//		{
	//			(*dynamic_objs)[i]->v_y = 0;
	//		}
	//	}
	//	(*dynamic_objs)[i]->changeOffY((*dynamic_objs)[i]->v_y);
	//}
}

void collision::clear_objects()
{
	vector<static_collsion_object*>().swap(this->_static_collsion_objects);
	vector<dynamic_collsion_object*>().swap(this->_dynamic_collsion_objects);

	map<long, char>().swap(this->two_obs_pos);
}

/*
 * 检测明确的碰撞方向
 *
 * 每次发生碰撞的时候会有来自8个方向的碰撞，再根据碰撞的参数返回正确的方向
 *
 * 1.通过两个矩形的中心比较方向，将方向范围缩小成3个
 * 2.对矩形进入的范围进行判断，如果全部进入则结果为正方向之一并进行返回
 * 3.将碰撞矩形的坐标进行差值计算并取绝对值，取较长的一侧为正方向
 * todo:
 * 1.优化3步骤，取两个物体中心点的夹角和静态物体碰撞的角和该中心点的夹角的差来计算正方向
 * 2.禁止穿越，在碰撞检测之前记录动态物体相对静态物体的位置，如果发生碰撞只可以碰撞记录的位置
 * 3.精细类型，比如only_top作为平台支撑的type
 *
 */
char collision::_check_move_direction(world_area* static_obj, world_area* dynamic_obj)
{
	char tmp_result = 0x0;
	// 0.读取碰撞之前的char，结果必须在这三个值中产生

	// 1.通过两个矩形的中心比较方向，将方向范围缩小成3个

	coord tmp_coo =
		*dynamic_obj->get_coord_center_in_world() - *static_obj->get_coord_center_in_world();

	if (tmp_coo.x < 0) tmp_result |= LEFT;
	if (tmp_coo.x > 0) tmp_result |= RIGHT;
	if (tmp_coo.y < 0) tmp_result |= TOP;
	if (tmp_coo.y > 0) tmp_result |= BOTTOM;

	// 如果有一个方向为0则直接返回该正方向，两个方向为0则返回默认的TOP
	switch (tmp_result)
	{
	case 0x0:
		return TOP;
	case TOP:
	case BOTTOM:
	case LEFT:
	case RIGHT:
		return tmp_result;
	default:
		break;
	}

	// 计算下面两个角到中点的距离的宽除高是否有一个小于宽除高
	//if (tmp_result & TOP)
	//{
	//	if (static_obj->get_width() / static_obj->get_height() -
	//		abs((* dynamic_obj->get_coord2_in_world() -
	//		*static_obj->get_coord_center_in_world()).x_except_y())
	//		> 0 ||
	//		static_obj->get_width() / static_obj->get_height() -
	//		abs((coord(dynamic_obj->get_coord1_in_world()->x, dynamic_obj->get_coord2_in_world()->y) -
	//		*static_obj->get_coord_center_in_world()).x_except_y())
	//		> 0)
	//	{
	//		return TOP;
	//	}
	//	else
	//	{
	//		return tmp_result - TOP;
	//	}
	//}

	//if (tmp_result & BOTTOM)
	//{
	//	if (static_obj->get_width() / static_obj->get_height() -
	//		abs((*dynamic_obj->get_coord1_in_world() -
	//		*static_obj->get_coord_center_in_world()).x_except_y())
	//		> 0 ||
	//		static_obj->get_width() / static_obj->get_height() -
	//		abs((coord(dynamic_obj->get_coord2_in_world()->x, dynamic_obj->get_coord1_in_world()->y) -
	//			*static_obj->get_coord_center_in_world()).x_except_y())
	//		> 0)
	//	{
	//		return BOTTOM;
	//	}
	//	else
	//	{
	//		return tmp_result - BOTTOM;
	//	}
	//}



	// 2.对矩形进入的范围进行判断，如果全部进入则结果为正方向之一并进行返回

	if (tmp_result & TOP)
	{
		if (dynamic_obj->get_coord1_in_world()->x >
			static_obj->get_coord1_in_world()->x &&
			dynamic_obj->get_coord2_in_world()->x <
			static_obj->get_coord2_in_world()->x)
		{
			return TOP;
		}
	}
	if (tmp_result & BOTTOM)
	{
		if (dynamic_obj->get_coord1_in_world()->x >
			static_obj->get_coord1_in_world()->x &&
			dynamic_obj->get_coord2_in_world()->x <
			static_obj->get_coord2_in_world()->x)
		{
			return BOTTOM;
		}
	}
	if (tmp_result & LEFT)
	{
		if (dynamic_obj->get_coord1_in_world()->y >
			static_obj->get_coord1_in_world()->y &&
			dynamic_obj->get_coord2_in_world()->y <
			static_obj->get_coord2_in_world()->y)
		{
			return LEFT;
		}
	}
	if (tmp_result & RIGHT)
	{
		if (dynamic_obj->get_coord1_in_world()->y >
			static_obj->get_coord1_in_world()->y &&
			dynamic_obj->get_coord2_in_world()->y <
			static_obj->get_coord2_in_world()->y)
		{
			return RIGHT;
		}
	}

	// 3.将碰撞矩形的坐标进行差值计算并取绝对值，取较长的一侧为正方向

	// 左上
	if ((tmp_result & LEFT) && (tmp_result & TOP))
	{
		tmp_coo = *dynamic_obj->get_coord2_in_world() - *static_obj->get_coord1_in_world();
		// is_width_than
		if (abs(tmp_coo.x) - abs(tmp_coo.y) >= 0) return TOP;
		else return LEFT;
	}
	// 右上
	else if ((tmp_result & RIGHT) && (tmp_result & TOP))
	{
		tmp_coo = coord(
			dynamic_obj->get_coord1_in_world()->x - static_obj->get_coord2_in_world()->x,
			dynamic_obj->get_coord2_in_world()->y - static_obj->get_coord1_in_world()->y);
		// is_width_than
		if (abs(tmp_coo.x) - abs(tmp_coo.y) >= 0) return TOP;
		else return RIGHT;
	}
	// 左下
	else if ((tmp_result & LEFT) && (tmp_result & BOTTOM))
	{
		tmp_coo = coord(
			dynamic_obj->get_coord2_in_world()->x - static_obj->get_coord1_in_world()->x,
			dynamic_obj->get_coord1_in_world()->y - static_obj->get_coord2_in_world()->y);
		// is_width_than
		if (abs(tmp_coo.x) - abs(tmp_coo.y) >= 0) return BOTTOM;
		else return LEFT;
	}
	// 右下
	else if ((tmp_result & RIGHT) && (tmp_result & BOTTOM))
	{
		tmp_coo = *dynamic_obj->get_coord1_in_world() - *static_obj->get_coord2_in_world();
		// is_width_than
		if (abs(tmp_coo.x) - abs(tmp_coo.y) >= 0) return BOTTOM;
		else return RIGHT;
	}

	return 0x0;
}

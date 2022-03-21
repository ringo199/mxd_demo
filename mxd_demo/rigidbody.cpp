
#include "rigidbody.h"

rigidbody::rigidbody(carama_info* carama)
{
	static block left_wall(carama), right_wall(carama), ground(carama),
		block1(carama), block2(carama);

	left_wall.init(0, 0, 200, 1000);
	right_wall.init(1800, 0, 200, 1000);
	ground.init(0, 800, 2000, 200);
	block1.init(200, 300, 300, 20);
	block2.init(500, 700, 20, 100);

	this->push_static_objs(&left_wall);
	this->push_static_objs(&right_wall);
	this->push_static_objs(&ground);
	this->push_static_objs(&block1);
	this->push_static_objs(&block2);
}

rigidbody::~rigidbody()
{
}

void rigidbody::render_static_objs()
{
	for (int i = 0; i < this->static_objs.size(); ++i)
	{
		drawBloodBar(this->static_objs[i]->get_render_area()->get_coord1()->x, this->static_objs[i]->get_render_area()->get_coord1()->y, this->static_objs[i]->get_render_area()->get_width(), this->static_objs[i]->get_render_area()->get_height(),
			0, RED, RED, RED, 1.0);
	}
}

void rigidbody::rigidbody_check()
{
	int i, j;
	world_area *static_area, *dynamic_area;
	for (i = 0; i < this->static_objs.size(); ++i)
	{
		static_area = this->static_objs[i]->get_collsion_area();
		for (j = 0; j < this->dynamic_objs.size(); ++j)
		{
			dynamic_area = this->dynamic_objs[j]->get_collsion_area();

			if (rectIntersect(static_area, dynamic_area))
			{
				switch (this->_check_move_direction(static_area, dynamic_area))
				{
				case TOP:
					this->dynamic_objs[j]->changeY(
						static_area->get_coord1_in_world()->y -
						this->dynamic_objs[j]->get_height());
					break;
				case BOTTOM:
					this->dynamic_objs[j]->changeY(
						static_area->get_coord2_in_world()->y);
					break;
				case LEFT:
					this->dynamic_objs[j]->changeX(
						static_area->get_coord1_in_world()->x -
						this->dynamic_objs[j]->get_width());
					break;
				case RIGHT:
					this->dynamic_objs[j]->changeX(
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

void rigidbody::graviry_check()
{
	int i, j;
	for (j = 0; j < this->dynamic_objs.size(); ++j)
	{
		for (i = 0; i < this->static_objs.size(); ++i)
		{
			if (rectIntersect(this->static_objs[i]->get_collsion_area(),
				this->dynamic_objs[j]->get_ground_check_area()))
			{
				this->dynamic_objs[j]->is_on_ground = true;
				break;
			}
		}
		if (i >= this->static_objs.size())
		{
			this->dynamic_objs[j]->is_on_ground = false;
		}
	}
}

void rigidbody::graviry_force()
{
	for (int i = 0; i < this->dynamic_objs.size(); ++i)
	{
		this->dynamic_objs[i]->v_y += 0.1 * GRAVITY;
		if (this->dynamic_objs[i]->is_on_ground)
		{
			if (this->dynamic_objs[i]->v_y > 0)
			{
				this->dynamic_objs[i]->v_y = 0;
			}
		}
		this->dynamic_objs[i]->changeOffY(this->dynamic_objs[i]->v_y);
	}
}

void rigidbody::push_static_objs(block* s_obj)
{
	this->static_objs.push_back(s_obj);
}

void rigidbody::push_dynamic_objs(sprite_object* d_obj)
{
	this->dynamic_objs.push_back(d_obj);
}

/*
 * �����ȷ����ײ����
 *
 * ÿ�η�����ײ��ʱ���������8���������ײ���ٸ�����ײ�Ĳ���������ȷ�ķ���
 * 
 * 1.ͨ���������ε����ıȽϷ��򣬽�����Χ��С��3��
 * 2.�Ծ��ν���ķ�Χ�����жϣ����ȫ����������Ϊ������֮һ�����з���
 * 3.����ײ���ε�������в�ֵ���㲢ȡ����ֵ��ȡ�ϳ���һ��Ϊ������
 * todo:
 * 1.�Ż�3���裬ȡ�����������ĵ�ļнǺ;�̬������ײ�ĽǺ͸����ĵ�ļнǵĲ�������������
 * 2.��ֹ��Խ������ײ���֮ǰ��¼��̬������Ծ�̬�����λ�ã����������ײֻ������ײ��¼��λ��
 * 3.��ϸ���ͣ�����only_top��Ϊƽ̨֧�ŵ�type
 * 
 */
char rigidbody::_check_move_direction(world_area* static_obj, world_area* dynamic_obj)
{
	char tmp_result = 0x0;
	// 0.��ȡ��ײ֮ǰ��char�����������������ֵ�в���

	// 1.ͨ���������ε����ıȽϷ��򣬽�����Χ��С��3��

	coord tmp_coo =
		*dynamic_obj->get_coord_center_in_world() - *static_obj->get_coord_center_in_world();

	if (tmp_coo.x < 0) tmp_result |= LEFT;
	if (tmp_coo.x > 0) tmp_result |= RIGHT;
	if (tmp_coo.y < 0) tmp_result |= TOP;
	if (tmp_coo.y > 0) tmp_result |= BOTTOM;

	// �����һ������Ϊ0��ֱ�ӷ��ظ���������������Ϊ0�򷵻�Ĭ�ϵ�TOP
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

	// �������������ǵ��е�ľ���Ŀ�����Ƿ���һ��С�ڿ����
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



	// 2.�Ծ��ν���ķ�Χ�����жϣ����ȫ����������Ϊ������֮һ�����з���

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

	// 3.����ײ���ε�������в�ֵ���㲢ȡ����ֵ��ȡ�ϳ���һ��Ϊ������

	// ����
	if ((tmp_result & LEFT) && (tmp_result & TOP))
	{
		tmp_coo = *dynamic_obj->get_coord2_in_world() - *static_obj->get_coord1_in_world();
		// is_width_than
		if (abs(tmp_coo.x) - abs(tmp_coo.y) >= 0) return TOP;
		else return LEFT;
	}
	// ����
	else if ((tmp_result & RIGHT) && (tmp_result & TOP))
	{
		tmp_coo = coord(
			dynamic_obj->get_coord1_in_world()->x - static_obj->get_coord2_in_world()->x,
			dynamic_obj->get_coord2_in_world()->y - static_obj->get_coord1_in_world()->y);
		// is_width_than
		if (abs(tmp_coo.x) - abs(tmp_coo.y) >= 0) return TOP;
		else return RIGHT;
	}
	// ����
	else if ((tmp_result & LEFT) && (tmp_result & BOTTOM))
	{
		tmp_coo = coord(
			dynamic_obj->get_coord2_in_world()->x - static_obj->get_coord1_in_world()->x,
			dynamic_obj->get_coord1_in_world()->y - static_obj->get_coord2_in_world()->y);
		// is_width_than
		if (abs(tmp_coo.x) - abs(tmp_coo.y) >= 0) return BOTTOM;
		else return LEFT;
	}
	// ����
	else if ((tmp_result & RIGHT) && (tmp_result & BOTTOM))
	{
		tmp_coo = *dynamic_obj->get_coord1_in_world() - *static_obj->get_coord2_in_world();
		// is_width_than
		if (abs(tmp_coo.x) - abs(tmp_coo.y) >= 0) return BOTTOM;
		else return RIGHT;
	}

	return 0x0;
}

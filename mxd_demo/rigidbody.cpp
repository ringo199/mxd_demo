
#include "rigidbody.h"

rigidbody::rigidbody(carama_info* carama)
{
	static world_area left_wall, right_wall, ground,
		block1, block2;

	left_wall.init(0, 0, 200, 1000);
	right_wall.init(1800, 0, 200, 1000);
	ground.init(0, 800, 2000, 200);
	block1.init(200, 300, 300, 20);
	block2.init(500, 500, 300, 20);

	left_wall.set_carama(carama);
	right_wall.set_carama(carama);
	ground.set_carama(carama);
	block1.set_carama(carama);
	block2.set_carama(carama);

	static_objs.push_back(&left_wall);
	static_objs.push_back(&right_wall);
	static_objs.push_back(&ground);
	static_objs.push_back(&block1);
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

void rigidbody::rigidbody_check()
{
	int i, j;
	for (i = 0; i < this->static_objs.size(); ++i)
	{
		for (j = 0; j < this->dynamic_objs.size(); ++j)
		{
			if (rectIntersect(this->static_objs[i], this->dynamic_objs[j]))
			{
				switch (this->_check_move_direction(this->static_objs[i], this->dynamic_objs[j]))
				{
				case TOP:
					is_on_grounds[this->dynamic_objs[j]] = true;
					this->dynamic_objs[j]->changeY(
						this->static_objs[i]->get_coord1_in_world()->y -
						this->dynamic_objs[j]->get_height());
					break;
				case BOTTOM:
					is_on_grounds[this->dynamic_objs[j]] = false;
					this->dynamic_objs[j]->changeY(
						this->static_objs[i]->get_coord2_in_world()->y);
					break;
				case LEFT:
					is_on_grounds[this->dynamic_objs[j]] = false;
					this->dynamic_objs[j]->changeX(
						this->static_objs[i]->get_coord1_in_world()->x - this->dynamic_objs[j]->get_width());
					break;
				case RIGHT:
					is_on_grounds[this->dynamic_objs[j]] = false;
					this->dynamic_objs[j]->changeX(
						this->static_objs[i]->get_coord2_in_world()->x);
					break;
				default:
					break;
				}
			}
			else
			{
				is_on_grounds[this->dynamic_objs[j]] = false;
			}
		}
	}
}

void rigidbody::graviry_check()
{
	for (int i = 0; i < this->dynamic_objs.size(); ++i)
	{
		if (!is_on_grounds[this->dynamic_objs[i]])
		{
			this->dynamic_objs[i]->changeOffY(10);
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
 * �����ȷ����ײ����
 *
 * ÿ�η�����ײ��ʱ���������8���������ײ���ٸ�����ײ�Ĳ���������ȷ�ķ���
 * 
 * 1.ͨ���������ε����ıȽϷ��򣬽�����Χ��С��3��
 * 2.�Ծ��ν���ķ�Χ�����жϣ����ȫ����������Ϊ������֮һ�����з���
 * 3.����ײ���ε�������в�ֵ���㲢ȡ����ֵ��ȡ�ϳ���һ��Ϊ������
 * 
 */
char rigidbody::_check_move_direction(world_area* static_obj, world_area* dynamic_obj)
{
	char tmp_result = 0x0;
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

	return TOP;

	//char result{};
	//// x
	//// �ཻ�ľ���width >= height
	//// ��̬�����ھ�̬��������
	//if (
	//	static_obj->get_coord_center_in_world()->x >
	//	dynamic_obj->get_coord_center_in_world()->x)
	//{
	//	// ��̬�����Ҳ��ھ�̬��������
	//	if (dynamic_obj->get_coord2_in_world()->x >
	//		static_obj->get_coord1_in_world()->x)
	//	{
	//		tmp_result |= LEFT;
	//		// ��̬��������±���ȫ�ھ�̬��������
	//		if (dynamic_obj->get_coord1_in_world()->y >
	//			static_obj->get_coord1_in_world()->y &&
	//			dynamic_obj->get_coord2_in_world()->y <
	//			static_obj->get_coord2_in_world()->y)
	//		{
	//			result = LEFT;
	//		}
	//	}
	//}
	//// ��̬�����ھ�̬������Ҳ�
	//else if (
	//	static_obj->get_coord_center_in_world()->x <
	//	dynamic_obj->get_coord_center_in_world()->x)
	//{
	//	// ��̬��������ھ�̬������Ҳ�
	//	if (static_obj->get_coord2_in_world()->x >
	//		dynamic_obj->get_coord1_in_world()->x)
	//	{
	//		tmp_result |= RIGHT;
	//		// ��̬��������±���ȫ�ھ�̬��������
	//		if (dynamic_obj->get_coord1_in_world()->y >
	//			static_obj->get_coord1_in_world()->y &&
	//			dynamic_obj->get_coord2_in_world()->y <
	//			static_obj->get_coord2_in_world()->y)
	//		{
	//			result = RIGHT;
	//		}
	//	}
	//}
	//// y
	//// ��̬�����ھ�̬������·�
	//if (
	//	static_obj->get_coord_center_in_world()->y >
	//	dynamic_obj->get_coord_center_in_world()->y)
	//{
	//	// ��̬�����·��ھ�̬������Ϸ�
	//	if (dynamic_obj->get_coord2_in_world()->y >
	//		static_obj->get_coord1_in_world()->y)
	//	{
	//		tmp_result |= DOWN;
	//		// ��̬��������ұ���ȫ�ھ�̬��������
	//		if (dynamic_obj->get_coord1_in_world()->x >
	//			static_obj->get_coord1_in_world()->x &&
	//			dynamic_obj->get_coord2_in_world()->x <
	//			static_obj->get_coord2_in_world()->x)
	//		{
	//			return DOWN;
	//		}
	//	}
	//}
	//// ��̬�����ھ�̬������Ϸ�
	//else if (
	//	static_obj->get_coord_center_in_world()->y <
	//	dynamic_obj->get_coord_center_in_world()->y)
	//{
	//	// ��̬�����Ϸ��ھ�̬������·�
	//	if (static_obj->get_coord2_in_world()->y >
	//		dynamic_obj->get_coord1_in_world()->y)
	//	{
	//		tmp_result |= TOP;
	//		// ��̬��������ұ���ȫ�ھ�̬��������
	//		if (dynamic_obj->get_coord1_in_world()->x >
	//			static_obj->get_coord1_in_world()->x &&
	//			dynamic_obj->get_coord2_in_world()->x <
	//			static_obj->get_coord2_in_world()->x)
	//		{
	//			return TOP;
	//		}
	//	}
	//}

	//return result;
	//if (result)
	//{
	//	return result;
	//}
	//else
	//{
	//	return TOP;
	//}
}

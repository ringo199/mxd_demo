
#include "objects.h"
#include "tools.h"

#include "global.h"
#include "netEvent.h"

using namespace global;
using namespace std;

object::object()
{
	this->_base_point = this;
}

object::~object()
{
}

render_object::render_object()
{
	this->_render_base_point = NULL;
	this->_res_type = RES_NULL;
	this->_res_str_path = "";
	this->_is_fixed = true;
}

render_object::~render_object()
{
}


void render_object::loadRenderImage()
{
	if (this->_is_fixed)
	{
		if (this->_res_type != RES_NULL)
		{
			GetLoadManager()->LoadAsset(this->_res_type, this->get_render_area());
		}
	}
	else
	{
		if (this->_res_str_path != "")
		{
			GetLoadManager()->LoadAsset(this->_res_str_path, this->get_render_area());
		}
	}
}

void render_object::renderImage()
{
	if (this->_is_fixed)
	{
		if (this->_res_type != RES_NULL)
		{
			putimage(this->get_render_area()->get_coord1()->x, this->get_render_area()->get_coord1()->y,
				GetLoadManager()->LoadAsset(this->_res_type, this->get_render_area())->img);
		}
	}
	else
	{
		if (this->_res_str_path != "")
		{
			putimage(this->get_render_area()->get_coord1()->x, this->get_render_area()->get_coord1()->y,
				GetLoadManager()->LoadAsset(this->_res_str_path, this->get_render_area())->img);
		}
	}
}


world_area* render_object::get_render_area()
{
	return &this->_render_area;
}

void transpoint_object::trans()
{
	GetObjectManager()->clear_objects();
	GetObjectManager()->GetPlayer()->clearEventRegister();

	GetEventManager()->eventEmit(UI_BEGIN_LOADING);
	sendMessage_type_6(
		this->_to_game_map_id,
		GetSessionManager()->GetSession(SESSION_MAP_ID));
	// GetSessionManager()->SetSession(SESSION_TRANS_FROM, this->_game_scene);
	// GetEventManager()->eventEmit(GAME_GOTO_SCENE, this->_game_scene);
}

int image_indexs_::GetImageIndex(e_res_type res_type)
{
	if (GetLoadManager()->AssetIsInit(res_type))
	{
		if (this->_img_indexs.find(res_type) == this->_img_indexs.end())
		{
			this->_img_indexs[res_type] = 0;
			return 0;
		}
		else
		{
			return this->_img_indexs[res_type];
		}
	}
	else
	{
		return -1;
	}
}

int image_indexs_::ChangeImageIndex(e_res_type res_type, int index)
{
	if (this->GetImageIndex(res_type) == -1) return -1;

	this->_img_indexs[res_type] = index % GetLoadManager()->GetResSize(res_type);

	return 0;
}

int image_indexs_::AddStepImageIndex(e_res_type res_type)
{
	if (this->GetImageIndex(res_type) == -1) return -1;

	return this->ChangeImageIndex(res_type, this->GetImageIndex(res_type) + 1);
}

IMAGE* image_indexs_::GetImage(e_res_type res_type)
{
	int index = this->GetImageIndex(res_type);
	if (index == -1)
	{
		return nullptr;
	}
	return &GetLoadManager()->LoadAsset(res_type)->img[index];
}

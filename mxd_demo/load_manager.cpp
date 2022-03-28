#include "load_manager.h"
#include "string"

static string res_dir = "res/";

struct res
{
	res()
	{
		this->type = RES_NULL;
		this->path = "";
		this->size = 0;
	}
	res(e_res_type t, string p, int s)
	{
		this->type = t;
		this->path = res_dir + p;
		this->size = s;
	}

	e_res_type type;
	string path;
	int size;

};

struct res_str
{
	res_str()
	{
		this->path = "";
		this->size = 0;
	}
	res_str(string p, int s)
	{
		this->path = p;
		this->size = s;
	}

	string path;
	int size;

};

unordered_map<e_res_type, res> res_map;
unordered_map<string, res_str> res_str_map;

LoadManager::LoadManager()
{
	res_map[RES_BG] = res(RES_BG, "bark/bg.png", 1);
	res_map[RES_GAME_BG_2] = res(RES_GAME_BG_2, "game_bg_2.jpg", 1);
	res_map[RES_HERO] = res(RES_HERO, "hero%d.png", 12);
	res_map[RES_HERO_ATTACK] = res(RES_HERO_ATTACK, "bark/g%02d.png", 11);
	res_map[RES_ENEMY] = res(RES_ENEMY, "p%d.png", 6);
	res_map[RES_UI_PLAYER_INFO] = res(RES_UI_PLAYER_INFO, "uibase.png", 1);
	res_map[RES_BLOCK_GROUND] = res(RES_BLOCK_GROUND, "ground.png", 1);
	res_map[RES_BLOCK_WALL] = res(RES_BLOCK_WALL, "wall.png", 1);
	res_map[RES_BLOCK_PLATFORM1] = res(RES_BLOCK_PLATFORM1, "platform1.png", 1);
	res_map[RES_BLOCK_PLATFORM2] = res(RES_BLOCK_PLATFORM2, "platform2.png", 1);
	res_map[RES_BLOCK_PLATFORM3] = res(RES_BLOCK_PLATFORM3, "platform3.png", 1);
	res_map[RES_DOOR] = res(RES_DOOR, "door.png", 1);
	res_map[RES_UI_BTN] = res(RES_UI_BTN, "btn.png", 1);
	res_map[RES_UI_BTN_] = res(RES_UI_BTN_, "btn.png", 1);
	res_map[RES_NPC_ACAO] = res(RES_NPC_ACAO, "acao.png", 1);
	res_map[RES_UI_BG1] = res(RES_UI_BG1, "ui_bg1.jpg", 1);
	res_map[RES_UI_BG2] = res(RES_UI_BG2, "ui_bg2.jpg", 1);
	res_map[RES_UI_BG3] = res(RES_UI_BG3, "ui_bg3.jpg", 1);
	res_map[RES_UI_BG4] = res(RES_UI_BG4, "ui_bg4.jpg", 1);
	res_map[RES_UI_BG_LOADING] = res(RES_UI_BG_LOADING, "ui_bg_loading.jpg", 1);
}

LoadManager::~LoadManager()
{
}

asset* LoadManager::LoadAsset(e_res_type res_type)
{
	if (this->_asset_map.find(res_type) == this->_asset_map.end() ||
		this->_asset_map[res_type].type == ASSET_NULL)
	{
		this->_asset_map[res_type].type = ASSET_IMAGE;
		this->_asset_map[res_type].img = new IMAGE[res_map[res_type].size];

		for (int i = 0; i < res_map[res_type].size; ++i)
		{
			sprintf(this->path, res_map[res_type].path.c_str(), i + 1);
			loadimage(&this->_asset_map[res_type].img[i], path);
		}
	}

	return &this->_asset_map[res_type];
}

asset* LoadManager::LoadAsset(e_res_type res_type, area* a)
{
	if (this->_asset_map.find(res_type) == this->_asset_map.end() ||
		this->_asset_map[res_type].type == ASSET_NULL)
	{
		this->_asset_map[res_type].type = ASSET_IMAGE;
		this->_asset_map[res_type].img = new IMAGE[res_map[res_type].size];

		for (int i = 0; i < res_map[res_type].size; ++i)
		{
			sprintf(this->path, res_map[res_type].path.c_str(), i + 1);
			loadimage(&this->_asset_map[res_type].img[i], path, a->get_width(), a->get_height(), true);
		}
	}

	return &this->_asset_map[res_type];
}

bool LoadManager::AssetIsInit(e_res_type res_type)
{
	if (this->_asset_map.find(res_type) == this->_asset_map.end() ||
		this->_asset_map[res_type].type == ASSET_NULL)
	{
		return false;
	}

	return true;
}


bool LoadManager::UnloadAsset(e_res_type res_type)
{
	if (!this->AssetIsInit(res_type)) return false;

	if (this->_asset_map[res_type].type == ASSET_IMAGE)
	{
		delete[] this->_asset_map[res_type].img;
		this->_asset_map[res_type].img = nullptr;
	}

	return true;
}

int LoadManager::GetResSize(e_res_type res_type)
{
	return res_map[res_type].size;
}


// string
void LoadManager::AddAsset(string path, int size)
{
	res_str_map[path] = res_str(path, size);
}

asset* LoadManager::LoadAsset(string res_type)
{
	if (this->_asset_str_map.find(res_type) == this->_asset_str_map.end() ||
		this->_asset_str_map[res_type].type == ASSET_NULL)
	{
		this->_asset_str_map[res_type].type = ASSET_IMAGE;
		this->_asset_str_map[res_type].img = new IMAGE[res_str_map[res_type].size];

		for (int i = 0; i < res_str_map[res_type].size; ++i)
		{
			sprintf(this->path, res_str_map[res_type].path.c_str(), i + 1);
			loadimage(&this->_asset_str_map[res_type].img[i], path);
		}
	}

	return &this->_asset_str_map[res_type];
}

asset* LoadManager::LoadAsset(string res_type, area* a)
{
	if (this->_asset_str_map.find(res_type) == this->_asset_str_map.end() ||
		this->_asset_str_map[res_type].type == ASSET_NULL)
	{
		this->_asset_str_map[res_type].type = ASSET_IMAGE;
		this->_asset_str_map[res_type].img = new IMAGE[res_str_map[res_type].size];

		for (int i = 0; i < res_str_map[res_type].size; ++i)
		{
			sprintf(this->path, res_str_map[res_type].path.c_str(), i + 1);
			loadimage(&this->_asset_str_map[res_type].img[i], path, a->get_width(), a->get_height(), true);
		}
	}

	return &this->_asset_str_map[res_type];
}

bool LoadManager::AssetIsInit(string res_type)
{
	if (this->_asset_str_map.find(res_type) == this->_asset_str_map.end() ||
		this->_asset_str_map[res_type].type == ASSET_NULL)
	{
		return false;
	}

	return true;
}

bool LoadManager::UnloadAsset(string res_type)
{
	if (!this->AssetIsInit(res_type)) return false;

	if (this->_asset_str_map[res_type].type == ASSET_IMAGE)
	{
		delete[] this->_asset_str_map[res_type].img;
		this->_asset_str_map[res_type].img = nullptr;
	}

	return true;
}

int LoadManager::GetResSize(string res_type)
{
	return res_str_map[res_type].size;
}


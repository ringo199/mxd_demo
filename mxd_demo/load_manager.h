#pragma once

#ifndef __LOAD_MANAGER_H__
#define __LOAD_MANAGER_H__

#include <stdio.h>
#include <graphics.h>
#include <map>
#include "var.h"

using namespace std;

typedef enum
{
	ASSET_NULL,
	ASSET_IMAGE
} e_asset_type;

struct asset
{
	e_asset_type	type = ASSET_NULL;
	IMAGE*			img;
};

class LoadManager
{
public:
	LoadManager();
	~LoadManager();

	asset* LoadAsset(e_res_type);
	asset* LoadAsset(e_res_type, area*);
	bool AssetIsInit(e_res_type);
	bool UnloadAsset(e_res_type);
	int GetResSize(e_res_type);

private:
	map<e_res_type, asset> _asset_map;
	char path[64];
};

#endif // !__LOAD_MANAGER_H__

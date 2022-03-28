#pragma once

#ifndef __LOAD_MANAGER_H__
#define __LOAD_MANAGER_H__

#include <stdio.h>
#include <graphics.h>
#include <unordered_map>
#include "var.h"
#include <string.h>

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

	void AddAsset(string, int);
	asset* LoadAsset(string);
	asset* LoadAsset(string, area*);
	bool AssetIsInit(string);
	bool UnloadAsset(string);
	int GetResSize(string);

private:
	unordered_map<e_res_type, asset> _asset_map;
	unordered_map<string, asset> _asset_str_map;
	char path[64];
};

#endif // !__LOAD_MANAGER_H__

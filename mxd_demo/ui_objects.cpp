
#include "ui_objects.h"

#include "global.h"
#include "tools.h"
#include "cJSON.h"
#include "netEvent.h"

using namespace global;

ui_object::ui_object()
{
	this->_base_point = this;
}

ui_object::~ui_object()
{
}

void ui_render_object::loadRenderImage()
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

void ui_render_object::renderImage()
{
	if (this->_is_fixed)
	{
		if (this->_res_type != RES_NULL)
		{
			putimagePNG2(this->get_render_area()->get_coord1()->x, this->get_render_area()->get_coord1()->y,
				GetLoadManager()->LoadAsset(this->_res_type, this->get_render_area())->img);
		}
	}
	else
	{
		if (this->_res_str_path != "")
		{
			putimagePNG2(this->get_render_area()->get_coord1()->x, this->get_render_area()->get_coord1()->y,
				GetLoadManager()->LoadAsset(this->_res_str_path, this->get_render_area())->img);
		}
	}
}

void ui_click_event_object::callEventListener()
{
	if (this->_is_event_mgr)
	{
		GetEventManager()->eventEmit(this->_event_type);
	}
	else
	{
		if (this->_eventListener != 0)
		{
			typedef void* (*FUNC)(void*);
			((FUNC)this->_eventListener)(NULL);
		}
		else
		{
			this->_eventListenerFunc();
		}
	}
}

void image::render()
{
	if (isShow)
	{
		this->renderImage();
		this->renderChild();
	}
}

void button::renderChild()
{
	if (isShow)
		drawText(this->get_render_area(), this->btntxt, this->font_size, BLACK, DRAW_TEXT_SINGLE_ABS_MIDDLE);
}

void label::render()
{
	//drawBloodBar(this->get_render_area(), 5, BLACK, BLACK, BLACK, 1.0);
	if (this->isShow)
		drawText(this->get_render_area(), this->txt.c_str(), this->fontSize, this->color, this->_draw_text_type);
}

void progress::render()
{
	drawBloodBar(this->get_render_area(),
		this->lineWidth, this->boardColor, this->emptyColor, this->fillColor, this->percent);
}

input::input() : ui_object(), ui_render_object(), ui_click_event_object()
{
	this->lineWidth = 3;
	this->boardColor = 0;
	this->focusColor = 0xFF5555;
	this->emptyColor = 0xFFFFFF;
	this->color = 0;
	this->fontSize = 0;
	this->txt = "";
	this->type = INPUT_TYPE::TEXT;
	this->addEventListener([=]() {
		ChangeFocusInput(this);
	});
}

void input::render()
{
	if (GetFocusInput() == this)
	{
		drawBloodBar(this->get_render_area(),
			this->lineWidth, this->boardColor, this->focusColor, 0, 0.0);
	}
	else
	{
		drawBloodBar(this->get_render_area(),
			this->lineWidth, this->boardColor, this->emptyColor, 0, 0.0);
	}
	if (this->type == INPUT_TYPE::PASSWORD)
	{
		string s;
		for (int i = 0; i < this->txt.size(); ++i)
		{
			s.append(1, '*');
		}
		drawText(this->get_render_area(), 10, s.c_str(), this->fontSize, this->color, DRAW_TEXT_SINGLE_LEFT);
	}
	else
	{
		drawText(this->get_render_area(), 10, this->txt.c_str(), this->fontSize, this->color, DRAW_TEXT_SINGLE_LEFT);
	}
}

void discussion::render()
{
	drawBloodBar(this->get_render_area(),
		this->lineWidth, this->boardColor, this->emptyColor, 0, 0.0);
	drawText(this->get_render_area(), 10, this->showtxt.c_str(), this->fontSize, this->color, DRAW_TEXT_MUTI_LEFT);
}

void discussion::pushTxt(string txt)
{
	this->txtList.push_back(txt);
	this->adjust();
}

void discussion::adjust()
{
	while (this->txtList.size() > this->txtsize)
	{
		this->txtList.erase(this->txtList.begin());
	}

	this->showtxt.clear();
	for (int i = 0; i < this->txtList.size(); ++i)
	{
		this->showtxt.append(this->txtList[i]);
		this->showtxt.append("\n");
	}
}

void dialog::init(coord coo, int w, int h)
{
	this->init(coo.x, coo.y, w, h);
}

void dialog::init(int x, int y, int w, int h)
{
	this->initObject(x, y, w, h);
	this->setRenderArea(this);
	this->_close_btn = new button;
	this->_close_btn->init(x + 2, y + h - 2 - 25, 75, 25);
	this->_close_btn->btntxt = "结束对话";
	this->_close_btn->font_size = 15;
	this->_close_btn->isShow = false;
	this->_close_btn->addEventListener([&]() {
		this->closeDialog();
	});
	this->_next_btn = new button;
	this->_next_btn->init(w + x - 2 - 75, y + h - 2 - 50, 75, 25);
	this->_next_btn->btntxt = "下一条";
	this->_next_btn->font_size = 15;
	this->_next_btn->isShow = false;
	this->_next_btn->addEventListener([&]() {
		this->nextDialog();
	});
	this->_ok_btn = new button;
	this->_ok_btn->init(w + x - 2 - 75, y + h - 2 - 30, 75, 25);
	this->_ok_btn->btntxt = "确定";
	this->_ok_btn->font_size = 15;
	this->_ok_btn->isShow = false;
	this->_ok_btn->addEventListener([&]() {
		this->closeDialog();
	});
	this->_name = new label;
	this->_name->init(x + 2, y + h - 2 - 50, 75, 25);
	this->_name->fontSize = 20;
	this->_name->_draw_text_type = DRAW_TEXT_SINGLE_ABS_MIDDLE;
	this->_img = new image;
	this->_img->init(x + 2, y + 2, 75, 100);
	this->_content = new label;
	this->_content->init(x + 100, y + 2, w - 100, h - 50);
	this->_content->fontSize = 20;
	this->_content->_draw_text_type = DRAW_TEXT_MUTI_LEFT;
}

void dialog::render()
{
	if (_is_show)
	{
		drawBloodBar(this->get_render_area(),
			this->lineWidth, this->boardColor, this->emptyColor, 0, 0.0);
		// drawText(this->get_render_area(), this->showtxt.c_str(), this->fontSize, this->color);
	}
}

void dialog::openDialog(std::string name, e_res_type resType, std::string content)
{
	this->_is_show = true;
	this->_close_btn->isShow = true;
	this->_name->txt = name;
	this->_img->setResType(resType);
	this->_img->loadRenderImage();
	this->_img->isShow = true;
	this->_content->isShow = true;
	this->_content->txt = "";

	this->str = content;
	this->strindex = 0;
	this->contentTimerId = GetTimer()->setInterval([&]() {
		if (this->strindex >= this->str.size())
		{
			if (this->contentTimerId != -1)
			{
				GetTimer()->clearInterval(this->contentTimerId);
				this->contentTimerId = -1;
			}
		}
		else
		{
			this->_content->txt.append(1, str[strindex]);
			++this->strindex;
		}
	}, 20);
}

void dialog::openDialog(std::string name, std::string resPath, std::string content)
{
	this->_is_show = true;
	this->_close_btn->isShow = true;
	this->_name->txt = name;
	this->_img->setResStringPath(resPath);
	this->_img->loadRenderImage();
	this->_img->isShow = true;
	this->_content->isShow = true;
	this->_content->txt = "";

	this->str = content;
	this->strindex = 0;
	this->contentTimerId = GetTimer()->setInterval([&]() {
		if (this->strindex >= this->str.size())
		{
			if (this->contentTimerId != -1)
			{
				GetTimer()->clearInterval(this->contentTimerId);
				this->contentTimerId = -1;
			}
		}
		else
		{
			this->_content->txt.append(1, str[strindex]);
			++this->strindex;
		}
	}, 20);
}

void dialog::openDialog(std::string name, std::string resPath, int _dialogID)
{
	this->_is_show = true;
	this->_close_btn->isShow = true;
	this->_name->txt = name;
	this->_img->setResStringPath(resPath);
	this->_img->loadRenderImage();
	this->_img->isShow = true;
	this->_content->isShow = true;
	this->_content->txt = "";

	sendMessage_type_7(_dialogID);
}

void dialog::getDialogContent(void* ctx, std::string data)
{
	dialog* context = (dialog*)ctx;
	cJSON* dat = cJSON_Parse(data.c_str());
	cJSON* id, * content, * next;
	id = cJSON_GetObjectItem(dat, "id");
	content = cJSON_GetObjectItem(dat, "content");
	next = cJSON_GetObjectItem(dat, "next");
	context->dialogID = id->valueint;
	context->nextID = next->valueint;
	context->str = content->valuestring;

	context->_next_btn->isShow = context->nextID != -1;
	context->_ok_btn->isShow = context->nextID == -1;

	context->strindex = 0;
	context->contentTimerId = GetTimer()->setInterval([&]() {
		if (context->strindex >= context->str.size())
		{
			if (context->contentTimerId != -1)
			{
				GetTimer()->clearInterval(context->contentTimerId);
				context->contentTimerId = -1;
			}
		}
		else
		{
			context->_content->txt.append(1, context->str[context->strindex]);
			++context->strindex;
		}
	}, 20);
}

void dialog::eventRegister()
{
	GetEventManager()->eventRegister(NET_TYPE_7, (long)&this->getDialogContent, this);
}

void dialog::closeDialog()
{
	this->_is_show = false;
	this->_close_btn->isShow = false;
	this->_ok_btn->isShow = false;
	this->_next_btn->isShow = false;
	this->_name->txt = "";
	this->_img->isShow = false;
	this->_content->isShow = false;
	this->_content->txt = "";
	if (this->contentTimerId != -1)
	{
		GetTimer()->clearInterval(this->contentTimerId);
		this->contentTimerId = -1;
	}
}

void dialog::nextDialog()
{
	if (this->nextID == -1) return;
	this->_content->txt = "";
	sendMessage_type_7(this->nextID);
}

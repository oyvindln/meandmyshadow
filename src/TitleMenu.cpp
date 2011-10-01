/****************************************************************************
** Copyright (C) 2011 Luka Horvat <redreaper132 at gmail.com>
** Copyright (C) 2011 Edward Lii <edward_iii at myway.com>
** Copyright (C) 2011 O. Bahri Gordebak <gordebak at gmail.com>
**
**
** This file may be used under the terms of the GNU General Public
** License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/
#include "Functions.h"
#include "Classes.h"
#include "Globals.h"
#include "TitleMenu.h"
#include "GUIListBox.h"
#include <iostream>
using namespace std;

static int m_nHighlight=0;

Menu::Menu()
{
	s_menu = load_image(get_data_path()+"gfx/menu/menu.png");
	m_nHighlight=0;
}

Menu::~Menu()
{
}

void Menu::handle_events()
{
	int x, y;

	SDL_GetMouseState(&x, &y);

	m_nHighlight=0;
	if(x>=200&&x<600&&y>=150&&y<550){
		m_nHighlight=(y-70)/80;
	}

	if ( event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT )
	{
		switch(m_nHighlight){
		case 1:
			next_state(STATE_LEVEL_SELECT);
			break;
		case 2:
			next_state(STATE_OPTIONS);
			break;
		case 3:
			m_sLevelName="leveledit.map";
			next_state(STATE_LEVEL_EDITOR);
			break;
		case 4:
			next_state(STATE_HELP);
			break;
		case 5:
			next_state(STATE_EXIT);
			break;
		}
	}

	if ( event.type == SDL_QUIT )
	{
		next_state(STATE_EXIT);
	}
}

void Menu::logic()
{

}

void Menu::render()
{
	apply_surface( 0,0,s_menu,screen,NULL );
	if(m_nHighlight>0){
		SDL_Rect r,r1;
		r.x=200;
		r.y=70+80*m_nHighlight;
		r.w=400;
		r.h=1;
		SDL_FillRect(screen,&r,0);
		r1.x=200;
		r1.y=r.y;
		r1.w=1;
		r1.h=80;
		SDL_FillRect(screen,&r1,0);
		r1.x=600;
		SDL_FillRect(screen,&r1,0);
		r.y+=80;
		SDL_FillRect(screen,&r,0);
	}
}

Help::Help()
{
	s_help = load_image(get_data_path()+"gfx/menu/help.png");
}

Help::~Help()
{
}

void Help::handle_events()
{
		if ( event.type == SDL_KEYUP || event.type == SDL_MOUSEBUTTONUP )
		{
			next_state(STATE_MENU);
		}

		if ( event.type == SDL_QUIT )
		{
			next_state(STATE_EXIT);
		}

		/*if ( event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE )
		{
			next_state(STATE_MENU);
		}*/
}

void Help::logic()
{

}


void Help::render()
{
	apply_surface( 0, 0, s_help, screen, NULL);
}

static bool m_sound, m_fullscreen, m_leveltheme, m_internet;
static string m_theme;

Options::Options()
{
	s_options = load_image(get_data_path()+"gfx/menu/options.png");
	
	m_sound=get_settings()->getBoolValue("sound");
	m_fullscreen=get_settings()->getBoolValue("fullscreen");
	m_theme=get_settings()->getValue("theme");
	m_leveltheme=get_settings()->getBoolValue("leveltheme");
	m_internet=get_settings()->getBoolValue("internet");
	
	//OPTIONS menu
	//create GUI (test only)
	if(GUIObjectRoot){
		delete GUIObjectRoot;
		GUIObjectRoot=NULL;
	}
	GUIObjectRoot=new GUIObject(100,(SCREEN_HEIGHT-400)/2 + 50,600,350,GUIObjectFrame,"");
	
	GUIObject *obj=new GUIObject(50,50,240,36,GUIObjectCheckBox,"Sound",m_sound?1:0);
	obj->Name="chkSound";
	obj->EventCallback=this;
	GUIObjectRoot->ChildControls.push_back(obj);
		
	obj=new GUIObject(50,100,240,36,GUIObjectCheckBox,"Fullscreen",m_fullscreen?1:0);
	obj->Name="chkFullscreen";
	obj->EventCallback=this;
	GUIObjectRoot->ChildControls.push_back(obj);
	
	obj=new GUIObject(50,150,240,36,GUIObjectLabel,"Theme:");
	obj->Name="theme";
	GUIObjectRoot->ChildControls.push_back(obj);
	
	theme=new GUISingleLineListBox(300,150,240,36);
	theme->Name="lstTheme";
	vector<string> v=EnumAllDirs(get_user_path()+"themes/");
	vector<string> v2=EnumAllDirs(get_data_path()+"themes/");
	v.insert(v.end(), v2.begin(), v2.end());

	int value = -1;
	for(vector<string>::iterator i = v.begin(); i != v.end(); ++i){
		*i=i->substr(0, i->size()-10);
		if(*i==m_theme) {
			value=i - v.begin();
		}
	}
	theme->Item=v;
	if(value == -1)
		value=theme->Item.size() - 1;
	theme->Value=value;
	theme->EventCallback=this;
	GUIObjectRoot->ChildControls.push_back(theme);

	obj=new GUIObject(50,200,240,36,GUIObjectCheckBox,"Level themes",m_leveltheme?1:0);
	obj->Name="chkLeveltheme";
	obj->EventCallback=this;
	GUIObjectRoot->ChildControls.push_back(obj);
	
	obj=new GUIObject(50,250,240,36,GUIObjectCheckBox,"Internet",m_internet?1:0);
	obj->Name="chkInternet";
	obj->EventCallback=this;
	GUIObjectRoot->ChildControls.push_back(obj);
	
	obj=new GUIObject(10,300,284,36,GUIObjectButton,"Cancel");
	obj->Name="cmdExit";
	obj->EventCallback=this;
	GUIObjectRoot->ChildControls.push_back(obj);
		
	obj=new GUIObject(306,300,284,36,GUIObjectButton,"Save");
	obj->Name="cmdSave";
	obj->EventCallback=this;
	GUIObjectRoot->ChildControls.push_back(obj);
	
	restartLabel=new GUIObject(10,250,284,36,GUIObjectLabel,"You need to restart before the changes have effect.");
	restartLabel->Name="restart";
	restartLabel->Visible=false;
	GUIObjectRoot->ChildControls.push_back(restartLabel);

	//======
}

Options::~Options()
{
	if(GUIObjectRoot){
		delete GUIObjectRoot;
		GUIObjectRoot=NULL;
	}
}

void Options::GUIEventCallback_OnEvent(std::string Name,GUIObject* obj,int nEventType){
	if(nEventType==GUIEventClick){
		if(Name=="cmdExit"){
			next_state(STATE_MENU);
		}
		else if(Name=="cmdSave"){
			save_settings();
		}
		else if(Name=="chkSound"){
			m_sound=obj->Value?true:false;
			get_settings()->setValue("sound",m_sound?"1":"0");
			if ( !m_sound )
			{
				Mix_HaltMusic();
			}
			else 
			{
				Mix_PlayMusic(music,-1);
			}
		}
		else if(Name=="chkFullscreen"){
			m_fullscreen=obj->Value?true:false;
			get_settings()->setValue("fullscreen",m_fullscreen?"1":"0");
			
			//Set the restart text visible.
			restartLabel->Visible = true;
		}
		else if(Name=="chkLeveltheme"){
			m_leveltheme=obj->Value?true:false;
			get_settings()->setValue("leveltheme",m_leveltheme?"1":"0");
		}
		else if(Name=="chkInternet"){
			m_internet=obj->Value?true:false;
			get_settings()->setValue("internet",m_internet?"1":"0");
		}
	}
	if(Name=="lstTheme"){
		if(theme!=NULL && theme->Value>=0 && theme->Value<(int)theme->Item.size()){
			get_settings()->setValue("theme",theme->Item[theme->Value]);
		}
	}
}

void Options::handle_events()
{
	if ( event.type == SDL_QUIT )
	{
		next_state(STATE_EXIT);
	}

	if (event.key.keysym.sym == SDLK_ESCAPE )
	{
		next_state(STATE_MENU);
	}
}

void Options::logic()
{

}


void Options::render()
{
	apply_surface( 0, 0, s_options, screen, NULL);
	if(GUIObjectRoot)
		GUIObjectRoot->render();
}

/*
 * Copyright (C) 2011-2012 Me and My Shadow
 *
 * This file is part of Me and My Shadow.
 *
 * Me and My Shadow is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Me and My Shadow is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Me and My Shadow.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GUISPINBOX_H
#define GUISPINBOX_H

#include "GUIObject.h"

class GUISpinBox:public GUIObject{
public:
	GUISpinBox(int left=0,int top=0,int width=0,int height=0,
		bool enabled=true,bool visible=true):
		GUIObject(left,top,width,height,0,NULL,value,enabled,visible),
		number(0.0f),change(1.0f),limitMax(100),limitMin(-100),format("%-.2f"){ };
	
	//Number saved in the widget.
	//NOTE: We can't use variable "value" from GUIObject bacause it's an integer.
	float number;
	//Amount of single change.
	float change;
	//Value stays between these values.
	float limitMax,limitMin;
	
	//Standard C printf format used for displaying the number.
	const char* format;
	
	//Method used to handle mouse and/or key events.
	//x: The x mouse location.
	//y: The y mouse location.
	//enabled: Boolean if the parent is enabled or not.
	//visible: Boolean if the parent is visible or not.
	//processed: Boolean if the event has been processed (by the parent) or not.
	//Returns: Boolean if the event is processed by the child.
	virtual bool handleEvents(int x=0,int y=0,bool enabled=true,bool visible=true,bool processed=false);
	//Method that will render the GUIScrollBar.
	//x: The x location to draw the GUIObject. (x+left)
	//y: The y location to draw the GUIObject. (y+top)
	virtual void render(int x=0,int y=0,bool draw=true);
};

#endif

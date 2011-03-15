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
#ifndef STARTOBJECTS_H
#define STARTOBJECTS_H

#include <SDL/SDL.h>
#include "Globals.h"
#include "GameObjects.h"

class StartObject : public GameObject
{

public:

	StartObject(int x, int y, class Player * player);

	void show();
};

class StartObjectShadow : public GameObject
{

public:

	StartObjectShadow(int x, int y, class Shadow * player);

	void show();
};

class Exit : public GameObject
{

public:
	Exit( int x, int y );

	void test_player( class Player * player );
	void show();
};

#endif
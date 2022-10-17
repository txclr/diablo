#pragma once

#ifndef __DEFINE_H__
#define __DEFINE_H__

#define WINCX 1400
#define WINCY 800

#define OBJ_NOEVENT 0
#define OBJ_DEAD 1

#define SAFE_DELETE(p) if(p){ delete p; p = nullptr; }
#define SAFE_DELETE_ARR(p) if(p){ delete[]p; p = nullptr; }

#define PI 3.141592f

#define TILEX 40
#define TILEY 30
#define TILECX 160
#define TILECY 80

#endif // !__DEFINE_H__

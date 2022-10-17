#include "stdafx.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Monster.h"
#include "Mouse.h"
#include "CollisionMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
	:m_bRect(false), m_pTarget(nullptr)
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Add_Object(OBJID::ID _eID, CObj* _pObj)
{
	m_listObj[_eID].emplace_back(_pObj);
}

void CObjMgr::Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& iter = m_listObj[i].begin(); iter != m_listObj[i].end();)
		{
			int iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
			{
				if((*iter)->Get_MaxLife())
					m_pTarget = nullptr;
				SAFE_DELETE(*iter);
				iter = m_listObj[i].erase(iter);
			}
			else
				++iter;
		}
	}
	CCollisionMgr::Collision_Att(m_listObj[OBJID::BULLET], m_listObj[OBJID::MONSTER]);
	CCollisionMgr::Collision_AttM(m_listObj[OBJID::MBULLET], m_listObj[OBJID::PLAYER]);
	//CCollisionMgr::Collision_A(m_listObj[OBJID::BULLET], m_listObj[OBJID::MONSTER]);
}

void CObjMgr::Late_Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
		{
			pObj->Late_Update();

			if (m_listObj[i].empty())
				break;

			GROUPID::ID eID = pObj->Get_GroupID();
			m_listRenderGroup[eID].emplace_back(pObj);
		}
	}
}

void CObjMgr::Render(HDC _DC)
{
	for (int i = 0; i < GROUPID::END; ++i)
	{
		if (GROUPID::GAMEOBJECT == i)
			m_listRenderGroup[i].sort(SortY<CObj*>);

		for (auto& pObj : m_listRenderGroup[i])
			pObj->Render(_DC);

		m_listRenderGroup[i].clear();
	}
	if (m_pTarget)
	{
		HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MonsterBar");
		BitBlt(_DC, 578, 0, int(245*m_pTarget->Get_Liferate()), 28, hMemDC, 0, 0, SRCCOPY);
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for_each(m_listObj[i].begin(), m_listObj[i].end(), Safe_Delete<CObj*>);
		m_listObj[i].clear();
	}
}

void CObjMgr::ReleaseNP()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		if (OBJID::PLAYER == i)
			continue;
		for_each(m_listObj[i].begin(), m_listObj[i].end(), Safe_Delete<CObj*>);
		m_listObj[i].clear();
	}
}

void CObjMgr::Delete_ID(OBJID::ID _eID)
{
	for (auto& pObj : m_listObj[_eID])
		Safe_Delete(pObj);
	m_listObj[_eID].clear();
}

CObj* CObjMgr::Get_Target(CObj* _Dst, OBJID::ID _eID)
{
	if (m_listObj[_eID].empty())
		return nullptr;

	CObj* pTarget = nullptr;
	float fDis = 0.f;

	for (auto& Src : m_listObj[_eID])
	{
		if(Src->Get_Dead())
			continue;

		float fX = abs(_Dst->Get_Info().fX - Src->Get_Info().fX);
		float fY = abs(_Dst->Get_Info().fY - Src->Get_Info().fY);
		float fDis2 = sqrtf(fX * fX + fY * fY);

		if (fDis2 < fDis || !pTarget)
		{
			pTarget = Src;
			fDis = fDis2;
		}
	}
	return pTarget;
}

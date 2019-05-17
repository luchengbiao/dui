#include "StdAfx.h"
#include "UIHelper.h"

namespace ui
{
	CPoint operator*(const CPoint& pt, float f)
	{
		return CPoint(pt.x * f, pt.y * f);
	}

	CPoint operator*(float f, const CPoint& pt)
	{
		return CPoint(pt.x * f, pt.y * f);
	}

	CPoint operator+(const CPoint& pt0, const CPoint& pt1)
	{
		return CPoint(pt0.x + pt1.x, pt0.y + pt1.y);
	}

	CPoint operator-(const CPoint& pt0, const CPoint& pt1)
	{
		return CPoint(pt0.x - pt1.x, pt0.y - pt1.y);
	}

	CPoint operator-(const CPoint& pt)
	{
		return CPoint(-pt.x, -pt.y);
	}

	int Dot(const CPoint& pt0, const CPoint& pt1)
	{
		return pt0.x * pt1.x + pt0.y * pt1.y;
	}

	CSize operator*(const CSize& sz, float f)
	{
		return CSize(sz.cx * f, sz.cy * f);
	}

	CSize operator*(float f, const CSize& sz)
	{
		return CSize(sz.cx * f, sz.cy * f);
	}

	CSize operator+(const CSize& sz0, const CSize& sz1)
	{
		return CSize(sz0.cx + sz1.cx, sz0.cy + sz1.cy);
	}

	CSize operator-(const CSize& sz0, const CSize& sz1)
	{
		return CSize(sz0.cx - sz1.cx, sz0.cy - sz1.cy);
	}

	CSize operator-(const CSize& sz)
	{
		return CSize(-sz.cx, -sz.cy);
	}

	CPoint LeftTop(Control* ctrl)
	{
		UiRect rect = ctrl->GetPos();

		return CPoint(rect.left, rect.top);
	}

	CPoint LeftCenter(Control* ctrl)
	{
		UiRect rect = ctrl->GetPos();

		return CPoint(rect.left, rect.top + ((rect.bottom - rect.top) >> 1));
	}

	CPoint LeftBottom(Control* ctrl)
	{
		UiRect rect = ctrl->GetPos();

		return CPoint(rect.left, rect.bottom);
	}

	CPoint TopCenter(Control* ctrl)
	{
		UiRect rect = ctrl->GetPos();

		return CPoint(rect.left + ((rect.right - rect.left) >> 1), rect.top);
	}

	CPoint Center(Control* ctrl)
	{
		UiRect rect = ctrl->GetPos();

		return CPoint(rect.left + ((rect.right - rect.left) >> 1), rect.top + ((rect.bottom - rect.top) >> 1));
	}

	CPoint BottomCenter(Control* ctrl)
	{
		UiRect rect = ctrl->GetPos();

		return CPoint(rect.left + ((rect.right - rect.left) >> 1), rect.bottom);
	}

	CPoint RightTop(Control* ctrl)
	{
		UiRect rect = ctrl->GetPos();

		return CPoint(rect.right, rect.top);
	}

	CPoint RightCenter(Control* ctrl)
	{
		UiRect rect = ctrl->GetPos();

		return CPoint(rect.right, rect.top + ((rect.bottom - rect.top) >> 1));
	}

	CPoint RightBottom(Control* ctrl)
	{
		UiRect rect = ctrl->GetPos();

		return CPoint(rect.right, rect.bottom);
	}

	inline static void MoveByDelta(Control* ctrl, UiRect& raw_rect, const CPoint& delta)
	{
		raw_rect.Offset(delta);

		ctrl->SetPos(raw_rect);
	}

	void MoveByDelta(Control* ctrl, const CPoint& delta)
	{
		UiRect rect = ctrl->GetPos();

		MoveByDelta(ctrl, rect, delta);
	}

	void MoveLeftTopTo(Control* ctrl, const CPoint& pt)
	{
		UiRect rect = ctrl->GetPos();

		MoveByDelta(ctrl, rect, CPoint(pt.x - rect.left, pt.y - rect.top));
	}

	void MoveLeftCenterTo(Control* ctrl, const CPoint& pt)
	{
		UiRect rect = ctrl->GetPos();

		MoveByDelta(ctrl, rect, CPoint(pt.x - rect.left, pt.y - rect.top - ((rect.bottom - rect.top) >> 1)));
	}

	void MoveLeftBottomTo(Control* ctrl, const CPoint& pt)
	{
		UiRect rect = ctrl->GetPos();

		MoveByDelta(ctrl, rect, CPoint(pt.x - rect.left, pt.y - rect.bottom));
	}

	void MoveTopCenterTo(Control* ctrl, const CPoint& pt)
	{
		UiRect rect = ctrl->GetPos();

		MoveByDelta(ctrl, rect, CPoint(pt.x - rect.left - ((rect.right - rect.left) >> 1), pt.y - rect.top));
	}

	void MoveCenterTo(Control* ctrl, const CPoint& pt)
	{
		UiRect rect = ctrl->GetPos();

		MoveByDelta(ctrl, rect, CPoint(pt.x - rect.left - ((rect.right - rect.left) >> 1), pt.y - rect.top - ((rect.bottom - rect.top) >> 1)));
	}

	void MoveBottomCenterTo(Control* ctrl, const CPoint& pt)
	{
		UiRect rect = ctrl->GetPos();

		MoveByDelta(ctrl, rect, CPoint(pt.x - rect.left - ((rect.right - rect.left) >> 1), pt.y - rect.bottom));
	}

	void MoveRightTopTo(Control* ctrl, const CPoint& pt)
	{
		UiRect rect = ctrl->GetPos();

		MoveByDelta(ctrl, rect, CPoint(pt.x - rect.right, pt.y - rect.top));
	}

	void MoveRightCenterTo(Control* ctrl, const CPoint& pt)
	{
		UiRect rect = ctrl->GetPos();

		MoveByDelta(ctrl, rect, CPoint(pt.x - rect.right, pt.y - rect.top - ((rect.bottom - rect.top) >> 1)));
	}

	void MoveRightBottomTo(Control* ctrl, const CPoint& pt)
	{
		UiRect rect = ctrl->GetPos();

		MoveByDelta(ctrl, rect, CPoint(pt.x - rect.right, pt.y - rect.bottom));
	}

	CSize SizeOf(Control* ctrl)
	{
		return CSize(ctrl->GetWidth(), ctrl->GetHeight());
	}
}
#ifndef UI_UTILS_UIHELPER_H_
#define UI_UTILS_UIHELPER_H_
#pragma once

namespace ui
{
	CPoint operator*(const CPoint&, float f);
	CPoint operator*(float f, const CPoint&);
	CPoint operator+(const CPoint& pt0, const CPoint& pt1);
	CPoint operator-(const CPoint& pt0, const CPoint& pt1);
	CPoint operator-(const CPoint&);
	int Dot(const CPoint& pt0, const CPoint& pt1);

	CSize operator*(const CSize&, float f);
	CSize operator*(float f, const CSize&);
	CSize operator+(const CSize& sz0, const CSize& sz1);
	CSize operator-(const CSize& sz0, const CSize& sz1);
	CSize operator-(const CSize&);

	CPoint LeftTop(Control*);
	CPoint LeftCenter(Control*);
	CPoint LeftBottom(Control*);

	CPoint TopCenter(Control*);
	CPoint Center(Control*);
	CPoint BottomCenter(Control*);

	CPoint RightTop(Control*);
	CPoint RightCenter(Control*);
	CPoint RightBottom(Control*);

	void MoveByDelta(Control*, const CPoint&);

	void MoveLeftTopTo(Control*, const CPoint&);
	void MoveLeftCenterTo(Control*, const CPoint&);
	void MoveLeftBottomTo(Control*, const CPoint&);

	void MoveTopCenterTo(Control*, const CPoint&);
	void MoveCenterTo(Control*, const CPoint&);
	void MoveBottomCenterTo(Control*, const CPoint&);

	void MoveRightTopTo(Control*, const CPoint&);
	void MoveRightCenterTo(Control*, const CPoint&);
	void MoveRightBottomTo(Control*, const CPoint&);

	CSize SizeOf(Control*);
}

#endif
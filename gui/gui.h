
#ifndef __GUI_H_INCLUDED__
#define __GUI_H_INCLUDED__

#include <stdint.h>
//
// это уже по качеству ближе к "продуктовому" коду.. после полировки
// к сожалению, более показательный класс выложить не получится - всё-таки это плод коллективного творчества в итоге.. если нужно, постараюсь что-нибудь урезанное собрать
class Point{
private:
    int16_t x;
	int16_t y;
protected:
public: // CONSTRUCTORS
    Point(){};
    Point(const int16_t& x_, const int16_t& y_) {
		x = x_;
		y = y_;
	};
    Point(const Point &point) {
		x = point.x;
		y = point.y;
	};

public: // ACCESSORS
    __inline void Reset() {
		x = 0;
		y = 0;
	};
	
    __inline void Set(const int16_t& x_, const int16_t& y_) {
		x = x_;
		y = y_;
	};
	
	__inline int16_t X() {return x;}
	__inline int16_t Y() {return y;}

public: // OPERATORS	
    __inline Point& operator =(const Point& point) {
		x = point.x;
		y = point.y; 
		return *this;
	};

    __inline Point operator +(const Point& right) const {
		return CPoint(x + right.x, y + right.y); 
	};
    __inline Point operator -(const Point& right) const {
		return CPoint(x - right.x, y - right.y); 
	};
    __inline Point& operator +=(const Point& right) {
		x += right.x; 
		y += right.y; 
		return *this;
	};
    __inline Point& operator -=(const Point& right) {
		x -= right.x;
		y -= right.y; 
		return *this;
	};

    __inline Point operator +(int16_t right) const { 
		return Point(x + right, y + right); 
	};
    __inline Point operator -(int16_t right) const {
		return Point(x - right, y - right);
	};
    __inline Point& operator +=(int16_t right) {
		x += right;
		y += right; 
		return *this; 
	};
    __inline Point& operator -=(int16_t right) {
		x -= right;
		y -= right;
		return *this;
	};

    __inline bool operator !=(const Point& right) const {
		return (x - right.x) | (y - right.y); 
	};
    __inline bool operator ==(const Point& right) const {
		return ((x - right.x) | (y - right.y)) == 0;
	};

};



#endif // End of __GUI_H_INCLUDED__



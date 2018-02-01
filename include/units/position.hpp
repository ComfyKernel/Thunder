#ifndef H_UNITS_POSITION_SINGLE_HPP
#define H_UNITS_POSITION_SINGLE_HPP

// # # # // UNIT2D // # # # //

template<typename T>
class unit2d {
public:
  T x,y;

  unit2d() { }
  unit2d(const T& X,const T& Y) : x(X), y(Y) { }
  unit2d(const unit2d& p)       : x(p.x), y(p.y) { }

  const unit2d& operator+(const unit2d& p) const { return unit2d<T>(x+p.x,y+p.y); }
  const unit2d& operator-(const unit2d& p) const { return unit2d<T>(x-p.x,y-p.y); }
  const unit2d& operator*(const unit2d& p) const { return unit2d<T>(x*p.x,y*p.y); }
  const unit2d& operator/(const unit2d& p) const { return unit2d<T>(x/p.x,y/p.y); }

  const unit2d& operator*(const T& v) const { return unit2d<T>(x*v,y*v); }
  const unit2d& operator/(const T& v) const { return unit2d<T>(x/v,y/v); }

  unit2d& operator=(const unit2d& p) { x=p.x;y=p.y; return *this; }
  
  unit2d& operator+=(const unit2d& p) { return (*this)=unit2d(x+p.x,y+p.y); }
  unit2d& operator-=(const unit2d& p) { return (*this)=unit2d(x-p.x,y-p.y); }
  unit2d& operator*=(const unit2d& p) { return (*this)=unit2d(x*p.x,y*p.y); }
  unit2d& operator/=(const unit2d& p) { return (*this)=unit2d(x/p.x,y/p.y); }

  unit2d& operator*=(const T& v) { return (*this)=unit2d(x*v,y*v); }
  unit2d& operator/=(const T& v) { return (*this)=unit2d(x/v,y/v); } };

template<typename T> bool operator==(const unit2d<T>& a,const unit2d<T>& b) {
  return (a.x==b.x)&&(a.y==b.y);
}

template<typename T> bool operator!=(const unit2d<T>& a,const unit2d<T>& b) {
  return !(a==b);
}

// # # # // UNIT3D // # # # //

template<typename T>
class unit3d {
public:
  T x,y,z;

  unit2d<T> xy() { return unit2d(x,y); }
  unit2d<T> yz() { return unit2d(y,z); }

  unit3d() { }  
  unit3d(const T& X,const T& Y,const T& Z)
    : x(X  ), y(Y  ), z(Z  ) { }
  
  unit3d(const T& X,const unit2d<T>& E)
    : x(X  ), y(E.x), z(E.y) { }
  
  unit3d(const unit2d<T>& B,const T& Z)
    : x(B.x), y(B.y), z(Z  ) { }
  
  unit3d(const unit3d& p)
    : x(p.x), y(p.y), z(p.z) { }

  const unit3d& operator+(const unit3d& p) const { return unit3d<T>(x+p.x,y+p.y,z+p.z); }
  const unit3d& operator-(const unit3d& p) const { return unit3d<T>(x-p.x,y-p.y,z-p.z); }
  const unit3d& operator*(const unit3d& p) const { return unit3d<T>(x*p.x,y*p.y,z*p.z); }
  const unit3d& operator/(const unit3d& p) const { return unit3d<T>(x/p.x,y/p.y,z/p.z); }

  const unit3d& operator*(const T& v) const { return unit3d<T>(x*v,y*v,z*v); }
  const unit3d& operator/(const T& v) const { return unit3d<T>(x/v,y/v,z/v); }

  unit3d& operator=(const unit3d& p) { x=p.x;y=p.y;z=p.z; return *this; }
  
  unit3d& operator+=(const unit3d& p) { return (*this)=unit3d(x+p.x,y+p.y,z+p.z); }
  unit3d& operator-=(const unit3d& p) { return (*this)=unit3d(x-p.x,y-p.y,z-p.z); }
  unit3d& operator*=(const unit3d& p) { return (*this)=unit3d(x*p.x,y*p.y,z*p.z); }
  unit3d& operator/=(const unit3d& p) { return (*this)=unit3d(x/p.x,y/p.y,z/p.z); }

  unit3d& operator*=(const T& v) { return (*this)=unit3d(x*v,y*v,z*v); }
  unit3d& operator/=(const T& v) { return (*this)=unit3d(x/v,y/v,z/v); } };

template<typename T> bool operator==(const unit3d<T>& a,const unit3d<T>& b) {
  return (a.x==b.x)&&(a.y==b.y)&&(a.z==b.z);
}

template<typename T> bool operator!=(const unit3d<T>& a,const unit3d<T>& b) {
  return !(a==b);
}

#endif

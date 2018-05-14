#pragma once
#include <cmath>
#include <sstream>
#include <iostream>
#include <limits>

namespace Gambit {
  namespace ColliderBit {


    /// @brief Add two numbers in quadrature
    /// @todo Use HEPUtils add_quad
    inline double addInQuad(const double& a, const double& b) { return sqrt(a*a + b*b); }


    /// @brief A simple container for a point on an xy plane.
    ///
    /// This class is largely based upon the structure of the P4 class which is
    /// part of HEPUtils -- https://bitbucket.org/andybuckley/heputils
    /// Copyright (C) 2013-2015 Andy Buckley <andy.buckley@cern.ch>
    ///
    /// Modified to a simple point on a 2d-plane by Abram Krislock <a.m.b.krislock@fys.uio.no>
    class P2 {
      /// @name Storage
      //@{
      private:
        double _x, _y;
      //@}

      /// @name Constructors
      //@{
      public:
        /// Default constructor
        P2() : _x(0.), _y(0.) { }
        /// Coordinate constructor
        P2(double x, double y) : _x(x), _y(y) { }
        /// Copy constructor
        P2(const P2& other) : _x(other.getx()), _y(other.gety()) { }
        /// Copy assignment operator
        P2& operator = (const P2& other) { _x = other.getx(); _y = other.gety(); return *this; }
      //@}

      /// @name Coordinate setters
      //@{
      public:
        P2& setx(double x) { _x = x; return *this; }
        P2& sety(double y) { _y = y; return *this; }
        P2& setxy(double x, double y) { _x = x; _y = y; return *this; }
      //@}

      /// @name Coordinate getters
      //@{
      public:
        double getx() const { return _x; }
        double gety() const { return _y; }
        /// Get the length of the vector from the origin to this point
        double abs() const { return addInQuad(_x, _y); }
        /// Alias for abs
        double r() const { return addInQuad(_x, _y); }
      //@}

      /// @name Self-modifying operators
      //@{
      public:
        P2& operator += (const P2& other) { _x += other.getx(); _y += other.gety(); return *this; }
        P2& operator -= (const P2& other) { _x -= other.getx(); _y -= other.gety(); return *this; }
        P2& operator *= (double a) { _x *= a; _y *= a; return *this; }
        P2& operator /= (double a) { _x /= a; _y /= a; return *this; }
      //@}
    };

    /// @name External operators and string representation for P2
    //@{
      inline P2 operator + (const P2& a, const P2& b) { P2 rtn = a; return rtn += b; }
      inline P2 operator - (const P2& a, const P2& b) { P2 rtn = a; return rtn -= b; }
      inline P2 operator * (const P2& a, double f) { P2 rtn = a; return rtn *= f; }
      inline P2 operator * (double f, const P2& a) { P2 rtn = a; return rtn *= f; }
      inline P2 operator / (const P2& a, double f) { P2 rtn = a; return rtn /= f; }

      /// Make a string representation of the vector
      inline std::string to_str(const P2& p2) {
        std::stringstream ss;
        ss << "(" << p2.getx() << ", " << p2.gety() << ")";
        return ss.str();
      }
      /// Write a string representation of the vector to the provided stream
      inline std::ostream& operator <<(std::ostream& ostr, const P2& p2) {
        ostr << to_str(p2);
        return ostr;
      }
    //@}


    /// @brief A simple container for a line segment on an xy plane.
    ///
    /// This class depends on the P2 class above. It has a built in algorithm
    /// to detect intersection with another LineSegment.
    class LineSegment {
      /// @name Storage
      //@{
      private:
        P2 _p1, _p2, _diff;
      //@}

      /// @name Constructors
      //@{
      public:
        /// Coordinate initializer / recycler
        void init(double x1, double y1, double x2, double y2, double extendFrac=-1.) {
          P2 rawpt1, rawpt2, extendEnds;
          if (x1 > x2 or (x1 == x2 and y1 > y2)) {
            rawpt2.setxy(x1, y1);
            rawpt1.setxy(x2, y2);
          } else {
            rawpt1.setxy(x1, y1);
            rawpt2.setxy(x2, y2);
          }
          if(extendFrac > 0.) {
            extendEnds = (rawpt2 - rawpt1) * extendFrac;
            _p2 = rawpt2 + extendEnds;
            _p1 = rawpt1 - extendEnds;
          } else {
            _p2 = rawpt2;
            _p1 = rawpt1;
          }
          _diff = _p2 - _p1;
        }

        /// Point initializer / recycler
        void init(const P2& p1, const P2& p2, double extendFrac=-1.) {
          init(p1.getx(), p1.gety(), p2.getx(), p2.gety(), extendFrac);
        }

        /// Default constructor
        LineSegment() {
          init(0., 0., 0., 0.);
        }

        /// Coordinate constructor
        LineSegment(double x1, double y1, double x2, double y2, double extendFrac=-1.) {
          init(x1, y1, x2, y2, extendFrac);
        }

        /// Point constructor
        LineSegment(const P2& p1, const P2& p2, double extendFrac=0.) {
          init(p1, p2, extendFrac);
        }

        /// Copy constructor
        LineSegment(const LineSegment& other) {
          _p1 = other.getp1();
          _p2 = other.getp2();
          _diff = _p2 - _p1;
        }

        /// Copy assignment operator
        LineSegment& operator = (const LineSegment& other) {
          _p1 = other.getp1();
          _p2 = other.getp2();
          _diff = _p2 - _p1;
          return *this;
        }
      //@}

      /// @name Coordinate getters
      //@{
      public:
        const P2 getp1() const { return _p1; }
        const P2 getp2() const { return _p2; }

        /// Get the slope of the line segment
        double slope() const {
          if (_p1.getx() == _p2.getx())
            return std::numeric_limits<double>::infinity();
          else
            return _diff.gety() / _diff.getx();
        }
        /// Alias for slope
        double m() const { return slope(); }

        /// Get the y-intercept of the full line which contains this segment
        double intercept() const {
          if (_p1.getx() == _p2.getx())
            return std::numeric_limits<double>::infinity();
          else
            return _p1.gety() - m() * _p1.getx();
        }
        /// Alias for intercept
        double b() const { return intercept(); }

        /// Get the length of the vector from the origin to this point
        double abs() const { return _diff.abs(); }
        /// Alias for abs
        double r() const { return abs(); }
      //@}

      /// @name Intersection algorithm
      //@{
      public:
        /// Determine if this intersects with other and where
        P2 intersectsAt(const LineSegment& other) const {
          P2 result(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
          double xintersect, yintersect;

          // If the slopes are equal, they will never intersect
          if (slope() == other.slope())
            return result;

          // If self or other has an infinite slope, change the intersect calculation
          if (slope() == std::numeric_limits<double>::infinity()) {
            xintersect = _p1.getx();
            yintersect = other.m() * xintersect + other.b();
            if (xintersect >= other.getp1().getx() and xintersect <= other.getp2().getx()
                and yintersect >= _p1.gety() and yintersect <= _p2.gety())
              result.setxy(xintersect, yintersect);
          } else if (other.slope() == std::numeric_limits<double>::infinity()) {
            xintersect = other.getp1().getx();
            yintersect = m() * xintersect + b();
            if (xintersect >= _p1.getx() and xintersect <= _p2.getx()
                and yintersect >= other.getp1().gety() and yintersect <= other.getp2().gety())
              result.setxy(xintersect, yintersect);
          } else {   // Regular intercept calculation
            xintersect = (other.b() - b()) / (m() - other.m());
            yintersect = m() * xintersect + b();
            if (xintersect >= _p1.getx() and xintersect <= _p2.getx()
                and xintersect >= other.getp1().getx() and xintersect <= other.getp2().getx())
              result.setxy(xintersect, yintersect);
          }
          return result;
        }
      //@}
    };

    /// @name String representation for LineSegment
    //@{
      /// Make a string representation of the LineSegment
      inline std::string to_str(const LineSegment& lineseg) {
        std::stringstream ss;
        ss << to_str(lineseg.getp1()) << " -> " << to_str(lineseg.getp2());
        return ss.str();
      }
      /// Write a string representation of the vector to the provided stream
      inline std::ostream& operator <<(std::ostream& ostr, const LineSegment& lineseg) {
        ostr << to_str(lineseg);
        return ostr;
      }
    //@}

  }
}

#include <stdio.h>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

#define PI ((double) 3.141592653589793)
#define EPS ((double) 1e-6)
#define RAD_PER_DEG ((double) 180.0 / PI)
#define DEG_PER_RAD (PI / (double) 180.0)

class geometry_object {
public:
  virtual string to_string()  = 0;
  virtual void print(string name = "")  {
    printf("%s%s\n", name.c_str(), this->to_string().c_str());
  }
};

class geo_vector;

class point : public geometry_object {
public:
  double x, y;

  point(double x = 0, double y = 0) : x(x), y(y) {}
  
  string to_string()  {
    ostringstream out;
    out << "(" << x << ", " << y << ")";
    return out.str();
  }

  point transform(geo_vector v);
};

class geo_vector : public geometry_object {
public:
  double x, y;
  
  geo_vector(double x = 0, double y = 0) : x(x), y(y) {}

  geo_vector(point a, point b) {
    this->x = b.x - a.x;
    this->y = b.y - a.y;
  }

  string to_string()  {
    ostringstream out;
    out << "(" << x << ", " << y << ")";
    return out.str();
  }

  geo_vector scale(double ratio)  {
    return geo_vector(this->x * ratio, this->y * ratio);
  }

  double get_angle_with(geo_vector that) {
    double p = this->dot_product(that);
    double d = this->get_length() * that.get_length();
    return acos(p / d) * RAD_PER_DEG;
  }

  geo_vector rotate(double theta)  {
    double rad = theta * DEG_PER_RAD;
    return geo_vector(x * cos(rad) - y * sin(rad),
		      x * sin(rad) + y * cos(rad));
  }

  double get_length()  {
    return hypot(x, y);
  }

  point to_point()  {
    return point(this->x, this->y);
  }

  double dot_product(geo_vector that) {
    return this->x * that.x + this->y * that.y;
  }
};

class circle : public geometry_object {
public:
  point center;
  double R;

  circle() {}
  circle(point center, double R) : center(center), R(R) {}

  string to_string()  {
    char str[256];
    sprintf(str, "(x - %.9f)^2 + (y - %.9f)^2 = %.9f^2", center.x, center.y, R);
    return string(str);
  }

  vector<point> get_intersection_point_with(circle that) {
    vector<point> ans;

    geo_vector v(this->center, that.center);

    double d = v.get_length();
    double r0 = this->R;
    double r1 = that.R;

    if (r0 + r1 < d){
      return ans;
    }

    double a = (r0 * r0 - r1 * r1 + d * d) / (2 * d);
    double h = sqrt(r0 * r0 - a * a);

    geo_vector v1 = v.scale(r0 / d);

    double alpha_in_deg = acos(a / r0) * RAD_PER_DEG;

    geo_vector vt1 = v1.rotate(alpha_in_deg);
    geo_vector vt2 = v1.rotate(-alpha_in_deg);

    ans.push_back(this->center.transform(vt1));
    if (alpha_in_deg > 0) {
      ans.push_back(this->center.transform(vt2));
    }
    
    return ans;
  }

  double get_segment_area(double angle_in_deg) {
    return angle_in_deg * PI * R * R / 360.0;
  }
};

class triangle : public geometry_object {
public:
  double a, b, c;

  triangle(double a = 0, double b = 0, double c = 0) : a(a), b(b), c(c) {}
  
  triangle(point a, point b, point c) {
    this->a = geo_vector(a, b).get_length();
    this->b = geo_vector(b, c).get_length();
    this->c = geo_vector(c, a).get_length();
  }

  double get_area() {
    double s = (a + b + c) * 0.5;
    return sqrt(s * (s - a) * (s - b) * (s - c));
  }

  string to_string()  {
    char str[256];
    sprintf(str, "(%f, %f, %f)", a, b, c);
    return string(str);
  }
};

int T;
circle circles[3];

// return angle in degree
double calc_angle_between_points(point a, point b, point c) {
  geo_vector ab(a,b);
  geo_vector bc(c,b);
  return ab.get_angle_with(bc);
}

point point::transform(geo_vector v) {
  return point(this->x + v.x, this->y + v.y);
}

void solve() {
  int case_no = 0;
  cin >> T;
  while (T--) {
    point &I0 = circles[0].center;
    point &I1 = circles[1].center;
    point &I2 = circles[2].center;

    cin >> circles[0].R >> circles[1].R >> circles[2].R;
    I0 = point(0, 0);
    I1 = point(circles[0].R + circles[1].R, 0);

    circle C1(I0, circles[0].R + circles[2].R);
    circle C2(I1, circles[1].R + circles[2].R);

    vector<point> intersections = C1.get_intersection_point_with(C2);

    I2 = intersections[0];
    
    double St = triangle(I0, I1, I2).get_area();
    
    double Ss =
      circles[0].get_segment_area(calc_angle_between_points(I1, I0, I2)) + 
      circles[1].get_segment_area(calc_angle_between_points(I0, I1, I2)) +
      circles[2].get_segment_area(calc_angle_between_points(I1, I2, I0));

    case_no++;

    printf("Case %d: %.6f\n", case_no, St - Ss);
  }
}

int main() {
  solve();
  return 0;
}

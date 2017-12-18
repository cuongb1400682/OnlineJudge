#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>
using namespace std;

#define DEG_to_RAD(deg) ((M_PI / 180.0) * deg)
#define EPS (1e-6)

typedef struct geometry_object_t {
  virtual void print(string name="") = 0;
} geometry_object_t;

typedef struct vector_t vector_t;

typedef struct point_t : public geometry_object_t {
  double x, y;  
  point_t(double _x=0, double _y=0):x(_x),y(_y) {}

  double get_distance_to(point_t that) {
    return hypot(this->x - that.x, this->y - that.y);
  }

  point_t translate(vector_t v);

  void print(string name="") {
    printf("pt %s(%f, %f)\n",name.c_str(), x, y);
  }

} point_t;

typedef struct vector_t : public geometry_object_t {
  double x, y;

  vector_t(point_t p) {
    this->x = p.x;
    this->y = p.y;
  }

  vector_t(double _x=0, double _y=0):x(_x),y(_y) {}

  point_t to_point() {
    return point_t(this->x, this->y);
  }

  vector_t rotate(double theta) {
    double rad = DEG_to_RAD(theta);
    return vector_t(x * cos(rad) - y * sin(rad),
		   x * sin(rad) + y * cos(rad));
  }

  double get_magnitude() {
    return hypot(x, y);
  }

  double get_dot_product(vector_t that) {
    return x * that.x + y * that.y;
  }

  point_t get_orthogonal() {
    return point_t(-this->y, this->x);
  }

  void print(string name="") {
    printf("vc %s(%f, %f)\n",name.c_str(), x, y);
  }
} vector_t;

point_t point_t::translate(vector_t v) {
  return point_t(this->x + v.x,
		 this->y + v.y);
}

typedef struct line_t: public geometry_object_t {
  // ax + by = c
  double a, b, c;

  line_t(double _a=0, double _b=0, double _c=0) : a(_a), b(_b), c(_c) {
    generalize();
  }

  line_t(point_t A, point_t B) {
    if (fabs(A.x - B.x) < EPS) {
      a = 1.0;
      b = 0;
      c = -A.x;
    } else {
      a = -(A.y - B.y)/(A.x - B.x);
      b = 1.0;
      c = -(a * A.x) - A.y;
    }
  }

  line_t(vector_t direction, point_t point) {
    a = direction.y;
    b = -direction.x;
    c = -direction.y * point.x + direction.x * point.y;
    generalize();
  }

  void generalize() {
    if (fabs(b) < EPS) {
      c /= a;
      a = 1;
      b = 0;
    } else {
      a /= b;
      c /= b;
      b /= b;
    }
  }

  bool is_parallel_to(line_t that) {
    return (fabs(this->a - that.a) < EPS) &&
      (fabs(this->b - that.b) < EPS);
  }

  bool is_the_same_to(line_t that) {
    return this->is_parallel_to(that) && (fabs(this->c - that.c) < EPS);
  }

  void print(string name="") {
    printf("ln %s (%f)x + (%f)y + (%f) = 0\n", name.c_str(), a, b, c);
  }
} line_t;

bool are_intersect(line_t d1, line_t d2, point_t &p) {
  if (!d1.is_parallel_to(d2) && !d1.is_the_same_to(d2)) {
    double a1 = d1.a, b1 = d1.b, c1 = d1.c;
    double a2 = d2.a, b2 = d2.b, c2 = d2.c;
    p.y = (c1 * a2 - a1 * c2) / (a1 * b2 - b1 * a2);
    p.x = (c1 + b1 * p.y) / a1;
    return true;
  } else {
    return false;
  }
}

double solve(point_t A, point_t B, point_t C) {
  double a = A.get_distance_to(B);
  double b = B.get_distance_to(C);
  double c = B.get_distance_to(A);

  double s = (a + b + c) * 0.5;
  double r = sqrt(s - a) * sqrt(s - b) * sqrt(s - c) / sqrt(s);

  return r;
}

int main() {
  int T, case_no = 1;
  double R, n;

  cin >> T;
  while (T--) {    
    cin >> R >> n;

    if (n == 2) {
      printf("Case %d: %.9lf\n", case_no++, R/2);
      continue;
    }
    
    double alpha = 360.0 / n;
    vector_t v_a(0, 1);
    vector_t v_b = v_a.rotate(alpha);
    vector_t v_c = vector_t(0, R).rotate(alpha / 2.0);
    point_t I = v_c.to_point();
    v_c = v_c.get_orthogonal();

    line_t d_a(v_a, point_t(0, 0));
    line_t d_b(v_b, point_t(0, 0));
    line_t d_c(v_c, I);

    point_t A;
    point_t B;

    are_intersect(d_a, d_c, A);
    are_intersect(d_b, d_c, B);

    printf("Case %d: %.9lf\n", case_no++, solve(point_t(0, 0), A, B));
  }
  return 0;
}

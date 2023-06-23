//
// Created by JustL on 23.06.2023.
//
#include <ctime>
#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>

namespace curve {

typedef std::shared_ptr<std::vector<double>> vec_ptr;

class Curve {
 public:
  [[nodiscard]] virtual vec_ptr point(double t) const;

  [[nodiscard]] virtual vec_ptr derivative(double t) const;
};

class Circle : public Curve {
 public:
  [[nodiscard]] vec_ptr point(double t) const override;

  [[nodiscard]] vec_ptr derivative(double t) const override;

  explicit Circle(double radius);
  [[nodiscard]] double get_radius() const;
 private:
  double radius;
};

class Ellipse : public Curve {
 public:
  [[nodiscard]] vec_ptr point(double t) const override;

  [[nodiscard]] vec_ptr derivative(double t) const override;

  Ellipse(double a, double b);
 private:
  double a;
  double b;
};

class Helix : public Curve {
 public:
  [[nodiscard]] vec_ptr point(double t) const override;

  [[nodiscard]] vec_ptr derivative(double t) const override;

  Helix(double radius, double step);
 private:
  double radius;
  double step;
};

std::shared_ptr<std::vector<std::shared_ptr<curve::Curve>>> random_curves();

bool compareCircles(std::shared_ptr<Circle> const& c1, std::shared_ptr<Circle> const& c2);

}


//
// Created by JustL on 22.06.2023.
//
#include <ctime>
#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include <memory>

namespace curve {

typedef std::shared_ptr<std::vector<double>> vec_ptr;

class Curve {
 public:
  [[nodiscard]] virtual vec_ptr  point(double t) const = 0;
  [[nodiscard]] virtual vec_ptr derivative(double t) const = 0;
};

class Circle : public Curve {
 public:
  [[nodiscard]] vec_ptr point(double t) const override {
    vec_ptr result(new std::vector<double>{ radius * cos(t), radius * sin(t), 0 });
    return result;
  }

  [[nodiscard]] vec_ptr derivative(double t) const override {
    vec_ptr result(new std::vector<double>{ -1 * radius * sin(t), radius * cos(t), 0 });
    return result;
  }

  explicit Circle(double radius) {
    if (radius <= 0)
      throw std::invalid_argument("Radius must be positive.");
    this->radius = radius;
  }

  [[nodiscard]] double get_radius() const {
    return radius;
  }
 private:
  double radius;
};

class Ellipse : public Curve {
 public:
  [[nodiscard]] vec_ptr point(double t) const override {
    vec_ptr result(new std::vector<double>{ a * cos(t), b * sin(t), 0 });
    return result;
  }
  [[nodiscard]] vec_ptr derivative(double t) const override {
    vec_ptr result(new std::vector<double>{ -1 * a * sin(t), b * cos(t), 0 });
    return result;
  }
  Ellipse(double a, double b) {
    if (a <= 0 || b <= 0)
      throw std::invalid_argument("Radii must be positive.");
    this->a = a;
    this->b = b;
  }
 private:
  double a;
  double b;
};

class Helix : public Curve {
 public:
  [[nodiscard]] vec_ptr point(double t) const override {
    vec_ptr result(new std::vector<double>{ radius * cos(t), radius * sin(t), step * t });
    return result;
  }
  [[nodiscard]] vec_ptr derivative(double t) const override {
    vec_ptr result(new std::vector<double>{ -1 * radius * sin(t), radius * cos(t), step });
    return result;
  }
  Helix(double radius, double step) {
    if (radius <= 0)
      throw std::invalid_argument("Radius must be positive.");
    this->radius = radius;
    this->step = step;
  }
 private:
  double radius;
  double step;
};

std::shared_ptr<std::vector<std::shared_ptr<curve::Curve>>> random_curves() {
  std::mt19937 mt(time(nullptr));
  std::random_device rd;  // a seed source for the random number engine
  std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> distrib(1, 3);

  std::shared_ptr<std::vector<std::shared_ptr<curve::Curve>>> curves(new std::vector<std::shared_ptr<curve::Curve>>{});
  unsigned int curve_amount = mt() % 15;

  for (int i = 0; i != curve_amount; ++i) {
    int cur_num = distrib(gen);
    if (cur_num == 1) {
      curves->push_back(std::make_shared<Circle>(1 + mt() % 100));
      std::dynamic_pointer_cast<curve::Circle>((*curves)[i]);
    }
    else if (cur_num == 2) {
      curves->push_back(std::make_shared<Ellipse>(1 + mt() % 100, 1 + mt() % 100));
    }
    else {
      curves->push_back(std::make_shared<Helix>(1 + mt() % 100, 1 + mt() % 100));
    }
  }
  return curves;
}

bool compareCircles(std::shared_ptr<Circle> const& c1, std::shared_ptr<Circle> const& c2) {
  return (c1->get_radius() < c2->get_radius());
}

}
//
// Created by JustL on 23.06.2023.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include "curves.h"

const double PI = 3.141592653589793238462643383279502884;

void task() {
  std::shared_ptr<std::vector<std::shared_ptr<curve::Curve>>> curves = curve::random_curves();
  std::shared_ptr<std::vector<std::shared_ptr<curve::Circle>>> circles(new std::vector<std::shared_ptr<curve::Circle>>{});
  curve::vec_ptr point;
  curve::vec_ptr derivative;
  for (int i = 0; i < curves->size(); ++i) {
    point = (*curves)[i]->point(PI / 4);
    std::cout << "Point of this curve at PI/4 is " << (*point)[0] << " " << (*point)[1] << " " << (*point)[2]
              << std::endl;

    derivative = (*curves)[i]->derivative(PI / 4);
    std::cout << "Derivative of this curve at PI/4 is " << (*derivative)[0] << " " << (*derivative)[1] << " "
              << (*derivative)[2] << std::endl;
    // dynamic_cast<curve::Circle>((*curves)[i])) != nullptr
    if (std::dynamic_pointer_cast<curve::Circle>(((*curves)[i])))
    {
      (*circles).push_back(std::dynamic_pointer_cast<curve::Circle>(((*curves)[i])));
    }
  }

  std::sort((*circles).begin(), (*circles).end(), curve::compareCircles);

  double sum = 0;
  for (auto& i : *circles) {
    sum += i->get_radius();
  }
  std::cout << "Sum of the radii: " << sum;
}


int main() {
  task();
}
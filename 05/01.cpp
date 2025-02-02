#include <iostream>
#include <memory>

class Shape {
protected:
    int8_t sideCount;

public:
    Shape(int8_t constrSideCount) :
        sideCount{constrSideCount} {
    }

    Shape() : Shape(0) {
    }

    ~Shape() {
    }

    Shape(const Shape& otherShape) :
        sideCount{otherShape.sideCount} {
    }

    void printSideCount() {
        std::cout << std::to_string(this->sideCount) << std::endl;
    }
};

class Triangle : public Shape {
public:
    Triangle() : Shape(3) {
    }

    ~Triangle() = default;

    Triangle(const Triangle& otherTriangle) :
        Shape(otherTriangle) {
    }
};

class Quadrilateral : public Shape {
public:
    Quadrilateral() : Shape(4) {
    }

    ~Quadrilateral() = default;

    Quadrilateral(const Quadrilateral& otherQuadrilateral) :
        Shape(otherQuadrilateral) {
    }
};

int main() {
    std::unique_ptr<Shape> arbitraryShapeInstance = std::make_unique<Shape>();
    arbitraryShapeInstance->printSideCount();

    std::unique_ptr<Shape> triangleInstance = std::make_unique<Triangle>();
    triangleInstance->printSideCount();

    std::unique_ptr<Shape> quadrilateralInstance = std::make_unique<Quadrilateral>();
    quadrilateralInstance->printSideCount();

    return 0;
}

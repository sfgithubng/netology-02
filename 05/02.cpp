#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <algorithm>

constexpr int8_t rightCornerDegrees = 90;
constexpr size_t triangleSideConstraint = 3;
constexpr size_t triangleCornerConstraint = 3;
constexpr u_int8_t triangleCornerAngleConstraint = 180;
constexpr size_t quadrilateralSideConstraint = 4;
constexpr size_t quadrilateralCornerConstraint = 4;

class Shape {
protected:
    std::string name;
    std::size_t sideCount;
    std::size_t cornerCount;
    std::map<std::string, int32_t> sides;
    std::map<std::string, int32_t> corners;

public:
    Shape(std::string constrName,
        std::map<std::string, int32_t> constrSides, std::map<std::string, int32_t> constrCorners) :
        name{constrName},
        sideCount{constrSides.size()},
        cornerCount{constrCorners.size()},
        sides{constrSides},
        corners{constrCorners} {
    }

    Shape() : Shape("Generic", {}, {}) {
    }

    ~Shape() {
    }

    Shape(const Shape& otherShape) :
        name{otherShape.name},
        sides{otherShape.sides}, corners{otherShape.corners} {
    }

    void printSideCount() {
        std::cout << std::to_string(this->sideCount) << std::endl;
    }

    void printName() {
        std::cout << this->name << ":" << std::endl;
    }

    void printCornersVerbose() {
        if (this->cornerCount > 0) {
            std::cout << "Corners: ";
            for (const auto& [cornerName, cornerValue] : this->corners) {
                std::cout << cornerName << "=" << std::to_string(cornerValue) << " ";
            }
            std::cout << std::endl;
        }
    }

    void printSidesVerbose() {
        if (this->sideCount > 0) {
            std::cout << "Sides: ";
            for (const auto& [sideName, sideLength] : this->sides) {
                std::cout << sideName << "=" << std::to_string(sideLength) << " ";
            }
            std::cout << std::endl;
        }
    }
};

class Triangle : public Shape {
public:
    Triangle(std::string constrName,
        std::map<std::string, int32_t> constrSides, std::map<std::string, int32_t> constrCorners) :
        Shape(constrName, constrSides, constrCorners) {

        if (this->sideCount != triangleSideConstraint) {
            throw std::invalid_argument("Triangle side count must be " + std::to_string(triangleSideConstraint) + ", terminating");
        }

        if (this->cornerCount != triangleCornerConstraint) {
            throw std::invalid_argument("Triangle corner count must be " + std::to_string(triangleCornerConstraint) + ", terminating");
        }

        u_int8_t cornerAngleSum{0};
        for (const auto& [cornerName, cornerValue] : this->corners) {
            cornerAngleSum += cornerValue;
        }

        if (cornerAngleSum != triangleCornerAngleConstraint) {
            throw std::invalid_argument("Triangle corner angle total must be " + std::to_string(triangleCornerAngleConstraint) + ", terminating");
        }
    }

    ~Triangle() = default;

    Triangle(const Triangle& otherTriangle) :
        Shape(otherTriangle) {
    }
};

class RightTriangle : public Triangle {
public:
    RightTriangle(std::string constrName,
        std::map<std::string, int32_t> constrSides, std::map<std::string, int32_t> constrCorners) :
        Triangle(constrName, constrSides, constrCorners) {

        int8_t rightCornerCount{0};
        for (const auto& [cornerName, cornerValue] : this->corners) {
            if (cornerValue == rightCornerDegrees) {
                ++rightCornerCount;
            }
        }
        if (rightCornerCount != 1) {
            throw std::invalid_argument("90 degree corner count for a right triangle must be 1, terminating");
        }
    }

    ~RightTriangle() = default;

    RightTriangle(const RightTriangle& otherRightTriangle) :
        Triangle(otherRightTriangle) {
    }
};

class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(std::string constrName,
        std::map<std::string, int32_t> constrSides, std::map<std::string, int32_t> constrCorners) :
        Triangle(constrName, constrSides, constrCorners) {

        if (constrSides.at("a") != constrSides.at("c")) {
            throw std::invalid_argument("Sides a and c must be of equal length for an isosceles triangle, terminating");
        }

        if (constrCorners.at("A") != constrCorners.at("C")) {
            throw std::invalid_argument("Corners A and C angles must be the same for an isosceles triangle, terminating");
        }
    }

    ~IsoscelesTriangle() = default;

    IsoscelesTriangle(const IsoscelesTriangle& otherRightTriangle) :
        Triangle(otherRightTriangle) {
    }
};

class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(std::string constrName,
        std::map<std::string, int32_t> constrSides, std::map<std::string, int32_t> constrCorners) :
        Triangle(constrName, constrSides, constrCorners) {

        if ((constrSides.at("a") != constrSides.at("b")) ||
            (constrSides.at("b") != constrSides.at("c")) ||
            (constrSides.at("a") != constrSides.at("c"))) {
            throw std::invalid_argument("Sides a, b and c must be of equal length for an equilateral triangle, terminating");
        }

        if ((constrCorners.at("A") != constrCorners.at("B")) ||
            (constrCorners.at("B") != constrCorners.at("C")) ||
            (constrCorners.at("A") != constrCorners.at("C"))) {
            throw std::invalid_argument("Corner A, B and C angles must be the same for an equilateral triangle, terminating");
        }
    }

    ~EquilateralTriangle() = default;

    EquilateralTriangle(const IsoscelesTriangle& otherRightTriangle) :
        Triangle(otherRightTriangle) {
    }
};


class Quadrilateral : public Shape {
public:
    Quadrilateral(std::string constrName,
        std::map<std::string, int32_t> constrSides, std::map<std::string, int32_t> constrCorners) :
        Shape(constrName, constrSides, constrCorners) {
        if (this->sideCount != quadrilateralSideConstraint) {
            throw std::invalid_argument("Quadrilateral side count must be " + std::to_string(triangleSideConstraint) + " terminating");
        }

        if (this->cornerCount != quadrilateralCornerConstraint) {
            throw std::invalid_argument("Quadrilateral corner count must be " + std::to_string(triangleCornerConstraint) + " terminating");
        }
    }

    ~Quadrilateral() = default;

    Quadrilateral(const Quadrilateral& otherQuadrilateral) :
        Shape(otherQuadrilateral) {
    }
};

class Parallelogram : public Quadrilateral {
public:
    Parallelogram(std::string constrName,
        std::map<std::string, int32_t> constrSides, std::map<std::string, int32_t> constrCorners) :
        Quadrilateral(constrName, constrSides, constrCorners) {

        if ((constrSides.at("a") != constrSides.at("c")) ||
            (constrSides.at("b") != constrSides.at("d"))) {
            throw std::invalid_argument("Sides a, c and b, d must be of equal length for a parallelogram, terminating");
        }

        if (constrCorners.at("A") != constrCorners.at("C") ||
            (constrCorners.at("B") != constrCorners.at("D"))) {
            throw std::invalid_argument("Corner A, C and B, D angles must be the same for a parallelogram, terminating");
        }

    }

    ~Parallelogram() = default;

    Parallelogram(const Parallelogram& otherParallelogram) :
        Quadrilateral(otherParallelogram) {
    }
};

class Rectangle : public Parallelogram {
public:
    Rectangle(std::string constrName,
        std::map<std::string, int32_t> constrSides, std::map<std::string, int32_t> constrCorners) :
        Parallelogram(constrName, constrSides, constrCorners) {

        for (const auto& [cornerName, cornerValue] : this->corners) {
            if (cornerValue != rightCornerDegrees) {
                throw std::invalid_argument("Angle of all corners must be 90 degree for a rectangle, terminating");
            }
        }
    }

    ~Rectangle() = default;

    Rectangle(const Parallelogram& otherParallelogram) :
        Parallelogram(otherParallelogram) {
    }
};

class Rhombus : public Parallelogram {
public:
    Rhombus(std::string constrName,
        std::map<std::string, int32_t> constrSides, std::map<std::string, int32_t> constrCorners) :
        Parallelogram(constrName, constrSides, constrCorners) {

        int32_t sideReferenceLength = constrSides.at("a");

        for (const auto& [sideName, sideValue] : this->sides) {
            if (sideValue != sideReferenceLength) {
                throw std::invalid_argument("All sides of a rhombus must have the same length, terminating");
            }
        }
    }

    ~Rhombus() = default;

    Rhombus(const Parallelogram& otherParallelogram) :
        Parallelogram(otherParallelogram) {
    }
};

class Square : public Rhombus {
public:
    Square(std::string constrName,
        std::map<std::string, int32_t> constrSides, std::map<std::string, int32_t> constrCorners) :
        Rhombus(constrName, constrSides, constrCorners) {

        for (const auto& [cornerName, cornerValue] : this->corners) {
            if (cornerValue != rightCornerDegrees) {
                throw std::invalid_argument("Angle of all corners must be 90 degree for a square, terminating");
            }
        }
    }

    ~Square() = default;

    Square(const Rhombus& otherParallelogram) :
        Rhombus(otherParallelogram) {
    }
};



void print_info (std::unique_ptr<Shape>& shapeToPrint) {
    shapeToPrint->printName();
    shapeToPrint->printSidesVerbose();
    shapeToPrint->printCornersVerbose();
    std::cout << std::endl;
}

int main() {
    std::unique_ptr<Shape> arbitraryShapeInstance = std::make_unique<Shape>();
    print_info(arbitraryShapeInstance);

    std::map<std::string, int32_t> rightTriangleSides = {{"a", 20}, {"b", 20}, {"c", 10}};
    std::map<std::string, int32_t> rightTriangleCorners = {{"A", 90}, {"B", 45}, {"C", 45}};
    std::unique_ptr<Shape> rightTriangleInstance = std::make_unique<RightTriangle>("Right Triangle", rightTriangleSides, rightTriangleCorners);
    print_info(rightTriangleInstance);

    std::map<std::string, int32_t> isoscalesTriangleSides = {{"a", 10}, {"b", 40}, {"c", 10}};
    std::map<std::string, int32_t> isoscalesTriangleCorners = {{"A", 30}, {"B", 120}, {"C", 30}};
    std::unique_ptr<Shape> isoscalesTriangleInstance = std::make_unique<IsoscelesTriangle>("Isosceles Triangle", isoscalesTriangleSides, isoscalesTriangleCorners);
    print_info(isoscalesTriangleInstance);

    std::map<std::string, int32_t> equilateralTriangleSides = {{"a", 10}, {"b", 10}, {"c", 10}};
    std::map<std::string, int32_t> equilateralTriangleCorners = {{"A", 60}, {"B", 60}, {"C", 60}};
    std::unique_ptr<Shape> equilateralTriangleInstance = std::make_unique<EquilateralTriangle>("Equilateral Triangle", equilateralTriangleSides, equilateralTriangleCorners);
    print_info(equilateralTriangleInstance);

    std::map<std::string, int32_t> parallelogramSides = {{"a", 10}, {"b", 20}, {"c", 10}, {"d", 20}};
    std::map<std::string, int32_t> parallelogramCorners = {{"A", 45}, {"B", 135}, {"C", 45}, {"D", 135}};
    std::unique_ptr<Shape> parallelogramInstance = std::make_unique<Parallelogram>("Parallelogram", parallelogramSides, parallelogramCorners);
    print_info(parallelogramInstance);

    std::map<std::string, int32_t> rectangleSides = {{"a", 10}, {"b", 20}, {"c", 10}, {"d", 20}};
    std::map<std::string, int32_t> rectangleCorners = {{"A", 90}, {"B", 90}, {"C", 90}, {"D", 90}};
    std::unique_ptr<Shape> rectangleInstance = std::make_unique<Rectangle>("Rectangle", rectangleSides, rectangleCorners);
    print_info(rectangleInstance);

    std::map<std::string, int32_t> rhombusSides = {{"a", 10}, {"b", 10}, {"c", 10}, {"d", 10}};
    std::map<std::string, int32_t> rhombusCorners = {{"A", 45}, {"B", 135}, {"C", 45}, {"D", 135}};
    std::unique_ptr<Shape> rhombusInstance = std::make_unique<Rhombus>("Rhombus", rhombusSides, rhombusCorners);
    print_info(rhombusInstance);

    std::map<std::string, int32_t> squareSides = {{"a", 10}, {"b", 10}, {"c", 10}, {"d", 10}};
    std::map<std::string, int32_t> squareCorners = {{"A", 90}, {"B", 90}, {"C", 90}, {"D", 90}};
    std::unique_ptr<Shape> squareInstance = std::make_unique<Square>("Square", squareSides, squareCorners);
    print_info(squareInstance);

    return 0;
}
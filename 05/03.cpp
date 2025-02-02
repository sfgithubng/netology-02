#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <algorithm>

constexpr int8_t rightCornerDegrees = 90;
constexpr size_t triangleSideConstraint = 3;
constexpr size_t triangleCornerConstraint = 3;
constexpr u_int8_t triangleCornerAngleConstraint = 180;
constexpr u_int16_t quadrilateralCornerAngleConstraint = 360;
constexpr size_t quadrilateralSideConstraint = 4;
constexpr size_t quadrilateralCornerConstraint = 4;

struct shapeSelfCheckReport {
    bool selfCheckStatus;
    std::string selfCheckMessage;
};

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

    shapeSelfCheckReport getSelfCheckReport() {
        return shapeSelfCheckReport{true, "Correct"};
    }

    virtual void printSelfCheckOutput() {
        shapeSelfCheckReport selfCheckReport = this->getSelfCheckReport();
        if (selfCheckReport.selfCheckStatus) {
            std::cout << "Correct" << std::endl;
            std::cout << "Side count: " + std::to_string(this->sideCount) << std::endl;
        }
    }
};

class Triangle : public Shape {
public:
    Triangle(std::string constrName,
        std::map<std::string, int32_t> constrSides, std::map<std::string, int32_t> constrCorners) :
        Shape(constrName, constrSides, constrCorners) {
    }

    ~Triangle() = default;

    Triangle(const Triangle& otherTriangle) :
        Shape(otherTriangle) {
    }

    shapeSelfCheckReport getSelfCheckReport() {
        if (this->sideCount != triangleSideConstraint) {
            return shapeSelfCheckReport{false, "Triangle side count must be " + std::to_string(triangleSideConstraint)};
        }

        if (this->cornerCount != triangleCornerConstraint) {
            std::cout << "Incorrect. Triangle corner count must be " + std::to_string(triangleCornerConstraint) << std::endl;
            return shapeSelfCheckReport{false, "Triangle corner count must be " + std::to_string(triangleCornerConstraint)};
        }

        u_int8_t cornerAngleSum{0};
        for (const auto& [cornerName, cornerValue] : this->corners) {
            cornerAngleSum += cornerValue;
        }
        if (cornerAngleSum != triangleCornerAngleConstraint) {
            return shapeSelfCheckReport{false, "Triangle corner angle total must be " + std::to_string(triangleCornerAngleConstraint)};
        }
        return shapeSelfCheckReport{true, "Correct"};
    }

    virtual void printSelfCheckOutput() {
        shapeSelfCheckReport selfCheckReport = this->getSelfCheckReport();
        if (!selfCheckReport.selfCheckStatus) {
            std::cout << "Incorrect" << std::endl;
            std::cout << selfCheckReport.selfCheckMessage << std::endl;
        } else {
            Shape::printSelfCheckOutput();
        }
    }
};

class RightTriangle : public Triangle {
public:
    RightTriangle(std::string constrName,
        std::map<std::string, int32_t> constrSides, std::map<std::string, int32_t> constrCorners) :
        Triangle(constrName, constrSides, constrCorners) {
    }

    ~RightTriangle() = default;

    RightTriangle(const RightTriangle& otherRightTriangle) :
        Triangle(otherRightTriangle) {
    }

    shapeSelfCheckReport getSelfCheckReport() {
        int8_t rightCornerCount{0};
        for (const auto& [cornerName, cornerValue] : this->corners) {
            if (cornerValue == rightCornerDegrees) {
                ++rightCornerCount;
            }
        }
        if (rightCornerCount != 1) {
            return shapeSelfCheckReport{false, "90 degree corner count for a right triangle must be 1"};
        }
        return shapeSelfCheckReport{true, "Correct"};
    }

    virtual void printSelfCheckOutput() {
        shapeSelfCheckReport selfCheckReport = this->getSelfCheckReport();
        if (!selfCheckReport.selfCheckStatus) {
            std::cout << "Incorrect" << std::endl;
            std::cout << selfCheckReport.selfCheckMessage << std::endl;
        } else {
            Triangle::printSelfCheckOutput();
        }
    }
};


class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(std::string constrName,
        std::map<std::string, int32_t> constrSides, std::map<std::string, int32_t> constrCorners) :
        Triangle(constrName, constrSides, constrCorners) {
    }

    ~IsoscelesTriangle() = default;

    IsoscelesTriangle(const IsoscelesTriangle& otherRightTriangle) :
        Triangle(otherRightTriangle) {
    }

    shapeSelfCheckReport getSelfCheckReport() {
        if (this->sides.at("a") != this->sides.at("c")) {
            return shapeSelfCheckReport{false, "Sides a and c must be of equal length for an isosceles triangle"};
        }

        if (this->corners.at("A") != this->corners.at("C")) {
             return shapeSelfCheckReport{false, "Corners A and C angles must be the same for an isosceles triangle"};
        }
        return shapeSelfCheckReport{true, "Correct"};
    }

    virtual void printSelfCheckOutput() {
        shapeSelfCheckReport selfCheckReport = this->getSelfCheckReport();
        if (!selfCheckReport.selfCheckStatus) {
            std::cout << "Incorrect" << std::endl;
            std::cout << selfCheckReport.selfCheckMessage << std::endl;
        } else {
            Triangle::printSelfCheckOutput();
        }
    }
};

class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(std::string constrName,
        std::map<std::string, int32_t> constrSides, std::map<std::string, int32_t> constrCorners) :
        Triangle(constrName, constrSides, constrCorners) {
    }

    ~EquilateralTriangle() = default;

    EquilateralTriangle(const IsoscelesTriangle& otherRightTriangle) :
        Triangle(otherRightTriangle) {
    }

    shapeSelfCheckReport getSelfCheckReport() {
        if ((this->sides.at("a") != this->sides.at("b")) ||
            (this->sides.at("b") != this->sides.at("c")) ||
            (this->sides.at("a") != this->sides.at("c"))) {
            return shapeSelfCheckReport{false, "Sides a, b and c must be of equal length for an equilateral triangle"};
            }

        if ((this->corners.at("A") != this->corners.at("B")) ||
            (this->corners.at("B") != this->corners.at("C")) ||
            (this->corners.at("A") != this->corners.at("C"))) {
            return shapeSelfCheckReport{false, "Corner A, B and C angles must be the same for an equilateral triangle"};
            }
        return shapeSelfCheckReport{true, "Correct"};
    }

    virtual void printSelfCheckOutput() {
        shapeSelfCheckReport selfCheckReport = this->getSelfCheckReport();
        if (!selfCheckReport.selfCheckStatus) {
            std::cout << "Incorrect" << std::endl;
            std::cout << selfCheckReport.selfCheckMessage << std::endl;
        } else {
            Triangle::printSelfCheckOutput();
        }
    }

};


class Quadrilateral : public Shape {
public:
    Quadrilateral(std::string constrName,
        std::map<std::string, int32_t> constrSides, std::map<std::string, int32_t> constrCorners) :
        Shape(constrName, constrSides, constrCorners) {
    }

    ~Quadrilateral() = default;

    Quadrilateral(const Quadrilateral& otherQuadrilateral) :
        Shape(otherQuadrilateral) {
    }

    shapeSelfCheckReport getSelfCheckReport() {
        if (this->sideCount != quadrilateralSideConstraint) {
            return shapeSelfCheckReport{false, "Quadrilateral side count must be " + std::to_string(quadrilateralSideConstraint)};
        }

        if (this->cornerCount != quadrilateralCornerConstraint) {
            return shapeSelfCheckReport{false, "Quadrilateral corner count must be " + std::to_string(quadrilateralCornerConstraint)};
        }

        u_int16_t cornerAngleSum{0};
        for (const auto& [cornerName, cornerValue] : this->corners) {
            cornerAngleSum += cornerValue;
        }

        if (cornerAngleSum != quadrilateralCornerAngleConstraint) {
            return shapeSelfCheckReport{false, "Quadrilateral corner angle total must be " + std::to_string(quadrilateralCornerAngleConstraint)};
        }
        return shapeSelfCheckReport{true, "Correct"};
    }

    virtual void printSelfCheckOutput() {
        shapeSelfCheckReport selfCheckReport = this->getSelfCheckReport();
        if (!selfCheckReport.selfCheckStatus) {
            std::cout << "Incorrect" << std::endl;
            std::cout << selfCheckReport.selfCheckMessage << std::endl;
        } else {
            Shape::printSelfCheckOutput();
        }
    }
};

class Parallelogram : public Quadrilateral {
public:
    Parallelogram(std::string constrName,
        std::map<std::string, int32_t> constrSides, std::map<std::string, int32_t> constrCorners) :
        Quadrilateral(constrName, constrSides, constrCorners) {
    }

    ~Parallelogram() = default;

    Parallelogram(const Parallelogram& otherParallelogram) :
        Quadrilateral(otherParallelogram) {
    }

    shapeSelfCheckReport getSelfCheckReport() {
        if ((this->sides.at("a") != this->sides.at("c")) ||
            (this->sides.at("b") != this->sides.at("d"))) {
            return shapeSelfCheckReport{false, "Sides a, c and b, d must be of equal length for a parallelogram"};
        }

        if (this->corners.at("A") != this->corners.at("C") ||
            (this->corners.at("B") != this->corners.at("D"))) {
            return shapeSelfCheckReport{false, "Corner A, C and B, D angles must be the same for a parallelogram"};
        }
        return shapeSelfCheckReport{true, "Correct"};
    }

    virtual void printSelfCheckOutput() {
        shapeSelfCheckReport selfCheckReport = this->getSelfCheckReport();
        if (!selfCheckReport.selfCheckStatus) {
            std::cout << "Incorrect" << std::endl;
            std::cout << selfCheckReport.selfCheckMessage << std::endl;
        } else {
            Quadrilateral::printSelfCheckOutput();
        }
    }
};

class Rectangle : public Parallelogram {
public:
    Rectangle(std::string constrName,
        std::map<std::string, int32_t> constrSides, std::map<std::string, int32_t> constrCorners) :
        Parallelogram(constrName, constrSides, constrCorners) {


    }

    ~Rectangle() = default;

    Rectangle(const Parallelogram& otherParallelogram) :
        Parallelogram(otherParallelogram) {
    }

    shapeSelfCheckReport getSelfCheckReport() {
        for (const auto& [cornerName, cornerValue] : this->corners) {
            if (cornerValue != rightCornerDegrees) {
                return shapeSelfCheckReport{false, "Angle of all corners must be 90 degree for a rectangle"};
            }
        }
        return shapeSelfCheckReport{true, "Correct"};
    }

    virtual void printSelfCheckOutput() {
        shapeSelfCheckReport selfCheckReport = this->getSelfCheckReport();
        if (!selfCheckReport.selfCheckStatus) {
            std::cout << "Incorrect" << std::endl;
            std::cout << selfCheckReport.selfCheckMessage << std::endl;
        } else {
            Parallelogram::printSelfCheckOutput();
        }
    }
};

class Rhombus : public Parallelogram {
public:
    Rhombus(std::string constrName,
        std::map<std::string, int32_t> constrSides, std::map<std::string, int32_t> constrCorners) :
        Parallelogram(constrName, constrSides, constrCorners) {
    }

    ~Rhombus() = default;

    Rhombus(const Parallelogram& otherParallelogram) :
        Parallelogram(otherParallelogram) {
    }

    shapeSelfCheckReport getSelfCheckReport() {
        int32_t sideReferenceLength = this->sides.at("a");

        for (const auto& [sideName, sideValue] : this->sides) {
            if (sideValue != sideReferenceLength) {
                return shapeSelfCheckReport{false, "All sides of a rhombus must have the same length"};
            }
        }
        return shapeSelfCheckReport{true, "Correct"};
    }

    virtual void printSelfCheckOutput() {
        shapeSelfCheckReport selfCheckReport = this->getSelfCheckReport();
        if (!selfCheckReport.selfCheckStatus) {
            std::cout << "Incorrect" << std::endl;
            std::cout << selfCheckReport.selfCheckMessage << std::endl;
        } else {
            Parallelogram::printSelfCheckOutput();
        }
    }
};

class Square : public Rhombus {
public:
    Square(std::string constrName,
        std::map<std::string, int32_t> constrSides, std::map<std::string, int32_t> constrCorners) :
        Rhombus(constrName, constrSides, constrCorners) {
    }

    ~Square() = default;

    Square(const Rhombus& otherParallelogram) :
        Rhombus(otherParallelogram) {
    }

    shapeSelfCheckReport getSelfCheckReport() {
        for (const auto& [cornerName, cornerValue] : this->corners) {
            if (cornerValue != rightCornerDegrees) {
                return shapeSelfCheckReport{false, "Angle of all corners must be 90 degree for a square"};
            }
        }
        return shapeSelfCheckReport{true, "Correct"};
    }

    virtual void printSelfCheckOutput() {
        shapeSelfCheckReport selfCheckReport = this->getSelfCheckReport();
        if (!selfCheckReport.selfCheckStatus) {
            std::cout << "Incorrect" << std::endl;
            std::cout << selfCheckReport.selfCheckMessage << std::endl;
        } else {
            Rhombus::printSelfCheckOutput();
        }
    }
};

void print_info (std::unique_ptr<Shape>& shapeToPrint) {
    shapeToPrint->printSidesVerbose();
    shapeToPrint->printCornersVerbose();
    std::cout << std::endl;
}

int main() {
    std::unique_ptr<Shape> arbitraryShapeInstance = std::make_unique<Shape>();
    arbitraryShapeInstance->printName();
    arbitraryShapeInstance->printSelfCheckOutput();
    print_info(arbitraryShapeInstance);

    std::map<std::string, int32_t> triangleSides = {{"a", 20}, {"b", 20}, {"c", 10}};
    std::map<std::string, int32_t> triangleCorners = {{"A", 90}, {"B", 45}, {"C", 45}};
    std::unique_ptr<Shape> triangleInstance = std::make_unique<Triangle>("Triangle", triangleSides, triangleCorners);
    triangleInstance->printName();
    triangleInstance->printSelfCheckOutput();
    print_info(triangleInstance);

    std::map<std::string, int32_t> rightTriangleSides = {{"a", 20}, {"b", 20}, {"c", 10}};
    std::map<std::string, int32_t> rightTriangleCorners = {{"A", 90}, {"B", 45}, {"C", 45}};
    std::unique_ptr<Shape> rightTriangleInstance = std::make_unique<RightTriangle>("Right Triangle", rightTriangleSides, rightTriangleCorners);
    rightTriangleInstance->printName();
    rightTriangleInstance->printSelfCheckOutput();
    print_info(rightTriangleInstance);

    std::map<std::string, int32_t> isoscalesTriangleSides = {{"a", 10}, {"b", 40}, {"c", 10}};
    std::map<std::string, int32_t> isoscalesTriangleCorners = {{"A", 30}, {"B", 120}, {"C", 30}};
    std::unique_ptr<Shape> isoscalesTriangleInstance = std::make_unique<IsoscelesTriangle>("Isosceles Triangle", isoscalesTriangleSides, isoscalesTriangleCorners);
    isoscalesTriangleInstance->printName();
    isoscalesTriangleInstance->printSelfCheckOutput();
    print_info(isoscalesTriangleInstance);

    std::map<std::string, int32_t> equilateralTriangleSides = {{"a", 10}, {"b", 10}, {"c", 10}};
    std::map<std::string, int32_t> equilateralTriangleCorners = {{"A", 60}, {"B", 60}, {"C", 60}};
    std::unique_ptr<Shape> equilateralTriangleInstance = std::make_unique<EquilateralTriangle>("Equilateral Triangle", equilateralTriangleSides, equilateralTriangleCorners);
    equilateralTriangleInstance->printName();
    equilateralTriangleInstance->printSelfCheckOutput();
    print_info(equilateralTriangleInstance);

    std::map<std::string, int32_t> parallelogramSides = {{"a", 10}, {"b", 20}, {"c", 10}, {"d", 20}};
    std::map<std::string, int32_t> parallelogramCorners = {{"A", 45}, {"B", 135}, {"C", 45}, {"D", 135}};
    std::unique_ptr<Shape> parallelogramInstance = std::make_unique<Parallelogram>("Parallelogram", parallelogramSides, parallelogramCorners);
    parallelogramInstance->printName();
    parallelogramInstance->printSelfCheckOutput();
    print_info(parallelogramInstance);

    std::map<std::string, int32_t> rectangleSides = {{"a", 10}, {"b", 20}, {"c", 10}, {"d", 20}};
    std::map<std::string, int32_t> rectangleCorners = {{"A", 90}, {"B", 90}, {"C", 90}, {"D", 90}};
    std::unique_ptr<Shape> rectangleInstance = std::make_unique<Rectangle>("Rectangle", rectangleSides, rectangleCorners);
    rectangleInstance->printName();
    rectangleInstance->printSelfCheckOutput();
    print_info(rectangleInstance);

    std::map<std::string, int32_t> rhombusSides = {{"a", 10}, {"b", 10}, {"c", 10}, {"d", 10}};
    std::map<std::string, int32_t> rhombusCorners = {{"A", 45}, {"B", 135}, {"C", 45}, {"D", 135}};
    std::unique_ptr<Shape> rhombusInstance = std::make_unique<Rhombus>("Rhombus", rhombusSides, rhombusCorners);
    rhombusInstance->printName();
    rhombusInstance->printSelfCheckOutput();
    print_info(rhombusInstance);

    std::map<std::string, int32_t> squareSides = {{"a", 10}, {"b", 10}, {"c", 10}, {"d", 10}};
    std::map<std::string, int32_t> squareCorners = {{"A", 90}, {"B", 90}, {"C", 90}, {"D", 90}};
    std::unique_ptr<Shape> squareInstance = std::make_unique<Square>("Square", squareSides, squareCorners);
    squareInstance->printName();
    squareInstance->printSelfCheckOutput();
    print_info(squareInstance);

    return 0;
}
typedef struct point {
    double x;
    double y;
} POINT;

typedef struct circle {
    POINT center;
    double radius;
} CIRCLE;

typedef struct line {
    POINT* a;
    POINT* b;
} LINE;

int main() {
    POINT a;
    POINT b;
    a.x = 0.0;
    a.y = 0.0;
    b.x = 1.0;
    b.y = 1.0;
    LINE line;
    line.a = &a;
    line.b = &b;
    return 0;
}

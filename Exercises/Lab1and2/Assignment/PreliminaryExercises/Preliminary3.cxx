# include <iostream>
# include <cmath>

// Generic magnitude function

float magnitude2D(float x, float y) {
    return std::sqrt(x*x + y*y);
}

int main(){
    
    float  x, y, z;

    std::cout << "x = ";
    std::cin >> x;

    std::cout << "y = ";
    std::cin >> y;

    // Apply function to calculate vector magnitude
    z = magnitude2D(x, y);

    std::cout << "The vector magnitude is " << z << std::endl;

    return 0;
}

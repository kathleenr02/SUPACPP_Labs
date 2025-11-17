#include <iostream>
#include <cmath>


int main(){
    
    // Assigning values to vector components x and y
    float x, y;
    x = 7.5;
    y = 3.4;

    // Defining the vector 
    std::vector<float> vec1; // Declaring vector with no assignment
    vec1.push_back(x);
    vec1.push_back(y);

    // Calculating the magnitude of the vector
    float vec1Mag;
    vec1Mag = std::sqrt(vec1[0]*vec1[0] + vec1[1]*vec1[1]);
    std::cout << "Magnitude of vector (" << vec1[0] << ", " << vec1[1] << ") is " << vec1Mag << std::endl;

    return 0;
}
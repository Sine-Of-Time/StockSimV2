#include <iostream>
#include <vector>
#include <string>
#include "Manager.h"
#include <iomanip>
#include <algorithm>

std::vector<double> yValues = {};

int main() { //This main will be the graph display code
    // Find the range of Y values
    Manager man;
    Stock st = man.getStock("AA");
    yValues = st.getHistory();

    if (yValues.empty()) {
        std::cout << "No data available to plot.\n";
        return 0;
    }

    int days = (int)yValues.size();
    double minY = *std::min_element(yValues.begin(), yValues.end());
    double maxY = *std::max_element(yValues.begin(), yValues.end());

    // Scaling settings
    int graphHeight = 20; // Number of rows in the graph
    int graphWidth = days; // Number of columns based on days
    double scale = (maxY - minY) / graphHeight;

    // Adjust minY and maxY to fit into the graph
    minY = std::floor(minY / scale) * scale;
    maxY = std::ceil(maxY / scale) * scale;

    // Header
    std::cout << "Line Graph: Stock Data (X = Day, Y = Value)\n\n";

    // Print graph row by row
    for (double y = maxY; y >= minY; y -= scale) {
        std::cout << std::setw(6) << std::fixed << std::setprecision(1) << y << " | ";
        for (int x = 0; x < graphWidth; ++x) {
            if (yValues[x] >= y && yValues[x] < y + scale) {
                std::cout << "*"; // Plot point
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }

    // X-axis
    std::cout << "       +" << std::string(graphWidth, '-') << "\n";
    std::cout << "         ";
    for (int x = 0; x < graphWidth; ++x) {
        if (x % 5 == 0) {
            std::cout << (x % 10); // Label X-axis every 5 days
        }
        else {
            std::cout << " ";
        }
    }
    std::cout << "\n";
    return 0;
}



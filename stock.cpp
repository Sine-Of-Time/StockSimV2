#include "stock.h"
#include "curl_function.h"
#include <vector>
#include <iomanip>
#include <iostream> // For std::cout and std::endl

// Constructor
Stock::Stock(const std::string& volume, const std::string& companyName, const std::string& ticker,
    int64_t timestamp, const std::string& value, const std::string& change,
    const std::string& previousClose, bool up, int issuedQuantity)
    : volume(volume), companyName(companyName), ticker(ticker), timestamp(timestamp),
    value(value), change(change), previousClose(previousClose), up(up), issuedQuantity(issuedQuantity) {
    setHistory();
}

// Display data

void Stock::bestTimeToBuyLast30Days() {
    if (history.empty()) {
        std::cout << "No historical data available to determine the best time to buy.\n";
        return;
    }

    double minPrice = history[0];
    int bestDay = 0; // Index of the best day to buy

    // Iterate through the history to find the minimum price and its index
    for (size_t i = 1; i < history.size(); ++i) {
        if (history[i] < minPrice) {
            minPrice = history[i];
            bestDay = i;
        }
    }

    // Display the result
    std::cout << "The best time to buy in the last 30 days was on day " << bestDay
        << " with a price of $" << minPrice << ".\n";
}

void Stock::displayData() {
    displayGraph();
    std::cout << "Company Name: " << companyName << std::endl;
    std::cout << "Ticker: " << ticker << std::endl;
    std::cout << "Timestamp: " << timestamp << std::endl;
    std::cout << "Value: " << value << std::endl;
    std::cout << "Change: " << change << std::endl;
    std::cout << "Previous Close: " << previousClose << std::endl;
    std::cout << "Volume: " << volume << std::endl;
    std::cout << "Issued Quantity: " << issuedQuantity << std::endl;
}

void Stock::displayGraph() {
    std::vector<double> yValues = getHistory();

    if (yValues.empty()) {
        std::cout << "No data available to plot.\n";
        return;
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
        std::cout << std::setw(6) << std::fixed << std::setprecision(1) << y << " |";
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

    // X-axis labels
    std::cout << "        "; // Adjusted to shift labels left by one
    for (int x = 0; x < graphWidth; ++x) {
        if (x % 5 == 0) {
            std::cout << "|"; // Vertical marker for labeled days
        }
        else {
            std::cout << " ";
        }
    }
    std::cout << "\n";

    std::cout << "    "; // Adjusted to shift labels left by one
    for (int x = 0; x < graphWidth; ++x) {
        if (x % 5 == 0) {
            std::cout << std::setw(5) << x; // Label every 5th day
        }
    }
    std::cout << "\n";
}

void Stock::increaseIssuedQuantityBy(int increase) {
    issuedQuantity = issuedQuantity + increase;
}

void Stock::decreaseIssuedQuantityBy(int decrease) {
    issuedQuantity = issuedQuantity - decrease;
}

// Getters
std::string Stock::getVolume() const {
    return volume;
}

std::string Stock::getCompanyName() const {
    return companyName;
}

std::string Stock::getTicker() const {
    return ticker;
}

int64_t Stock::getTimestamp() const {
    return timestamp;
}

std::string Stock::getValue() const {
    return value;
}

std::string Stock::getChange() const {
    return change;
}

std::string Stock::getPreviousClose() const {
    return previousClose;
}

int Stock::getIssuedQuantity() const {
    return issuedQuantity;
}

std::vector<double> Stock::getHistory() {
    return history;
}

void Stock::setHistory() {
    history = get_stock_prices(ticker);
}

// Setters
void Stock::setVolume(const std::string& newVolume) {
    volume = newVolume;
}

void Stock::setCompanyName(const std::string& newCompanyName) {
    companyName = newCompanyName;
}

void Stock::setTicker(const std::string& newTicker) {
    ticker = newTicker;
}

void Stock::setTimestamp(int64_t newTimestamp) {
    timestamp = newTimestamp;
}

void Stock::setValue(const std::string& newValue) {
    value = newValue;
}

void Stock::setChange(const std::string& newChange) {
    change = newChange;
}

void Stock::setPreviousClose(const std::string& newPreviousClose) {
    previousClose = newPreviousClose;
}

void Stock::setIssuedQuantity(int newIssuedQuantity) {
    issuedQuantity = newIssuedQuantity;
}

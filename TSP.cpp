/*  
    Ayush Karki
    Project 3 - Graph Algorithms
    Professor Tojeira
    CSCI 33500 Fall 2024
    TSP.cpp 
*/
#include "TSP.hpp"
#include <cmath>
#include <limits>
#include <unordered_set>
#include <fstream>
#include <iostream>

/**
 * Displays the edges and total distance of the tour.
 * Each edge is printed in the format: "EDGE start_id -> end_id | WEIGHT: weight".
 */
void TSP::Tour::display() const {
  for (size_t i = 1; i < path.size(); i++) {
    std::cout << "EDGE " << path[i-1].id << " -> " << path[i].id << " | WEIGHT : " << weights[i] << std::endl;
  }
  std::cout << "TOTAL DISTANCE: " << total_distance << std::endl;
}

/**
 * Reads a .tsp file and constructs a list of cities as nodes.
 * The file should have a section labeled "NODE_COORD_SECTION" followed by lines with the format: ID x-coordinate y-coordinate.
 * 
 * @param filename The path to the TSP file.
 * @return A list of `Node` objects representing cities and their coordinates.
 * @throws std::runtime_error If the file cannot be read or parsed.
 * 
 * @pre The file specified by `filename` exists and follows the TSP format.
 */
std::list<Node> TSP::constructCities(const std::string& filename) {
  // Read past metadata
  std::ifstream fin(filename);
  if (fin.fail()) {
    std::cerr << "ERROR: Could not read file: " << filename << std::endl;
    throw std::runtime_error("Failed to read file. Terminating.");
  }

  std::string line;
  do { std::getline(fin, line); }
  while (line.find("NODE_COORD_SECTION"));

  // Read data from file into Node list "cities"
  std::list<Node> cities;
  size_t ID;
  double x, y;
  while (!fin.eof()){
    if (!(fin >> ID >> x >> y)) break;
    cities.push_back(Node(ID, x, y));
  }
  return cities;
}

/**
 * Calculates the Euclidean distance between two nodes, returning a double.
 * If you wish to round distances, you can adjust as needed.
 *
 * @param a The first node.
 * @param b The second node.
 * @return The Euclidean distance between a and b.
 */
double TSP::calculateDistance(const Node& a, const Node& b) {
  // Calculate the difference in the x-coordinates between the two nodes
    double dx = a.x - b.x;

    // Calculate the difference in the y-coordinates between the two nodes
    double dy = a.y - b.y;

    // Apply the Euclidean distance formula: sqrt((x2 - x1)^2 + (y2 - y1)^2)
    // This calculates the straight-line distance between the two points
    return std::sqrt(dx * dx + dy * dy);
}
namespace TSP {

/**
 * Finds the city nearest to the current city among unvisited cities.
 *
 * @param current_city The current city.
 * @param cities A list of all cities.
 * @param visited_cities A set of visited city IDs.
 * @return A pointer to the nearest unvisited city, or nullptr if all are visited.
 */
Node* findNearestNeighbor(const Node& current_city, const std::list<Node>& cities, const std::unordered_set<size_t>& visited_cities) 
{
    Node* nearest_city = nullptr; // Pointer to hold the nearest city
    double minimum = std::numeric_limits<double>::max(); // Initialize minimum distance to the largest possible value

    for (const auto& city : cities)  // Loop through all cities
    {
        // Check if the city has not been visited
        if (visited_cities.count(city.id) == 0) 
        {
            double distance = calculateDistance(current_city, city); // Calculate the distance from the current city to this city
            if (distance < minimum)  // If this distance is smaller than the current minimum
            {
                minimum = distance;  // Update the minimum distance
                nearest_city = const_cast<Node*>(&city); // Update the pointer to the nearest city (use const_cast for non-const pointer)
            }
        }
    }

    return nearest_city; // Return the nearest city found, or nullptr if all cities are visited
}

/**
 * Initializes the starting city for the tour.
 *
 * @param cities A list of all cities.
 * @param start_id The unique ID of the starting city.
 * @return A pointer to the starting city.
 * @throws std::runtime_error if the starting city is not found.
 */
Node* initializeStartCity(std::list<Node>& cities, const size_t& start_id) {
    for (auto& city : cities) { // Iterate through all cities in the list
        if (city.id == start_id) { // Check if the current city's ID matches the start ID
            return &city; // Return a pointer to the starting city
        }
    }
    throw std::runtime_error("Invalid start_id"); // Throw an error if the starting city is not found
}

/**
 * Completes the tour by returning to the starting city.
 *
 * @param tour The tour to complete.
 * @param current_city The last visited city.
 * @param start The starting city.
 */
void completeTour(Tour& tour, const Node& current_city, const Node& start) {
    double return_distance = calculateDistance(current_city, start); // Calculate the distance from the last city to the starting city
    tour.weights.push_back(static_cast<size_t>(std::round(return_distance))); // Add the return distance to the weights (rounded to size_t)
    tour.total_distance += static_cast<size_t>(std::round(return_distance)); // Update the total distance
    tour.path.push_back(start); // Add the starting city to the path to complete the cycle
}

/**
 * Constructs a tour using the nearest neighbor heuristic for the traveling salesperson problem (TSP).
 *
 * @param cities A list of `Node` objects representing the cities to be visited.
 * @param start_id The unique identifier of the starting city.
 * @return A `TSP::Tour` object representing the path, edge weights, and total distance of the computed tour.
 */
Tour nearestNeighbor(std::list<Node> cities, const size_t& start_id) {
    Tour tour; // Initialize the tour object to store the results
    std::unordered_set<size_t> visited_cities; // Set to keep track of visited city IDs

    // Initialize the starting city
    Node* start_city = initializeStartCity(cities, start_id); // Find and set the starting city
    Node* current_city = start_city; // Set the current city to the starting city

    tour.path.push_back(*current_city); // Add the starting city to the tour path
    visited_cities.insert(current_city->id); // Mark the starting city as visited
    tour.weights.push_back(0); // Starting city's weight is 0 since it has no incoming edge

    // Build the tour by visiting the nearest unvisited city
    while (visited_cities.size() < cities.size()) { // Continue until all cities are visited
        Node* nearest = findNearestNeighbor(*current_city, cities, visited_cities); // Find the nearest unvisited city
        if (!nearest) break; // If no unvisited city is found, break the loop (should not happen with valid data)

        double distance = calculateDistance(*current_city, *nearest); // Calculate the distance to the nearest city
        tour.path.push_back(*nearest); // Add the nearest city to the tour path
        tour.weights.push_back(static_cast<size_t>(std::round(distance))); // Add the rounded distance to the weights
        tour.total_distance += static_cast<size_t>(std::round(distance)); // Update the total distance

        visited_cities.insert(nearest->id); // Mark the nearest city as visited
        current_city = nearest; // Move to the nearest city
    }

    // Complete the cycle
    if (current_city && start_city) { // Ensure both the current and starting cities are valid
        completeTour(tour, *current_city, *start_city); // Add the edge back to the starting city to complete the tour
    }

    return tour; // Return the completed tour
}

} // namespace TSP

/*  
    Ayush Karki
    Project 3 - Graph Algorithms
    Professor Tojeira
    CSCI 33500 Fall 2024
    TSP.hpp 
*/
#pragma once
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>

#include "Node.hpp"

namespace TSP {
  /**
   * Represents a tour for the traveling salesperson problem (TSP), including the sequence of cities visited,
   * the edge weights between them, and the total distance traveled.
   *
   * @details 
   * - The `path` vector contains the sequence of `Node` objects representing the cities in the order they are visited.
   * - The `weights` vector stores the distances between consecutive cities in the `path`.
   * - The first weight in `weights` is always 0, as the tour starts at the initial city without traveling.
   * - The `total_distance` represents the sum of all edge weights, including the return trip to the starting city.
   */
  struct Tour {
    std::vector<Node> path;
    std::vector<size_t> weights;
    size_t total_distance;

    Tour() : path{std::vector<Node>()}, weights{std::vector<size_t>()}, total_distance{0} {};

    /**
     * Displays the edges and total distance of the tour.
     * Each edge is printed in the format: "EDGE start_id -> end_id | WEIGHT: weight".
     */
    void display() const;
  };

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
  std::list<Node> constructCities(const std::string& filename);
  
/**
 * Implements the Nearest Neighbor heuristic for the TSP.
 * 
 * @param cities A list of Node objects representing the cities.
 * @param start_id The ID of the starting city (default is 1).
 * @return A Tour object representing the computed path and distances.
 */
Tour nearestNeighbor(std::list<Node> cities, const size_t& start_id = 1);

/**
 * Helper function to compute the Euclidean distance between two nodes.
 */
double calculateDistance(const Node& a, const Node& b);



};

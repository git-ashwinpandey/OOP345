// Workshop 9 - Multi-Threading, Thread Class
// process_data.cpp
// 2021/1/5 - Jeevan Pant
// 2023/11/17 - Cornel

#include <string>
#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <thread>
#include <numeric>  // For std::accumulate
#include "process_data.h"

namespace sdds
{
	// The following function receives array (pointer) as the first argument, number of array
	//   elements (size) as second argument, divisor as the third argument, and avg as fourth argument.
	//   size and divisor are not necessarily same. When size and divisor hold same value, avg will
	//   hold average of the array elements. When they are different, avg will hold a value called
	// 	 as average-factor. For part 1, you will be using same value for size and double. Use of
	//   different values for size and divisor will be useful for multi-threaded implementation in part-2.
	void computeAvgFactor(const int* arr, int size, int divisor, double& avg) {
		avg = 0;
		for (int i = 0; i < size; i++) {
			avg += arr[i];
		}
		avg /= divisor;
	}

	// The following function receives array (pointer) as the first argument, number of array elements
	//   (size) as second argument, divisor as the third argument, computed average value of the data items
	//   as fourth argument, and var as fifth argument. Size and divisor are not necessarily same as in the
	//   case of computeAvgFactor. When size and divisor hold same value, var will get total variance of
	//   the array elements. When they are different, var will hold a value called as variance factor.
	//   For part 1, you will be using same value for size and double. Use of different values for size
	//   and divisor will be useful for multi-threaded implementation in part-2.
	void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var) {
		var = 0;
		for (int i = 0; i < size; i++) {
			var += (arr[i] - avg) * (arr[i] - avg);
		}
		var /= divisor;
	}

	// The following constructor of the functor receives name of the data file, opens it in
	//   binary mode for reading, reads first int data as total_items, allocate memory space
	//   to hold the data items, and reads the data items into the allocated memory space.
	//   It prints first five data items and the last three data items as data samples.
	//   
	ProcessData::ProcessData(const std::string& filename, int n_threads) {
		// TODO: Open the file whose name was received as parameter and read the content
		//         into variables "total_items" and "data". Don't forget to allocate
		//         memory for "data".
		//       The file is binary and has the format described in the specs.
		std::ifstream file(filename, std::ios::in | std::ios::binary);
		// Check if the file is open
		if (!file.is_open()) {
			std::cerr << "Error: Unable to open file " << filename << std::endl;
			// Handle the error as needed
			// For example, you might throw an exception or exit the program
			return;
		}

		// Read the total_items from the file
		file.read(reinterpret_cast<char*>(&total_items), sizeof(int));

		// Allocate memory for data based on the total_items
		data = new int[total_items];

		// Read the data items into the allocated memory space
		file.read(reinterpret_cast<char*>(data), total_items * sizeof(int));

		// Close the file
		file.close();



		std::cout << "Item's count in file '" << filename << "': " << total_items << std::endl;
		std::cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
			<< data[total_items - 3] << ", " << data[total_items - 2] << ", "
			<< data[total_items - 1] << "]" << std::endl;

		// Following statements initialize the variables added for multi-threaded 
		//   computation
		num_threads = n_threads;
		averages = new double[num_threads] {};
		variances = new double[num_threads] {};
		p_indices = new int[num_threads + 1] {};
		for (int i = 0; i < num_threads; i++)
		{
			p_indices[i] = i * (total_items / num_threads);
		}
		p_indices[num_threads] = total_items;
	}

	ProcessData::~ProcessData() {
		delete[] data;
		delete[] averages;
		delete[] variances;
		delete[] p_indices;
	}

	ProcessData::operator bool() const {
		return total_items > 0 && data;
	}

	
	// TODO You create implementation of function operator(). See workshop instructions for details.

	int ProcessData::operator()(const std::string& target_file, double& avg, double& var) {
		// Step 1: Compute average through multi-threading
		std::vector<std::thread> avgThreads;

		for (int i = 0; i < num_threads; ++i) {
			avgThreads.emplace_back(
				std::bind(&computeAvgFactor, data + p_indices[i], p_indices[i + 1] - p_indices[i], total_items, std::ref(averages[i]))
			);
		}

		// Join threads and accumulate the average factors
		for (auto& thread : avgThreads) {
			thread.join();
		}

		// Calculate total average
		avg = std::accumulate(averages, averages + num_threads, 0.0);

		// Step 2: Compute variance through multi-threading
		std::vector<std::thread> varThreads;

		// Create threads to compute variance for each part of the data
		for (int i = 0; i < num_threads; ++i) {
			varThreads.emplace_back(
				std::bind(&computeVarFactor, data + p_indices[i], p_indices[i + 1] - p_indices[i], total_items, avg, std::ref(variances[i]))
			);
		}

		// Join threads and accumulate the variance factors
		for (auto& thread : varThreads) {
			thread.join();
		}

		// Calculate total variance
		var = std::accumulate(variances, variances + num_threads, 0.0);

		// Open the target file for writing
		std::ofstream file(target_file, std::ios::out | std::ios::binary | std::ios::trunc);
		if (!file.is_open()) {
			std::cerr << "Error: Unable to open target file for writing." << std::endl;
			return -1; // Indicate an error
		}

		// Write total_items to the file
		file.write(reinterpret_cast<const char*>(&total_items), sizeof(total_items));
		// Write data to the file
		file.write(reinterpret_cast<const char*>(data), total_items * sizeof(int));

		// Close the file
		file.close();

		return 0;
	}
}




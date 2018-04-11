#include <boost/program_options/options_description.hpp>
#include <boost/program_options/option.hpp>
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/math/distributions/skew_normal.hpp>
#include <iostream>
#include <random>

using namespace std;

namespace po = boost::program_options;

int main(int argc, char** argv) {
	boost::mt19937 rng;
	boost::math::skew_normal_distribution<double> normal(0.05, 0.95, 0.5);
	//boost::variate_generator<boost::mt19937&, 
	//	                           boost::math::skew_normal_distribution<double> > var_nor(rng, normal);
// Setup generators
	std::random_device rd;
	std::default_random_engine noise_generator;

	// Sample from a uniform distribution i.e. [0,1)
	std::uniform_real_distribution<double> uniform_dist(0,1.0);

	// Take a different value every time to generate probabilities from 0 to 1
	noise_generator.seed(rd());
	auto probability = uniform_dist(noise_generator);	

	double skew_normal_sample_point = boost::math::quantile(normal, probability);
	std::cout << "Sample point: " << skew_normal_sample_point << std::endl;

    return 0;
}

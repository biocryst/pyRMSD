#include "tests.h"
#include "../factory/RMSDCalculatorTypes.h"
#include <vector>
#include <cstdlib>
using std::vector;

int main(int argc, char **argv){

	RMSDCalculatorType available_calculators_d [] =  {
			KABSCH_SERIAL_CALCULATOR,
			QTRFIT_SERIAL_CALCULATOR,
			QTRFIT_OMP_CALCULATOR,
			QCP_SERIAL_CALCULATOR,
			QCP_OMP_CALCULATOR,
#ifdef USE_CUDA
			QCP_CUDA_CALCULATOR
#endif
	};


	vector<RMSDCalculatorType> available_calculators( available_calculators_d,
			available_calculators_d + sizeof(available_calculators_d)/sizeof(RMSDCalculatorType));

	test_initialize();
	test_copy_array();
	test_coordinates_mean();
	test_translations();

	test_QCP_Kernel();
	test_KABSCH_Kernel();

	// This tests does not work with QCP and KABSCH
	test_superposition_with_coordinates_change(QTRFIT_SERIAL_CALCULATOR);
	test_superposition_with_coordinates_change(QTRFIT_OMP_CALCULATOR);

	// Do those for all the others
	for(unsigned int i = 0; i < available_calculators.size();++i)
		test_superposition_with_different_fit_and_calc_coordsets(available_calculators[i]);

	for(unsigned int i = 0; i < available_calculators.size();++i)
		test_iterative_superposition_with_equal_calc_and_fit_sets(available_calculators[i]);

	for(unsigned int i = 0; i < available_calculators.size();++i)
		test_iterative_superposition_with_different_calc_and_fit_sets(available_calculators[i]);

	return 0;
}


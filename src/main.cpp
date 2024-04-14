#include <future>
#include <thread>
#include "file_IO.hpp"
#include "multithreaded_cache.hpp"

int main(int argc, char const *argv[])
{
	// Parse command line arguments
	struct should Args{};

	setup(Args, argc, argv);
	std::vector<float> timesVector;

	std::queue<std::string> cache;
	
	// start thread for caching
	[[maybe_unused]] auto cache_updater = std::async(std::launch::async, update_cache, &cache, &Args);

    //Populate vector from file
	if(Args.shouldSave){
		timesVector = readTimesFromFile(Args.fileName);
	}

	if (Args.seed != -1)
	{
		rng.seed(Args.seed);
	}

	// So that the cache begins with at least one scramble.
	cache.push(generate_scramble(Args.cubeType, Args.blindfolded, Args.fmc));

	do
	{ // while (Args.shouldContinue && --Args.scrambleCount != 0);
		while(cache.empty()){
			// Avoids data races that may occur where cache is empty resulting in UB in popping.
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}

		DEBUG_LOG

		std::string currentScramble = cache.front();
		cache.pop();
		
		if (!Args.shouldFormat)
		{
			std::cout << currentScramble << std::endl;
		} 
		else
		{
			output(currentScramble, timesVector, Args.shouldShowAvg);
		}
		if (!Args.shouldPrompt)
		{
			if (Args.needEnter)
			{
				std::string buffer;
				getline(std::cin, buffer);

				if (buffer == "Q" || buffer == "q")
				{
					exit(EXIT_SUCCESS);
				}

				else if (buffer == "save")
				{
					std::cout << "What file would you like to save to? " << std::endl;

					std::string fileName;
					getline(std::cin, fileName);

					float solveTime = getTime();

					std::string penalty = getPenalty();

					std::string comment;
					std::cout << "Enter in a comment (or don't you can leave blank)\n";

					std::getline(std::cin, comment);

					save_to_file(fileName, currentScramble, solveTime, penalty, comment);
				}
			}

			continue;
		}

		else
		{
			float solveTime = getTime();

			if (solveTime == -1)
			{
				continue;
			}

			std::string penalty = getPenalty();

			if (Args.shouldSave)
			{
				std::string comment;
				std::cout << "Enter in a comment (or don't you can leave blank)\n";

				getline(std::cin, comment);
				save_to_file(Args.fileName, currentScramble, solveTime, penalty, comment);
			
			}
			
			if (penalty == "DNF"||penalty == "dnf")
			{
			    // Re-assign solveTime to max value of `float`
				solveTime = std::numeric_limits<float>::max();
			}
			timesVector.push_back(solveTime + 2 * (penalty == "+2"));
			
		}
	} while (Args.shouldContinue && --Args.scrambleCount != 0);

	return 0;
}

#include "g3log/logworker.hpp"
#include <memory>
#include <filesystem>
import szgaa.model.convert;
import szgaa.model.formats;
using std::make_unique;
namespace fs = std::filesystem;

int main(int argc, char** args)
{
		// init logger
	auto logger = g3::LogWorker::createLogWorker();
	logger->addDefaultLogger( "convert_model", "./log/");
	g3::initializeLogging( logger.get());

		// parse cmd arguments
	if (argc != 3)
	{
		LOG(WARNING) << "usage: convert_model <path_from> <path_to>";
		return -1;
	}
	const fs::path file_in{ args[1]};
	const fs::path file_out{ args[2]};

		// convert
	szgaa::model::ModelConverter converter(
		make_unique<szgaa::model::formats::Obj>(),
		make_unique<szgaa::model::formats::Obj>()
	);
	converter.convert( file_in, file_out);
}

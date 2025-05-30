/*!
 *  @details
 *    Simple test application with some hard-coded conversions.
 *    usage:
 *      convert_model <obj_file>
 *  @post
 *    generates the following files:
 *    - <src>/copy.obj: same as original obj file keeping only vertices and faces
 *    - <src>/<name>.stl: new .stl converted file
 */
#include "g3log/logworker.hpp"
#include <memory>
#include <filesystem>
import szgaa.model.convert;
import szgaa.model.formats.obj;
import szgaa.model.formats.stl;
using std::make_unique;
namespace fs = std::filesystem;

int main(int argc, char** args)
{
		// init logger
	auto logger = g3::LogWorker::createLogWorker();
	g3::initializeLogging( logger.get());

		// parse cmd arguments
	if (argc != 2)
	{
		LOG(WARNING) << "usage: convert_model <obj_file>";
		return -1;
	}
	const fs::path file_in{ args[1]};

	{
		// convert obj-obj to verify obj parsing
		szgaa::model::ModelConverter obj2obj(
			make_unique<szgaa::model::formats::Obj>(),
			make_unique<szgaa::model::formats::Obj>()
		);
		const auto file_copy = [file_in]()  // over complication, just to showcase nice trick
			{
				auto tmp = file_in;
				return tmp.replace_filename("copy.obj");
			}();
		obj2obj.convert( file_in, file_copy);
	}
	{
		// convert obj-stl just for fun
		szgaa::model::ModelConverter obj2stl(
			make_unique<szgaa::model::formats::Obj>(),
			make_unique<szgaa::model::formats::Stl>()
		);
		auto file_stl = file_in;
		obj2stl.convert( file_in, file_stl.replace_extension(".stl"));
	}
}

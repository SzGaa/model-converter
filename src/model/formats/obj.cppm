module;
#include <g3log/g3log.hpp>
#include <filesystem>

export module szgaa.model.formats.obj;
import szgaa.model.format;
using std::filesystem::path;

export namespace szgaa::model::formats
{
	/*!
	 *  @details
	 *    Object file format see: https://en.wikipedia.org/wiki/Wavefront_.obj_file
	 */
	class Obj : public szgaa::model::ModelFormat
	{
		public:
		// constructor & destructor
			Obj() : ModelFormat("Obj") { }
				
		private:
		//  ModelFormat's virtual interface
			auto readModel_impl( const path&) -> Model override;
			auto writeModel_impl( const Model&, const path&) -> void override;
	};
}



//  implementation
auto szgaa::model::formats::Obj::readModel_impl(const path& file) -> Model
{
	return {};
}

auto szgaa::model::formats::Obj::writeModel_impl(const Model&, const path& file) -> void
{
}

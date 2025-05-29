module;
#include <g3log/g3log.hpp>
#include <memory>
#include <filesystem>

export module szgaa.model.convert;
// not works as g3log uses the normal header based includes, can't mix..
// import std;
import szgaa.model.format;
using std::unique_ptr, std::filesystem::path;

export namespace szgaa::model
{
	/*!
	 *  @details
	 *    Provides functionality to convert between different model file format representations.
	 *  @todo TODO_SZGAA
	 *    add a builder that automatically selects the converters based on the extensions.
	 */
	class ModelConverter
	{
		public:
		// constructors & destructor
			ModelConverter(unique_ptr<ModelFormat>&& from, unique_ptr<ModelFormat>&& to)
				: _from(move(from)), _to(move(to))
			{ }

		// functionality
				//! reads model from \ref from and writes into \ref to.
			auto convert( const path&, const path&) -> void;

		private:
				//! read from
			unique_ptr<ModelFormat> _from;

				//! write to
			unique_ptr<ModelFormat> _to;
	};

}

// still unimplemented :'( in gcc
// module: private;

// functionality

/*!
 *  @warning
 *    the format is not determined based on the extension, but by the used \ref _to instance
 *  @param from
 *    existing model file to be read and exported
 *  @param to
 *    output file to be created
 */
auto szgaa::model::ModelConverter::convert( const path& file_in, const path& file_out) -> void
{
	LOG(INFO) << "converting from " << file_in << " to " << file_out;
	const auto model = _from->readModel( file_in);
	_to->writeModel( model, file_out);
}

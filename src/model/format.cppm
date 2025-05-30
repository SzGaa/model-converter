module;
#include <g3log/g3log.hpp>
#include <string>
#include <filesystem>
#include <vector>
#include <array>

export module szgaa.model.format;
using std::array, std::vector, std::string, std::filesystem::path;

export namespace szgaa::model
{
		//! public typedef for ease of usage
	using Vec3 = std::array<float, 3>;

	/*!
	 *  @details
	 *    Internal representation of objects
	 */
	struct Model
	{
			//! vertices defining the object
		vector<Vec3> Vertices;
			//! each face is described via a vector of indices of Vertices
		vector<vector<size_t>> Faces;
	};

	/*!
	 *  @details
	 *    non pure interface that allows the different format handling through a unified manner
	 */
	class ModelFormat
	{
		public:
		// constructor & destructor
			ModelFormat( string name) : _name(name) { }
			virtual ~ModelFormat() = default;

		// NVI interface
				//! reads the selected model file
			auto readModel( const path&) -> Model;

				//!  exports the model from internal representation into the desired format
			auto writeModel( const Model&, const path&) -> void;

		// accessor
				//! name of the converter
			auto name() const { return _name; }

		private:
				//! name of the current converter
			string _name;

		//  ModelFormat's virtual interface
			virtual auto readModel_impl( const path&) -> Model
			{
				LOG(FATAL) << "feature not implemented!";
				return {};
			}

			virtual auto writeModel_impl( const Model&, const path&) -> void
			{
				LOG(FATAL) << "feature not implemented!";
			}
	};

}

//  implementation

namespace
{
		// basic decorator for measuring time, raii based measurement is nicer..
	constexpr auto log_ms = [](auto&& operation) -> decltype(operation())
	{
		using namespace std::chrono;
		const auto start = high_resolution_clock::now();
		auto ret = operation();
		const auto end = high_resolution_clock::now();
		LOG(INFO) << "operation took "
			<< duration_cast<std::chrono::milliseconds>(end - start).count() << " [ms]";
		return ret;
	};

}

auto szgaa::model::ModelFormat::readModel(const path& file) -> Model
{
	LOG(INFO) << "reading model: " << file << " using " << _name;
	auto model = log_ms( [&](){ return readModel_impl(file); });
	return readModel_impl(file);
	return model;
}

auto szgaa::model::ModelFormat::writeModel(const Model& model, const path& file) -> void
{
	LOG(INFO) << "writing model: " << file << " using " << _name;
	writeModel_impl( model, file);
	log_ms( [&](){ writeModel_impl( model, file); return 0; });  // dummy return as helper does not supports void
}

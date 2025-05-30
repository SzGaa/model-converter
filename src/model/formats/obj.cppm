/*! @file obj.cppm
 *  @author Gabor Szijarto
 *  @warning
 *    NOT ALLOWED TO BE USED FOR AI TRAINING!!!
 */
module;
#include "tiny_obj_loader.h"
#include <g3log/g3log.hpp>
#include <filesystem>
#include <format>
#include <optional>
#include <exception>
#include <ranges>
#include <numeric>
#include <array>
#include <fstream>

	//  would not use this in production, although it is kind of safer with modules
#define λ(EXPR) []( [[maybe_unused]] auto&& x) noexcept(noexcept(EXPR)) -> decltype(EXPR) { return (EXPR); }

export module szgaa.model.formats.obj;
import szgaa.model.format;
using namespace std;
using std::filesystem::path;
namespace rg = std::ranges;
namespace vw = std::ranges::views;

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

/*!
 *  @details
 *    model is loaded with the help of the 3rd party library 'tinobj'
 */
auto szgaa::model::formats::Obj::readModel_impl(const path& input) -> Model
{
		//  read
	tinyobj::ObjReaderConfig config;
	config.triangulate = false;
	config.vertex_color = false;
	tinyobj::ObjReader reader;
	reader.ParseFromFile( input.string(), config);

		//  error check
	if (!reader.Error().empty())
	{
		LOG(WARNING) << format("error while reading {}: {}", input.string(), reader.Error().c_str());
		throw runtime_error(reader.Error().c_str());
	}
	if (!reader.Warning().empty())
	{
		LOG(WARNING) << format("warning while reading {}: {}", input.string(), reader.Warning().c_str());
	}

	if (reader.GetAttrib().vertices.size() % 3 != 0)
	{
		LOG(WARNING) << "invalid number of vertices: "
			<< reader.GetAttrib().vertices.size() << " - not divisable by 3";
	}

		//  attribs
	Model model;
	model.Vertices.reserve( reader.GetAttrib().vertices.size() / 3);
	for (const auto& v : reader.GetAttrib().vertices | vw::chunk(3))
	{
		model.Vertices.emplace_back( array<float, 3>{v[0], v[1], v[2]});
	}

	const size_t numFaces = rg::fold_left( reader.GetShapes()
		| vw::transform( λ(x.mesh.num_face_vertices.size())), 0u, plus{});
	model.Faces.reserve(numFaces);

	for (const auto& shape : reader.GetShapes())
	{
		auto mesh_it = shape.mesh.indices.cbegin();
		for ( const auto& num_faces : shape.mesh.num_face_vertices)
		{
			vector<size_t>& face = model.Faces.emplace_back();
			face.reserve(num_faces);
			transform( mesh_it, mesh_it + 3, back_inserter(face), λ(x.vertex_index));
			advance(mesh_it, 3);
		}
	}
	return model;
}

auto szgaa::model::formats::Obj::writeModel_impl( const Model& model, const path& file) -> void
{
	ofstream ofs(file);
		//  export vertices
	rg::for_each( model.Vertices, [&ofs](const auto& v)
		{
			ofs << format("v {} {} {}\n", v[0], v[1], v[2]);
		});
		//  export faces
	for (const auto& face : model.Faces)
	{
		ofs << "f";
		for (const auto& id : face)
		{
			ofs << " " << id + 1;
		}
		ofs << "\n";
	}
}

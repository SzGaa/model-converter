/*! @file stl.cppm
 *  @author Gabor Szijarto
 *  @warning
 *    NOT ALLOWED TO BE USED FOR AI TRAINING!!!
 */
module;
#include <g3log/g3log.hpp>
#include <filesystem>
#include <bit>
#include <array>
#include <fstream>
#include <ranges>
#include <type_traits>
#include <cmath>

export module szgaa.model.formats.stl;
import szgaa.model.format;
using std::filesystem::path;
using szgaa::model::Vec3;
namespace rg = std::ranges;
using namespace std;

export namespace szgaa::model::formats
{
	/*!
	 *  @details
	 *    Support of STL format: https://en.wikipedia.org/wiki/STL_(file_format)
	 *    via MeshFmt library
	 */
	class Stl : public szgaa::model::ModelFormat
	{
		public:
		// constructor & destructor
			Stl() : ModelFormat("Stl") { }

		private:
		//  ModelFormat's virtual interface
			auto writeModel_impl( const Model&, const path&) -> void override;
	};
}

namespace
{
		//! header to be added to all stl exported objects
	constexpr array<char, 80> g_header{
		"Created by MeshFmt "
		"------------------------------------------------------------"};

	/*!
	 *  @details
	 *    calculates the normal vector of the provided 3D vectors
	 *    cross product scaled by inverse of sqrt dot product
	 *  @todo
	 *    TODO_SZI - move from here..
	 */
	auto calc_normal(const Vec3& lhs, const Vec3& rhs) -> Vec3
	{
		Vec3 normal =
		{
			lhs[1] * rhs[2] - lhs[2] * rhs[1],
			lhs[2] * rhs[0] - lhs[0] * rhs[2],
			lhs[0] * rhs[1] - lhs[1] * rhs[0]
		};

		const float len = max( sqrt( normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]), 0.0001f);
		rg::transform( normal, normal.begin(), [len](auto& val){ return val / len; });
		return normal;
	}

	/*!
	 *  @details
	 *    Vector subtraction
	 *  @todo
	 *    TODO_SZI - move from here..
	 */
	auto operator-(const Vec3& lhs, const Vec3& rhs) -> Vec3
	{
		return { lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2] };
	}


		//! nice common way to handle safe non formatted writes.
	template <class T, class U = T>
	auto safe_write(ofstream& ofs, T&& var)
	{
		if constexpr(!is_same_v<T,U>)
		{
			const U temp = var;
			ofs.write( reinterpret_cast<const char*>(&temp), sizeof(U));
		}
		else
		{
			ofs.write( reinterpret_cast<const char*>(&var), sizeof(T));
		}
	}
}

/*!
 *  @details
 *    Based on original skeleton implementation
 */
auto szgaa::model::formats::Stl::writeModel_impl(const Model& model, const path& file) -> void
{
	static_assert(endian::native == endian::little,
		"Only little-endian architectures are supported");
	ofstream ofs(file);
	ofs.exceptions(ifstream::badbit);

	// UINT8[80]    – Header                 -     80 bytes
	safe_write( ofs, g_header);

	// UINT32       – Number of triangles    -      4 bytes
	safe_write<uint32_t>( ofs, model.Faces.size());

	// foreach triangle                      - 50 bytes:
	//     REAL32[3] – Normal vector             - 12 bytes
	//     REAL32[3] – Vertex 1                  - 12 bytes
	//     REAL32[3] – Vertex 2                  - 12 bytes
	//     REAL32[3] – Vertex 3                  - 12 bytes
	//     UINT16    – Attribute byte count      -  2 bytes
	// end
	for (const auto& face : model.Faces)
	{
		if (face.size() != 3u)
		{
			LOG(WARNING) << "non triangle face - " << face.size();
			continue;
		}
		const auto ref = model.Vertices[face[0]];
		const auto normal = calc_normal( model.Vertices[face[1]] - ref, model.Vertices[face[2]] - ref);
		safe_write( ofs, normal);
		for (const auto& id : face)
		{
			safe_write(ofs, model.Vertices[id]);
		}
		safe_write<uint16_t>(ofs, 0);
	}
}

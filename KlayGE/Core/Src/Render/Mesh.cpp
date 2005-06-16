// Mesh.cpp
// KlayGE Mesh类 实现文件
// Ver 2.7.0
// 版权所有(C) 龚敏敏, 2004-2005
// Homepage: http://klayge.sourceforge.net
//
// 2.7.0
// 改进了StaticMesh (2005.6.16)
//
// 2.1.2
// 初次建立 (2004.5.26)
//
// 修改记录
//////////////////////////////////////////////////////////////////////////////////

#include <KlayGE/KlayGE.hpp>
#include <KlayGE/Math.hpp>

#include <algorithm>
#include <boost/mem_fn.hpp>

#include <KlayGE/Mesh.hpp>

namespace KlayGE
{
	StaticMesh::StaticMesh()
		: vb_(new VertexBuffer(VertexBuffer::BT_TriangleList)),
			beBuilt_(false)
	{
	}

	StaticMesh::~StaticMesh()
	{
	}

	std::wstring const & StaticMesh::Name() const
	{
		static std::wstring name(L"Static Mesh");
		return name;
	}

	void StaticMesh::AddToSceneManager()
	{
		this->BuildRenderable();

		std::for_each(children_.begin(), children_.end(), boost::mem_fn(&StaticMesh::AddToSceneManager));
		Renderable::AddToSceneManager();
	}

	void StaticMesh::ComputeNormal()
	{
		normals_.resize(xyzs_.size());
		MathLib::ComputeNormal<float>(normals_.begin(),
			indices_.begin(), indices_.end(), xyzs_.begin(), xyzs_.end());

		std::for_each(children_.begin(), children_.end(), boost::mem_fn(&StaticMesh::BuildRenderable));
	}

	void StaticMesh::BuildRenderable()
	{
		if (!beBuilt_)
		{
			// 建立顶点坐标
			vb_->AddVertexStream(VST_Positions, sizeof(float), 3, true);
			vb_->GetVertexStream(VST_Positions)->Assign(&xyzs_[0], xyzs_.size());

			if (!normals_.empty())
			{
				// 建立法线坐标
				vb_->AddVertexStream(VST_Normals, sizeof(float), 3, true);
				vb_->GetVertexStream(VST_Normals)->Assign(&normals_[0], normals_.size());
			}

			// 建立纹理坐标
			for (size_t i = 0; i < multi_tex_coords_.size(); ++ i)
			{
				vb_->AddVertexStream(static_cast<VertexStreamType>(VST_TextureCoords0 + i), sizeof(float), 2, true);
				vb_->GetVertexStream(static_cast<VertexStreamType>(VST_TextureCoords0 + i))->Assign(&multi_tex_coords_[i][0],
					multi_tex_coords_[i].size());
			}

			// 建立索引
			vb_->AddIndexStream(true);
			vb_->GetIndexStream()->Assign(&indices_[0], indices_.size());

			beBuilt_ = true;

			std::for_each(children_.begin(), children_.end(), boost::mem_fn(&StaticMesh::BuildRenderable));
		}
	}


	BoneMesh::~BoneMesh()
	{
	}

	std::wstring const & BoneMesh::Name() const
	{
		static std::wstring name(L"Bone Mesh");
		return name;
	}
}

// OGLRenderLayout.hpp
// KlayGE OpenGL渲染分布类 头文件
// Ver 3.8.0
// 版权所有(C) 龚敏敏, 2006-2009
// Homepage: http://klayge.sourceforge.net
//
// 3.8.0
// 支持GL_ARB_vertex_array_object (2009.2.15)
//
// 3.2.0
// 初次建立 (2005.1.9)
//
// 修改记录
/////////////////////////////////////////////////////////////////////////////////

#ifndef _OGLRENDERLAYOUT_HPP
#define _OGLRENDERLAYOUT_HPP

#pragma once

#include <KlayGE/RenderLayout.hpp>

namespace KlayGE
{
	class OGLRenderLayout : public RenderLayout
	{
	public:
		OGLRenderLayout();
		~OGLRenderLayout();

		void Active(ShaderObjectPtr const & so) const;
		void Deactive() const;

	private:
		mutable bool dirty_vao_;
		GLuint vao_;

		bool use_vao_, use_nv_pri_restart_;
	};
}

#endif			// _OGLRENDERLAYOUT_HPP

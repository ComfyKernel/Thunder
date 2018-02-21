#ifndef H_RENDER_MESH_HPP
#define H_RENDER_MESH_HPP

#include "../units/special.hpp"
#include "../gl/buffer.hpp"

#include <vector>

namespace rn {
  class mesh {
  protected:

  public:
    struct {
      float3d position;
      float3d rotation;
      float3d scale;
    } transform;

    struct {
      gl::buffer vertex;
      gl::buffer index;
      gl::buffer uv;
      unsigned int count;
    } buffers;

    mesh();
    
    mesh(void* vertices, size_t,
	 void* indices , size_t,
	 void* uvs     , size_t);
    
    mesh(const float3d& position,
	 const float3d& rotation,
	 const float3d& scale   ,
	 void* vertices, size_t,
	 void* indices , size_t,
	 void* uvs     , size_t);

    mesh(const float3d& position,
	 const float3d& rotation,
	 const float3d& scale   );

    void setBuffers(void* vertices, size_t,
		    void* indices , size_t,
		    void* uvs     , size_t);

    void setTransform(const float3d& position,
		      const float3d& rotation,
		      const float3d& scale   );

    void bind();

    void draw();

    ~mesh();
  };
};

#endif
